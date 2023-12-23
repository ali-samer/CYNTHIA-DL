#pragma once

/**
 * @HeteroDict: A Compile-Time Evaluated Heterogeneous Dictionary
 *
 * @Overview:
 * The HeteroDict class template is part of an exploration into advanced C++ template metaprogramming,
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
 * auto heteroDict = HeteroDict::Create().Set<A>(1.2f).Set<B>(false);
 *
 * @Features:
 * - Compile-time key-value pair evaluation and storage.
 * - Flexible API for setting and retrieving values with type safety.
 * - Efficient storage mechanism using tuples and shared pointers.
 */


#include "include_utils.h"
#include "utils.h"
#include "new_tuple_type.h"

/**
 * The choice of conveying the namespace as "details" is an attempt to follow common C++ conventions
 * by having the "details" namespace contain inner implementation code that end users generally don't
 * need to interact with or know about. This keeps the external-facing interface cleaner and modular.
 *
 * The following is lower-level machinery supporting the dictionary API...
 **/
namespace details
{
	template <
		size_t NumOfTypeParams ,
		template < typename... > class TypeContainer ,
		                         typename... Pack
	>
	struct InitContainer
	{
		static_assert( NumOfTypeParams , "You must specify < typename... keys > in order to `set` key-valued pairs to "
		                                 "their corresponding identifiers." );
		using type = typename InitContainer< NumOfTypeParams - 1 , TypeContainer , NullParam , Pack... >::type;
	};

	template <
		template < typename... > class TypeContainer ,
		                         typename... Pack
	>
	struct InitContainer< 0 , TypeContainer , Pack... >
	{
		using type = TypeContainer< Pack... >;
	};

	template <
		typename Target ,
		typename... RemainingTs
	>
	struct IndexOf;

	template <
		typename Target ,
		typename... RemainingTs
	>
	struct IndexOf< Target , Target , RemainingTs... > :
		std::integral_constant< size_t , 0 >
	{
	};

	template <
		typename Target ,
		typename MissMatch ,
		typename... RemainingTs
	>
	struct IndexOf< Target , MissMatch , RemainingTs... > :
		std::integral_constant<
			size_t ,
			1 + IndexOf< Target , RemainingTs... >::value
		>
	{
	};

	template <
		typename Target ,
		typename... RemainingTs
	>
	struct IndexOf : public std::exception
	{
		const char* what() const noexcept override
		{
			return "Target not located within list...";
		}
	};

	template <typename T, typename... Types>
	struct Contains;


	template <typename T, typename... Types>
	struct Contains<T, T, Types...> : std::true_type {};

	template <typename T>
	struct Contains<T> : std::false_type {};

	template <typename T, typename U, typename... Types>
	struct Contains<T, U, Types...> : Contains<T, Types...> {};

}

namespace cydl
{

// to ensure flexibility the use of variadic templates is essential to both
// template classes to set key-valued pairs
	template < typename... Keys > // keys will be saved in Keys
	class HeteroDict final
	{
		template < typename... Vals > // Valued pairs will be saved in Vals in parallel with Keys
		struct ValStrg
		{
		public:
			using TupleType = typename details::InitContainer< sizeof...( Vals ) , std::tuple >::Type;

			ValStrg ( ) = default;

			ValStrg ( std::shared_ptr< void >(&& input)[sizeof... ( Vals )] )
			{
				for ( size_t i = 0 ; i < sizeof... ( Vals ) ; i++ )
					m_tuple[ i ] = std::move( input[ i ] );
			}

			template < typename Key , typename Val >
			constexpr auto Set ( Val && val ) &&
			{
				using namespace details;
				constexpr static size_t TagPos = IndexOf< Key , Keys... >::val;

				using rawVal = std::decay_t< Val >;
				rawVal* tmp = new rawVal( std::forward< Val >( val ) );

				m_tuple[ TagPos ] = std::shared_ptr< void >( tmp ,
				                                             [ ] ( void* ptr )
				                                             {
				                                               rawVal* nptr = static_cast<rawVal*>(ptr);
				                                               delete nptr;
				                                             } );

				using new_type = NewTuple_t< rawVal , TagPos , ValStrg< > , Vals... >;
				return new_type( std::move( m_tuple ) );
			}

			template < typename Key >
			constexpr auto & Get ( ) const;

		private:
			std::shared_ptr< void > m_tuple[sizeof...( Vals )];
		};
	public:
		static auto Create ( )
		{
			using type = typename details::InitContainer< sizeof... ( Keys ) , ValStrg >::type;
			return type { };
		}

	};
}

