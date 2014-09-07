#ifndef BINTREE_H_INCLUDED
#define BINTREE_H_INCLUDED
#include <iostream>
#include "Vector.h"
using namespace std;

struct Node
{
	char value;
	size_t subtreesWeight;
	Node * left, *right;

	Node();
	Node(char val, size_t weight=0);
};

class HuffmanTree
{
private:
	Node * root;

	void Copy(Node* sourceRoot, Node*& destRoot);
	void Delete(Node*& root);

	void Print(Node* root, ostream& os) const;
public:
	HuffmanTree();
	HuffmanTree(HuffmanTree& leftSubtree, HuffmanTree& rightSubtree);
	HuffmanTree(char rootVal, size_t rWeight=0);
	HuffmanTree(const HuffmanTree& hTree);
	HuffmanTree& operator =(const HuffmanTree& hTree);
	~HuffmanTree();

	bool operator > (const HuffmanTree & tree) const;
	bool operator == (const HuffmanTree & tree) const;
	bool operator < (const HuffmanTree & tree) const;
	bool operator >= (const HuffmanTree & tree) const;
	bool operator <= (const HuffmanTree & tree) const;

	char GetRootValue() const;
	size_t GetRootWeight() const;
	Node* GetRoot() const;

	bool IsLeaf(Node* node) const;

	bool ContainsSymbol(Node* root, const char symbol);
	void EncodeSymbol(const char symbol, Vector<char>& code);// if-ovete

	void Print(ostream& os) const;

	friend ostream& operator << (ostream& os, const HuffmanTree& tree);
};

#endif // BINTREE_H_INCLUDED
