#pragma once


#include <limits>

#include <memory>
#include <stdexcept>
#include <cstdio>
#include <string>
#include <iostream>

CYDL_BEGIN_LIB_NAMESPACE

enum Size : CYDL_INT8 { dynamic = -1 };
enum BufferSize : CYDL_INT64
{
	Tiny = 256,          // 256 bytes, for very small data reads
	Small = 1024,        // 1 KB, for small data reads
	Medium = 8192,       // 8 KB, a common medium size for file I/O
	Large = 32768,       // 32 KB, for larger file I/O operations
	VeryLarge = 131072,  // 128 KB, for significant chunks of data
	Huge = 1048576       // 1 MB, for very large data transfers like video, large files, etc.
};
// New enum with classifiable names
enum class OperationBufferSize : CYDL_INT64
{
	TextProcessing = BufferSize::Small,      // Small buffers for text processing
	FileRead = BufferSize::Medium,           // Medium buffers for file reads
	NetworkTransfer = BufferSize::Large,     // Large buffers for network transfers
	DataStreaming = BufferSize::VeryLarge,   // Very large buffers for data streaming
	BulkDataProcessing = BufferSize::Huge    // Huge buffers for bulk data processing
};



CYDL_BEGIN_LIB_UTILS_NAMESPACE
/// \FUNCTION_PROTOTYPES
std::string exec ( const char* cmd , std::size_t bufferSize = CYDL_BUFFER_SIZE );
std::string exec ( const char* cmd , BufferSize bufferSize );
std::string exec ( const char* cmd , OperationBufferSize bufferSize );
template < typename T1, typename T2 >
int norm_buff_size( T1 t1, T2 t2 = -1 )
{
	return t1 == cydl::dynamic ? t2 : t1;
}

struct NullParam; // Null Parameter Placeholder
typedef NullParam NullParameter;
CYDL_END_LIB_UTILS_NAMESPACE


CYDL_BEGIN_LIB_DETAILS_NAMESPACE
std::string exec_ ( const char* cmd , BufferSize bufferSize );
CYDL_END_LIB_DETAILS_NAMESPACE

CYDL_BEGIN_LIB_DETAILS_NAMESPACE
std::string exec_ ( const char* cmd , BufferSize bufferSize )
{
		return  "";
}
CYDL_END_LIB_DETAILS_NAMESPACE

CYDL_END_LIB_NAMESPACE




