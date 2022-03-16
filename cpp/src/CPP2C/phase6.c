#include <stdio.h>
#include <stdlib.h>

struct private
{
	int x;
	int y;
};
struct B
{
	struct private b;
};

typedef struct B B;

void print(B *b_);

B BInit_int(int x_ , int y_)
{
	B this = {.b.x = x_, .b.y = y_};
	return this;
}

B BInit_default()
{
	B b = {.b.x = 0, .b.y = 0};
	return b;
}

void BCtor(B *const this)
{
	printf("BCtor for:");
	print(this);
}

void BDtor(B *const this)
{
	printf("BDtor for:");
	print(this);
}

void SetX(B *const b, int x)
{
	b->b.x = x;
}

void SetY(B *const b, int y)
{
	b->b.y = y;
}

void print(B *b_)
{
	printf("(%d, %d)\n", b_->b.x, b_->b.y);
}

int main()
{
	// Phase 6

	// B b1;
	// BCtor(&b1);
	// SetX(&b1, 5);
	// SetY(&b1, 6);
	// print(&b1);

	// B *b2 = malloc(sizeof(B));
	// *b2 = BInit_default();
	// BCtor(b2);
	// SetX(b2, 5);
	// SetY(b2, 6);

	// print(b2);

	// BDtor(&b1);
	// BDtor(b2);

	// Phase 8

	B array1[100];
	

	B *array2 = malloc(sizeof(B) * 100);

	
}