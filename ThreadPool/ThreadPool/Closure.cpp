#include "Closure.h"

namespace threadpool {

template <class T>
ClosureInterface* NewClosure(T(*fun)())
{
	return new Closure0<T(*)()>(fun);
}

template <class T, class Arg1>
ClosureInterface* NewClosure(T(*fun)(Arg1), Arg1 arg1)
{
	return new Closure1<T(*)(Arg1), Arg1>(fun, arg1);
}

template <class T, class Arg1, class Arg2>
ClosureInterface* NewClosure(T(*fun)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
{
	return new Closure2<T(*)(Arg1, Arg2), Arg1, Arg2>(fun, arg1, arg2);
}

template <class T, class Arg1, class Arg2, class Arg3>
ClosureInterface* NewClosure(T(*fun)(Arg1, Arg2, Arg3), Arg1 arg1, Arg2 arg2, Arg3 arg3)
{
	return new Closure3<T(*)(Arg1, Arg2, Arg3), Arg1, Arg2, Arg3>(fun, arg1, arg2, arg3);
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
ClosureInterface* NewClosure(Obj* obj, T(Obj::*fun)())
{
	return new ObjClosure0<Obj, T(Obj::*)()>(obj, fun);
}

template <class Obj, class T, class Arg1>
ClosureInterface* NewClosure(Obj* obj, T(Obj::*fun)(Arg1), Arg1 arg1)
{
	return new ObjClosure1<Obj, T(Obj::*)(Arg1)>(obj, fun, arg1);
}

template <class Obj, class T, class Arg1, class Arg2>
ClosureInterface* NewClosure(Obj* Obj, T(Obj::*fun)(Arg1, Arg2), Arg1 arg1, Arg2 arg2)
{
	return new ObjClosure2<Obj, T(Obj::*)(Arg1, Arg2)>(obj, fun, arg1, arg2);
}

template <class Obj, class T, class Arg1, class Arg2, class Arg3>
ClosureInterface* NewClosure(Obj* obj, T(Obj::*fun)(Arg1, Arg2, Arg3), Arg1 arg1, Arg2 arg2, Arg3 arg3)
{
	return new ObjClosure3<Obj, T(Obj::*)(Arg1, Arg2, Arg3), Arg1, Arg2, Arg3>(obj, fun, arg1, arg2, arg3);
}

} // namespace threadpool