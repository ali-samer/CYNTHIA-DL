#include "cydl.h"


using namespace cydl::details;

template < class T, template  < typename... > class U >
struct PolicySelect
{

};
template < typename... TPolicies >
struct Accumulator
{


	using TPoliCont = cydl::details::PolicyContainer< TPolicies... >;
	using TPolicyRes = PolicySelect< struct AccPolicy, TPoliCont >;
};

auto func()
{
	std::__distance();
}