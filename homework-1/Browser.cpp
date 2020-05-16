#include "Browser.h"
#include <ctime>
#include <cstring>
#include <iostream>

Browser::Tab::Tab(const char* URL) :URL(NULL), next(NULL), prev(NULL)
{
	setURL(URL);
	setTimestamp();
}

Browser::Tab::Tab(const Tab& other) :URL(NULL), next(NULL), prev(NULL)
{
	setURL(other.URL);
	setTimestamp();
}

Browser::Tab& Browser::Tab::operator=(const Tab& other)
{
	if (this == &other)
	{
		return *this;
	}

	setURL(other.URL);
	setTimestamp();
	return *this;
}

Browser::Tab::~Tab()
{
	delete[] URL;
	URL = NULL;
	next = NULL;
	prev = NULL;
}

void Browser::Tab::setURL(const char* URL)
{
	delete[] this->URL;
	this->URL = new char[strlen(URL) + 1];
	strcpy(this->URL, URL);
}

void Browser::Tab::setTimestamp()
{
	this->timestamp = time(NULL);
}

void Browser::Tab::print() const
{
	std::cout << URL << ' ' << timestamp << '\n';
}

Browser::Browser()
{
	Tab* tab = new Tab("about:blank");
	current = tab;
	first = tab;
}

Browser::Browser(const Browser& other)
{
	copyFrom(other);
}

Browser& Browser::operator=(const Browser& other)
{
	if (this == &other)
	{
		return *this;
	}
	free();
	copyFrom(other);
	return *this;
}

Browser::~Browser()
{
	free();
}

void Browser::copyFrom(const Browser& other)
{
	Tab* helper_first = new Tab(other.first->URL);
	this->current = helper_first;
	this->first = helper_first;
	for (Tab* i = other.first->next; i != NULL; i = i->next)
	{
		this->insert(i->URL);
	}
}

void Browser::free()
{
	current = first;
	for (Tab* i = first; i->next != NULL;)
	{
		i = i->next;
		remove();
	}
	delete[] current->URL;
	current = NULL;
	first = NULL;
}

void Browser::go(const char* URL)
{
	current->setURL(URL);
	current->setTimestamp();
}

void Browser::insert(const char* URL)
{
	Tab* helper = new Tab(URL);
	helper->prev = current;
	helper->next = current->next;
	if (current->next != NULL)
	{
		current->next->prev = helper;
	}
	current->next = helper;
	current = helper;
}

void Browser::back()
{
	if (current->prev == NULL)
	{
		return;
	}
	else
	{
		current = current->prev;
	}
}

void Browser::forward()
{
	if (current->next == NULL)
	{
		return;
	}
	else
	{
		current = current->next;
	}
}

void Browser::remove()
{
	Tab* helper = current;
	if (current->next)
	{
		if (current == first)
		{
			first = first->next;
			first->prev = NULL;
			current = current->next;
		}
		else
		{
			current->prev->next = current->next;
			current->next->prev = current->prev;
			current = current->next;
		}
	}
	else if (current->prev)
	{
		current->prev->next = NULL;
		current = current->prev;
	}
	else
	{
		Browser* empty = new Browser();
		current = empty->current;
		first = empty->first;
	}
	delete helper;
}

void Browser::print() const
{
	for (Tab* i = first; i != NULL; i = i->next)
	{
		if (i == current)
		{
			std::cout << ">";
		}
		i->print();
	}
}