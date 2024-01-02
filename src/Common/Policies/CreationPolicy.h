#pragma once


#include <stdlib.h>


namespace cydl::policies
{
	template < class T >
	struct OpNewCreator
	{
		static T* Create ( ) { return new T; }
	protected:
		~OpNewCreator ( ) { }
	};

	template < class T >
	struct MallocCreator
	{
		static T* Create ( )
		{
			void* buf = malloc( sizeof( T ) );
			if ( !buf )
				return 0;
			return new( buf ) T;
		}
	protected:
			~MallocCreator() { }
	};
}