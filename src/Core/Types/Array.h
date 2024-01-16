
#pragma once


#include "Core/Tags/Types.h"
#include "Core/Internal/EvalBuffer.h"
#include "Core/Containers/Batch.h"


CYDL_BEGIN_LIB_NAMESPACE
		CYDL_BEGIN_LIB_DETAILS_NAMESPACE

				template < typename Data , typename DataCategory >
				class CYDL_DEFAULT_AFLAG ArrayImpl;

				template < typename Data >
				class CYDL_DEFAULT_AFLAG ArrayImpl< Data , CategoryTags::Matrix >
				{
				public:
					using ElementType = typename Data::ElementType;
					using DeviceType = typename Data::DeviceType;

					ArrayImpl ( CYDL_SIZET p_rowNum = 0 , CYDL_SIZET p_colNum = 0 )
						: m_rowNum( p_rowNum ) ,
						  m_colNum( p_colNum ) { }

					template < typename Iterator , std::enable_if_t< IsIterator < Iterator>> * = nullptr >
					ArrayImpl ( Iterator b , Iterator e );

				public:
					CYDL_FORCE_INLINE CYDL_SIZET rows ( ) const CYDL_NOEXCEPT { return m_rowNum; }
					CYDL_FORCE_INLINE CYDL_SIZET cols ( ) const CYDL_NOEXCEPT { return m_colNum; }
					CYDL_FORCE_INLINE CYDL_SIZET batchs ( ) const CYDL_NOEXCEPT { return m_evalBuf->size( ); }

					bool availableForWrite ( ) const { return ( !m_evalBuf.isEvaluated( ) ) && ( m_buffer.use_count( ) == 1 ); }
				private:
					CYDL_SIZET                                                           m_rowNum;
					CYDL_SIZET                                                           m_colNum;
					std::shared_ptr< std::vector< Data>>                                 m_buffer;
					EvalBuffer< Batch< ElementType , DeviceType , CategoryTags::Matrix>> m_evalBuf;
				};

				template < typename Data >
				class CYDL_DEFAULT_AFLAG ArrayImpl< Data , CategoryTags::Scalar >
				{
					// TODO: Implement the ArrayImpl < Data, Scalar > class
				};

		CYDL_END_LIB_DETAILS_NAMESPACE

		template < typename T >
		class CYDL_DEFAULT_AFLAG Array : public CYDL_VDETAILS::ArrayImpl< T , DataCategory_t< T > >
		{
		public:
			using ElementType = typename T::ElementType;
			using TypeCategory = DataCategory_t< T >;
			using DeviceType = typename T::DeviceType;
			using CYDL_VDETAILS::ArrayImpl< T , TypeCategory >::ArrayImpl;
		};

		template < typename T >
		CYDL_CONSTEXPR bool IsBatchVector< Array< T > > = IsVector< T >;

		template < typename T >
		CYDL_CONSTEXPR bool IsBatchMatrix< Array< T > > = IsMatrix< T >;

		template < typename T >
		CYDL_CONSTEXPR bool IsBatchScalar< Array< T > > = IsScalar< T >;

CYDL_END_LIB_NAMESPACE