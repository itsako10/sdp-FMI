#ifndef _BROWSER_
#define _BROWSER_

class Browser
{
private:
	struct Tab
	{
		Tab(const char* URL);
		Tab(const Tab& other);
		Tab& operator=(const Tab& other);
		~Tab();

		void setURL(const char* URL);
		void setTimestamp();

		void print() const;

		char* URL;
		int timestamp;
		Tab* next;
		Tab* prev;
	};

public:
	Browser();
	Browser(const Browser& other);
	Browser& operator=(const Browser& other);
	~Browser();

	void go(const char* URL);
	void insert(const char* URL);
	void back();
	void forward();
	void remove();
	void print() const;

private:
	void copyFrom(const Browser& other);
	void free();

private:
	Tab* current;
	Tab* first;
};

#endif //_BROWSER_