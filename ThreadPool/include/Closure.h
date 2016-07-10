#pragma once

#ifndef THREADPOOL_CLOSURE_H
#define THREADPOOL_CLOSURE_H

namespace threadpool {

// 类模板（一般将声明和定义都放在.h文件）

class ClosureInterface
{
public:
	virtual ~ClosureInterface()
	{
	}

	virtual void Run() = 0;
};

template <class Funct>
class Closure0 : public ClosureInterface
{
public:
	Closure0(Funct fun)
	{
		m_fun = fun;
	}

	virtual ~Closure0()
	{
	}

	virtual void Run()
	{
		(*m_fun)();
	}

private:
	Funct m_fun;
};

template <class Funct, class Arg1>
class Closure1 : public ClosureInterface
{
public:
	Closure1(Funct fun, Arg1 arg1)
	{
		m_fun = fun;
		m_arg1 = arg1;
	}

	virtual ~Closure1()
	{
	}

	virtual void Run()
	{
		(*m_fun)(m_arg1);
	}

private:
	Funct m_fun;
	Arg1 m_arg1;
};

template <class Funct, class Arg1, class Arg2>
class Closure2 : public ClosureInterface
{
public:
	Closure2(Funct fun, Arg1 arg1, Arg2 arg2)
	{
		m_fun = fun;
		m_arg1 = arg1;
		m_arg2 = arg2;
	}
	
	virtual ~Closure2() 
	{
	}
	
	virtual void Run()
	{
		(*m_fun)(m_arg1, m_arg2);
	}

private:
	Funct m_fun;
	Arg1 m_arg1;
	Arg2 m_arg2;
};

template <class Funct, class Arg1, class Arg2, class Arg3>
class Closure3 : public ClosureInterface
{
public:
	Closure3(Funct fun, Arg1 arg1, Arg2 arg2, Arg3 arg3)
	{
		m_fun = fun;
		m_arg1 = arg1;
		m_arg2 = arg2;
		m_arg3 = arg3;
	}
	
	virtual ~Closure3()
	{
	}

	virtual void Run()
	{
		(*m_fun)(m_arg1, m_arg2, m_arg3);
	}

private:
	Funct m_fun;
	Arg1 m_arg1;
	Arg2 m_arg2;
	Arg3 m_arg3;
};

template <class Obj, class Funct>
class ObjClosure0 : public ClosureInterface
{
public:
	ObjClosure0(Obj* p, Funct fun)
	{
		m_pObj = p;
		m_fun = fun;
	}

	virtual ~ObjClosure0()
	{

	}

	virtual void Run()
	{
		(m_pObj->*m_fun)();
	}

private:
	Obj* m_pObj;
	Funct m_fun;
};

template <class Obj, class Funct, class Arg1>
class ObjClosure1 : public ClosureInterface
{
public:
	ObjClosure1(Obj* p, Funct fun, Arg1 arg1)
	{
		m_pObj = p;
		m_fun = fun;
		m_arg1 = arg1;
	}

	virtual ~ObjClosure1()
	{
	}
	
	virtual void Run()
	{
		(m_pObj->*m_fun)(m_arg1);
	}

private:
	Obj* m_pObj;
	Funct m_fun;
	Arg1 m_arg1;
};

template <class Obj, class Funct, class Arg1, class Arg2>
class ObjClosure2 : public ClosureInterface
{
public:
	ObjClosure2(Obj* p, Funct fun, Arg1 arg1, Arg2 arg2)
	{
		m_pObj = p;
		m_arg1 = arg1;
		m_arg2 = arg2;
	}

	virtual ~ObjClosure2()
	{
	}
	
	virtual void Run()
	{
		(m_pObj->*m_fun)(m_arg1, m_arg2);
	}

private:
	Obj* m_pObj;
	Funct m_fun;
	Arg1 m_arg1;
	Arg2 m_arg2;
};

template <class Obj, class Funct, class Arg1, class Arg2, class Arg3>
class ObjClosure3 : public ClosureInterface
{
public:
	ObjClosure3(Obj* p, Funct fun, Arg1 arg1, Arg2 arg2, Arg3 arg3)
	{
		m_pObj = p;
		m_fun = fun;
		m_arg1 = arg1;
		m_arg2 = arg2;
		m_arg3 = arg3;
	}

	virtual ~ObjClosure3()
	{
	}
	
	virtual void Run()
	{
		(m_pObj->*m_fun)(m_arg1, m_arg2, m_arg3);
	}

private:
	Obj* m_pObj;
	Funct m_fun;
	Arg1 m_arg1;
	Arg2 m_arg2;
	Arg3 m_arg3;
};


// 函数模板（一般将声明放在.h文件，定义放在.cpp文件）

template <class T>
ClosureInterface* NewClosure(T (*fun)())
{
	return new Closure0<T (*)()>(fun);
}

template <class T, class Arg1>
ClosureInterface* NewClosure(T (*fun)(Arg1), Arg1 arg1)
{
	return new Closure1<T (*)(Arg1), Arg1>(fun, arg1);
}

template <class T, class Arg1, class Arg2>
ClosureInterface* NewClosure(T (*fun)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
{
	return new Closure2<T (*)(Arg1, Arg2), Arg1, Arg2>(fun, arg1, arg2);
}

template <class T, class Arg1, class Arg2, class Arg3>
ClosureInterface* NewClosure(T (*fun)(Arg1, Arg2, Arg3), Arg1 arg1, Arg2 arg2, Arg3 arg3)
{
	return new Closure3<T (*)(Arg1, Arg2, Arg3), Arg1, Arg2, Arg3>(fun, arg1, arg2, arg3);
}


/***************************************************
T(Obj::*fun)(Arg1)
操作符 ::* 用来声明一个类成员函数指针,即该指针指向特定类的成员函数

(objPtr->*fun)(arg1)
操作符 ->* 用来通过对象指针调用类成员函数指针
(obj.*fun)(arg1)
操作符 .* 用来通过对象调用类成员函数指针
****************************************************/

template <class Obj, class T>
ClosureInterface* NewClosure(Obj* obj, T (Obj::* fun)())
{
        return new ObjClosure0<Obj, T (Obj::* )()>(obj, fun);
}

template <class Obj, class T, class Arg1>
ClosureInterface* NewClosure(Obj* obj, T (Obj::* fun)(Arg1), Arg1 arg1)
{
        return new ObjClosure1<Obj, T (Obj::* )(Arg1), Arg1>(obj, fun, arg1);
}

template <class Obj, class T, class Arg1, class Arg2>
ClosureInterface* NewClosure(Obj* obj, T (Obj::* fun)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
{
        return new ObjClosure2<Obj, T (Obj::*)(Arg1, Arg2), Arg2, Arg2>(obj, fun, arg1, arg2);
}

template <class Obj, class T, class Arg1, class Arg2, class Arg3>
ClosureInterface* NewClosure(Obj* obj, T (Obj::* fun)(Arg1, Arg2, Arg3), Arg1 arg1, Arg2 arg2, Arg3 arg3)
{
        return new ObjClosure3<Obj, T (Obj::*)(Arg1, Arg2, Arg3), Arg1, Arg2, Arg3>(obj, fun, arg1, arg2, arg3);
}

} // namespace threadpool

#endif // THREADPOOL_CLOSURE_H
