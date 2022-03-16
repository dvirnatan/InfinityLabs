/* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~
 ~ Author        R&D 111                                       *
 * Description   factory API                                   ~
 ~ Date          13.03.2022                                    *
 * Company       ILRD Ramat Gan                                ~
 ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ */

#ifndef ILRD_RD111_FACTORY_HPP
#define ILRD_RD111_FACTORY_HPP

#include <boost/core/noncopyable.hpp>   // noncopyable
#include <map> 							// map
#include "singelton.hpp" 				

namespace ilrd
{

template <class BASE, typename KEY, typename PARAM>
class Factory : private  boost::noncopyable
{
public:
    void Add(KEY, BASE*(*func)(PARAM p));
    BASE* Create(KEY key, PARAM p) const;
private:
	Factory();
    std::map<KEY,  BASE* (*)(PARAM)> m_container;
	friend class Singleton<Factory<BASE,KEY,PARAM> >;
};

template <class BASE, typename KEY, typename PARAM>
Factory<BASE,KEY,PARAM>::Factory()
{
	// Empty
}

template <class BASE, typename KEY, typename PARAM>
void Factory<BASE,KEY,PARAM>::Add(KEY key, BASE*(*func)(PARAM p))
{
	if(m_container.insert(std::pair<KEY, BASE*(*)(PARAM)>(key, func)).second == false)
	{
		throw std::invalid_argument("insert failed, key may be invalid");
	}
}

template <class BASE, typename KEY, typename PARAM>
BASE* Factory<BASE,KEY,PARAM>::Create(KEY key, PARAM p) const
{

	typename std::map<KEY,  BASE* (*)(PARAM)>::const_iterator iter =  m_container.find(key);
	if(iter == m_container.end())
	{
		throw std::invalid_argument("find failed");
	}

	return iter->second(p);
}


}//namespace ilrd

#endif // ILRD_RD111_FACTORY_HPP
