#pragma once

// TODO: implement the TypeChecker utility api
// @formatter: off
CYDL_BEGIN_LIB_NAMESPACE
		CYDL_BEGIN_LIB_UTILS_NAMESPACE

				template < typename... >
				struct TypeList;

				template < typename T >
				struct TypeChecker_
				{
					static CYDL_CONSTEXPR bool value = false;
				};

		CYDL_END_LIB_UTILS_NAMESPACE
CYDL_END_LIB_NAMESPACE

