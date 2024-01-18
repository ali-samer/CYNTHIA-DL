#pragma once


#include <vector>
#include <tuple>

#include "DataProcessing/CSV.h"
#include <iostream>

CYDL_BEGIN_LIB_NAMESPACE

		template < CYDL_SIZET Cols , typename... T >
		class CSVParser
		{
		public:
			using RowType = std::tuple< T... >;
			using ValuesIterator = std::vector< double >::iterator;
			using CategoricalIterator = std::vector< std::string >::iterator;

		public:
			CSVParser ( std::string p_filePath )
				: m_colsNum( Cols ) ,
				  m_csvReader( p_filePath ) { }

			CYDL_CONSTEXPR void read (unsigned int p_intCols )
			{
				try
				{
					bool done = false;
					while ( !done )
					{
						done = !readRow_( std::make_index_sequence< std::tuple_size_v< RowType > >{ } ,
						                                            m_row , m_csvReader );
						if(!done)
						{
							m_categoricalCol.push_back(std::get<p_intCols>(m_row));
							fillValues_(std::make_index_sequence<m_colsNum - 1>{}, m_row, m_values);
						}
					}
				} catch(const io::error::no_digit& e) {
					std::cerr << e.what() << std::endl;
				}

			}

			std::pair<ValuesIterator, ValuesIterator> iterate()
			{
				return {m_values.begin(), m_values.end()};
			}

		private:
			template < CYDL_SIZET... Idx , typename Type , typename Reader >
			bool readRow_ ( std::index_sequence< Idx... > , Type & row , Reader & r )
			{
				return r.read_row( std::get< Idx >( row )... );
			}

			template < CYDL_SIZET... Idx , typename Type >
			void fillValues_ ( std::index_sequence< Idx... > , Type & row , std::vector< double > & data )
			{
				data.insert( data.end( ) , { std::get< Idx >( row )... } );
			}

		private:
			CYDL_SIZET                 m_colsNum;
			std::vector< std::string > m_categoricalCol;
			std::vector< double >      m_values;
			RowType                    m_row;
			io::CSVReader< Cols > m_csvReader;
		};

CYDL_END_LIB_NAMESPACE