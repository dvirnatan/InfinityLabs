/**************************************
Author: Dvir Natan
Reviewer: Matan
Status: Approved
Date: 20.02.2022
***************************************/

#include <iostream>   // cout,  cerr
#include <dirent.h> // struct dirent
  
#include "file_dir.hpp"

namespace ilrd
{

AbstractFile::AbstractFile(std::string name) : m_name(name)
{
    //empty
}

AbstractFile::~AbstractFile()
{
    //empty
}

std::string AbstractFile::GetName() const
{
    return m_name;
}

File::File(std::string name) : AbstractFile(name)
{
    //empty
}

File::~File()
{
    //empty
}

void File::Print(std::string indentation) const
{
	std::cout << indentation << GetName() << std::endl;
}

Directory::Directory(std::string name) : AbstractFile(name)
{  
	DIR *directory = opendir(name.c_str());
	if (NULL == directory)
	{
		std::cerr << "Failed to open directory\n";
		throw std::exception();
	}
	try
	{
		struct dirent *dir;
		while ((dir = readdir(directory)) != NULL)
		{
			if(dir->d_name[0] == '.')
			{
				continue;
			}
			std::string path = name + "/" + dir->d_name;
			if(dir->d_type == DT_DIR)
			{
    			m_content.push_back(new Directory(path));
			}
			else 
			{
				m_content.push_back(new File(path));
			}
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		closedir(directory);
		Directory::~Directory();
	}

	closedir(directory);
} 

Directory::~Directory()
{
	std::list<AbstractFile*>::const_iterator iter;
	
	for(iter = m_content.begin(); iter != m_content.end(); ++iter)
	{
		delete (*iter);
	}
}

void Directory::Print(std::string indentation) const
{
	std::list<AbstractFile*>::const_iterator iter;

	for(iter = m_content.begin(); iter != m_content.end(); ++iter)
	{
		(*iter)->Print(indentation + "\t");
	}
}


}//namespace ilrd
