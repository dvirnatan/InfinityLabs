#ifndef __KNIGHT_TOUR_H__
#define __KNIGHT_TOUR_H__

#include <stddef.h>
#define BOARD_SIDE 8
#define BOARD_LENGTH 8

typedef struct knt knt_t;

void KnightTour(size_t board[BOARD_SIDE * BOARD_LENGTH], size_t row, size_t col);

#endif /* __KNIGHT_TOUR_H__ */
