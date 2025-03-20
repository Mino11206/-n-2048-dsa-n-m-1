#include <iostream>
#include "mainGame.h"
#include <ctime>
using namespace std;


int main() {
    srand(time(0));
    int board[10][10];
    int size;
    size = 4;
    int score;

    inittialize(board, size, score);
    printBoard(board, size);

    char direction;
    Queue q;
    while(direction != 'e') {
        cin >> direction;
        moveTiles(direction, board, size, q, score);
        printBoard(board, size);
    }

}