#include "BinaryString.h"
#include <iostream>
#include <cstring>

using namespace std;

BinaryString::BinaryString(unsigned long size)
{
	this->size=size;
	this->bString=new unsigned char [this->size];
	memset(this->bString, 0, size);
}


BinaryString::BinaryString(const BinaryString& binStr)
{
	this->Copy(binStr);
}

BinaryString& BinaryString::operator = (const BinaryString& binStr)
{
	if(this != &binStr)
	{
		this->Delete();
		this->Copy(binStr);
	}

	return *this;
}


BinaryString::~BinaryString()
{
	this->Delete();
}


void BinaryString::Copy(const BinaryString& binStr)
{
	this->size=binStr.size;
	this->bString=new unsigned char [this->size];

	memcpy(this->bString, binStr.bString, this->size);
}

void BinaryString::Delete()
{
	delete [] this->bString;
}

void BinaryString::Resize(size_t newSize)
{
	unsigned char* temp = new unsigned char [newSize];

	memset(temp, 0, newSize);
	memcpy(temp, this->bString, this->size);

	this->size=newSize;

	delete [] this->bString;

	this->bString = temp;
}

void BinaryString::Set(unsigned long index)
{
	if(index >= this->size*8)
	{
		this->Resize(this->size*2);
	}

	this->bString [index/8] |= (1<<(8-(index%8)-1));

}


void BinaryString::Clear(unsigned long index)
{
	if(index >= this->size*8)
	{
		this->Resize(this->size*2);
	}

	this->bString[index/8] &= ~(1<<(8-(index%8)-1));
}

ostream& operator << (ostream & os, const BinaryString& binStr)
{
	cout<<binStr.bString;

	return os;
}


unsigned char* BinaryString::GetString() const
{
	return this->bString;
}

unsigned char& BinaryString::operator [] (unsigned long index)
{
	return this->bString[index];
}

unsigned long BinaryString::Size() const
{
	return this->size;
}
