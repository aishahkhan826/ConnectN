
#ifndef NCursesConnectN_WIN_H
#define NCursesConnectN_WIN_H

#include <stdbool.h>
#include "board.h"
#include "move.h"


//bool isGameOver(char** board, const int numRows, const int numCols, const char blank_space, const int toWin, const char pieces);
bool isGameOver(Board board, int pieces, TurnType playerTurn);
bool win(Board board, int pieces, TurnType playerTurn);
bool horzWin(Board board, int pieces, TurnType playerTurn);
bool vertWin(Board board, int pieces, TurnType playerTurn);
bool diagWin(Board board, int pieces, TurnType playerTurn);
bool leftDiagWin(Board board, int pieces, TurnType playerTurn);
bool rightDiagWin(Board board, int pieces, TurnType playerTurn);
bool tie(Board board, int pieces, TurnType playerTurn);
void declareWinner (Board board, int pieces, TurnType playerTurn, FILE *fp);
//void declareWinner(Board board, int pieces, TurnType playerTurn, CursorTrackedWindow* annouuncement);
//const chtype declareWinner (Board board, int pieces, TurnType playerTurn);
//void annoucementdeclare( Board* annoucement, Board board, int pieces, TurnType playerTurn);

#endif //NCursesConnectN_WIN_H
