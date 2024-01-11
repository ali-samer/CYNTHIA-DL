#pragma once


#include "type_traits"
#include <cstdlib>
#include <stdlib.h>


/**
 * @file
 * @Test:
 * This file will encompass encapsulation to hide `risky` interfaces from the frame users of the framework.
 * We implement hiding to some extent: providing the user with matrix-level access in a special way
 */

CYDL_BEGIN_LIB_NAMESPACE
		CYDL_BEGIN_LIB_DETAILS_NAMESPACE

				template < typename T >
				struct CYDL_DEFAULT_AFLAG LowerAccessImpl; // TODO: to be implemented

				/**
				 * LowerAccess function should only be accessed by the internal mechanism of the framework
				 */
				template < typename T >
				auto CYDL_FORCE_INLINE LowerAccess ( T && param )
				{
					return LowerAccessImpl< CYDL_VUTILS::RemoveConstRef< T > >( std::forward< T >( param ) );
				}

		CYDL_END_LIB_DETAILS_NAMESPACE
CYDL_END_LIB_NAMESPACE