#pragma once

namespace cydl::details
{
	template < typename... Policies >
	struct PolicyContainer;

	template < typename... Policies >
	using Policy = PolicyContainer < Policies... >;

	template < typename... T >
	constexpr static bool IsPolicyContainer = false;

	template < typename... T >
	constexpr static bool IsPolicyContainer< PolicyContainer < T... > > = true;

	template < typename LayerName, typename... Policies >
	struct SubPolicyContainer;

	template < typename T >
	constexpr bool IsSubPolicyContainer = false;

	template < typename Layer, typename... T >
	constexpr static bool IsSubPolicyContainer< SubPolicyContainer< Layer, T... > > = true;

}