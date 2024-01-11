#pragma once

#include "Scalar.h"
#include "Common/Internal/EvalBuffer.h"


CYDL_BEGIN_LIB_NAMESPACE
template < typename T, typename Device, typename Scalar = Scalar<int, DeviceTags::CPU> >
class CYDL_DEFAULT_AFLAG TrivialMatrix
{
public:
	typedef T ElementType;
	typedef T Element_t;
	typedef Device DeviceType;
	typedef Device Device_t;
	typedef T* Pointer;
	typedef T& Reference;
	typedef T&& R_reference;

	TrivialMatrix(CYDL_SIZET p_rowNum, CYDL_SIZET p_colNum, Scalar p_val);

	CYDL_FORCE_INLINE CYDL_SIZET rows ( ) const CYDL_NOEXCEPT { return m_rowNum; }
	CYDL_FORCE_INLINE CYDL_SIZET cols ( ) const CYDL_NOEXCEPT { return m_colNum; }

	CYDL_FORCE_INLINE auto elementValue() const CYDL_NOEXCEPT { return m_value; }

private:
	Scalar m_value;
	CYDL_SIZET m_rowNum;
	CYDL_SIZET m_colNum;

	CYDL_VDETAILS::EvalBuffer< Matrix< ElementType , DeviceType>> m_evalBuf;

};

template < typename T, typename Device >
CYDL_CONSTEXPR bool IsMatrix<TrivialMatrix<T, Device>> = true;

template < typename T, typename Device, typename Val_t >
auto make_trivial_matrix(CYDL_SIZET p_rowNum, CYDL_SIZET p_colNum, Val_t&& m_val)
{
	using RawVal = typename CYDL_VUTILS::RemoveConstRef<Val_t>::type;

	if CYDL_CONSTEXPR (IsScalar<RawVal>)
	{
		if CYDL_CONSTEXPR (std::is_same_v<Device, DeviceTags::CPU>)
		{
			return TrivialMatrix<T, Device, RawVal >(p_rowNum, p_colNum, m_val);
		}
	}
	else
	{
		T tmpT = static_cast<T>(m_val);
		Scalar<T, DeviceTags::CPU > scalar(std::move(tmpT));
		return TrivialMatrix<T, Device, Scalar<T, DeviceTags::CPU>>(p_rowNum, p_colNum, std::move(scalar));
	}
}

CYDL_END_LIB_NAMESPACE