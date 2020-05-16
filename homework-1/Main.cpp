#include <iostream>
#include <cstring>
#include "Browser.h"

const int MAX_BUFFER_SIZE = 2048;
const int MAX_COMMAND_SIZE = 7;

Browser browser;

void command(const char* command)
{
	char helper_command[MAX_COMMAND_SIZE + 1];
	char helper_URL[MAX_BUFFER_SIZE];

	for (int i = 0; i < MAX_COMMAND_SIZE + 1; ++i)
	{
		helper_command[i] = '\0';
	}

	for (int i = 0; command[i] != ' ' && command[i] != '\0'; ++i)
	{
		helper_command[i] = command[i];
	}

	if (strcmp(helper_command, "GO") == 0)
	{
		int j = 0;
		for (int i = 3; command[i] != '\0'; ++i)
		{
			helper_URL[i - 3] = command[i];
			j++;
		}
		helper_URL[j] = '\0';
		browser.go(helper_URL);
	}
	else if (strcmp(helper_command, "INSERT") == 0)
	{
		int j = 0;
		for (int i = 7; command[i] != '\0'; ++i)
		{
			helper_URL[i - 7] = command[i];
			j++;
		}
		helper_URL[j] = '\0';
		browser.insert(helper_URL);
	}
	else if (strcmp(helper_command, "BACK") == 0)
	{
		browser.back();
	}
	else if (strcmp(helper_command, "FORWARD") == 0)
	{
		browser.forward();
	}
	else if (strcmp(helper_command, "REMOVE") == 0)
	{
		browser.remove();
	}
	else if (strcmp(helper_command, "PRINT") == 0)
	{
		browser.print();
	}
	else if (strcmp(helper_command, "EXIT") == 0)
	{
		return;
	}
	else
	{
		std::cerr << "Incorrect command!\n";
		return;
	}
}

int main()
{
	char buffer[MAX_BUFFER_SIZE];
	do
	{
		std::cin.getline(buffer, MAX_BUFFER_SIZE);
		command(buffer);
	} while (strcmp(buffer, "EXIT") != 0);

	return 0;
}