#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Hash.h"

const int MAX_PATH = 260;

void fillWithZeros(char* arr, int size)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = '\0';
	}
}

int main()
{
	Hash horo;

	char file_name[MAX_PATH];
	for (int i = 0; i < MAX_PATH; ++i)
	{
		file_name[i] = '\0';
	}
	std::cout << "Enter path: ";
	std::cin >> file_name;

	std::ifstream file;
	file.open(file_name, std::ios::in);

	if (file.is_open())
	{
		char name1[32];
		char name2[32];
		char name3[32];

		file.getline(name1, 32);

		file.getline(name2, 32);
		while (strcmp(name1, name2) == 0)
		{
			std::cout << "There is a person with this name!" << std::endl;
			file.getline(name2, 32);
		}

		file.getline(name3, 32);
		while (strcmp(name3, name1) == 0 || strcmp(name3, name2) == 0)
		{
			std::cout << "There is a person with this name!" << std::endl;
			file.getline(name3, 32);
		}

		horo.addFirst(name1);
		horo.addSecond(name2);
		horo.addThird(name3);

		char name[32];
		while (file.getline(name, 32))
		{
			horo.add(name, horo.getFirst()->name, horo.getFirst()->right->name);
		}

		file.close();
	}

	horo.print();

	char buffer_command[8];
	while (strcmp(buffer_command, "EXIT") != 0)
	{
		std::cin >> buffer_command;
		if (strcmp(buffer_command, "RELEASE") == 0)
		{
			char buf[50];
			std::cin.getline(buf, 50);

			char who[32];
			fillWithZeros(who, 32);
			int i = 2;
			int j = 0;
			for (; buf[i] != '"'; ++i)
			{
				who[j] = buf[i];
				++j;
			}

			i = i + 3;

			char lrb[12];
			fillWithZeros(lrb, 12);
			int k = 0;
			for (; buf[i] != '"'; ++i)
			{
				lrb[k] = buf[i];
				++k;
			}

			horo.release(who, lrb);

		/*	char who[32];
			std::cin >> who;
		
			char lrb[6];
			std::cin >> lrb;

			horo.release(who, lrb);*/
		}
		else if (strcmp(buffer_command, "GRAB") == 0)
		{
			char buf[50];
			std::cin.getline(buf, 50);

			char who[32];
			fillWithZeros(who, 32);
			int i = 2;
			int j = 0;
			for (; buf[i] != '"'; ++i)
			{
				who[j] = buf[i];
				++j;
			}

			i = i + 3;

			char lrb[12];
			fillWithZeros(lrb, 12);
			int k = 0;
			for (; buf[i] != '"'; ++i)
			{
				lrb[k] = buf[i];
				++k;
			}

			horo.grap(who, lrb);

			/*char who[32];
			std::cin >> who;

			char lrb[6];
			std::cin >> lrb;

			horo.grap(who, lrb);*/
		}
		else if (strcmp(buffer_command, "INFO") == 0)
		{
			char buf[36];
			std::cin.getline(buf, 36);
			char who[32];
			fillWithZeros(who, 32);

			for (int i = 2; buf[i] != '"'; ++i)
			{
				who[i - 2] = buf[i];
			}

			horo.info(who);

			/*char who[32];
			std::cin >> who;

			horo.info(who);*/
		}
		else if (strcmp(buffer_command, "ADD") == 0)
		{
			char buf[128];
			std::cin.getline(buf, 128);

			char who[32];
			fillWithZeros(who, 32);
			int i = 2;
			for (; buf[i] != '"'; ++i)
			{
				who[i - 2] = buf[i];
			}

			i = i + 3;

			char label_left[32];
			fillWithZeros(label_left, 32);
			int j = 0;
			for (; buf[i] != '"'; ++i)
			{
				label_left[j] = buf[i];
				++j;
			}

			i = i + 3;

			char label_right[32];
			fillWithZeros(label_right, 32);
			int k = 0;
			for (; buf[i] != '"'; ++i)
			{
				label_right[k] = buf[i];
				++k;
			}

			horo.add(who, label_left, label_right);

			/*char who[32];
			std::cin >> who;

			char label_left[32];
			std::cin >> label_left;

			char label_right[32];
			std::cin >> label_right;

			horo.add(who, label_left, label_right);*/
		}
		else if (strcmp(buffer_command, "REMOVE") == 0)
		{
			char buf[36];
			std::cin.getline(buf, 36);
			char who[32];
			fillWithZeros(who, 32);

			for (int i = 2; buf[i] != '"'; ++i)
			{
				who[i - 2] = buf[i];
			}

			horo.remove(who);

			/*char who[32];
			std::cin >> who;

			horo.remove(who);*/
		}
		else if (strcmp(buffer_command, "SWAP") == 0)
		{
			char buf[80];
			std::cin.getline(buf, 80);

			char who1[32];
			fillWithZeros(who1, 32);
			int i = 2;
			int j = 0;
			for (; buf[i] != '"'; ++i)
			{
				who1[j] = buf[i];
				++j;
			}

			i = i + 3;

			char who2[32];
			fillWithZeros(who2, 32);
			int k = 0;
			for (; buf[i] != '"'; ++i)
			{
				who2[k] = buf[i];
				++k;
			}

			horo.swap(who1, who2);

			/*char who1[32];
			std::cin >> who1;

			char who2[32];
			std::cin >> who2;

			horo.swap(who1, who2);*/
		}
		else if (strcmp(buffer_command, "PRINT") == 0)
		{
			horo.print();
		}
		else if (strcmp(buffer_command, "EXIT") == 0)
		{

			return 0;
		}
	}

	return 0;
}