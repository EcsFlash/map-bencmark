#pragma once
#include <iostream>
#include <string>
using namespace std;
template<typename K, typename V>
class TreeMap{
protected:
	struct Node {
		K key;
		V value;
		int height;
		Node* left;
		Node* right;
		Node(K _key, V  _value) {
			key = _key;
			value = _value;
			height = 1;
			left = nullptr;
			right = nullptr;
		}
	};
	Node* root;
	
	struct transport {
		K k;
		V v;
		transport(K& _k, V& _v) {
			k = _k;
			v = _v;
		}
	};

	int Height(Node* node)
	{
		return node ? node->height : 0;
	}

	bool isEmpty()
	{
		return root == nullptr;
	}
	void commitHeight(Node* node)
	{
		if (!node)
		{
			return;
		}
		int left = Height(node->left);
		int right = Height(node->right);
		node->height = (left > right ? left : right) + 1;
	}

	int Bfactor(Node* node)
	{
		return  Height(node->right) - Height(node->left);
	}

	void RightRotation(Node*& p)
	{
		Node* q = p->left;
		p->left = q->right;
		q->right = p;
		commitHeight(p);
		commitHeight(q);
		p = q;
	}

	void LeftRotation(Node*& p)
	{
		Node* q = p->right;
		p->right = q->left;
		q->left = p;
		commitHeight(p);
		commitHeight(q);
		p = q;
	}

	void balance(Node*& p)
	{
		int bfactor = Bfactor(p);
		if (bfactor == 2)
		{
			if (Bfactor(p->right) < 0)
				RightRotation(p->right);
			LeftRotation(p);
		}

		if (bfactor == -2)
		{
			if (Bfactor(p->left) > 0)
				LeftRotation(p->left);
			RightRotation(p);
		}
		commitHeight(p);

	}

	void insert(Node*& node, const K& k, const V& v) {
		if (node == nullptr) {
			node = new Node(k, v);
		}
		else if (k < node->key) {
			iterations_i++;
			insert(node->left, k, v);
		}
		else if (k > node->key){
			iterations_i++;
			insert(node->right, k, v);
		}
		balance(node);

	}
	
	void clear(Node*& node)
	{
		if (node != nullptr)
		{
			clear(node->left);
			clear(node->right);
			delete node;
			node = nullptr;
		}
	}

	int getWidth(int height) const {
		if (height == 1) {
			return 1;
		}
		return 2 * getWidth(height - 1);
	}

	transport succesor(Node*& node) {
		if (node->right) {
			return succesor(node->right);
		}
		else {
			Node* temp = node;
			transport result(node->key, node->value);
			node = node->left;
			delete temp;
			temp = nullptr;
			return result;
		}
	}
	void remove(Node*& node, K& k) {
		if (node) {
			if (k < node->key) {
				iterations_r++;
				remove(node->left, k);
			}
			else if (k > node->key) {
				iterations_r++;
				remove(node->right, k);
			}
			else if (k == node->key) {
				if (node->left && node->right) {
					transport succ = succesor(node->left);
					node->key = succ.k;
					node->value = succ.v;
				}
				else if (node->left && !node->right) {
					Node* temp = node;
					node = node->left;
					delete temp;
					temp = nullptr;
				}
				else if (!node->left && node->right) {
					Node* temp = node;
					node = node->right;
					delete temp;
					temp = nullptr;
				}
				else if (!node->left && !node->right) {
					delete node;
					node = nullptr;
					return;
				}
				balance(node);
			}
		}
		else {
			throw invalid_argument("failed to remove");
		}
	}

	bool search(Node* node, K& k) {
		if (node) {
			if (k < node->key) {
				iterations_s++;
				return search(node->left, k);
			}
			else if (k > node->key) {
				iterations_s++;
				return search(node->right, k);
			}
			if (k == node->key) {
				return true;
			}
		}
		return false;
	}
	void prefixOrder(Node*& node) {
		if (node) {
			
			prefixOrder(node->left);
			cout << node->key << node->value << endl;
			prefixOrder(node->right);
			
		}
	}

public:
	int iterations_i, iterations_s, iterations_r;
	TreeMap() {
		iterations_i = iterations_s = iterations_r = 0;
		root = nullptr;
	}
	~TreeMap() {
		clear(root);
	}
	void print() {
		prefixOrder(root);
	}
	void Insert(const K& k, const V& v) {
		insert(root, k, v);
	}
	bool Search(K& k) {
		return search(root, k);
	}
	void Remove(K& k) {
		remove(root, k);
	}
};