#pragma once


CYDL_BEGIN_LIB_NAMESPACE

struct CYDL_DEFAULT_AFLAG CategoryTags CYDL_FINAL
{
	struct Scalar;
	struct Vector;
	struct Matrix;

	struct BatchScalar; // list of scalars
	struct BatchVector; // list of vectors
	struct BatchMatrix; // list of matrices
};

/// \Scalars
template < typename T >
CYDL_CONSTEXPR bool IsScalar = false;

template < >
CYDL_CONSTEXPR bool IsScalar< CategoryTags::Scalar > = true;

template < typename T >
CYDL_CONSTEXPR bool IsScalar< const T > = IsScalar< T >;

template < typename T >
CYDL_CONSTEXPR bool IsScalar< T & > = IsScalar< T >;

template < typename T >
CYDL_CONSTEXPR bool IsScalar< const T & > = IsScalar< T >;

template < typename T >
CYDL_CONSTEXPR bool IsScalar< T && > = IsScalar< T >;

template < typename T >
CYDL_CONSTEXPR bool IsScalar< const T && > = IsScalar< T >;

/// \Scalar: Batch Checking
template < typename T >
CYDL_CONSTEXPR bool IsBatchScalar = false;

template < >
CYDL_CONSTEXPR bool IsBatchScalar< CategoryTags::BatchScalar > = true;

template < typename T >
CYDL_CONSTEXPR bool IsBatchScalar< const T > = IsBatchScalar< T >;

template < typename T >
CYDL_CONSTEXPR bool IsBatchScalar< T & > = IsBatchScalar< T >;

template < typename T >
CYDL_CONSTEXPR bool IsBatchScalar< const T & > = IsBatchScalar< T >;

template < typename T >
CYDL_CONSTEXPR bool IsBatchScalar< T && > = IsBatchScalar< T >;

template < typename T >
CYDL_CONSTEXPR bool IsBatchScalar< const T && > = IsBatchScalar< T >;

/// \Vector
template < typename T >
CYDL_CONSTEXPR bool IsVector = false;

template < >
CYDL_CONSTEXPR bool IsVector< CategoryTags::Vector > = true;

template < typename T >
CYDL_CONSTEXPR bool IsVector< const T > = IsVector< T >;

template < typename T >
CYDL_CONSTEXPR bool IsVector< T & > = IsVector< T >;

template < typename T >
CYDL_CONSTEXPR bool IsVector< const T & > = IsVector< T >;

template < typename T >
CYDL_CONSTEXPR bool IsVector< T && > = IsVector< T >;

template < typename T >
CYDL_CONSTEXPR bool IsVector< const T && > = IsVector< T >;

/// \Vector: Batch Checking
template <typename T>
CYDL_CONSTEXPR bool IsBatchVector = false;

template <>
CYDL_CONSTEXPR bool IsBatchVector<CategoryTags::BatchVector> = true;

template <typename T>
CYDL_CONSTEXPR bool IsBatchVector<const T> = IsBatchVector<T>;

template <typename T>
CYDL_CONSTEXPR bool IsBatchVector<T &> = IsBatchVector<T>;

template <typename T>
CYDL_CONSTEXPR bool IsBatchVector<const T &> = IsBatchVector<T>;

template <typename T>
CYDL_CONSTEXPR bool IsBatchVector<T &&> = IsBatchVector<T>;

template <typename T>
CYDL_CONSTEXPR bool IsBatchVector<const T &&> = IsBatchVector<T>;

/// \Matrix
template < typename T >
CYDL_CONSTEXPR bool IsMatrix = false;

template < >
CYDL_CONSTEXPR bool IsMatrix< CategoryTags::Matrix > = true;

template < typename T >
CYDL_CONSTEXPR bool IsMatrix< const T > = IsMatrix< T >;

template < typename T >
CYDL_CONSTEXPR bool IsMatrix< T & > = IsMatrix< T >;

template < typename T >
CYDL_CONSTEXPR bool IsMatrix< const T & > = IsMatrix< T >;

template < typename T >
CYDL_CONSTEXPR bool IsMatrix< T && > = IsMatrix< T >;

template < typename T >
CYDL_CONSTEXPR bool IsMatrix< const T && > = IsMatrix< T >;

/// \Matrix: Batch Checking
template < typename T >
CYDL_CONSTEXPR bool IsBatchMatrix = false;

template < >
CYDL_CONSTEXPR bool IsBatchMatrix< CategoryTags::BatchMatrix > = true;

template < typename T >
CYDL_CONSTEXPR bool IsBatchMatrix< const T > = IsBatchMatrix< T >;

template < typename T >
CYDL_CONSTEXPR bool IsBatchMatrix< T & > = IsBatchMatrix< T >;

template < typename T >
CYDL_CONSTEXPR bool IsBatchMatrix< const T & > = IsBatchMatrix< T >;

template < typename T >
CYDL_CONSTEXPR bool IsBatchMatrix< T && > = IsBatchMatrix< T >;

template < typename T >
CYDL_CONSTEXPR bool IsBatchMatrix< const T && > = IsBatchMatrix< T >;

CYDL_BEGIN_LIB_DETAILS_NAMESPACE

/// \Mapping: Data Category To Types
template < typename T >
struct CYDL_DEFAULT_AFLAG DataCategory_ CYDL_FINAL
{
private:
	template <
		bool isScalar , bool isVector , bool isMatrix , bool isBatchScalar ,
		bool isBatchVector, bool isBatchMatrix , typename Dummy = void
	>
	struct helper;

	template < typename Dummy >
	struct helper< true , false , false , false, false, false , Dummy >
	{
		using type = typename CategoryTags::Scalar;
	};

	template < typename Dummy >
	struct helper< false , true , false , false, false, false , Dummy >
	{
		using type = typename CategoryTags::Vector;
	};

	template < typename Dummy >
	struct helper< false , false , true , false, false, false , Dummy >
	{
		using type = typename CategoryTags::Matrix;
	};

	template < class Dummy >
	struct helper< false , false , false , true, false, false , Dummy >
	{
		using type = typename CategoryTags::BatchScalar;
	};

	template < class Dummy >
	struct helper< false , false , false , false, true, false , Dummy >
	{
		using type = typename CategoryTags::BatchVector;
	};

	template < class Dummy >
	struct helper< false , false , false , false, false, true , Dummy >
	{
		using type = typename CategoryTags::BatchMatrix;
	};

public:
	using type = typename helper< IsScalar< T > , IsVector< T >, IsMatrix< T > , IsBatchScalar< T > ,
	                              IsBatchVector< T>, IsBatchMatrix< T >>::type;
};

CYDL_END_LIB_DETAILS_NAMESPACE

template < typename T >
using DataCategory_t = typename CYDL_VDETAILS::DataCategory_< T >::type;
CYDL_END_LIB_NAMESPACE