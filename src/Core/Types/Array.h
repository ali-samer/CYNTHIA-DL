
#pragma once


#include "Core/Tags/Types.h"
#include "Core/Internal/EvalBuffer.h"
#include "Core/Containers/Batch.h"


CYDL_BEGIN_LIB_NAMESPACE
		CYDL_BEGIN_LIB_DETAILS_NAMESPACE

				template < typename Data , typename DataCategory >
				class CYDL_INTERNAL_AFLAG ArrayImpl;

				template < typename Data >
				class CYDL_INTERNAL_AFLAG ArrayImpl< Data , CategoryTags::Matrix >
				{
				public:
					using ElementType = typename Data::ElementType;
					using DeviceType = typename Data::DeviceType;

					ArrayImpl ( CYDL_SIZET p_rowNum = 0 , CYDL_SIZET p_colNum = 0 )
						: m_rowNum( p_rowNum ) ,
						  m_colNum( p_colNum ) { }

					template < typename Iterator , std::enable_if_t< IsIterator< Iterator>>* = nullptr >
					ArrayImpl ( Iterator b , Iterator e ) : m_buffer( b , e )
					{
						using OrgType = typename std::iterator_traits< Iterator >::value_type; // Original type
						using RawType = std::decay_t< OrgType >; // Corrected to std::decay_t

						static_assert( std::is_same_v< typename RawType::ElementType , std::decay_t< ElementType > > ,
						               "Incompatible Types -> ElementType: " CYDL_TOSTRING( ElementType )
						               " RawType::ElementType: " CYDL_TOSTRING( typename RawType::ElementType ) );
					}


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
				class CYDL_INTERNAL_AFLAG ArrayImpl< Data , CategoryTags::Scalar >
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


		template < typename Iterator >
		auto CYDL_STRONG_INLINE make_array ( Iterator begin , Iterator end )
		{
			using Data = typename std::iterator_traits< Iterator >::value_type;
			using RawData = CYDL_VUTILS::RemoveConstRef_t< Data >;
			return Array< RawData >( begin , end );
		}

CYDL_END_LIB_NAMESPACE