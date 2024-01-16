#pragma once

CYDL_BEGIN_LIB_NAMESPACE

		template < typename T , typename Device , typename Category >
		class CYDL_DEFAULT_AFLAG Batch;

		template < typename T , typename Device >
		class CYDL_DEFAULT_AFLAG Batch< T , Device , CategoryTags::Scalar >;

		template < typename T , typename Device >
		class CYDL_DEFAULT_AFLAG Batch< T , Device , CategoryTags::Matrix >
		{
		private:
			typedef Matrix< T , Device > MatrixType;
		public:
			typedef T      ElementType;
			typedef T      Element_t;
			typedef Device DeviceType;
			typedef T  * Pointer;
			typedef T  & Reference;
			typedef T  && R_reference;


			Batch ( CYDL_SIZET p_batchNum = 0 , CYDL_SIZET p_rowNum = 0 , CYDL_SIZET p_colNum = 0 )
				: m_batchNum( p_batchNum ) ,
				  m_rowNum( p_rowNum ) ,
				  m_colNum( p_colNum ) ,
				  m_rowLen( p_colNum ) ,
				  m_rawMatrixSize( p_rowNum * p_colNum )
			{
				m_memory = CYDL_VDETAILS::ContinuousMemory< MatrixType , DeviceType >( m_batchNum );
			}


			CYDL_FORCE_INLINE CYDL_SIZET rows ( ) const CYDL_NOEXCEPT { return m_rowNum; }
			CYDL_FORCE_INLINE CYDL_SIZET cols ( ) const CYDL_NOEXCEPT { return m_colNum; }
			CYDL_FORCE_INLINE CYDL_SIZET batchs ( ) const CYDL_NOEXCEPT { return m_batchNum; }

			CYDL_DONT_IGNORE_AFLAG CYDL_FORCE_INLINE bool availableForWrite ( ) const CYDL_NOEXCEPT { m_memory.useCount( ) == 1; }
			CYDL_STRONG_INLINE void setValue ( CYDL_SIZET p_batchID , CYDL_SIZET p_rowID , CYDL_SIZET p_colID ,
			                                   ElementType val )
			{
				assert( availableForWrite( ) );
				assert( ( p_batchID < m_batchNum ) && ( p_batchID >= 0 ) );
				m_memory.rawMemory( )[ p_batchID ].setValue( p_rowID , p_colID , val );
			}

			const auto operator[] ( CYDL_SIZET p_batchID ) const CYDL_NOEXCEPT
			{
				assert( ( p_batchID >= 0 ) && ( p_batchID < m_batchNum ) );
				return m_memory.rawMemory( )[ p_batchID ];
			}

			auto subBatchMatrix ( CYDL_SIZET p_rowA , CYDL_SIZET p_rowB , CYDL_SIZET p_colA , CYDL_SIZET p_colB )
			{
				// TODO: implement subBatchMatrix (my thought here is to return a new batch
				//  matrix for all the adjusted matrices)
			}

		private:
			CYDL_VDETAILS::ContinuousMemory< ElementType , DeviceType > m_memory;
			CYDL_SIZET m_rowNum;
			CYDL_SIZET m_colNum;
			CYDL_SIZET m_batchNum;
			CYDL_SIZET m_rowLen;
			CYDL_SIZET m_rawMatrixSize;
		};

		template < typename T , typename Device >
		using BatchMatrix = Batch< T , Device , CategoryTags::Matrix >;

		template < typename T , typename Device >
		using BatchVector = Batch< T , Device , CategoryTags::Vector >;

		template < typename T , typename Device >
		using BatchScalar = Batch< T , Device , CategoryTags::Scalar >;

		template < typename T , typename Device >
		CYDL_CONSTEXPR bool IsBatchMatrix< Batch< T , Device , CategoryTags::Matrix>> = true;

		template < typename T , typename Device >
		CYDL_CONSTEXPR bool IsBatchVector< Batch< T , Device , CategoryTags::Vector>> = true;

		template < typename T , typename Device >
		CYDL_CONSTEXPR bool IsBatchScalar< Batch< T , Device , CategoryTags::Scalar>> = true;

CYDL_END_LIB_NAMESPACE
