#include "huffman.h"
#include "MYTree.h"

std::string encode(const std::string& text) {
	Tree t(text);
	string s = "";
	auto m = t.getCodeFromTree();
	for (auto c : text)
		s += m[c];
	return s;
}

std::string decode(const std::string& encoded, std::map<char, std::string>& codes) {
	string s = "";
	string ans = "";
	map<string, char> NORMcodes;
	for (auto f : codes)
		NORMcodes[f.second] = f.first;
	for (int i = 0; i < encoded.size(); i++) {
		s += encoded[i];
		if (NORMcodes.find(s) != NORMcodes.end()) {
			ans += NORMcodes[s];
			s = "";
		}
	}
	return ans;
}
