#pragma once

CYDL_BEGIN_LIB_NAMESPACE

CYDL_BEGIN_LIB_DETAILS_NAMESPACE

template < typename T >
class LowerAccessImpl< Matrix< T, DeviceTags::CPU > >
{
public:
	CYDL_STRONG_EXPLICIT LowerAccessImpl(Matrix< T, DeviceTags::CPU> mat) : m_matrix(mat) { }
	CYDL_FORCE_INLINE auto mutableRawMemory() { m_matrix.m_memory.rawMemory(); }
	CYDL_FORCE_INLINE const auto rawMemory() const CYDL_NOEXCEPT { m_matrix.m_memory.rawMemory(); }
	CYDL_FORCE_INLINE CYDL_SIZET rowLen() const CYDL_NOEXCEPT { return m_matrix.m_rowLen; }

private:
	Matrix< T, DeviceTags::CPU > m_matrix;
};

CYDL_END_LIB_DETAILS_NAMESPACE

CYDL_END_LIB_NAMESPACE