#include "BigFloat.h"
#include <iostream>

int main()
{
	auto a = BigFloat("10.0");
	auto b = BigFloat("50.0");
	auto expected = BigFloat("0.2");

	auto res = a / b;
	std::cout << res << std::endl;
	return 0;
}