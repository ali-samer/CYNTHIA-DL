#pragma once

/**
 * @HeteroDict: A Compile-Time Evaluated Heterogeneous Dictionary
 *
 * @Overview:
 * The Map class template is part of an exploration into advanced C++ template metaprogramming,
 * drawing inspiration from the book "C++ Template Metaprogramming in Practice; A Deep Learning Framework."
 * This implementation, co-developed by Samer Ali, adds a unique twist to the concepts presented in the book,
 * adapting and extending them to fit the specific needs of Cynthia's framework.
 *
 * @Acknowledgment:
 * The design and conceptualization of this framework owe much to the ideas and examples presented by
 * Wei Li, the author of "C++ Template Metaprogramming in Practice; A Deep Learning Framework." Samer Ali has
 * significantly contributed to the evolution of this framework, enhancing its functionality and adapting it
 * for broader applications. This collaborative effort has been instrumental in advancing the utility and scope
 * of the original implementation.
 *
 * @Example Usage:
 * auto map = Map::Create().Set<A>(1.2f).Set<B>(false);
 *
 * @Features:
 * - Compile-time key-value pair evaluation and storage.
 * - Flexible API for setting and retrieving values with type safety.
 * - Efficient storage mechanism using tuples and shared pointers.
 */


#include <stdlib.h>


#include "Common/Utils/IncludeUtils.h"
#include "Common/Utils/Utils.h"
#include "Tuple.h"

/**
 * The choice of conveying the namespace as "details" is an attempt to follow common C++ conventions
 * by having the "details" namespace contain inner implementation code that end users generally don't
 * need to interact with or know about. This keeps the external-facing interface cleaner and modular.
 *
 * The following is lower-level machinery supporting the dictionary API...
 **/


CYDL_BEGIN_LIB_NAMESPACE

CYDL_BEGIN_LIB_DETAILS_NAMESPACE
// InitContainer: Initializes a type container with a specified number of types.
// If the number of provided types is less than NumOfTypeParams, it pads the container with NullParam.

// Recursive case: Pad the container until the number of types reaches NumOfTypeParams.
template <
	size_t NumOfTypeParams ,
	template < typename... > class TypeContainer , typename... Pack
>
struct InitContainer
{
	static_assert( NumOfTypeParams , "You must specify <typename... keys> to set "
	                                 "key-valued pairs to their corresponding identifiers." );
	using type = typename InitContainer< NumOfTypeParams - 1 , TypeContainer , NullParam , Pack... >::type;
};

// Base case: When NumOfTypeParams reaches 0, stop padding and define the container type.
template < template < typename... > class TypeContainer , typename... Pack >
struct InitContainer< 0 , TypeContainer , Pack... >
{
	using type = TypeContainer< Pack... >;
};

// Contains: Checks if a type T is present in a list of types Types...
template < typename T , typename... Types >
struct Contains_;

// Base case: Type T is not found in the list.
template < typename T >
struct Contains_< T > : std::false_type
{
};

// Match found case: Type T matches the first type in the list.
template < typename T , typename... Types >
struct Contains_< T , T , Types... > : std::true_type
{
};

// Recursive case: Type T does not match the first type in the list, continue searching.
template < typename T , typename MissMatch , typename... Types >
struct Contains_< T , MissMatch , Types... > : Contains_< T , Types... >
{
};

template < typename Target , typename... RemainingTs >
using Contains = Contains_< Target , RemainingTs... >;

// IndexOf: Returns index of a type if a type Target is present in a list of types RemainingTs...
template < typename Target , typename... RemainingTs >
struct IndexOf_;

// Base case: Target not found
template < typename Target >
struct IndexOf_< Target >
{
	static CYDL_CONSTEXPR size_t value = std::numeric_limits< size_t >::max( );
};

// Recursive case: Target not matched, continue searching
template < typename Target , typename MissMatch , typename... RemainingTs >
struct IndexOf_< Target , MissMatch , RemainingTs... >
{
	static CYDL_CONSTEXPR size_t value = 1 + IndexOf_< Target , RemainingTs... >::value;
};

// Match found case: Target matched, return current index
template < typename Target , typename... RemainingTs >
struct IndexOf_< Target , Target , RemainingTs... >
{
	static CYDL_CONSTEXPR size_t value = 0;
};

// Alias template for user convenience
template < typename Target , typename... RemainingTs >
using IndexOf = IndexOf_< Target , RemainingTs... >;

template < size_t Index , typename... Ts >
struct GetElementByIndex;

template < typename T , typename... Ts >
struct GetElementByIndex< 0 , T , Ts... >
{
	using type = T;
};

template < size_t Index , typename... Ts >
struct GetElementByIndex
{
	static_assert( Index >= 0 && "Illegal use of template function. Index must be >= 0" );
	using type = typename GetElementByIndex< Index - 1 , Ts... >::type;
};
CYDL_END_LIB_DETAILS_NAMESPACE


// to ensure flexibility the use of variadic templates is essential to both
// template classes to set key-valued pairs
template < typename... Keys > // keys will be saved in Keys
class CYDL_DEFAULT_AFLAG Map CYDL_FINAL
{
	template < typename... Vals > // Valued pairs will be saved in Vals in parallel with Keys
	struct Value
	{
	public:
		using TupleType = typename details::InitContainer< sizeof...( Vals ) , std::tuple >::Type;

		Value ( ) = default;

		CYDL_STRONG_EXPLICIT Value ( std::shared_ptr< void >(&& input)[sizeof... ( Vals )] )
		{
			for ( size_t i = 0 ; i < sizeof... ( Vals ) ; i++ )
				m_tuple[ i ] = std::move( input[ i ] );
		}

		template < typename Key , typename Val >
		CYDL_CONSTEXPR auto Set ( Val && val ) &&
		{
			using namespace details;
			CYDL_CONSTEXPR size_t TagPos = IndexOf< Key , Keys... >::value;

			using rawVal = std::decay_t< Val >;
			rawVal* tmp = new rawVal( std::forward< Val >( val ) ); // NOLINT(*-use-auto)

			m_tuple[ TagPos ] = std::shared_ptr< void >( tmp ,
			                                             [ ] ( void* ptr )
			                                             {
			                                               rawVal* nptr = static_cast<rawVal*>(ptr);
			                                               delete nptr;
			                                             } );

			using new_type = Tuple_t< rawVal , TagPos , Value< > , Vals... >;
			return new_type( std::move( m_tuple ) );
		}

		template < typename Key >
		CYDL_CONSTEXPR CYDL_STRONG_INLINE auto & Get ( ) const
		{
			CYDL_CONSTEXPR size_t TagPos = details::IndexOf< Key , Keys... >::value;
			if CYDL_CONSTEXPR ( TagPos == std::numeric_limits< std::decay_t< decltype( TagPos ) > >::max( ) )
			{
				std::decay_t< decltype( GetHelper< Key >( ) ) > defaultObject { };
				return defaultObject;
			}

			auto ptr = std::static_pointer_cast< std::decay_t< decltype( GetHelper< Key >( ) )>>(
				m_tuple[ TagPos ] );
			return *ptr;
		}

	private:
		template < typename Key >
		auto GetHelper ( ) -> typename CYDL_VDETAILS::GetElementByIndex< CYDL_VDETAILS::IndexOf< Key , Keys... >::value , Keys... >::type { }

	private:
		std::shared_ptr< void > m_tuple[sizeof...( Vals )];
	};
public:
	static auto Create ( )
	{
		using type = typename CYDL_VDETAILS::InitContainer< sizeof... ( Keys ) , Value >::type;
		return type { };
	}

};
CYDL_END_LIB_NAMESPACE

