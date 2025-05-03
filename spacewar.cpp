#include "main/main.hpp"

int main(const int p_argc, char *p_argv[])
{
	if (!spacewar::main::init()) {
		return 1;
	}
	return 0;
}
