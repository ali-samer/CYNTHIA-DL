#pragma once

CYDL_BEGIN_LIB_NAMESPACE

		template < typename T , typename Device >
		class CYDL_TEMPLATE_DEFAULT_CFLAG Scalar // TODO: must finish implementation
		{
		public:
			typedef T      ElementType;
			typedef Device DeviceType;
			typedef T * pointer;
			typedef T & reference;
			typedef T type;

			// The explicit constructor will assign a default value to the m_value variable if the user
			// does not pass
			CYDL_STRONG_EXPLICIT Scalar ( ElementType value = ElementType( ) ) : m_value( value ) { }

			auto CYDL_FORCE_INLINE value ( ) { return m_value; }

			/// \Overloads
			bool operator== ( const Scalar & scalar ) const
			{

			}

			template < class OtherType >
			bool operator== ( const OtherType & ) const
			{

			}

			template < typename Data >
			bool operator!= ( const Data & data ) const
			{

			}

			auto evalRegister ( ) const
			{

			}

		private:
			ElementType m_value;
		};

CYDL_END_LIB_NAMESPACE