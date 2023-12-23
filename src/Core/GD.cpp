#include "Core/GD.h"

namespace cydl
{
	std::optional<std::vector<double>> gradient_descent(std::function<double(double)> df,
														double x,
														long double alpha,
														int iterations,
														double epsilon)
	{
		std::vector<double> history;
		history.push_back(x);

		for(int i = 0; i < iterations; i++)
		{
			if(std::abs(df(x)) < epsilon)
			{
				std::cout << "The gradient is small enough!" << std::endl;
				return history;
			}
			x = x - alpha * df(x);
			history.push_back(x);
		}
		return std::nullopt;
	}


}