#ifndef MINHEAP_H_INCLUDED
#define MINHEAP_H_INCLUDED

using namespace std;

const int INVALID_INDEX=0;

struct Children
{
	size_t left;
	size_t right;
};

template <typename T>
class MinHeap
{
private:
	T* heap;
	size_t maxSize;
	size_t currentSize;

	void Copy(const MinHeap<T> & heap);
	void Delete();
	void Resize(size_t newSize);

	size_t GetParent(size_t index);
	Children GetChildren(size_t index);

	void HeapifyUp(size_t index);
	void HeapifyDown(size_t index);
public:
	MinHeap(size_t maxSize);
	MinHeap(const MinHeap<T> & heap);
	MinHeap<T> & operator = (const MinHeap<T> & heap);
	~MinHeap();

	T* GetMin();
	void Push(T elem);

	bool IsEmpty()const;
	bool IsFull()const;

	size_t GetSize() const;

	void Print()const;
};

template <typename T>
MinHeap<T>::MinHeap(size_t maxSize)
{
	this->maxSize=maxSize;
	this->heap=new T[this->maxSize];
	this->currentSize=0;
}

template <typename T>
MinHeap<T>::MinHeap(const MinHeap<T> & heap)
{
	this->Copy(heap);
}

template <typename T>
MinHeap<T>& MinHeap<T>::operator = (const MinHeap<T> & heap)
{
	if(this != &heap)
	{
		this->Delete();
		this->Copy(heap);
	}

	return *this;
}

template <typename T>
MinHeap<T>::~MinHeap()
{
	this->Delete();
}

template <typename T>
void MinHeap<T>::Copy(const MinHeap<T> & heap)
{
	this->maxSize=heap.maxSize;
	this->heap=new T[this->maxSize];
	this->currentSize=heap.currentSize;
	for(size_t i=1; i < heap.currentSize; ++i)
	{
		this->heap[i]=heap.heap[i];
	}
}

template <typename T>
void MinHeap<T>::Delete()
{
	delete[] this->heap;
}

template <typename T>
void MinHeap<T>::Resize(size_t newSize)
{
	this->maxSize=newSize;
	T* temp=new T[this->maxSize];

	for(size_t i=1; i <= this->currentSize; i++)
	{
		temp[i]=this->heap[i];
	}

	this->Delete();
	this->heap=temp;
}

template <typename T>
size_t MinHeap<T>::GetParent(size_t index)
{
	return index/2;
}

template <typename T>
Children MinHeap<T>::GetChildren(size_t index)
{
	Children children;

	size_t leftChild=2*index;
	if(leftChild <= this->currentSize)
	{
		children.left=leftChild;
	}
	else
	{
		children.left=INVALID_INDEX;
	}

	size_t rightChild=2*index+1;
	if(rightChild <= this->currentSize)
	{
		children.right=rightChild;
	}
	else
	{
		children.right=INVALID_INDEX;
	}

	return children;
}

template <typename T>
bool MinHeap<T>::IsEmpty()const
{
	return this->currentSize==0;
}

template <typename T>
bool MinHeap<T>::IsFull() const
{
	return this->currentSize + 1 == this->maxSize;
}

template <typename T>
void MinHeap<T>::HeapifyUp(size_t index)
{
	size_t parent=GetParent(index);

	if(parent == 0 || this->heap[parent]<=this->heap[index])
		return;

	swap(this->heap[index], this->heap[parent]);
	this->HeapifyUp(parent);
}

template <typename T>
void MinHeap<T>::HeapifyDown(size_t index)
{
	size_t left, right, lesserElIndex=index;

	Children indexChildren=GetChildren(index);
	left=indexChildren.left;
	right=indexChildren.right;

	if(left != INVALID_INDEX && this->heap[left] < this->heap[lesserElIndex])
	{
		lesserElIndex=left;
	}

	if(right != INVALID_INDEX && this->heap[right] < this->heap[lesserElIndex])
	{
		lesserElIndex=right;
	}

	if(lesserElIndex != index)
	{
		swap(this->heap[index], this->heap[lesserElIndex]);
		this->HeapifyDown(lesserElIndex);
	}
}

template <typename T>
T* MinHeap<T>::GetMin()
{
	T* minElement=new T;

	if(this->IsEmpty())
	{
		return NULL;
	}

	else
	{
		*minElement=this->heap[1];
	}

	swap(this->heap[1], this->heap[currentSize]);
	--(this->currentSize);
	this->HeapifyDown(1);

	return minElement;
}

template <typename T>
void MinHeap<T>::Push(T elem)
{
	if(this->IsFull())
	{
		this->Resize(this->maxSize*2);
		this->maxSize*=2;
	}

	this->currentSize++;
	this->heap[this->currentSize]=elem;

	HeapifyUp(this->currentSize);
}

template <typename T>
size_t MinHeap<T>::GetSize() const
{
	return this->currentSize;
}

template <typename T>
void MinHeap<T>::Print()const
{
	if (this->IsEmpty())
	{
		cout<<"Empty heap"<<endl;
		return;
	}

	for (size_t i=1; i <= this->currentSize; ++i)
	{
		cout<<this->heap[i]<< " ";
	}
	cout<<endl;
}

#endif // MINHEAP_H_INCLUDED
