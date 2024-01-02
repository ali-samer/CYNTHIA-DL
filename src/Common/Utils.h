#pragma once

#include <limits>

CYDL_BEGIN_LIB_NAMESPACE
	CYDL_BEGIN_LIB_DETAILS_NAMESPACE
	struct NullParam; // Null Parameter Placeholder

	typedef NullParam NullParameter;

	template < typename T >
	using TypeMax = typename std::numeric_limits<T>::max();
	CYDL_END_LIB_DETAILS_NAMESPACE
CYDL_END_LIB_NAMESPACE
