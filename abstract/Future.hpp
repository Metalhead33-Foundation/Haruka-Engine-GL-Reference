#ifndef FUTURE_HPP
#define FUTURE_HPP
#include <shared_mutex>
#include "Global.hpp"

template < class Type > class ReadReference;
template < class Type > class Reference;
template < class Type > class Future;

class StorageBase {
  protected:
	// Storage lock
	volatile bool m_initialized;
	bool m_reading = 0;
	std::shared_timed_mutex m_access;
	std::condition_variable_any m_initialize;

  public:
	StorageBase( ) : m_initialized( false ) {}

  public:
	// Locking functions
	void readLock( ) {
		m_access.lock_shared( );
		m_reading = true;
	}
	void writeLock( ) {
		m_access.lock( );
		m_reading = false;
	}
	void unlock( ) {
		if ( m_reading ) {
			m_access.unlock_shared( );
		} else {
			m_access.unlock( );
		}
	}

	// Wait function, call after locking
	void waitInitialized( ) {
		while ( !m_initialized ) {
			m_initialize.wait( m_access );
		}
	}

	// Initialized notify function
	void initialized( ) {
		if ( !m_initialized ) {
			m_initialized = true;
			m_initialize.notify_all( );
		}
	}

	bool isInitialized( ) { return m_initialized; }
};

// Storage with locking
template < class Type > class Storage : public StorageBase {
	friend class ReadReference< Type >;
	friend class Reference< Type >;
	friend class Future< Type >;

	// Actual data
	Type *m_data;

  public:
	Storage( ) : StorageBase( ), m_data( 0 ) {}

	// Create a storage with data, initialized
	Storage( const Type &data )
		: StorageBase( ), m_data( new Type( data ) ) {}

	~Storage( ) {
		if ( m_data ) {
			delete m_data;
		}
	}

  public:
	void beginSet( ) { writeLock( ); }
	void endSet( ) {
		initialized( );
		unlock( );
	}

	void set( const Type &data ) {
		if ( !m_data )
			m_data = new Type( );
		( *m_data ) = ( data );
	}

	void unset( ) {
		beginSet( );
		if ( !m_data ) {
			m_data = new Type( );
		} else {
			( *m_data ) = Type( );
		}
		endSet( );
	}

  public:
	operator Type &( ) {
		if ( !m_data )
			m_data = new Type( );
		return *m_data;
	}

	void invalidate() {
		std::unique_lock<std::shared_timed_mutex> lock(m_access);
		m_initialized = false;
	}

	Type *operator->( ) {
		if ( !m_data )
			m_data = new Type( );
		return m_data;
	}
};

template < class Type > class ReadReference;

// Opaque reference for tracking without being locked
template < class Type > class Reference {
	friend class ReadReference< Type >;

  protected:
	// Actual data
	std::shared_ptr< Storage< Type > > m_ptr;

  public:
	// Create an empty Reference
	Reference( ) {}
	// Create an Reference to already existing data
	Reference( std::shared_ptr< Storage< Type > > ptr ) { m_ptr = ptr; }

	// Clear the reference
	void clear( ) { m_ptr.reset( ); }

	// Get a copy of the data
	operator Type( ) const {
		if ( m_ptr ) {
			m_ptr->readLock( );
			m_ptr->waitInitialized( );
			Type data = *m_ptr->m_data;
			m_ptr->unlock( );
			return data;
		} else {
			return Type( );
		}
	}

	//            const Type *operator->( ) const { return
	//            m_ptr->m_data; }

	operator bool( ) const {
		return ( m_ptr && m_ptr->isInitialized( ) );
	}

	bool operator==( const Reference< Type > &other ) const {
		return m_ptr == other.m_ptr;
	}
};

template < class Type > class ReadReference {
	std::shared_ptr< Storage< Type > > m_ptr;

  public:
	ReadReference( ) {}
	ReadReference( const Reference< Type > &ref ) {
		m_ptr = ref.m_ptr;

		if ( m_ptr ) {
			m_ptr->readLock( );
			m_ptr->waitInitialized( );
		}
	}

	ReadReference( ReadReference< Type > &other ) {
		if ( m_ptr != other.m_ptr && m_ptr ) {
			// Release the current lock
			m_ptr->unlock( );
		}
		m_ptr = other.m_ptr;
		other.m_ptr.clear( );
	}

	~ReadReference( ) {
		if ( m_ptr ) {
			m_ptr->unlock( );
		}
	}

	// Clear the reference
	void clear( ) {
		if ( m_ptr ) {
			// Unlock it first before releasing it
			m_ptr->unlock( );
		}
		m_ptr.reset( );
	}

	// Get a copy of the data
	operator Type( ) const {
		if ( m_ptr ) {
			return *m_ptr->m_data;
		} else {
			return Type( );
		}
	}

	operator bool( ) const { return m_ptr && m_ptr->isInitialized( ); }

	const Type *operator->( ) const { return m_ptr->m_data; }

	operator Reference< Type >( ) { return m_ptr; }
};

// Future data
template < class Type > class Future {
	// Instance going to get value
	std::shared_ptr< Storage< Type > > m_ptr;

  public:
	// Create a new empty future, initialize the storage and lock it for
	// writing
	Future( ) : m_ptr( new Storage< Type >( ) ) {}

	// Copy over the reference
	Future( const Future< Type > &other ) : m_ptr( other.m_ptr ) {}

	// Store the data, it is now initialized
	void store( const Type &data ) const {
		m_ptr->writeLock( );
		m_ptr->set( data );
		m_ptr->initialized( );
		m_ptr->unlock( );
	}

	// Read access, only accessible after initialized
	operator Type( ) const {
		m_ptr->readLock( );
		m_ptr->waitInitialized( );
		Type data = ( *m_ptr.get( ) );
		m_ptr->unlock( );
		return data;
	}
};

template < class IdType > inline bool isValidId( IdType id ) {
	return id.isValid( );
}

inline bool isValidId( const std::string& id ) { return !id.empty(); }

inline bool isValidId( size_t id ) { return id >= 0; }


#endif // FUTURE_HPP
