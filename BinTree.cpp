#include<iostream>
#include "BinTree.h"

using namespace std;

Node::Node()
{
	this->subtreesWeight=0;
	this->left=this->right=NULL;
}

Node::Node(char val, size_t weight)
{
	this->value=val;
	this->subtreesWeight=weight;
	this->left=this->right=NULL;
}

HuffmanTree::HuffmanTree()
{
	this->root=NULL;
}

HuffmanTree::HuffmanTree(char rootVal, size_t rWeight)
{
	this->root=new Node(rootVal, rWeight);
}

HuffmanTree::HuffmanTree(HuffmanTree& leftSubtree, HuffmanTree& rightSubtree)
{
	this->root=new Node;
	this->root->subtreesWeight=leftSubtree.root->subtreesWeight
						+ rightSubtree.root->subtreesWeight;
	this->root->left=leftSubtree.root;
	this->root->right=rightSubtree.root;
}

void HuffmanTree::Copy(Node* sourceRoot, Node*& destRoot)
{
	if(!sourceRoot)
	{
		return;
	}

	destRoot=new Node(sourceRoot->value, sourceRoot->subtreesWeight);
	this->Copy(sourceRoot->left, destRoot->left);
	this->Copy(sourceRoot->right, destRoot->right);
}

void HuffmanTree::Delete(Node*& root)
{
	if(!root)
	{
		return;
	}

	this->Delete(root->left);
	this->Delete(root->right);

	delete root;
	root=NULL;
}

HuffmanTree::HuffmanTree(const HuffmanTree& hTree)
{
	this->Copy(hTree.root, this->root);
}

HuffmanTree& HuffmanTree::operator = (const HuffmanTree& hTree)
{
	if(this != &hTree)
	{
		this->Delete(this->root);
		this->Copy(hTree.root, this->root);
	}

	return *this;
}

HuffmanTree::~HuffmanTree()
{
	this->Delete(this->root);
}

bool HuffmanTree::operator > (const HuffmanTree & tree) const
{
	return this->root->subtreesWeight > tree.root->subtreesWeight;
}

bool HuffmanTree::operator == (const HuffmanTree & tree) const
{
	return this->root->subtreesWeight == tree.root->subtreesWeight;
}

bool HuffmanTree::operator < (const HuffmanTree & tree) const
{
	return !(this->operator == (tree)) && !(this->operator > (tree));
}

bool HuffmanTree::operator >= (const HuffmanTree & tree) const
{
	return !(this->operator < (tree));
}

bool HuffmanTree::operator <= (const HuffmanTree & tree) const
{
	return !(this->operator > (tree));
}

char HuffmanTree::GetRootValue() const
{
	return this->root->value;
}

size_t HuffmanTree::GetRootWeight() const
{
	return this->root->subtreesWeight;
}

Node* HuffmanTree::GetRoot() const
{
	return this->root;
}

bool HuffmanTree::IsLeaf(Node* node) const
{
	return ( (node->left==NULL) && (node->right==NULL) );
}

bool HuffmanTree::ContainsSymbol(Node* root, const char symbol)
{
	if(!root)
		return false;

	if(this->IsLeaf(root) && root->value == symbol)
		return true;

	else
	{
		if(this->ContainsSymbol(root->left, symbol))
			return true;

		else
		{
			return this->ContainsSymbol(root->right, symbol);
		}
	}
}

void HuffmanTree::EncodeSymbol(const char symbol, Vector<char>& code)
{
	bool isEncoded=false;
	Node* node=this->root;

	while(!isEncoded)
	{
		if(this->IsLeaf(node))
		{
			isEncoded=true;
			code.Push('\0');
		}
        else
		{
			if(this->ContainsSymbol(node->left, symbol))
			{
				code.Push('0');
				node=node->left;
			}

			else
			{
				code.Push('1');
				node=node->right;
			}
		}
	}
}

void HuffmanTree::Print(Node* root, ostream& os) const
{
	if(!root)
		return;

	os<<root->value<<" - "<<root->subtreesWeight<<' ';

	this->Print(root->left, os);
	this->Print(root->right, os);
}

void HuffmanTree::Print(ostream& os) const
{
	this->Print(this->root, os);
	os<<endl;
}

ostream& operator << (ostream& os, const HuffmanTree& tree)
{
	tree.Print(os);
	return os;
}
