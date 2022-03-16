/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~
 ~ Author        R&D 111                                       *
 * Description   logger API                                   ~
 ~ Date          14.03.2022                                    *
 * Company       ILRD Ramat Gan                                ~
 ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef ILRD_RD111_LOGGER_HPP
#define ILRD_RD111_LOGGER_HPP

#include <boost/core/noncopyable.hpp>   // noncopyable
#include <string>						// string
#include <condition_variable>

#include "thread_pool.hpp"

namespace ilrd
{

class Logger : private boost::noncopyable
{
public:
	enum Severity {INFO, DEBUG, ERROR};
	Logger(const std::string& file_name, Severity = ERROR);
	~Logger();

	void Log(std::string, Severity = INFO);
	void SetSeverity(Severity);

private:
	std::string m_fileName;
	Severity m_severity;
	ThreadPool m_pool;
	bool Exit;
	std::condition_variable cond_var_exit;  
	std::mutex m;
	void LastTask();
};

} // namespace ilrd

#endif