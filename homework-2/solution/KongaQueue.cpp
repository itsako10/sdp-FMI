#include "KongaQueue.h"
#include <iostream>
#include <cstring>

void stringCopy(char* dest, const char* source)
{
	int length = strlen(source);
	int i = 0;
	while (i < length)
	{
		dest[i] = source[i];
		++i;
	}
	dest[i] = '\0';
}

KongaQueue::Student::Student(const char* name, const char* uni) : name(NULL), uni(NULL), next(NULL), prev(NULL)
{
	setName(name);
	setUni(uni);
}

KongaQueue::Student::Student(const Student& other) : name(NULL), uni(NULL), next(NULL), prev(NULL)
{
	setName(other.name);
	setUni(other.uni);
}
KongaQueue::Student& KongaQueue::Student::operator=(const Student& other)
{
	if (this == &other)
	{
		return *this;
	}
	setName(other.name);
	setUni(other.uni);
	return *this;
}

KongaQueue::Student::~Student()
{
	delete[] this->name;
	delete[] this->uni;
	name = NULL;
	uni = NULL;
	next = NULL;
	prev = NULL;
}

void KongaQueue::Student::setName(const char* name)
{
	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	stringCopy(this->name, name);
}

void KongaQueue::Student::setUni(const char* uni)
{
	delete[] this->uni;
	this->uni = new char[strlen(uni) + 1];
	stringCopy(this->uni, uni);
}

void KongaQueue::Student::print() const
{
	std::cout << "(" << this->name << ", " << this->uni << ")";
}

KongaQueue::KongaQueue()
{
	Student* student = new Student("Integralcho", "fmi");
	first = student;
	last = student;
}

KongaQueue::KongaQueue(Student* first)
{
	this->first = first;
	first->prev = NULL;

	if (first->next == NULL)
	{
		this->last = first;
	}
	else
	{
		for (Student* i = first; i != NULL; i->next)
		{
			this->last = i;
		}
	}
}

KongaQueue::KongaQueue(const KongaQueue& other)
{
	copyFrom(other);
}

KongaQueue& KongaQueue::operator=(const KongaQueue& other)
{
	if (this == &other)
	{
		return *this;
	}
	free();
	copyFrom(other);
	return *this;
}

KongaQueue::~KongaQueue()
{
	free();
}

void KongaQueue::copyFrom(const KongaQueue& other)
{
	Student* helper_first = new Student(other.first->name, other.first->uni);
	this->first = helper_first;
	this->last = helper_first;;
	for (Student* i = other.first->next; i != NULL; i = i->next)
	{
		this->append(i->name, i->uni);
	}
}

void KongaQueue::free()
{	
	for (Student* i = this->first; i != NULL;)
	{
		Student* helper_next = i->next;
		removeFirst();
		i = helper_next;
	}
	this->first = NULL;
	this->last = NULL;
}

void KongaQueue::append(const char* name, const char* uni)
{
	Student* student = new Student(name, uni);
	
	if (strcmp(uni, "fmi") == 0)
	{
		if (strcmp(last->uni, "unss") == 0)
		{
			std::cout << "Incompatible people" << '\n';
		}
		else
		{
			student->prev = this->last;
			student->next = NULL;
			last->next = student;
			last = student;
		}
	}
	else if (strcmp(uni, "tu") == 0)
	{
		if (strcmp(last->uni, "fmi") == 0)
		{
			std::cout << "Incompatible people" << '\n';
		}
		else
		{
			student->prev = this->last;
			student->next = NULL;
			last->next = student;
			last = student;
		}
	}
	else if (strcmp(uni, "unss") == 0)
	{
		if (strcmp(last->uni, "tu") == 0)
		{
			std::cout << "Incompatible people" << '\n';
		}
		else
		{
			student->prev = this->last;
			student->next = NULL;
			last->next = student;
			last = student;
		}
	}
	else
	{
		std::cout << "Unknown uni!" << '\n';
	}
}

void KongaQueue::removeLast()
{
	if (first == last)
	{
		delete first;
		this->first = NULL;
		this->last = NULL;
		return;
	}
	Student* helper = last;
	last = last->prev;
	last->next = NULL;
	delete helper;
}

void KongaQueue::removeFirst()
{
	if (first == last)
	{
		delete first;
		this->first = NULL;
		this->last = NULL;
	}
	else
	{
		Student* helper = first;
		first = first->next;
		first->prev = NULL;
		delete helper;
	}
}

KongaQueue* KongaQueue::remove(const char* name)
{
	if (strcmp(first->name, name) == 0)
	{
		removeFirst();
		return NULL;
	}
	for (Student* i = first; i != last; i = i->next)
	{
		if (strcmp(i->name, name) == 0)
		{
			Student* helper_new_last = i;
			Student* new_first = i->next;
			KongaQueue* new_konga_queue = new KongaQueue(new_first);
			this->last = helper_new_last;
			this->last->next = NULL;
			removeLast();
			return new_konga_queue;
		}
	}
	if (strcmp(last->name, name) == 0)
	{
		removeLast();
		return NULL;
	}
}

void KongaQueue::print() const
{
	Student* i = this->first;
	//внасям допълнение в сравнение с предаденото домашно
	if (i == NULL)
	{
		return;
	}
	//край на допълнението
	while (i->next != NULL)
	{
		i->print();
		std::cout << " - ";
		i = i->next;
	}
	i->print();
	std::cout << '\n';
}

KongaQueue::Student* KongaQueue::getFirst() const
{
	return this->first;
}

KongaQueue::Student* KongaQueue::getLast() const
{
	return this->last;
}
