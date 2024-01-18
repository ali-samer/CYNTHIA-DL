#include "Utils.h"

#include "Macros.h"

CYDL_BEGIN_LIB_NAMESPACE

CYDL_BEGIN_LIB_UTILS_NAMESPACE


template < typename T >
using TypeMax = typename std::numeric_limits< T >::max ( );

std::string exec ( const char* cmd , CYDL_INT64 bufferSize )
{
	std::cout << "Size_t buffersize = " << bufferSize << std::endl;
	bufferSize =  norm_buff_size( bufferSize , 12 ); // TODO

	std::unique_ptr< char[] >                     buffer( new char[bufferSize] );
	std::string                                   result { };
	std::unique_ptr< FILE , decltype( &pclose ) > pipe( popen( cmd , "r" ) , pclose );
	if ( !pipe )
	{
		throw std::runtime_error( "popen() failed!" );
	}
	result += '\n';
	while ( fgets( buffer.get( ) , bufferSize , pipe.get( ) ) != nullptr )
	{
		result += buffer.get( );
	}
	return result;
}
std::string exec ( const char* cmd , BufferSize bufferSize )
{
	if( bufferSize == dynamic )
	{
		return exec(cmd, OperationBufferSize::FileRead);
	}
}
std::string exec ( const char* cmd , OperationBufferSize bufferSize )
{
	return exec(cmd, CYDL_SIZET(bufferSize));
}


CYDL_END_LIB_UTILS_NAMESPACE

CYDL_END_LIB_NAMESPACE