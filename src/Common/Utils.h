#pragma once

#include <limits>

namespace cydl::details
{
	struct NullParam; // Null Parameter Placeholder

	typedef NullParam NullParameter;

	template < typename T >
	using TypeMax = std::numeric_limits<T>::max();
}
