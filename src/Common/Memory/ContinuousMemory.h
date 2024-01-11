#pragma once


#include <memory>
#include <unistd.h>


CYDL_BEGIN_LIB_NAMESPACE

CYDL_BEGIN_LIB_DETAILS_NAMESPACE

template < typename Elem , typename Device >
class CYDL_DEFAULT_AFLAG ContinuousMemory CYDL_FINAL
{
private:
	static_assert( std::is_same< CYDL_VUTILS::RemoveConstRef_t< Elem > , Elem >::value );

	using Element_t = Elem;

	std::shared_ptr< Element_t > m_memory;
	Element_t* m_memoryStart;

public:
	CYDL_STRONG_EXPLICIT ContinuousMemory ( CYDL_SIZET sizeParam ) // TODO: change CYDL_VPOLICIES::MallocCreator to an interface between different devices and allocations strategies
		: m_memory( Allocator< Device , CYDL_VPOLICIES::MallocCreator >::template Allocate< Element_t >(
		sizeParam ) ) ,
		  m_memoryStart( m_memory.get( ) ) { }

	ContinuousMemory ( std::shared_ptr< Element_t > memoryParam , Element_t* memoryStartParam )
		: m_memory( std::move( memoryParam ) ) ,
		  m_memoryStart( memoryStartParam ) { }

	CYDL_FORCE_INLINE auto rawMemory ( ) CYDL_NOEXCEPT { return m_memoryStart; }

	CYDL_FORCE_INLINE const std::shared_ptr< Element_t > sharedPtr ( ) { return m_memory; }

	CYDL_FORCE_INLINE bool operator== (
		const ContinuousMemory & val ) { return ( m_memory == val.m_memory ) && ( m_memoryStart == val.m_memoryStart ); }

	CYDL_FORCE_INLINE bool operator!= ( const ContinuousMemory & val )
	{
		return !( operator==( val ) );
	}

	CYDL_FORCE_INLINE CYDL_SIZET useCount ( ) { return m_memory.use_count( ); }

};

CYDL_END_LIB_DETAILS_NAMESPACE

CYDL_END_LIB_NAMESPACE