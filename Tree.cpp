#include "Tree.h"
#include <stack>
#include <map>
#include <queue>

using namespace std;


std::string encode(std::string const& in)
{
	CodeTree tree(in);
	auto codes = tree.getCodes();
	return encode(in, codes);
}

std::string encodeAndGetCodes(std::string const& in, std::unordered_map<char, std::string>& codes)
{
	CodeTree tree(in);
	codes = tree.getCodes();
	return encode(in, codes);
}

std::string decode(std::string const& in, std::map<char, std::string> const& codes)
{
	std::unordered_map<std::string, char> invcodes;
	for (auto const& p : codes)
		invcodes.insert({ p.second, p.first });
	string out;
	string code;
	for (char c : in)
	{
		code += c;
		if (invcodes.find(code) != invcodes.end())
		{
			out += invcodes.at(code);
			code.clear();
		}
	}

	return out;
}

std::string encode(std::string const& in, std::unordered_map<char, std::string> const& codes)
{
	string out;
	for (char c : in)
		out += codes.at(c);

	return out;
}

CodeTree::Node::Node(Node* left, Node* right) : left(left), right(right), count(left->count + right->count), value(std::min(left->value, right->value)){}

CodeTree::CodeTree(std::string const& str)
{
	size_t map[256] = {};
	for (size_t i = 0; i < str.size(); ++i)
		++map[str[i]];
	auto comparator = [](Node* a, Node* b) {
		return a->count > b->count; };
	priority_queue<Node*, vector<Node*>, decltype(comparator)> pq(comparator);
	for (int i = 0; i < 256; i++)
		if (map[i])
			pq.push(new Node(i, map[i]));


	
	while (pq.size() > 1)
	{
		Node* l = pq.top();
		pq.pop();
		Node* r = pq.top();
		pq.pop();
		pq.push(new Node(l, r));
	}

	root = pq.top();
}

std::unordered_map<char, std::string> CodeTree::getCodes() const
{
	Node const* n = root;
	std::unordered_map<char, std::string> m;
	string str;
	size_t len = 0;
	stack<pair<Node const*, size_t>> st;

	while (n || !st.empty())
	{
		if (n && n->c)
		{
			m[n->c] = str;
			if (st.empty())
				n = nullptr;
			else
			{
				auto p = st.top();
				st.pop();
				n = p.first;
				str.resize(p.second);
				str += '1';
			}
		}
		else if (n)
		{
			st.push({ n->right, str.size() });
			n = n->left;
			str += '0';
			len++;
		}
	}

	return m;
}

CodeTree::~CodeTree()
{
	stack<Node*> s;
	while (root || !s.empty())
	{
		if (!root)
		{
			root = s.top();
			s.pop();
		}
		if (root->right)
			s.push(root->right);
		auto left = root->left;
		delete root;
		root = left;
	}
}
