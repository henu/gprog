#include "json.hpp"
#include "types.hpp"
#include "network.hpp"

#include <cstdlib>
#include <fstream>
#include <streambuf>

int main(int argc, char** argv)
{
	Strings args(argv, argv + argc);

	if (args.size() > 1) {
		std::string src_path = args[1];
		std::ifstream src_file(src_path.c_str());
		JSON src(src_file);
		Network net(src);
	}

	return EXIT_SUCCESS;
}
