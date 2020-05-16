#ifndef _KongaSet_
#define _KongaSet_

#include "KongaQueue.h"

class KongaSet
{
public:
	KongaSet();
	KongaSet(const KongaSet& other);
	KongaSet& operator=(const KongaSet& other);
	~KongaSet();

	void append(const char* name, const char* uni, unsigned index); 
	void removeLast(unsigned index); 
	void removeFirst(unsigned index); 
	void remove(const char* name, unsigned index);
	void merge(unsigned index1, unsigned index2);
	void print() const;

private:
	void copyFrom(const KongaSet& other); 
	void free(); 
	void resizeIfNeeded(); 

private:
	KongaQueue** arr;
	size_t size;
	size_t used;
};

#endif //_KongaSet_