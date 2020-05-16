#ifndef _KongaQueue_
#define _KongaQueue_

class KongaQueue
{
private:
	struct Student
	{
		Student(const char* name, const char* uni);
		Student(const Student& other);
		Student& operator=(const Student& other);
		~Student();

		void setName(const char* name);
		void setUni(const char* uni);

		void print() const;

		char* name;
		char* uni;
		Student* next;
		Student* prev;
	};

public:
	KongaQueue();
	KongaQueue(Student* first);
	KongaQueue(const KongaQueue& other);
	KongaQueue& operator=(const KongaQueue& other);
	~KongaQueue();

	void append(const char* name, const char* uni);
	void removeLast();
	void removeFirst();
	KongaQueue* remove(const char* name);
	void print() const;

	Student* getFirst() const;
	Student* getLast() const;

private:
	void copyFrom(const KongaQueue& other);
	void free();

private:
	Student* first;
	Student* last;
};

#endif //_KongaQueue_