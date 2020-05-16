#ifndef _HASH_
#define _HASH_

class Hash
{
public:
	struct Person
	{
		Person(const char* name);

		void setName(const char* name);

		char name[32];
		Person* left;
		Person* right;
		Person* next; //next in the list of the hash on same index
		bool hold_left;
		bool hold_right;
	};

public:
	Hash();
	~Hash();

	int hashFunc(const char* name);
	Person* find(const char* name);
	
	void release(const char* name, const char* lrb);
	void grap(const char* name, const char* lrb);
	void info(const char* name);
	void add(const char* name, const char* label_left, const char* label_right);
	void remove(const char* name);
	void swap(const char* name1, const char* name2);
	void print() const;
	void addFirst(const char* name);
	void addSecond(const char* name);
	void addThird(const char* name);
	Person* getFirst() const;

private:
	void resizeIfNeeded();

private:
	Person* first;
	Person** arr;
	int used;
	int size;
};

#endif // _HASH_