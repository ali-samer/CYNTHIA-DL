#pragma once


#include <stdlib.h>


CYDL_BEGIN_LIB_NAMESPACE
CYDL_BEGIN_LIB_POLICIES_NAMESPACE
template < class T >
struct OpNewCreator
{
	static T* Create ( CYDL_SIZET elementsCount = 1 ) { return new T[elementsCount]; }
protected:
	~OpNewCreator ( ) { }
};

template < class T >
struct MallocCreator
{
	static T* Create ( CYDL_SIZET elementsCount = 1 )
	{
		void* buf = malloc( sizeof( T ) * elementsCount );
		if ( !buf )
			return 0;
		return new( buf ) T;
	}

	static auto Delete( CYDL_SIZET elementsCount)
	{
		return [elementsCount](T* ptr)
		{
		  for ( CYDL_SIZET i = 0; i < elementsCount; ++i)
		  {
			  ptr[i].~T();
		  }
		  std::free(ptr);
		};
	}
protected:
	~MallocCreator ( ) { }
};
CYDL_END_LIB_POLICIES_NAMESPACE
CYDL_END_LIB_NAMESPACE