#pragma once

CYDL_BEGIN_LIB_NAMESPACE
CYDL_BEGIN_LIB_POLICIES_NAMESPACE
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
CYDL_END_LIB_POLICIES_NAMESPACE
CYDL_END_LIB_NAMESPACE