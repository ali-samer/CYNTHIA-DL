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
			void setValue ( CYDL_SIZET p_rowID , CYDL_SIZET p_colID , ElementType val );
			const auto operator() ( CYDL_SIZET p_rowID , CYDL_SIZET p_colID ) const;
			bool availableForWrite ( ) const;

			Matrix subMatrix ( CYDL_SIZET p_rowA , CYDL_SIZET p_rowB , CYDL_SIZET p_colA , CYDL_SIZET p_colB ) const;

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

CYDL_END_LIB_NAMESPACE