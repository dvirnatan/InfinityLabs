/**********************************/
/*			logger			      */
/*								  */
/*	Author: Dvir Natan 			  */
/*	Reviwer:        			  */
/*	Date: 				          */
/*	Status: 	                  */		  
/**********************************/
#include <iostream>
#include <fstream>
#include <ctime>

#include "logger.hpp"

static void WriteToFileTask(std::string str, std::string m_fileName)
{
	std::ofstream logger;
	logger.open(m_fileName , std::ios::in | std::ios::app);
	time_t t = time(0);
	logger << ctime(&t) << str;
	logger.close();
}


namespace ilrd
{

Logger::Logger(const std::string& file_name, Severity level) : 
m_fileName(file_name),
m_severity(level),
m_pool(1),
Exit(false)
{
	// Empty
}

Logger::~Logger()
{
	m_pool.AddTask(ThreadPool::LOW, std::bind(&Logger::LastTask, this));
	std::unique_lock<std::mutex> lock(m);
	while(Exit != true)
	{
		cond_var_exit.wait(lock);
	}
}

void Logger::Log(std::string str, Severity Level)
{
	if(Level >= m_severity)
	{
		m_pool.AddTask(ThreadPool::HIGH, std::bind(WriteToFileTask, str, m_fileName));
	}
}

void Logger::SetSeverity(Severity Level)
{
	m_severity = Level;
}


void Logger::LastTask()
{
	m_pool.SetNumThreads(0);
	Exit = true;
	cond_var_exit.notify_all();
}

} // namespace ilrd

