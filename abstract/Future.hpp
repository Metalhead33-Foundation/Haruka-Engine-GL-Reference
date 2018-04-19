#ifndef FUTURE_HPP
#define FUTURE_HPP
#include <shared_mutex>
#include "Global.hpp"

template < class Type > class Future;

class StorageBase {
  protected:
	// Storage lock
	volatile bool m_initialized;
	bool m_reading = 0;
	std::shared_timed_mutex m_access;
	std::condition_variable_any m_initialize;
	uint64_t m_count = 0;

  public:
	StorageBase( ) : m_initialized( false ) {}

  public:
	// Locking functions
	void readLock( ) { m_access.lock_shared(); m_reading = true; }
	void writeLock( ) { m_access.lock( ); m_reading = false; }
	void unlock( ) {
		if(m_reading) {
			m_access.unlock_shared();
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
			m_initialize.notify_all();
		}
	}

	bool isInitialized( ) { return m_initialized; }
};

// Storage with locking
template < class Type > class Storage : public StorageBase {
	friend class Future< Type >;

	// Actual data
	Type *m_data;

  public:
	Storage( ) : StorageBase( ), m_data( 0 ) {}
	~Storage( ) {
		if(m_data) {
			delete m_data;
		}
	}

	// Create a storage with data, initialized
	Storage( const Type &data )
	: StorageBase( ), m_data( new Type( data ) ) {}

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

	Type *operator->( ) {
	if ( !m_data )
		m_data = new Type( );
	return m_data;
	}
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
	operator Type( ) {
	m_ptr->readLock( );
	m_ptr->waitInitialized( );
	Type data = ( *m_ptr.data( ) );
	m_ptr->unlock( );
	return data;
	}
};



#endif // FUTURE_HPP
