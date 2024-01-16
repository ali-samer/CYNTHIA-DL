#pragma once

#include "Core/Utils/IncludeUtils.h"
#include "Core/Utils/Utils.h"

CYDL_BEGIN_LIB_NAMESPACE
CYDL_BEGIN_LIB_DETAILS_NAMESPACE

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
> CYDL_FINAL
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
> CYDL_FINAL
{
	using type = TypeContainer<ModifiedTypes..., Target, RemainingTs...>;
};

CYDL_END_LIB_DETAILS_NAMESPACE

template <
    typename Target, size_t KeyPos,
	typename TypeContainer,
	typename... RemainingTs
>
using Tuple_t = typename CYDL_VDETAILS::NewTuple_<
        Target, KeyPos, 0, TypeContainer, RemainingTs...
    >::type;

template <
	typename Target, size_t KeyPos,
	typename TypeContainer,
	typename... RemainingTs
>
 using Tuple = CYDL_VDETAILS::NewTuple_<
	Target, KeyPos, 0, TypeContainer, RemainingTs...
>;

CYDL_END_LIB_NAMESPACE