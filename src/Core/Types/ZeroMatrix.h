#pragma once


#include "TrivialMatrix.h"


CYDL_BEGIN_LIB_NAMESPACE

		template < typename T , typename Device, typename Dummy >
		class ZeroMatrix : public TrivialMatrix< T , Device , Scalar< T , Device > >
		{
		public:
			using Base = TrivialMatrix< T , Device , Scalar< T , Device>>;
			typedef T      ElementType;
			typedef T      Element_t;
			typedef Device DeviceType;
			typedef Device Device_t;
			typedef T * Pointer;
			typedef T & Reference;
			typedef T && R_reference;


			// Constructor
			ZeroMatrix ( CYDL_SIZET p_rowNum , CYDL_SIZET p_colNum, CYDL_UNUSED_AFLAG Dummy )
				: Base( p_rowNum , p_colNum , Scalar< T , Device >( 0 ) ) { }

		};
		template < typename T, typename Device >
		CYDL_CONSTEXPR bool IsMatrix<ZeroMatrix<T, Device, CategoryTags::Scalar>> = true;

		template < typename T , typename Device >
		auto make_zero_matrix ( CYDL_SIZET rowNum , CYDL_SIZET colNum )
		{
			return ZeroMatrix< T , Device, CYDL_VUTILS::NullParam >( rowNum , colNum );
		}

CYDL_END_LIB_NAMESPACE
