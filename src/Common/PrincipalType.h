#pragma once

CYDL_BEGIN_LIB_NAMESPACE

	CYDL_BEGIN_LIB_DETAILS_NAMESPACE

		template < typename TagCategory, typename T, typename Device >
		struct CYDL_TEMPLATE_DEFAULT_CFLAG PrincipleType_;

		template < typename T, typename Device >
		struct CYDL_TEMPLATE_DEFAULT_CFLAG PrincipleType_< CategoryTags::Matrix, T, Device>
		{
			using type = Matrix<T, Device>;
		};

		// TODO: implement further specializations

	CYDL_END_LIB_DETAILS_NAMESPACE

	template < typename TagCategory, typename T , typename ComputingDevice >
	using PrincipleType = typename CYDL_VDETAILS::PrincipleType_<TagCategory, T, ComputingDevice >::type;

CYDL_END_LIB_NAMESPACE