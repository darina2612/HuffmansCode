#include <iostream>
#include <fstream>
#include "BinTree.h"
#include "MinHeap.h"
#include "BinaryString.cpp"
#include "Compress.h"
#include "Decompress.h"

using namespace std;

extern Vector< HuffmanTree* > toDelete;

int main()
{

	//WriteBinaryFile("compr","text");

	Decompress("compr", "decompressed");


	FreeMemory();

	return 0;
}
