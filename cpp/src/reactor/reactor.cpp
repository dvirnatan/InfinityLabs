/**********************************/
/*			reactor			      */
/*								  */
/*	Author: Dvir Natan 			  */
/*	Reviwer: Yair      			  */
/*	Date: 	20/03/22	          */
/*	Status: Aprroved              */		  
/**********************************/
#include <sys/types.h>

#include "reactor.hpp"

namespace ilrd
{

Reactor::Reactor() : m_runingFlag(false), m_maxFd(0) 
{
	FD_ZERO(&m_masterSet);
}

void Reactor::Add(int fd, std::function< void ()> notify)
{
	m_map.insert(std::pair<int, std::function<void ()> >(fd, notify));
	FD_SET(fd, &m_masterSet);
	m_maxFd = (fd > m_maxFd) ? fd : m_maxFd; 
}

void Reactor::Remove(int fd)
{
	m_map.erase(fd);
	FD_CLR(fd, &m_masterSet);
	if(m_maxFd == fd)
	{
		m_maxFd = m_map.rbegin()->first;
	}
}

void Reactor::Run()
{
	m_runingFlag = true;

	while(m_runingFlag == true)
	{
		fd_set workinSet = m_masterSet;

		int readyFds = select(m_maxFd + 1, &workinSet, 0, 0, 0);

		if(readyFds < 0)
			throw std::exception();

		for(auto it : m_map)
		{
			if(readyFds == 0)
				break;
				
			if(FD_ISSET(it.first, &workinSet))
			{
				--readyFds;
				it.second();
			}
		}
	}// while(m_runingFlag == true)
}

void Reactor::Stop()
{
	m_runingFlag = false;
}

}; // namespace ilrd

