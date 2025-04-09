#include "../include/lexer.h"

static Token token(const std::string& value, TokenType type) {
	return { value, type };
}

static bool isAlpha(const char& value) {
	return toupper(value) != tolower(value);
}

static bool isInt(const char& value) {
	const char c = static_cast<int>(value);
	const char bounds[2] = { static_cast<int>('0'), static_cast<int>('9') };
	return (c >= bounds[0] && c <= bounds[1]);
}

static bool isSkippable(const char& value) {
	return value == ' ' || value == '\n' || value == '\t';
}

std::vector<Token> tokenize(const std::string& sourceCode) {
	std::vector<Token> tokens(0);
	std::vector<char> src(sourceCode.length());
	size_t src_size = src.size();

	auto popFrontSrc = [&src]()->const std::string {
		if (src.empty()) {
			return "\0";
		}

		std::string r = " ";
		r[0] = src.front();
		src.erase(src.begin());
		return r;
	};

	for (size_t i = 0; i < src_size; i++) {
		src[i] = sourceCode[i];
	}

	// Build each token until end of file
	while(!src.empty()) {
		if (src[0] == '(') {
			tokens.push_back(token(popFrontSrc(), TokenType::OPEN_PAREN));
		}
		else if (src[0] == ')') {
			tokens.push_back(token(popFrontSrc(), TokenType::CLOSE_PAREN));
		}
		else if (src[0] == '+' || src[0] == '-' || src[0] == '*' || src[0] == '/') {
			tokens.push_back(token(popFrontSrc(), TokenType::BINARY_OPERATOR));
		}
		else if (src[0] == '=') {
			tokens.push_back(token(popFrontSrc(), TokenType::EQUALS));
		}
		else {
			// Handle multi-character tokens

			// Build number token
			if (isInt(src[0])) {
				std::string num = "";
				while (!src.empty() && isInt(src[0])) {
					num += popFrontSrc();
				}

				tokens.push_back(token(num, TokenType::NUMBER));
			}
			else if (isAlpha(src[0])) {
				std::string ident = "";
				while (!src.empty() && isAlpha(src[0])) {
					ident += popFrontSrc();
				}

				// check for reserved keywords
				if (KEYWORDS.find(ident) == KEYWORDS.end()) {
					tokens.push_back(token(ident, TokenType::IDENTIFIER));
				}
				else {
					TokenType reserved = KEYWORDS.at(ident);
					tokens.push_back(token(ident, reserved));
				}
			}
			else if (isSkippable(src[0])) {
				popFrontSrc();
			}
			else {
				std::cout << "Unrecognized character found in source: [" << (int)src[0] << ']' << std::endl;
				exit(1);
			}
		}
	}

	return tokens;
}