#include <iostream>
#include "neurocyn.h"
#include "xtensor.hpp"
//#include "Macros.h"
#include <cmath>
#include <xtensor/xarray.hpp>
#include <string>
#include "cydl.h"


int main ( )
{
	#ifdef CYDL_DEFINE_GLOBAL_MACROS
	std::cout << "CYDL VERSION IS AT LEAST 0.1.0: " <<  std::boolalpha << CYDL_VERSION_AT_LEAST(0,1,0) << std::endl;
	#endif
	return 0;
}
