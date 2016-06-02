#include "stdafx.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;

class Base
{
public:
	virtual void clone() = 0;
};

class Base1 : virtual Base
{
public:
	Base1() {}

	virtual void speakClearly()
	{
		cout << "Base1::speakClearly()" << endl;
	}

	virtual void clone()
	{
		cout << "Base1::clone()" << endl;
	}

	virtual ~Base1() {}
};

class Base2 : virtual Base
{
public:
	Base2() {}

	virtual void mumble()
	{
		cout << "Base2::mumble()" << endl;
	}

	virtual void clone()
	{
		cout << "Base2::clone()" << endl;
	}

	virtual ~Base2() {}
};


class Derived : public Base1, public Base2
{
public:
	Derived() {}

	void clone()
	{
		cout << "Derived::clone()" << endl;
	}

	virtual void somethingElse()
	{
		cout << "Derived::somethingElse()" << endl;
	}

	~Derived() {}
};

int main()
{
	Base1* b1 = new Derived();
	b1->clone();
	b1->speakClearly();
	// b1->somethingElse();
	dynamic_cast<Derived*>(b1)->somethingElse();

	Base2 *b2 = new Derived();
	b2->clone();
	b2->mumble();
	// b2->somethingElse();
	dynamic_cast<Derived*>(b2)->somethingElse();

	cout << "sizeof(Base1) = " << sizeof(new Base1()) << endl;
	cout << "sizeof(Derived) = " << sizeof(new Derived()) << endl;

	system("pause");
	return 0;
}
