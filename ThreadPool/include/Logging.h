#pragma once

#ifndef THREADPOOL_LOGGING_H
#define THREADPOOL_LOGGING_H

#include <sstream>
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

// #error Ԥ����ָ��������ǣ��������ʱ��ֻҪ����#error �ͻ�����һ�����������ʾ��Ϣ����ֹͣ���롣
#ifdef XLOG
#error "XLOG has been defined already"
#endif // XLOG

#ifdef XCHECK
#error "XCHECK has been defined already"
#endif // XCHECK

// #��ʾ����Ӧ�����ַ�����  
// ##��ʾ���Ѻ��������궨����������еı�ʶ��������һ���γ�һ���µı�ʶ��
#define XLOG(level) threadpool::Logger(threadpool::LL_##level, __FILE__, __LINE__).Stream()
#define XCHECK(exp) if(!(exp)) XLOG(FATAL) << "exp: ["#exp << "] false. "

namespace threadpool {

enum {
	LL_DEBUG = 0,
	LL_INFO = 1,
	LL_WARNING = 2,
	LL_ERROR = 3,
	LL_FATAL = 4
}; // enum

static const char* LOG_LEVEL_ARRAY[] = { "DEBUG", "INFO", "WARNING", "ERROR", "FATAL" };
static const char* LOG_TIME_FORMAT = "%Y-%m-%d %H:%M:%S";

class Logger {
public:
	Logger(size_t level, const char* filename, int lineno) : m_level(level)
	{
#ifdef LOGGING_LEVEL
		if (m_level < LOGGING_LEVEL)
		{
			return;
		}
#endif
		assert(m_level <= sizeof(LOG_LEVEL_ARRAY) / sizeof(*LOG_LEVEL_ARRAY));
		// assert�������ǣ������������ʽ��ֵ�����Ϊ�٣���Ϊ0��������stderr��ӡһ��������Ϣ��Ȼ��ͨ������abort����ֹ�������С�
		char buf[32];
		time_t now;
		time(&now);
		strftime(buf, sizeof(buf), LOG_TIME_FORMAT, localtime(&now));
		m_stream << buf
			<< " " << filename
			<< ":" << lineno
			<< " " << LOG_LEVEL_ARRAY[m_level]
			<< " ";
	}

	~Logger() {
#ifdef LOGGING_LEVEL
		if (m_level < LOGGING_LEVEL)
		{
			return;
		}
#endif
		std::cerr << m_stream.str() << std::endl;
		if (m_level == LL_FATAL)
		{
			abort();
		}
	}

	std::ostream& Stream() {
		return m_stream;
	}

private:
	std::ostringstream m_stream;
	size_t m_level;
}; // class Logger

} // namespace threadpool

#endif // THREADPOOL_LOGGING_H