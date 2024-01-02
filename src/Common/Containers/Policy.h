#pragma once

namespace cydl::details
{
	template < typename... Policies >
	class PolicyContainer;

	template < typename... Policies >
	using Policies = PolicyContainer < Policies... >;

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