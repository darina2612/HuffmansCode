#ifndef DECOMPRESS_H_INCLUDED
#define DECOMPRESS_H_INCLUDED

#include <iostream>
#include <fstream>
#include "BinTree.h"
#include "MinHeap.h"
#include "BinaryString.h"
#include "Vector.h"
#include "Decompress.h"

using namespace std;

unsigned long* ReadBinaryFile( const char* fileName, unsigned long& bitsToRead, unsigned char*& bytes);

void BuildDecodingTree(unsigned long* freqs, HuffmanTree*& tree);

void Decompress(const char* binFileName, const char* outFileNme);
#endif // DECOMPRESS_H_INCLUDED
