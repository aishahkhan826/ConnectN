

#ifndef NCursesConnectN_MOVE_H
#define NCursesConnectN_MOVE_H

#include <stdbool.h>
#include "CursorTrakedWindow.h"
//#include "board.h"

typedef enum{Player1 = 0, Player2 = 1}TurnType;

typedef struct Move_Struct{
    int row, col;
    char marker;
}Move;

struct Board_Struct;


Move getValidMove(struct Board_Struct* board, struct Board_Struct* playboard, struct Board_Struct* annboard, TurnType playerTurn, CursorTrackedWindow* boardwin, CursorTrackedWindow* playwin, FILE* fp, int pieces);
bool isValidMove(Move move,  struct Board_Struct* board, int numArgsRead, int numArgsNeeded);
const char* PlayerToString(TurnType player);

#endif //NCursesConnectN_MOVE_H
