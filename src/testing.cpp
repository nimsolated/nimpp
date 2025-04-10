#include "../include/lexer.h"
#include <fstream>
#include <sstream>

int main() {
	// open the source file
	std::ifstream source("src/mytext.txt");
	if (!source){
		std::cout << "Failed to open the source file.\n";
		return 1;
	}

	// output each character into ostringstream
	std::ostringstream oss;
	char c;
	while (c = source.get()) {
		// if source's end of file is reached
		if ((int)c == -1) {
			break;
		}
		oss << c;
	}

	// cout the tokens
	std::string source_string = oss.str();
	std::vector<Token> tokens = tokenize(source_string);
	size_t source_size = tokens.size();
	for (size_t i = 0; i < source_size; i++) {
		std::cout << tokens[i] << std::endl;
	}

	// close the source file
	source.close();
}