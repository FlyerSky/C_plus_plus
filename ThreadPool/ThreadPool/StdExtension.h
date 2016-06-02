#pragma once

#ifndef THREADPOOL_STD_EXTENSION_H
#define THREADPOOL_STD_EXTENSION_H

#include <map>

#ifdef __APPLE__
#include <unordered_map>
#include <unordered_set>
#elif(__cplusplus == 201103L)
#include <unordered_map>
#include <unordered_set>
#elif defined _MSC_VER
#include <unordered_map>
#include <unordered_set>
#else
#include <tr1/unordered_map>
#include <tr1/unordered_set>
namespace std {
	using std::tr1::unordered_map;
	using std::tr1::unordered_set;
}
#endif

#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#define print(x) std::cout << x << std::endl;

namespace std {

template <class T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	if (v.empty())
	{
		return os << "[]";
	}

	os << "[" << v[0];
	for (size_t i = 1; i < v.size(); i++)
	{
		os << ", " << v[i];
	}
	os << "]";
	return os;
}

template <>
inline ostream& operator<<(ostream& os, const vector<string>& v)
{
	if (v.empty())
	{
		return os << "[]";
	}

	os << "[\"" << v[0];
	for (size_t i = 1; i < v.size(); i++)
	{
		os << "\", \"" << v[i];
	}
	os << "\"]";
	return os;
}

template <typename T>
ostream& operator<<(ostream& os, const deque<T>& dq)
{
	if (dq.empty())
	{
		return os << "[]";
	}

	os << "[\"" << dq[0];
	for (size_t i = 0; i < dq.size(); ++i)
	{
		os << "\", \"" << dq[i];
	}
	os << "\"]";
	return os;
}

template <class T1, class T2>
ostream& operator<<(ostream& os, const pair<T1, T2>& pr)
{
	os << pr.first << ":" << pr.second;
	return os;
}

template <class T>
string& operator<<(string& str, const T& obj)
{
	stringstream ss;
	ss << obj;
	return str = ss.str();
}

template <class T1, class T2>
ostream& operator<<(ostream& os, const map<T1, T2> mp)
{
	if (mp.empty())
	{
		os << "{}";
		return os;
	}

	os << '{';
	typename map<T1, T2>::const_iterator it = mp.begin();
	os << *it;
	++it;
	while (it != mp.end())
	{
		os << ", " << *it++;
	}
	os << '}';
	return os;
}

template <class T1, class T2>
ostream& operator<<(ostream& os, const std::unordered_map<T1, T2> mp)
{
	if (mp.empty())
	{
		os << "{}";
		return os;
	}

	os << '{';
	typename std::unordered_map<T1, T2>::const_iterator it = mp.begin();
	os << *it;
	++it;
	while (it != mp.end())
	{
		os << ", " << *it++;
	}
	os << '}';
	return os;
}

template <class T>
ostream& operator<<(ostream& os, const set<T> st)
{
	if (st.empty())
	{
		os << "{}";
		return os;
	}

	os << '{';
	typename set<T>::const_iterator it = st.begin();
	os << *it;
	++it;
	while (it != st.end())
	{
		os << ", " << *it++;
	}
	os << '}';
	return os;
}

template <class ContainType, class KeyType>
bool isIn(const ContainType& contain, const KeyType& key)
{
	return contain.end() != contain.find(key)
}

template <class T>
basic_string<T>& operator<<(basic_string<T>& s, ifstream& ifs)
{
	return s.assign((istreambuf_iterator<T>(ifs)), istreambuf_iterator<T>());
}

template <class T>
ofstream& operator<<(ofstream& ofs, const basic_string<T>& s)
{
	ostreambuf_iterator<T> itr(ofs);
	copy(s.begin(), s.end(), itr);
	return ofs;
}

/******************************************************************************
1��STLֻ��һ���ַ����ࣺbasic_string��һ��basic_string����һ����0�����������ַ������顣
�ַ���������basic_stringģ��Ĳ������ܵ���˵��һ��basic_string���͵ı���Ӧ�ñ�������͸���Ķ���
����Եõ�һ��ָ���ڲ���������ֻ��ָ�룬�����κ�д��������ʹ��basic_string�Ĳ������ͷ�����
2��basic_string������Ԥ��������ͣ�����char��string���ͺͰ���wchar_t��wstring���͡�
*******************************************************************************/

/******************************************************************************
����assign�ĺ����ĺô��������ڲ���ʹ�ø�ֵ���� = ��������£����Խ�һ�������еĲ���Ԫ��
ͨ�����������ݸ�ֵ����һ�������У�������assign��ʹ�ù����У���һ����Ҫ�ر�ע�⣬���ǵ�
��assign()�����������������㹻�Ŀռ������ɸ��ƹ�����Ԫ�ء�
*******************************************************************************/

} // namespace std

#endif