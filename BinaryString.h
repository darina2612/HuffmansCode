#ifndef BINARYSTRING_H_INCLUDED
#define BINARYSTRING_H_INCLUDED
#include <iostream>
using namespace std;

class BinaryString
{
private:
	unsigned char* bString;
	unsigned long size;

	void Copy(const BinaryString& binStr);
	void Delete();

	void Resize(unsigned long newSize);
public:
	BinaryString(unsigned long size = 2);
	BinaryString(const BinaryString& binStr);
	BinaryString& operator = (const BinaryString& binStr);
	~BinaryString();

	void Set(unsigned long index);
	void Clear(unsigned long index);

	unsigned char* GetString() const;

	unsigned char& operator [] (unsigned long index);

	unsigned long Size() const;

	friend ostream& operator << (ostream & os, const BinaryString& binStr);
};

#endif // BINARYSTRING_H_INCLUDED

