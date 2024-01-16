
#pragma once

#include "Core/Tags/Types.h"

CYDL_BEGIN_LIB_NAMESPACE
CYDL_BEGIN_LIB_DETAILS_NAMESPACE

template < typename Data, typename DataCategory >
class CYDL_DEFAULT_AFLAG ArrayImpl;

template < typename Data >
class CYDL_DEFAULT_AFLAG ArrayImpl<Data, CategoryTags::Matrix >
{
	// TODO: Implement the ArrayImpl < Data, Matrix > class
};

template < typename Data >
class CYDL_DEFAULT_AFLAG ArrayImpl<Data, CategoryTags::Scalar >
{
	// TODO: Implement the ArrayImpl < Data, Scalar > class
};

CYDL_END_LIB_DETAILS_NAMESPACE

template < typename T >
class CYDL_DEFAULT_AFLAG Array : public CYDL_VDETAILS::ArrayImpl< T, DataCategory_t< T > >
{
public:
	using ElementType = typename T::ElementType;
	using TypeCategory = DataCategory_t<T>;
	using DeviceType = typename T::DeviceType;
	using CYDL_VDETAILS::ArrayImpl< T, TypeCategory >::ArrayImpl;
};
template < typename T >
CYDL_CONSTEXPR bool IsBatchVector< Array< T > > = IsVector< T >;

template < typename T >
CYDL_CONSTEXPR bool IsBatchMatrix< Array< T > > = IsMatrix< T >;

template < typename T >
CYDL_CONSTEXPR bool IsBatchScalar< Array< T > > = IsScalar< T >;

CYDL_END_LIB_NAMESPACE