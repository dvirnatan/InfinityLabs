#include <cstdio>
#include <iostream>

class Ex25
{
	public:
		explicit Ex25(int a_);
		void Foo();
		int Get_m_a() const;
		int m_b;

	private:
		int m_a;
};

Ex25::Ex25(int a_) : m_a(a_) {}

int Ex25::Get_m_a() const
{
	return this->m_a;
}

void Foo(const Ex25 &ex25_)
{
	printf("%d\n", ex25_.Get_m_a());

}

void Ex25::Foo() 
{
	Ex25* &&pt = this;
	printf("%d\n", m_a);
	std::cout << pt << std::endl;
	std::cout << &pt << std::endl;
	std::cout << this << std::endl;
}

int main()
{
	Ex25 x1(1);
	Ex25 x2(3);
	x1 = x2;

	x1.Foo();
	printf("%d\n", x1.Get_m_a());
	x1.m_b = 3;
	printf("m_b: %d\n", x1.m_b);
	Foo(x1);

	return 0;
}