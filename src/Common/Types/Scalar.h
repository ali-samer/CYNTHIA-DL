#pragma once

CYDL_BEGIN_LIB_NAMESPACE

template < typename T , typename Device >
class CYDL_DEFAULT_AFLAG Scalar // TODO: must finish implementation
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

	CYDL_FORCE_INLINE auto value ( ) { return m_value; }

	/// \Overloads
	CYDL_FORCE_INLINE bool operator== ( const Scalar & scalar ) const
	{
		return m_value == scalar.m_value;
	}

	template < class OtherType >
	CYDL_STRONG_INLINE bool operator== ( const OtherType & ) const
	{
		CYDL_WARNING( "`Scalar` computing type must be compared with its equivalent computing type" );
		return false;
	}

	template < typename Data >
	CYDL_FORCE_INLINE bool operator!= ( const Data & data ) const
	{
		return true;
	}

	auto evalRegister ( ) const
	{

	}

private:
	ElementType m_value;
};

template < typename T , typename Device >
CYDL_CONSTEXPR bool IsScalar< Scalar< T , Device>> = true;

CYDL_END_LIB_NAMESPACE