#pragma once


#include <array>
#include <cassert>
#include <numeric>
#include <stdexcept>


CYDL_BEGIN_LIB_NAMESPACE

		CYDL_BEGIN_LIB_DETAILS_NAMESPACE
				template < CYDL_SIZET DimNum , typename CurrIndexType , typename... RemainingIndexType >
				CYDL_SIZET IndexToOffset ( const std::array< CYDL_SIZET , DimNum > & dims , CYDL_SIZET & p_gap ,
				                           CurrIndexType currIdx , RemainingIndexType ...remainingIdx )
				{
					CYDL_CONSTEXPR CYDL_SIZET indexPos = DimNum - sizeof...( RemainingIndexType ) - 1;
					if CYDL_CONSTEXPR ( static_cast<CYDL_SIZET>(currIdx) >= dims[ indexPos ] )
						throw std::runtime_error( "Invalid dimension index." );

					if CYDL_CONSTEXPR ( sizeof...( RemainingIndexType ) == 0 )
						return static_cast<CYDL_SIZET >(currIdx);
					else
					{
						CYDL_SIZET currGap = 1;
						CYDL_SIZET res     = IndexToOffset( dims , currGap , remainingIdx... );
						p_gap = currGap * dims[ indexPos + 1 ];
						res += static_cast< CYDL_SIZET >( currIdx ) * p_gap;
						return res;
					}
				}

				template < CYDL_SIZET DimNum , int ...N >
				CYDL_FORCE_INLINE
				CYDL_SIZET IndexToOffset ( const std::array< CYDL_SIZET , DimNum > & p_dims ,
				                           const std::array< CYDL_SIZET , DimNum > & p_indexes ,
				                           std::index_sequence< N... >* )
				{
					return IndexToOffset( p_dims , 1 , std::get< N >( p_indexes )... );
				}

				template < CYDL_SIZET ID , typename ShapeType >
				CYDL_FORCE_INLINE
				void FillShape ( ShapeType & p_shape ) { }
		CYDL_END_LIB_DETAILS_NAMESPACE

		template < CYDL_SIZET UDimNum >
		class CYDL_DEFAULT_AFLAG Shape
		{
			static_assert( UDimNum > 0 );
		public:
			CYDL_CONSTEXPR static CYDL_SIZET DimNum = UDimNum;

			CYDL_STRONG_EXPLICIT Shape ( ) = default;

			template <
				typename ...IntTypes ,
				std::enable_if_t< (std::is_convertible_v< IntTypes , CYDL_SIZET > && ...) >* = nullptr
			>
			CYDL_STRONG_EXPLICIT Shape ( IntTypes ...p_shapes )
			{
				static_assert( sizeof...( IntTypes ) == DimNum );
				CYDL_VDETAILS::FillShape< 0 >( m_dims , p_shapes... );
			}

			CYDL_FORCE_INLINE
			bool operator== ( const Shape & p_val ) const CYDL_NOEXCEPT { return m_dims == p_val.m_dims; }

			template < CYDL_SIZET DimNumTemp >
			CYDL_FORCE_INLINE
			bool operator== ( const Shape< DimNumTemp > & ) const { return false; }

			CYDL_SIZET count ( ) const
			{
				return std::accumulate( std::begin( m_dims ) , std::end( m_dims ) ,
				                        static_cast<CYDL_SIZET>(1) , std::multiplies< >( ) );
			}

			// TODO: Finish Shape Class Implementation

		private:
			std::array< CYDL_SIZET , DimNum > m_dims { };
		};

CYDL_END_LIB_NAMESPACE