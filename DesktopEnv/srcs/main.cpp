#include "Core.hpp"

int main(int argc, char* argv[])
{
	Core l_Core(argc, argv);
	l_Core.Init();
	l_Core.Run();
}
