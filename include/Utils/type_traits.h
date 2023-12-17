#pragma once

/**
 * @name Samer Ali
 * @dec: Type Meta-function utilities. The following code has been inspired from the book
 * "C++ Template Metaprogramming in Practice: A Deep Learning Framework" by Li Wei.
 * This file will contain a custom implementation utility meta-functions for type traits
 * */

#include <type_traits>
#include <functional>


namespace cy
{

	template < class Fun >
	class y_combinator_result
	{
		Fun fun_;
	public:
		template < class T >
		explicit y_combinator_result ( T && fun ): fun_( std::forward< T >( fun ) ) { }

		template < class ...Args >
		decltype( auto ) operator() ( Args && ...args )
		{
			return fun_( std::ref( *this ) , std::forward< Args >( args )... );
		}
	};



	template < typename T >
	struct UnsignedMap
	{
		using type = T;
	};

	template < >
	struct UnsignedMap< int >
	{
		using type = unsigned int;
	};

	template < >
	struct UnsignedMap< long >
	{
		using type = unsigned long;
	};

	template < typename T >
	using UnsignedMap_t = typename UnsignedMap< T >::type;

	///
	template < bool AddOrRemoveRef >
	struct TypeReferenceModifier;

	template < >
	struct TypeReferenceModifier< false >
	{
		template < typename T >
		using Modifier = typename std::remove_reference_t< T >;
	};


	template < bool AddOrRemoveRef , typename T >
	using TypeReferenceModifier_t = typename TypeReferenceModifier< AddOrRemoveRef >::template Modifier< T >;

	///
	template < typename T >
	struct RemoveConstRef
	{
	private:
		using const_val = typename std::remove_reference_t< T >;
	public:
		using type = typename std::remove_const_t< const_val >;
	};

	template < typename T >
	using RemoveConstRef_t = RemoveConstRef< T >::type;
}