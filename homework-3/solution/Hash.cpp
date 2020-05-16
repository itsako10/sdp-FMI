#include "Hash.h"
#include <iostream>
#include <cstring>

Hash::Person::Person(const char* name)
{
	setName(name);
	this->left = NULL;
	this->right = NULL;
	this->next = NULL;
	this->hold_left = 0;
	this->hold_right = 0;
}

void Hash::Person::setName(const char* name)
{
	if (name == NULL)
	{
		std::cout << "No name!\n";
		this->name[0] = '\0';
	}
	else
	{
		for (int i = 0; i < 30; ++i)
		{
			this->name[i] = name[i];
		}
		this->name[30] = '\0';
	}

}

Hash::Hash()
{
	this->size = 32;
	this->arr = new Person*[size];
	for (int i = 0; i < size; ++i)
	{
		arr[i] = NULL;
	}

	this->used = 0;
	this->first = NULL;
}

Hash::~Hash()
{
	for (int i = 0; i < size; ++i)
	{
		delete this->arr[i];
	}
	delete[] arr;
}

void Hash::resizeIfNeeded()
{
	double helper = double(used) / double(size);
	if (helper > 0.7)
	{
		int new_size = size * 2;
		Person** helper = new Person*[new_size];
		for (int i = 0; i < new_size; ++i)
		{
			helper[i] = NULL;
		}

		delete[] arr;
		this->size = new_size;

		int index = hashFunc(first->name);
		helper[index] = first;

		for (Person* i = this->first->left; i != first; i = i->left)
		{
			index = hashFunc(i->name);
			if (helper[index] == NULL)
			{
				helper[index] = i;
			}
			else
			{
				Person* j = helper[index];
				for (; j->next != NULL; j = j->next)
				{
					;
				}
				j->next = i;
			}
		}
		this->arr = helper;
	}
}

int Hash::hashFunc(const char* name)
{
	int lenght = strlen(name);
	int sum = 6068;
	for (int i = 0; i < lenght; ++i)
	{
		sum = sum * 33 + (int)name[i];
	}

	return abs(sum % this->size);
}

Hash::Person* Hash::find(const char* name)
{
	int index = hashFunc(name);
	for (Person*i = arr[index]; i != NULL; i = i->next)
	{
		if (strcmp(name, i->name) == 0)
		{
			return i;
		}
	}

	std::cout << "There is no person with this name!\n";
	return NULL;
}

void Hash::release(const char* name, const char* lrb)
{
	Person* helper = find(name);
	if (helper == NULL)
	{
		return;
	}

	if (strcmp(lrb, "left") == 0)
	{
		helper->hold_left = 0;
	}
	else if (strcmp(lrb, "right") == 0)
	{
		helper->hold_right = 0;
	}
	else if (strcmp(lrb, "both") == 0)
	{
		helper->hold_left = 0;
		helper->hold_right = 0;
	}
	else
	{
		std::cout << "Unknown command!\n";
		return;
	}
}

void Hash::grap(const char* name, const char* lrb)
{
	Person* helper = find(name);
	if (helper == NULL)
	{
		return;
	}

	if (strcmp(lrb, "left") == 0)
	{
		helper->hold_left = 1;
	}
	else if (strcmp(lrb, "right") == 0)
	{
		helper->hold_right = 1;
	}
	else if (strcmp(lrb, "both") == 0)
	{
		helper->hold_left = 1;
		helper->hold_right = 1;
	}
	else
	{
		std::cout << "Unknown command!\n";
		return;
	}
}

void Hash::info(const char* name)
{
	Person* helper = find(name);
	if (helper == NULL)
	{
		return;
	}

	std::cout << helper->left->name << " ";

	if (helper->hold_left == 1)
	{
		std::cout << "<--";
	}
	else
	{
		std::cout << "---";
	}

	if (helper->left->hold_right == 1)
	{
		std::cout << ">";
	}
	else
	{
		std::cout << "-";
	}

	std::cout << " " << helper->name << " ";

	if (helper->right->hold_left == 1)
	{
		std::cout << "<--";
	}
	else
	{
		std::cout << "---";
	}

	if (helper->hold_right == 1)
	{
		std::cout << ">";
	}
	else
	{
		std::cout << "-";
	}

	std::cout << " " << helper->right->name << std::endl;
}

void Hash::add(const char* name, const char* label_left, const char* label_right)
{
	Person* helper_left = find(label_left);
	Person* helper_right = find(label_right);

	if (helper_left->left != helper_right && helper_left->right != helper_right)
	{
		std::cout << "Error: label_left and label_right are not neighbours!" << std::endl;
		return;
	}

	int index = hashFunc(name);
	for (Person* j = arr[index]; j != NULL; j = j->next)
	{
		if (strcmp(j->name, name) == 0)
		{
			std::cout << "There is a person with this name!" << std::endl;
			return;
		}
	}

	Person* to_add = new Person(name);

	Person* i = arr[index];
	if (i == NULL)
	{
		arr[index] = to_add;
	}
	else
	{
		for (; i->next != NULL; i = i->next)
		{
			;
		}

		i->next = to_add;
	}

	to_add->left = helper_left;
	helper_left->right = to_add;

	to_add->right = helper_right;
	helper_right->left = to_add;

	to_add->hold_left = 1;
	to_add->hold_right = 1;

	helper_left->hold_left = 1;
	helper_left->hold_right = 1;

	helper_right->hold_left = 1;
	helper_right->hold_right = 1;

	++used;
	resizeIfNeeded();
}

