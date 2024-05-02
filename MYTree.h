#pragma once
#include <stack>
#include <string>
#include <queue>
#include <map>

using namespace std;

class Tree {
private:
	struct Node {
		int value = 0;
		Node* left = NULL, * right = NULL;
		char c = 0;
		Node(char x, int val) {
			c = x;
			value = val;
		}
		Node(Node* leftson, Node* rightson) {
			left = leftson;
			right = rightson;
			value = leftson->value + rightson->value;
		}
	};
	Node* root;
	static void recurDelete(Node* a) {
		if (a)
		{
			recurDelete(a->left);
			recurDelete(a->right);
			delete a;
		}
	}
	static void recurFunc(Node* a, map<char, string>& m, string s) {
		if (a->c) {
			m[a->c] = s;
		}
		else {
			recurFunc(a->left, m, s + '0');
			recurFunc(a->right, m, s + '1');
		}
	}
public:

	Tree(const string& text) {
		int array[256] = { 0 };
		auto greaterPair = [](Node* a, Node* b) {return a->value > b->value; };
		priority_queue<Node*, vector<Node*>, decltype(greaterPair)> pq(greaterPair);
		for (char c : text)
			array[c]++;
		for (int i = 0; i < 256; i++)
			//for (int i = 255; i>= 0; i--)
			if (array[i]) {
				Node* n = new Node(i, array[i]);
				pq.push(n);
			}
		while (pq.size() > 1) {
			auto a = pq.top();
			pq.pop();
			auto b = pq.top();
			pq.pop();
			pq.push(new Node(a, b));
		}
		root = pq.top();
	}
	map<char, string> getCodeFromTree() {
		map<char, string> m;
		string s = "";
		recurFunc(root, m, s);
		return m;
	}
	~Tree() {
		recurDelete(root);
	}

};