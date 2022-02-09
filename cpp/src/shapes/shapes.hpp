#ifndef ILRD__111__SHAPES
#define ILRD__111__SHAPES

#include <cstddef> //size_t
#include <list>

namespace ilrd
{
class Shape
{
public:
    Shape() : m_offset(0) {}
    virtual ~Shape(){}
    virtual void Draw() const = 0;
    void Move(size_t offset_);
private:
    size_t m_offset;
};

/*class Line : public Shape
{
public:
    virtual void Draw() const;
};

class Circle : public Shape
{
public:
    virtual void Draw() const;
};

class Rectangle : public Shape
{
public:
    virtual void Draw() const;
};

class Square : public Shape
{
public:
    virtual void Draw() const;
};*/

void Draw(const std::list<Shape*> listOfShapes);
}//ilrd

#endif // !ILRD__111__SHAPES