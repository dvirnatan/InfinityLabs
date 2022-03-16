#ifndef ILRD_RD111_FILE_DIR_HPP
#define ILRD_RD111_FILE_DIR_HPP

#include <string> // string
#include <list> // list

namespace ilrd
{

class AbstractFile
{
public:
    explicit AbstractFile(std::string name);
    virtual ~AbstractFile() = 0;
    virtual void Print(std::string indentation) const = 0;
    std::string GetName() const;

private:
    AbstractFile(const AbstractFile&); // avoid from generated cctor
    AbstractFile& operator=(const AbstractFile&);// avoid from generated assignment op
    const std::string m_name;
};

class File: public AbstractFile
{
public:
    File(std::string name);
    virtual ~File();
    virtual void Print(std::string indentation) const;
};

class Directory: public AbstractFile
{
public:
    Directory(std::string name);
    virtual ~Directory();

    virtual void Print(std::string indentation) const;
private:
    std::list<AbstractFile *> m_content;
};


}//namespace ilrd

#endif // ILRD_RD111_FILE_DIR_HPP
