#include <iostream>
#include <iterator>

#include "general_shapes.hpp"

using namespace std;
namespace ilrd
{
void Shape::Move(size_t offset_)
{
	m_offset = offset_;
}

void Shape::Draw() const
{
	for(size_t i = 0; i < m_offset; ++i)
	{
		cout << " ";
	}
}

void Line::Draw() const
{
	Shape::Draw();
	cout << "Line" << endl;
}

void Circle::Draw() const
{
	Shape::Draw();
	cout << "Circle" << endl;
}

void Rectangle::Draw() const
{
	Shape::Draw();
	cout << "Rectangle" << endl;
}

void Square::Draw() const
{
	Shape::Draw();
	cout << "Square" << endl;
}

void Draw(std::list<Shape*> listOfShapes)
{
	list<Shape*>::const_iterator iter = listOfShapes.begin();
	while(iter != listOfShapes.end())
	{
		(*iter)->Draw();
		++iter;
	}
}

}//namespace ilrd