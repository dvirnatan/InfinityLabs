
struct Point
{
	int m_x;
	int m_y;
};


struct A
{/* char a; */};

struct B
{
	int x;
	int y;
	struct Point p;
};

struct B BInit()
{
	struct B b = {.p = {0, 0}};
	return b;
}

struct B Bcopy(struct B other_)
{
	struct B this = {.x = other_.x, .y = other_.y, .p = other_.p};
	return this;
}

void BCtor() {}

int main()
{
	struct A a;

	struct B b = BInit();
	BCtor(); // no need.

	struct B b2 = Bcopy(b);

	b2 = b;

	return 0;
}