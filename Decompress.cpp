#include <iostream>
#include <fstream>
#include <cstring>
#include "BinTree.h"
#include "MinHeap.h"
#include "BinaryString.h"
#include "Vector.h"
#include "Compress.h"
#include "Decompress.h"

using namespace std;

extern Vector<HuffmanTree*> toDelete;

unsigned long* ReadBinaryFile( const char* fileName, unsigned long& bitsToRead, unsigned char*& bytes )
{
	ifstream file;
	file.open(fileName, ios::binary);

	if(!file)
	{
		cout<<"Can't open \""<<fileName<<"\"";
		return NULL;
	}

	int symbolsAppearedNum;

	file.read((char*) &symbolsAppearedNum, sizeof(int));

	CodeNode* symbolsAppeared = new CodeNode [symbolsAppearedNum];

	file.read((char*) symbolsAppeared, symbolsAppearedNum*sizeof(CodeNode));

	unsigned long * result = new unsigned long [SYMBOLS_NUMBER];

	for(size_t i=0; i < SYMBOLS_NUMBER; ++i)
	{
		result[i]=0;
	}

	for(size_t i=0; i < symbolsAppearedNum; ++i)
	{
		int index=(int)symbolsAppeared[i].ch;
		result[index]=symbolsAppeared[i].frequency;
	}


	file.read((char*)& bitsToRead, sizeof(unsigned long));

	unsigned long bytesToRead=(bitsToRead/8)+1;

	unsigned char* bytesRead= new unsigned char [bytesToRead];

	memset(bytesRead, 0, bytesToRead);

	file.read((char*) bytesRead, bytesToRead*sizeof(unsigned char));

	bytes=bytesRead;

	return result;
}

void BuildDecodingTree(unsigned long* freqs, HuffmanTree*& tree)
{
	MinHeap<HuffmanTree> heap(SYMBOLS_NUMBER);
	SetHeap(heap, freqs,SYMBOLS_NUMBER);

	while(heap.GetSize() > 1)
	{
		HuffmanTree* leftSubtree = new HuffmanTree(*(heap.GetMin()));
		HuffmanTree* rightSubtree = new HuffmanTree(*(heap.GetMin()));

		toDelete.Push(leftSubtree);
		toDelete.Push(rightSubtree);

		HuffmanTree* parentTree = new HuffmanTree(*leftSubtree, *rightSubtree);
		heap.Push(*parentTree);
	}

	tree=heap.GetMin();
}

void Decompress(const char* binFileName, const char* outFileName)
{
	unsigned long bitsToDecode;
	unsigned char* code;

	unsigned long * frequencies=ReadBinaryFile(binFileName, bitsToDecode, code);

	HuffmanTree* decodingTree;

	BuildDecodingTree(frequencies, decodingTree);

	Node* node=decodingTree->GetRoot();
	Node* tmp = node->left->right->right;

	ofstream outFile;
	outFile.open(outFileName);

	if(!outFile)
	{
		cout<<"Can't open \""<<outFileName<<"\"";
		return;
	}

	for(size_t i =0; i < bitsToDecode; ++i)
	{
		if(decodingTree->IsLeaf(node))
		{
			outFile<<node->value;
			node=decodingTree->GetRoot();
		}


		if((code[i/8]>>(8-(i % 8)-1)) & 1)
		{
			node=node->right;
		}

		else
		{
			node=node->left;
		}

	}
}

