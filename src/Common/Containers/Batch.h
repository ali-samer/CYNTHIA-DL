#pragma once

CYDL_BEGIN_LIB_NAMESPACE

		template < typename T , typename Device , typename Category >
		class CYDL_DEFAULT_AFLAG Batch;

		template < typename T , typename Device >
		class CYDL_DEFAULT_AFLAG Batch< T , Device , CategoryTags::Scalar >;

		template < typename T , typename Device >
		class CYDL_DEFAULT_AFLAG Batch< T , Device , CategoryTags::Matrix >
		{
		public:
			typedef T ElementType;
			typedef T Element_t;
			typedef Device DeviceType;
			typedef T* Pointer;
			typedef T& Reference;
			typedef T&& R_reference;

			Batch(CYDL_SIZET p_batchNum = 0, CYDL_SIZET p_rowNum = 0, CYDL_SIZET p_colNum = 0);

			CYDL_FORCE_INLINE CYDL_SIZET rows() const CYDL_NOEXCEPT { return m_rowNum; }
			CYDL_FORCE_INLINE CYDL_SIZET cols() const CYDL_NOEXCEPT { return m_colNum; }
			CYDL_FORCE_INLINE CYDL_SIZET batchs() const CYDL_NOEXCEPT { return m_batchNum; }

			CYDL_FORCE_INLINE bool availableForWrite() const CYDL_NOEXCEPT { m_memory.useCount() == 1; }
			CYDL_STRONG_INLINE void setValue(CYDL_SIZET p_batchID, CYDL_SIZET p_rowID, CYDL_SIZET p_colID, ElementType val)
			{
			}

			const auto operator[] (CYDL_SIZET p_batchID) const CYDL_NOEXCEPT
			{

			}

			auto SubBatchMatrix(CYDL_SIZET)

		private:
			CYDL_VDETAILS::ContinuousMemory<ElementType , DeviceType > m_memory;
			CYDL_SIZET m_rowNum;
			CYDL_SIZET m_colNum;
			CYDL_SIZET m_batchNum;
			CYDL_SIZET m_rowLen;
			CYDL_SIZET m_rawMatrixSize;
		};

		template < typename T , typename Device >
		CYDL_CONSTEXPR bool IsBatchMatrix< Batch< T , Device , CategoryTags::Matrix>> = true;

		template < typename T , typename Device >
		CYDL_CONSTEXPR bool IsBatchScalar< Batch< T , Device , CategoryTags::Scalar>> = true;

CYDL_END_LIB_NAMESPACE
