

#include <stdio.h>
#include "win.h"


bool isGameOver(Board board, int pieces, TurnType playerTurn){

    return win(board, pieces, playerTurn)|| tie(board, pieces, playerTurn);

}



bool win(Board board, int pieces, TurnType playerTurn){
    return horzWin(board, pieces, playerTurn) || vertWin(board, pieces, playerTurn) || diagWin(board, pieces, playerTurn);

}

bool horzWin(Board board, int pieces, TurnType playerTurn) {
    int same;

    for (int row = 0; row < board.numRows; row++) {
        same = 0;
        for (int col = 0; col < board.numCols; col++) {
            same = (board.theBoard[row][col] == "XO"[playerTurn]) ? (same + 1) : 0;
            if (same == pieces) {
                //printf("horiz\n");
                return true;
            }
        }
    }
    return false;
}

bool vertWin(Board board, int pieces, TurnType playerTurn) {
    int same;

    for (int col = 0; col < board.numCols; col++) {
        same = 0;
        for (int row = 0; row < board.numRows; row++) {
            same = (board.theBoard[row][col] == "XO"[playerTurn]) ? (same + 1) : 0;
            if (same == pieces) {
                //printf("vert\n");
                return true;
            }
        }
    }
    return false;
}


bool diagWin(Board board, int pieces, TurnType playerTurn){
    return leftDiagWin(board, pieces, playerTurn) || rightDiagWin(board, pieces, playerTurn);
}

bool leftDiagWin(Board board, int pieces, TurnType playerTurn){
    int same = 0;

    if (board.numCols < pieces || board.numRows < pieces){
        return false;
    }
    else{
        for (int row = 0; row < board.numRows - pieces +1; row++){
            for (int col = 0; col < board.numCols - pieces+1; col++){
                same = 0;
                for (int k = 0; k < pieces; k++){
                    if(board.theBoard[row + k][col + k] != "XO"[playerTurn]){
                        same = 0;
                    }
                    else{
                        same++;
                        // printf("ld %d %d %d %d\n", row, col, k, same);

                        if (same == pieces){

                            //printf("ld %d %d %d\n", row, col, k);
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;

}

bool rightDiagWin(Board board, int pieces, TurnType playerTurn){
    int same = 0;

    if (board.numCols < pieces || board.numRows < pieces){
        return false;
    }
    else{
        for (int row = board.numRows - 1; row > board.numRows - pieces; row--){
            for(int col = 0; col <= board.numCols - pieces; col++){
                same = 0;
                for (int k = 0; row - k >= 0 ; k++){
                    if (board.theBoard[row - k][col + k] != "XO"[playerTurn]){
                        same = 0;
                    }
                    else{
                        ++same;
                        if (same == pieces){
                            //printf("rd\n");
                            return true;
                        }
                    }
                }
            }
        }

    }
    return false;
}


bool tie (Board board, int pieces, TurnType playerTurn){
    if(win(board, pieces, playerTurn)){
        return false;
    }

    for (int row = 0; row < board.numRows; row++){
        for (int col = 0; col < board.numCols; col++){
            if (board.theBoard[row][col] == '*'){
                return false;
            }
        }
    }

    return true;
}




void declareWinner (Board board, int pieces, TurnType playerTurn, FILE *fp){
    if(win(board, pieces, playerTurn)){
        int winner = playerTurn == Player1 ? Player1 : Player2;
        winner ++;

        fprintf(fp, "Player %d won!\n", winner);

    }
    else{
        fprintf(fp, "Tie Game\n");
    }
}
