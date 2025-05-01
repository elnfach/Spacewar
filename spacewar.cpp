#include "main/main.hpp"

int main(const int p_argc, char *p_argv[])
{
	if (!spacewar::main::init()) {
		return EXIT_FAILURE;
	}
	return 0;
}
