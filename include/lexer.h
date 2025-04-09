#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>

enum TokenType {
	UNDEFINED = -1,
	NUMBER,
	IDENTIFIER,
	EQUALS,
	OPEN_PAREN,
	CLOSE_PAREN,
	BINARY_OPERATOR,
	LET
};

const std::unordered_map<std::string, TokenType> KEYWORDS = {
	{"let", TokenType::LET}
};

struct Token {
	std::string m_value;
	TokenType m_type;

	Token() : m_value(""), m_type(TokenType::UNDEFINED) {}
	Token(const std::string& value, TokenType type) : m_value(value), m_type(type) {}
	virtual ~Token() = default;

	friend std::ostream& operator<<(std::ostream& os, const Token& tk) {
		os << '[' << tk.m_value << ", " << tk.m_type << ']';
		return os;
	}
};

static Token token(const std::string& value, TokenType type);
static bool isAlpha(const char& value);
static bool isInt(const char& value);
static bool isSkippable(const char& value);
std::vector<Token> tokenize(const std::string& sourceCode);