void Hash::remove(const char* name)
{
	Person* to_delete = find(name);
	if (to_delete == NULL)
	{
		return;
	}

	if (to_delete == this->first)
	{
		first = to_delete->left;
	}

	if (to_delete->hold_left == 0 && to_delete->hold_right == 0 && to_delete->left->hold_right == 0 && to_delete->right->hold_left == 0)
	{
		to_delete->left->right = to_delete->right;
		to_delete->right->left = to_delete->left;

		to_delete->left->hold_right = 1;
		to_delete->right->hold_left = 1;

		int index = hashFunc(name);
		Person* i = arr[index];
		if (strcmp(i->name, name) == 0)
		{
			arr[index] = NULL;
		}
		else
		{
			for (; strcmp(i->next->name, name) != 0; i = i->next);
			i->next = i->next->next;
		}

		to_delete->left = NULL;
		to_delete->right = NULL;
		to_delete->next = NULL;
		delete to_delete;
		--used;

		std::cout << "Free at last!" << std::endl;

		if (used <= 2)
		{
			for (int i = 0; i < size; ++i)
			{
				for (Person* j = arr[i]; j != NULL;)
				{
					Person* j_helper = j->next;
					delete j;
					j = j_helper;
				}
			}
			delete[] arr;

			std::cout << "...and the music stops!" << std::endl;
		}
	}
	else
	{
		std::cout << "This won't be so easy!" << std::endl;
		return;
	}
}

void Hash::swap(const char* name1, const char* name2)
{
	Person* helper1 = find(name1);
	Person* helper2 = find(name2);

	bool helper_for_left;
	bool helper_for_right;

	if (helper1->left == helper2)
	{
		if (helper1->hold_right == 1 || helper2->hold_left == 1 || helper1->right->hold_left == 1 || helper2->left->hold_right == 1)
		{
			return;
		}

		helper1->hold_right = helper1->hold_left;
		helper2->hold_left = helper2->hold_right;
		helper1->hold_left = 0;
		helper2->hold_right = 0;

		helper2->left->right = helper1;
		helper1->right->left = helper2;
		helper1->left = helper2->left;
		helper2->left = helper1;
		helper2->right = helper1->right;
		helper1->right = helper2;
	}
	else if (helper1->right == helper2)
	{
		if (helper2->hold_right == 1 || helper1->hold_left == 1 || helper2->right->hold_left == 1 || helper1->left->hold_right == 1)
		{
			return;
		}

		helper1->hold_left = helper1->hold_right;
		helper2->hold_right = helper2->hold_left;
		helper1->hold_right = 0;
		helper2->hold_left = 0;

		helper1->left->right = helper2;
		helper2->right->left = helper1;
		helper2->left = helper1->left;
		helper1->left = helper2;
		helper1->right = helper2->right;
		helper2->right = helper1;
	}
	else
	{
		return;
	}
}

void Hash::print() const
{
	std::cout << first->name << std::endl;
	for (Person* i = this->first->left; i != first; i = i->left)
	{
		std::cout << i->name << std::endl;
	}
}

void Hash::addFirst(const char* name)
{
	Person* to_add = new Person(name);
	int index = hashFunc(name);
	arr[index] = to_add;
	this->first = to_add;
	++used;
}

void Hash::addSecond(const char* name)
{
	Person* to_add = new Person(name);
	int index = hashFunc(name);
	int first_index = hashFunc(first->name);

	if (index == first_index)
	{
		arr[index]->next = to_add;
	}
	else
	{
		arr[index] = to_add;
	}

	first->left = to_add;
	to_add->right = first;

	first->hold_left = 1;
	to_add->hold_right = 1;
	++used;
}

void Hash::addThird(const char* name)
{
	Person* to_add = new Person(name);
	Person* second = first->left;
	int index = hashFunc(name);
	int first_index = hashFunc(first->name);
	int second_index = hashFunc(second->name);

	if (index == first_index && index == second_index)
	{
		arr[index]->next->next = to_add;
	}
	else if (index == first_index || index == second_index)
	{
		arr[index]->next = to_add;
	}
	else
	{
		arr[index] = to_add;
	}

	first->right = to_add;
	to_add->left = first;
	to_add->right = second;
	second->left = to_add;

	to_add->hold_left = 1;
	to_add->hold_right = 1;

	first->hold_right = 1;
	second->hold_left = 1;
	
	++used;
}

Hash::Person* Hash::getFirst() const
{
	return this->first;
}