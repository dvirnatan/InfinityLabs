/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~
 ~ Author        R&D 111                                       *
 * Description   reactor API                                   ~
 ~ Date          16.03.2022                                    *
 * Company       ILRD Ramat Gan                                ~
 ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef ILRD_RD111_REACTOR_HPP
#define ILRD_RD111_REACTOR_HPP

#include <functional> // std::function
#include <map>

namespace ilrd
{

class Reactor
{
public:
    explicit Reactor();
    void Add(int fd, std::function< void ()> notify);
    void Remove(int fd);
    void Run();
    void Stop();
private:
    std::map<int, std::function<void ()> > m_map;
	bool m_runingFlag;
	int m_maxFd;
	fd_set m_masterSet;
};

}//namespace ilrd

#endif // ILRD_RD111_REACTOR_HPP