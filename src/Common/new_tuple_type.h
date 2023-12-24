#pragma once

#include "include_utils.h"
#include "utils.h"

namespace cydl::details
{
	template <
		typename Target ,
		size_t LocTarget , size_t NumOfScannedTs ,
		typename ProcessedTs ,
		typename... RemainingTs
	>
	struct NewTuple_;

	template <
		typename Target ,
		size_t LocTarget , size_t NumOfScannedTs ,
		template < typename... > class TypeContainer ,
		typename... ModifiedTypes , typename CurrentT ,
		typename... RemainingTs
	>
	struct NewTuple_<
		Target , LocTarget , NumOfScannedTs ,
		TypeContainer< ModifiedTypes... > , CurrentT ,
		RemainingTs...
	> final
	{
		using type = typename NewTuple_<
			Target , LocTarget , NumOfScannedTs + 1 ,
			TypeContainer< ModifiedTypes... , CurrentT > , RemainingTs...
		>::type;
	};

	template <
		typename Target , size_t LocTarget ,
		template < typename... > class TypeContainer ,
		typename... ModifiedTypes , typename CurrentT ,
		typename... RemainingTs
	>
	struct NewTuple_<
		Target, LocTarget, LocTarget, TypeContainer<ModifiedTypes...>,
		CurrentT, RemainingTs...
	> final
	{
		using type = TypeContainer<ModifiedTypes..., Target, RemainingTs...>;
	};
}

namespace cydl
{
	template <
	    typename Target, size_t KeyPos,
		typename TypeContainer,
		typename... RemainingTs
    >
	using Tuple_t = typename details::NewTuple_<
	        Target, KeyPos, 0, TypeContainer, RemainingTs...
	    >::type;

	template <
		typename Target, size_t KeyPos,
		typename TypeContainer,
		typename... RemainingTs
	>
	using Tuple = details::NewTuple_<
		Target, KeyPos, 0, TypeContainer, RemainingTs...
	>;
}


