#include <iostream>
#include "KongaQueue.h"
#include "KongaSet.h"

const int MAX_BUFFER_SIZE = 128;
const int MAX_COMMAND_SIZE = 11;
const int MAX_NAME_LENGTH = 64;
const int MAX_UNI_NAME = 4;
const int MAX_KongaQueues_Count = 40;

KongaSet konga_set;

void fillStrWithZeros(char* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = '\0';
	}
}

void command(const char* command)
{
	char helper_command[MAX_COMMAND_SIZE + 1];

	fillStrWithZeros(helper_command, MAX_COMMAND_SIZE + 1);

	for (int i = 0; command[i] != ' ' && command[i] != '\0'; ++i)
	{
		helper_command[i] = command[i];
	}

	if (strcmp(helper_command, "append") == 0)
	{
		char argument1[MAX_NAME_LENGTH + 1];
		int i_command = 7;

		fillStrWithZeros(argument1, MAX_NAME_LENGTH + 1);

		int j = 0;
		for (i_command; command[i_command] != ' '; ++i_command)
		{
			argument1[j] = command[i_command];
			++j;
		}

		char argument2[MAX_UNI_NAME + 1];
		fillStrWithZeros(argument2, MAX_UNI_NAME + 1);

		int k = 0;
		for (i_command = i_command + 1; command[i_command] != ' '; ++i_command)
		{
			argument2[k] = command[i_command];
			++k;
		}

		int argument3;
		char int_helper[MAX_KongaQueues_Count + 1];

		fillStrWithZeros(int_helper, MAX_KongaQueues_Count + 1);

		int q = 0;
		for (i_command = i_command + 1; command[i_command] != '\0'; ++i_command)
		{
			int_helper[q] = command[i_command];
			++q;
		}

		argument3 = atoi(int_helper);

		konga_set.append(argument1, argument2, argument3);
	}
	else if (strcmp(helper_command, "removeLast") == 0)
	{
		int i_command = 11;
		int argument;
		char int_helper[MAX_KongaQueues_Count + 1];
		
		fillStrWithZeros(int_helper, MAX_KongaQueues_Count + 1);

		int j = 0;
		for (i_command; command[i_command] != '\0'; ++i_command)
		{
			int_helper[j] = command[i_command];
			++j;
		}

		argument = atoi(int_helper);

		konga_set.removeLast(argument);
	}
	else if (strcmp(helper_command, "removeFirst") == 0)
	{
		int i_command = 12;
		int argument;
		char int_helper[MAX_KongaQueues_Count + 1];
		fillStrWithZeros(int_helper, MAX_KongaQueues_Count + 1);

		int j = 0;
		for (i_command; command[i_command] != '\0'; ++i_command)
		{
			int_helper[j] = command[i_command];
			++j;
		}

		argument = atoi(int_helper);

		konga_set.removeFirst(argument);
	}
	else if (strcmp(helper_command, "print") == 0)
	{
		konga_set.print();
	}
	else if (strcmp(helper_command, "merge") == 0)
	{
		int i_command = 6;

		int argument1;
		char int_helper1[MAX_KongaQueues_Count + 1];
		fillStrWithZeros(int_helper1, MAX_KongaQueues_Count + 1);

		int j = 0;
		for (i_command; command[i_command] != ' '; ++i_command)
		{
			int_helper1[j] = command[i_command];
			++j;
		}
		argument1 = atoi(int_helper1);

		int argument2;
		char int_helper2[MAX_KongaQueues_Count + 1];
		fillStrWithZeros(int_helper2, MAX_KongaQueues_Count + 1);

		int k = 0;
		for (i_command = i_command + 1; command[i_command] != '\0'; ++i_command)
		{
			int_helper2[k] = command[i_command];
			++k;
		}

		argument2 = atoi(int_helper2);

		konga_set.merge(argument1, argument2);
	}
	else if (strcmp(helper_command, "remove") == 0)
	{
		int i_command = 7;

		char argument1[MAX_NAME_LENGTH + 1];
		fillStrWithZeros(argument1, MAX_NAME_LENGTH + 1);

		int j = 0;
		for (i_command; command[i_command] != ' '; ++i_command)
		{
			argument1[j] = command[i_command];
			++j;
		}

		int argument2;
		char int_helper[MAX_KongaQueues_Count + 1];
		fillStrWithZeros(int_helper, MAX_KongaQueues_Count + 1);

		int k = 0;
		for (i_command = i_command + 1; command[i_command] != '\0'; ++i_command)
		{
			int_helper[k] = command[i_command];
			++k;
		}

		argument2 = atoi(int_helper);

		konga_set.remove(argument1, argument2);
	}
	else if (strcmp(helper_command, "quit") == 0)
	{
		return;
	}
}

int main()
{
	/* този коментар е предаденото като домашно, останалото, което пиша
	/го правя след като съм предал домашното
	char buffer[MAX_BUFFER_SIZE];
	do
	{
		std::cin.getline(buffer, MAX_BUFFER_SIZE);
		command(buffer);
	} while (strcmp(buffer, "quit") != 0);
	*/
	
	//KongaQueue queue;
	//queue.print();
	//queue.removeLast();
	//queue.print();
	//char* a = new char[1000];

	char buffer1[1024];
	char buffer2[1024];
	std::cin >> buffer1;
	std::cout << "Buffer1: " << buffer1 << std::endl;
	if (strcmp(buffer1, "hello") == 0)
	{
		std::cin >> buffer2;
		std::cout << "Buffer2: " << buffer2 << std::endl;
	}

	
	//system("pause");
	return 0;
}