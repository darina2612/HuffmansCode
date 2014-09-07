#include <iostream>
#include "Compress.h"

using namespace std;

Vector<HuffmanTree*> toDelete;

unsigned long* ReadFile(const char* fileName)
{
	ifstream file;
	file.open(fileName);

	if(!file)
	{
		cout<<"Can't open\""<<fileName<<"\""<<endl;
		return NULL;
	}

	unsigned long* symbolsFrequency = new unsigned long [SYMBOLS_NUMBER];

	for(size_t i=0; i < SYMBOLS_NUMBER; ++i)
	{
		symbolsFrequency[i]=0;
	}

	char ch;
	while(file)
	{
		file.get(ch);
		symbolsFrequency[(int)ch]++;
	}

	return symbolsFrequency;
}

void SetHeap(MinHeap <HuffmanTree> & heap, unsigned long* freqs, size_t freqsSize)
{
	for(size_t i=0; i < freqsSize; ++i)
	{
		HuffmanTree leaf ((char)i, freqs[i]);

		if(freqs[i] >0)
		{
			heap.Push(leaf);
		}
	}
}

bool IsBuilt(const MinHeap<HuffmanTree> h)
{
	return h.GetSize()==1;
}

HuffmanTree* BuildEncodingTree(const char* fileName, unsigned long *& symbolsFreqs, int & symbolsAppearedNumber)  //??
{
	MinHeap<HuffmanTree> heap(SYMBOLS_NUMBER);

	symbolsFreqs=ReadFile(fileName);

	SetHeap(heap, symbolsFreqs,SYMBOLS_NUMBER);

	symbolsAppearedNumber=heap.GetSize();

	while(heap.GetSize() > 1)
	{
		HuffmanTree* leftSubtree = new HuffmanTree(*(heap.GetMin()));
		HuffmanTree* rightSubtree = new HuffmanTree(*(heap.GetMin()));

		toDelete.Push(leftSubtree);
		toDelete.Push(rightSubtree);

		HuffmanTree* parentTree = new HuffmanTree(*leftSubtree, *rightSubtree);
		heap.Push(*parentTree);
	}

	HuffmanTree* result;
	result=heap.GetMin();

	return result;
}

void WriteBinaryFile(const char* outFileName, const char* inFileName)
{
	ofstream file;
	file.open(outFileName, ios::binary);

	if(!file)
	{
		cout<<"Can't open \""<<outFileName<<"\""<<endl;
		return;
	}

	char* tableToEncode [SYMBOLS_NUMBER];
	for(size_t i=0; i < SYMBOLS_NUMBER; ++i)
	{
		tableToEncode[i]=NULL;
	}

	int tableToWriteSize=0;

	CodeNode* codeTable;
	codeTable=Encode(inFileName, tableToEncode, tableToWriteSize);

	BinaryString bitsetToWrite;

	ifstream source;
	source.open(inFileName);

	if(!source)
	{
		cout<<"Can't open \""<<inFileName<<"\""<<endl;
		return;
	}

	unsigned long i=0;
	while(source)
	{
		char ch;
		source.get(ch);
		int index=(int) ch;

		WriteInBinaryString(tableToEncode[index], bitsetToWrite, i);
	}

	file.write((const char*) &tableToWriteSize, sizeof(int));
	file.write((const char*) codeTable, tableToWriteSize*sizeof(CodeNode));

	file.write((const char*) & i, sizeof(unsigned long));

	file.write((const char*) bitsetToWrite.GetString(), bitsetToWrite.Size()*sizeof(unsigned char));

}

CodeNode* Encode(const char* fileName,char** toEncode, int & symbolsNum)
{
	unsigned long* symbolsFrequencies;
	HuffmanTree* huffTree;
	size_t j=0;

	huffTree=BuildEncodingTree(fileName, symbolsFrequencies,symbolsNum);

	CodeNode* codeTableToWrite = new CodeNode[symbolsNum];

	for(size_t i=0; i < SYMBOLS_NUMBER; ++i)
	{
		if(symbolsFrequencies[i] > 0)
		{
			Vector<char> symbIcode;
			char symbI=(char) i;



			huffTree->EncodeSymbol((char)i, symbIcode);
			toEncode[i]=new char [symbIcode.Size()];
			ToString(symbIcode, toEncode[i]);

			codeTableToWrite[j].ch=symbI;
			codeTableToWrite[j].frequency=symbolsFrequencies[i];

			++j;
		}

	}

	return codeTableToWrite;
}

void ToString (Vector<char> & v, char* str)
{
	for(size_t i=0; i < v.Size(); ++i)
	{
		str[i]=v[i];
	}
}

void WriteInBinaryString (char* codeString, BinaryString& bitString, unsigned long& lastSetIndex )//??
{

	while(*codeString)
	{
		//cout<<lastSetIndex<<" ";
		if(*codeString == '1')
		{

			bitString.Set(lastSetIndex);
		}
		else
		{
			bitString.Clear(lastSetIndex);
		}
		++codeString;
		lastSetIndex++;
	}
}

void FreeMemory()
{
	for(size_t i=0; i < toDelete.Size(); ++i)
	{
		delete toDelete[i];
	}
}
