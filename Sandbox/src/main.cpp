#include <iostream>
#include "neurocyn.h"
#include <cmath>
#include <string>
#include <signal.h>
#include "cydl.h"


int main ( )
{
	#ifdef CYDL_DEFINE_GLOBAL_MACROS
	std::cout << "CYDL VERSION IS AT LEAST 0.1.0: " <<  std::boolalpha << CYDL_VERSION_AT_LEAST(0,2,0) << std::endl;
	#endif

	cydl::MatrixXXX<int, cydl::DynamicDim, cydl::DynamicDim> mat;

	mat.setZero(1, 1);
	return 0;

}
