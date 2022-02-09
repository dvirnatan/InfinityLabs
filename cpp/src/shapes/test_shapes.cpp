#include <iostream>

#include "general_shapes.hpp"

using namespace ilrd;

int main()
{
	using std::list;
	list<Shape*> list_t;

	Line line;

	Circle circle;
	circle.Move(10);

	Rectangle rectangle;
	rectangle.Move(25);

	Square squere;
	squere.Move(40);

	list_t.push_back(&line);
	list_t.push_back(&circle);
	list_t.push_back(&rectangle);
	list_t.push_back(&squere);

	Draw(list_t);

	return 0;
}