#ifndef COMPRESS_H_INCLUDED
#define COMPRESS_H_INCLUDED

#include <iostream>
#include <fstream>
#include "BinTree.h"
#include "MinHeap.h"
#include "BinaryString.h"
#include "Vector.h"

using namespace std;

const size_t SYMBOLS_NUMBER=256;

struct CodeNode
{
	char ch;
	unsigned long frequency;
};

unsigned long* ReadFile(const char* fileName);

void SetHeap(MinHeap <HuffmanTree> & heap, unsigned long* ferqs, size_t freqsSize);

HuffmanTree* BuildEncodingTree(const char* fileName, unsigned long *& symbolsFreqs, int & symbolsAppearedNumber);

bool IsBuilt(const MinHeap<HuffmanTree> h);

void WriteBinaryFile(const char* outFileName, const char* inFileName);

void ToString (Vector<char> & v, char* str);

CodeNode* Encode(const char* fileName, char** toEncode, int & symbolsNum);

void WriteInBinaryString (char* codeString, BinaryString& bitString, unsigned long& lastSetIndex);

void FreeMemory();

#endif // COMPRESS_H_INCLUDED

