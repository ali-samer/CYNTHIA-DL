#pragma once

CYDL_BEGIN_LIB_NAMESPACE

		template < typename T , typename Device >
		class CYDL_TEMPLATE_DEFAULT_CFLAG Matrix;

		template < typename T >
		class CYDL_TEMPLATE_DEFAULT_CFLAG Matrix< T , DeviceTags::CPU >
		{
		public:
			typedef T               ElementType;
			typedef DeviceTags::CPU DeviceType;
			typedef T * pointer;
			typedef T & reference;
			typedef T  type;

			Matrix ( CYDL_SIZET rowParam = 0 , CYDL_SIZET colParam = 0 );

			CYDL_SIZET CYDL_FORCE_INLINE rows ( ) { return m_rowNum; }
			CYDL_SIZET CYDL_FORCE_INLINE cols ( ) { return m_colNum; }
			CYDL_SIZET CYDL_FORCE_INLINE rowsLen ( ) { return m_rowLen; }

			/// \Interfaces :READ/WRITE ACCESS
			void setValue ( CYDL_SIZET p_rowID , CYDL_SIZET p_colID , ElementType val )
			{
				assert( availableForWrite( ) );
				assert( ( p_rowID < m_rowNum ) && ( p_colID < m_colNum ) );
				m_memory.rawMemory( )[ p_rowID * m_rowLen + p_colID ] = val;
			}
			CYDL_STRONG_INLINE const auto operator() ( CYDL_SIZET p_rowID , CYDL_SIZET p_colID ) const
			{
				assert( ( p_rowID < m_rowNum ) && ( p_colID < m_colNum ) );
				return m_memory.rawMemory( )[ p_rowID * m_rowLen + p_colID ];
			}
			CYDL_DONT_IGNORE_ATTRIBUTE CYDL_FORCE_INLINE bool availableForWrite ( ) const
			{
				return m_memory.useCount() == 1;
			}

			Matrix subMatrix ( CYDL_SIZET p_rowA , CYDL_SIZET p_rowB , CYDL_SIZET p_colA , CYDL_SIZET p_colB ) const
			{
				assert( (p_rowA < m_rowNum) && (p_colA < m_colNum) );
				assert( (p_colB <= m_rowNum) && (p_colB <= m_colNum) );

				pointer pos = m_memory.rawMemory() + p_rowA * m_rowLen + p_colA;
				return Matrix(m_memory.sharedPtr(),
							  pos,
							  p_rowB - p_rowA,
							  p_colB - p_colA,
							  m_rowLen);
			}

		private:
			Matrix ( std::shared_ptr< ElementType > p_memory ,
			         pointer p_memoryStart , CYDL_SIZET p_rowNum , CYDL_SIZET p_colNum , CYDL_SIZET p_rowLen )
				: m_memory( p_memory , p_memory ) ,
				  m_rowNum( p_rowNum ) ,
				  m_colNum( p_colNum ) ,
				  m_rowLen( p_rowLen ) { }

			CYDL_VDETAILS::ContinuousMemory< ElementType , DeviceType > m_memory;
			CYDL_SIZET m_rowNum;
			CYDL_SIZET m_colNum;
			CYDL_SIZET m_rowLen;
		};

		template < typename T , typename Device >
		CYDL_CONSTEXPR bool IsMatrix< Matrix< T , Device > > = true;

CYDL_END_LIB_NAMESPACE