#include <iostream>
#include "main/main.hpp"

#define nameof(name) #name

int main(const int p_argc, char *p_argv[])
{
	for (int i = 1; i < p_argc; i++)
	{
		std::cout << p_argv[i] << std::endl;
	}

	if (spacewar::main main; !main.init()) {
		return EXIT_FAILURE;
	}
	return 0;
}
