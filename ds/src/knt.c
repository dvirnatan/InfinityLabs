#include <stdio.h>
#include <stddef.h>

#include "bit_array.h"

#define BOARD_SIDE 8
#define BOARD_LENGTH 8
#define INDEXS 64
#define HighestDgree 9

int KnightTourAux(bit_arr_t been_here, size_t index,size_t board[BOARD_SIDE * BOARD_LENGTH]);
void KnightTour(size_t board[BOARD_SIDE * BOARD_LENGTH], size_t row, size_t col);
static void Swap (size_t *a, size_t *b);
static size_t GetDegree(bit_arr_t been_here, size_t index);
static void BubbleSortDgree(bit_arr_t been_here ,size_t index);


size_t LUT[INDEXS][BOARD_SIDE] = {0};

void Init()
{
    int i, c, r;

    for(i = 0; i < INDEXS; ++i)
        {
            r = i / BOARD_SIDE;
            c = i % BOARD_SIDE;

            LUT[i][0] = (r + 2 < BOARD_SIDE && c + 1 < BOARD_SIDE) ? (r + 2) * BOARD_SIDE + (c + 1) : INDEXS;

            LUT[i][1] = (r + 2 < BOARD_SIDE && c - 1 >= 0) ? (r + 2) * BOARD_SIDE + (c - 1) : INDEXS;

            LUT[i][2] = (r - 2 >= 0 && c + 1 < BOARD_SIDE) ? (r - 2) * BOARD_SIDE + (c + 1) : INDEXS;

            LUT[i][3] = (r - 2 >= 0 && c - 1 >= 0) ? (r - 2) * BOARD_SIDE + (c - 1) : INDEXS;

            LUT[i][4] = (r + 1 < BOARD_SIDE && c + 2 < BOARD_SIDE) ? (r + 1) * BOARD_SIDE + (c + 2) : INDEXS;

            LUT[i][5] = (r + 1 < BOARD_SIDE && c - 2 >= 0) ? (r + 1) * BOARD_SIDE + (c - 2) : INDEXS;

            LUT[i][6] = (r - 1 >= 0 && c + 2 < BOARD_SIDE) ? (r - 1) * BOARD_SIDE + (c + 2) : INDEXS;

            LUT[i][7] = (r - 1 >= 0 && c - 2 >= 0) ? (r - 1) * BOARD_SIDE + (c - 2) : INDEXS;
        }
}


static size_t GetDegree(bit_arr_t been_here, size_t index)
{

    size_t i = 0;
    size_t counter = 0;
    if(index == INDEXS)
    {
        return HighestDgree;
    }

    for(i = 0; i < BOARD_SIDE; ++i)
    {
        if(LUT[index][i] < INDEXS && GetBit(been_here, LUT[index][i]) == 0)
        {
            ++counter;
        }
    }
    return counter;
}

static void BubbleSortDgree(bit_arr_t been_here ,size_t index)
{
	size_t i = 0, swapped = 1;
		
	while(swapped > 0)
	{
		swapped = 0;

		for(i = 0 ; i + 1 < BOARD_SIDE; ++i)
		{
			if(GetDegree(been_here, LUT[index][i]) > GetDegree(been_here, LUT[index][i+1]))
			{
				Swap(&LUT[index][i], &LUT[index][i + 1]);
				swapped = 1;
			}
		}
	}
}

void KnightTour(size_t board[BOARD_SIDE * BOARD_LENGTH], size_t row, size_t col)
{
    bit_arr_t been_here = 0;
    been_here = SetAllOff(been_here);
    Init();
    KnightTourAux(been_here, row * BOARD_SIDE + col, board);
}

int KnightTourAux(bit_arr_t been_here, size_t index,size_t board[BOARD_SIDE * BOARD_LENGTH])
{
    bit_arr_t all_on = 0;
    size_t next_index = 0;
    size_t i = 0;
    size_t status = 1;

    all_on = SetAllOn(all_on);

    been_here = SetBitOn(been_here, index);

    if(CountOn(been_here) == CountOn(all_on))
    {
        return 0;
    }

    BubbleSortDgree(been_here, index);

    for(i = 0; i < BOARD_SIDE; ++i)
    {
        next_index = LUT[index][i];
        if(next_index != INDEXS && GetBit(been_here, next_index) != 1)
        {
            status = KnightTourAux(been_here, next_index, ++board);
        }
        if(status == 0)
        {
            *board = index;
            return 0;
        }
    }
    return 1;
}

static void Swap (size_t *a, size_t *b)
{
    size_t temp;

	temp = *a;
    *a = *b;
    *b = temp;
}

int main ()
{
    size_t i = 0;
    size_t board[INDEXS] = {0};
    size_t row = 0, col = 0;

    KnightTour(board, 1, 1);

    for(i = 0; i < 64; ++i)
    {
        if(!(i % 8))
        {
            puts("\n");
        }
        row = board[i] / BOARD_LENGTH;
        col = board[i] % BOARD_LENGTH;

        printf("(%ld,%ld) ", row, col);
    }
    puts("");
  
    return 0;
}

