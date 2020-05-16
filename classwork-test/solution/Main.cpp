/////////////////////////////////////////////////////////////
//
// Author: Христо Александров Терзийски
// FN: 45219
// Program: Информатика
// Grade: 3
// Task: 1
// Date:11.11.2018
//
#include <iostream>

class Calculator
{
private:
	class Calculation
	{
	public:
		Calculation();
		void push(double number);
		void pop();
		void add();
		void substract();
		void negative();
		void max() const;
		void print() const;
		void setUsed(int new_used);

	private:
		int used;
		double arr[255];
	};

public:
	Calculator();

	void push(double number, unsigned index);
	void pop(unsigned index);
	void add();
	void substract();
	void negative();
	void max() const;
	void print() const;
	void create();

private:
	void resizeIfNeeded();

private:
	Calculation** cal_arr;
	int size;
	int used;
};

Calculator::Calculation::Calculation()
{
	used = -1;
}

void Calculator::Calculation::push(double number)
{
	if (used >= 254)
	{
		std::cout << "No more space in this calculation!\n";
	}
	++used;
	arr[used] = number;
}

void Calculator::Calculation::pop()
{
	--used;
}

void Calculator::Calculation::add()
{
	if (used <= 0)
	{
		return;
	}

	double b = arr[used];
	--used;
	double a = arr[used];
	--used;

	push(a + b);
}

void Calculator::Calculation::negative()
{
	arr[used] = -(arr[used]);
}

void Calculator::Calculation::substract()
{
	if (used <= 0)
	{
		return;
	}

	double b = arr[used];
	--used;
	double a = arr[used];
	--used;

	push(a - b);
}

void Calculator::Calculation::max() const
{
	if (used == -1)
	{
		std::cout << "none";
		return;
	}

	double max = arr[used];

	for (int i = used - 1; i >= 0; --i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	std::cout << max;
}

void Calculator::Calculation::print() const
{
	if (used < 0)
	{
		std::cout << "Empty calculation.\n";
		return;
	}

	for (int i = 0; i <= used; ++i)
	{
		std::cout << arr[i] << " ";
	}
	std::cout << '\n';
}

void Calculator::Calculation::setUsed(int new_used)
{
	this->used = new_used;
}

Calculator::Calculator()
{
	cal_arr = NULL;
	size = 0;
	used = -1;
}

void Calculator::push(double number, unsigned index)
{
	resizeIfNeeded();
	if (index > used || index > size)
	{
		std::cout << "Invalid index!\n";
	}
	else
	{
		cal_arr[index]->push(number);
	}
}

void Calculator::pop(unsigned index)
{
	if (index > used || index > size)
	{
		std::cout << "Invalid index!\n";
	}
	else
	{
		cal_arr[index]->pop();
	}

	if (used < 0)
	{
		delete cal_arr[index];

		for (int i = index; i < used; ++i)
		{
			cal_arr[i] = cal_arr[i + 1];
		}
	}
}

void Calculator::add()
{
	for (int i = 0; i <= used; ++i)
	{
		cal_arr[i]->add();
	}
}

void Calculator::substract()
{
	for (int i = 0; i <= used; ++i)
	{
		cal_arr[i]->substract();
	}
}

void Calculator::negative()
{
	for (int i = 0; i <= used; ++i)
	{
		cal_arr[i]->negative();
	}
}

void Calculator::max() const
{
	for (int i = 0; i <= used; ++i)
	{
		std::cout << "Calculation " << i << " max: ";
		cal_arr[i]->max();
		std::cout << '\n';
	}
}

void Calculator::print() const
{
	for (int i = 0; i <= used; ++i)
	{
		std::cout << "Index " << i << ": ";
		cal_arr[i]->print();
	}
}

void Calculator::resizeIfNeeded()
{
	if (size == 0)
	{
		Calculation** helper = new Calculation*[1];
		cal_arr = helper;
		cal_arr[0] = new Calculation;
		cal_arr[0]->setUsed(-1);
		size = 1;
		used = -1;
	}
	if (used == (size - 1))
	{
		Calculation** helper = new Calculation*[size * 2];
		for (int i = 0; i <= used; ++i)
		{
			helper[i] = cal_arr[i];
		}
		delete[] cal_arr;
		cal_arr = helper;
		size = size * 2;
		//used - не се променя
	}
}

void Calculator::create()
{
	resizeIfNeeded();
	++used;
	cal_arr[used] = new Calculation;
	cal_arr[used]->setUsed(-1);
}

int main()
{
	Calculator cal;
	cal.push(10, 0);
	cal.print();

	std::cout << "Hello world!\n";
	std::cout << "Itsko" << std::endl;

	return 0;
}