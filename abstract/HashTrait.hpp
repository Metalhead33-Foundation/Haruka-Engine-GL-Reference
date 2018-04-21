#ifndef HASHTRAIT_HPP
#define HASHTRAIT_HPP
#include <unordered_map>
#include "Future.hpp"
#include <cassert>

template < class Type, class IdType > class MapTrait {
public:
	typedef Storage< Type > SType;
	typedef std::shared_ptr< SType > RType;
	typedef std::unordered_map< IdType, RType > HashTrait;
	typedef typename HashTrait::iterator HashIterator;
	// typedef typename HashTrait::_Args _Args;
private:
	HashTrait m_cache;
	std::shared_timed_mutex m_lock;

  public:

	// Get an cache reference without initialize information. Always
	// returns a
	// valid pointer.
		template <typename... Args>
	RType getEntry( const IdType& id, Args&&... args ) {
		// Check the ID for validity
		assert( isValidId( id ) );

		// If it's not, return an empty pointer
		if ( !isValidId( id ) ) // Should not happen
			return RType( );

		RType ptr;
		{
			std::shared_lock< std::shared_timed_mutex > read( m_lock );
			auto it = m_cache.find( id );
			if ( it != m_cache.end( ) ) {
				ptr = it->second;
				return ptr;
			}
		}

		ptr = RType( new SType( Type( id, args ... ) ) );
		{
			std::unique_lock< std::shared_timed_mutex > write( m_lock );
			m_cache.emplace(id, ptr);
			return ptr;
		}
	}
	HashIterator find(const IdType& id)
	{
		m_lock.lock();
		return m_cache.find(id);
	}
	HashIterator begin() {
		m_lock.lock();
		return m_cache.begin();
	}
	HashIterator end() {
		return m_cache.end();
	}
	void finish() {
		m_lock.unlock();
	}
	HashIterator erase(HashIterator it)
	{
		return m_cache.erase(it);
	}

	void removeEntry( const IdType& id ) {
		if(!isValidId(id))
			return;

		auto it = find(id);
		std::unique_lock< std::shared_timed_mutex > remover( m_lock );
		if(it != m_cache.end())
			m_cache.erase(it);
	}
};

#endif // HASHTRAIT_HPP
