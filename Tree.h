#pragma once

#include <unordered_map>
#include <map>
#include <string>

class CodeTree
{
	struct Node
	{
		Node* left{}, * right{};
		size_t count;
		char c{}, value;

		Node(char c, size_t count) : c(c), count(count), value(c) {}
		Node(Node* left, Node* right);
	}* root;
public:
	CodeTree(std::string const& str);
	CodeTree(CodeTree const&) = delete;
	CodeTree(CodeTree &&) = delete;
	CodeTree& operator=(CodeTree const&) = delete;
	CodeTree& operator=(CodeTree&&) = delete;
	std::unordered_map<char, std::string> getCodes() const;
	~CodeTree();
};


std::string encode(std::string const&, std::unordered_map<char, std::string> const&);
std::string encode(std::string const&);
std::string encodeAndGetCodes(std::string const&, std::unordered_map<char, std::string>&);
std::string decode(std::string const&, std::map<char, std::string> const&);