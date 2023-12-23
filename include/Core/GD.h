
// gradient descent header file

#pragma once

#include <optional>
#include <functional>
#include <math.h>
#include <vector>
#include <iostream>
#include <iomanip>

namespace cydl
{
	std::optional<std::vector<double>> gradient_descent(std::function<double(double)> df,
														double x,
														long double alpha = 0.01,
														int iterations = 100,
														double epsilon = 1e-8);

}
