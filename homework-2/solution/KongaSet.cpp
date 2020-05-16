#include "KongaSet.h"
#include "KongaQueue.h"
#include <iostream>

const int MAX_UNI_NAME = 4;

KongaSet::KongaSet()
{
	arr = new KongaQueue*[1];
	arr[0] = new KongaQueue;
	size = 1;
	used = 0;
}

KongaSet::KongaSet(const KongaSet& other)
{
	copyFrom(other);
}

KongaSet& KongaSet::operator=(const KongaSet& other)
{
	if (this == &other)
	{
		return *this;
	}
	free();
	copyFrom(other);
	return *this;
}

void KongaSet::copyFrom(const KongaSet& other)
{
	this->arr = new KongaQueue*[other.size];
	for (int i = 0; i < other.size; ++i)
	{
		this->arr[i] = other.arr[i];
	}

	this->size = other.size;
	this->used = other.used;
}

void KongaSet::resizeIfNeeded()
{
	if (size == (used + 1))
	{
		int new_size = size * 2;
		KongaQueue** helper_arr = new KongaQueue*[new_size];
		for (int i = 0; i < size; ++i)
		{
			helper_arr[i] = this->arr[i];
		}
		this->size = size * 2;
		delete[] arr;
		arr = helper_arr;
	}
}

void KongaSet::free()
{
	for (int i = 0; i < used; ++i)
	{
		delete arr[i];
	}
	delete[] arr;
}

KongaSet::~KongaSet()
{
	free();
}

void KongaSet::print() const
{
	for (int i = 0; i <= used; ++i)
	{
		std::cout << "Line" << i << ": ";
		arr[i]->print();
	}
}

void KongaSet::append(const char* name, const char* uni, unsigned line_index)
{
	if (line_index > used)
	{
		std::cout << "Invalid index!" << std::endl;
		return;
	}
	arr[line_index]->append(name, uni);
}

void KongaSet::removeLast(unsigned line_index)
{
	if (line_index > used)
	{
		std::cout << "Invalid index!" << std::endl;
		return;
	}
	/*if (arr[line_index]->getFirst() == NULL)
	{
		return;
	}*/
	arr[line_index]->removeLast();
	if (arr[line_index]->getFirst() == NULL)
	{
		delete arr[line_index];
		for (int i = line_index; i < used; ++i)
		{
			arr[i] = arr[i + 1];
		}
		--used;
	}
}

void KongaSet::removeFirst(unsigned line_index)
{
	if (line_index > used)
	{
		std::cout << "Invalid index!" << std::endl;
		return;
	}
	arr[line_index]->removeFirst();
	if (arr[line_index]->getFirst() == NULL)
	{
		delete arr[line_index];
		for (int i = line_index; i < used; ++i)
		{
			arr[i] = arr[i + 1];
		}
		--used;
	}
}

void KongaSet::merge(unsigned index1, unsigned index2)
{
	if (strcmp(arr[index2]->getFirst()->uni, "fmi") == 0)
	{
		if ((strcmp(arr[index1]->getLast()->uni, "fmi") == 0) || (strcmp(arr[index1]->getLast()->uni, "tu") == 0))
		{
			arr[index1]->getLast()->next = arr[index2]->getFirst();
			arr[index2]->getFirst()->prev = arr[index1]->getLast();
			delete arr[index2];
			for (int i = index2; i < used; ++i)
			{
				arr[i] = arr[i + 1];
			}
			--used;
		}
		else if (strcmp(arr[index1]->getLast()->uni, "unss") == 0)
		{
			std::cout << "Incompatible people" << std::endl;
		}
		else
		{
			std::cout << "Unknown uni!" << '\n';
		}
	}
	else if (strcmp(arr[index2]->getFirst()->uni, "tu") == 0)
	{
		if ((strcmp(arr[index1]->getLast()->uni, "tu") == 0) || (strcmp(arr[index1]->getLast()->uni, "unss") == 0))
		{
			arr[index1]->getLast()->next = arr[index2]->getFirst();
			arr[index2]->getFirst()->prev = arr[index1]->getLast();
			delete arr[index2];
			for (int i = index2; i < used; ++i)
			{
				arr[i] = arr[i + 1];
			}
			--used;
		}
		else if (strcmp(arr[index1]->getLast()->uni, "fmi") == 0)
		{
			std::cout << "Incompatible people" << std::endl;
		}
		else
		{
			std::cout << "Unknown uni!" << '\n';
		}
	}
	else if (strcmp(arr[index2]->getFirst()->uni, "unss") == 0)
	{
		if ((strcmp(arr[index1]->getLast()->uni, "unss") == 0) || (strcmp(arr[index1]->getLast()->uni, "fmi") == 0))
		{
			arr[index1]->getLast()->next = arr[index2]->getFirst();
			arr[index2]->getFirst()->prev = arr[index1]->getLast();
			delete arr[index2];
			for (int i = index2; i < used; ++i)
			{
				arr[i] = arr[i + 1];
			}
			--used;
		}
		else if (strcmp(arr[index1]->getLast()->uni, "tu") == 0)
		{
			std::cout << "Incompatible people" << std::endl;
		}
		else
		{
			std::cout << "Unknown uni!" << '\n';
		}
	}
}

void KongaSet::remove(const char* name, unsigned index)
{
	KongaQueue* helper = arr[index]->remove(name);
	
	if (arr[index]->getFirst() == NULL)
	{
		delete arr[index];
		for (int i = index; i < used; ++i)
		{
			arr[i] = arr[i + 1];
		}
		--used;
	}

	if (helper == NULL)
	{
		return;
	}

	resizeIfNeeded();
	arr[used + 1] = helper;
	++used;
}