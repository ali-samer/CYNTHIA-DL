#include "cydl.h"


#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <array>
#include "Eigen/Dense"
#include "Eigen/Core"

const char* sep() { return "\n--------------------------\n"; }

int main ( )
{
	using std::cout, std::endl;

	Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic > mat;
	mat.resize(3,4);
	mat <<  1, 1, 2, 4,
			4, 5, -5, -1,
			-2, -3, 5, -6;
	std::cout << mat << std::endl;
	cout << sep();

	mat.row(1) = mat.row(1) - 4 * mat.row(0);
	cout << sep();
	std::cout << mat << std::endl;
	cout << sep();

	mat.row(2) = mat.row(2) + 2 * mat.row(0);
	mat.row(2) = mat.row(2) + mat.row(1);
	std::cout << mat << std::endl;
	cout << sep();
	return 0;
}
