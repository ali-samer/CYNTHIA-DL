#pragma once

#include <exception>
#include "Core/utils/Macros.h"

CYDL_BEGIN_LIB_NAMESPACE
	CYDL_BEGIN_LIB_POLICIES_NAMESPACE
		template < class T >
		struct NoChecking
		{
			static void Check(T*) { }
		};

		template < class T >
		struct EnforceNotNull
		{
			class NullPointerException : public std::exception
			{
				const char* what() CYDL_NOEXCEPT
				{
					return "NullPointerException";
				}
			};
			static void Check(T*& ptr)
			{
				if (!ptr)
				{
					auto rawptr = std::decay_t<T>();
					ptr = rawptr.GetDefaultObject();
				}
			}
		};
	CYDL_END_LIB_POLICIES_NAMESPACE
CYDL_END_LIB_NAMESPACE