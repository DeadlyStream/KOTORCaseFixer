#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

fs::path toLower(const fs::path& path);
void makeAllLowercase(fs::path& path);

int main(int argc, const char* argv[]) {
	auto path = argc > 1 ? fs::path(argv[1]) : fs::current_path();

	makeAllLowercase(path);
}

fs::path toLower(const fs::path& path) {
	string str = path.string();

	for( string::size_type i = 0; i < str.length(); ++i ) {
		unsigned char c = str[i];
		str[i] = tolower(c);
	}

	return fs::path(str);
}

void makeAllLowercase(fs::path& path) {
	for( auto& entry : fs::recursive_directory_iterator(path) ) {
		fs::path from = entry.path();
		fs::path to = from;

		to.replace_filename(toLower(to.filename()));
		fs::rename(from, to);
	}
}