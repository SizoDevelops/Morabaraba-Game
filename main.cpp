#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <fstream>
#include "class.h"
using namespace std;


void generateRandomPosition(int numRows, int numCols, int& row, int& col) {
    row = rand() % numRows;
    col = rand() % numCols;
}

// Count the number of pieces in the board

    int countPieces(int ** board, int player) {
     
    int count = 0;
    for (int i = 0 ; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] == player) {
                count++;
            }
        }
    }
    return count;
}


 

// Check if current placement of a cow is possible if not then that move is invalid

bool isValidPlacement(int **board, int row, int col) {
    return board[row][col] == 0;
}

// Check if move to be played is valid is not then the move is invalid
bool isValidMove(int **board, int srcRow, int srcCol, int destRow, int destCol, int player) {
 
//  Check if the source input from player matches the piece in that position
    if (board[srcRow][srcCol] != player)
        return false;

//Check if the destination spot is available or is empty
    if (board[destRow][destCol] != 0)
        return false;

// Return true if the move made is to the adjacent spot to that piece
    return (srcRow == destRow && abs(srcCol - destCol) == 1) ||
           (srcCol == destCol && abs(srcRow - destRow) == 1);
}




// Check if a recently played piece forms a mill
bool isMillFormed(int** board, int row, int col, int player, ofstream& MorabarabaResults) {
// Containers for checked mills

    std::vector< int > checkMillForRowOne;
    std::vector< int > checkMillForRowTwo;
    std::vector< int > checkMillForRowThree;
    std::vector< int > checkVerticalMills;

    // Horizontal Mill Combinations
    int rowOne[][3] = {
        {0, 1, 2}, {2, 3, 4}, {4, 5, 6}, {6, 7, 0},

    };
    int rowTwo[][3] = {
        {0, 1, 2}, {2, 3, 4}, {4, 5, 6}, {6, 7, 0},

    };
    int rowThree[][3] = {
        {0, 1, 2}, {2, 3, 4}, {4, 5, 6}, {6, 7, 0},
    };

// Vertical Combinations
    int verticalMills[][3] = {
        {0, 0, 0}, {1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4,4,4}, {5,5,5} , {6,6,6}, {7,7,7}

    };



// Check all Mills in row 1
    if(row == 0){

        for (int i = 0; i < 4; i++) {
        int piece1 = board[row][rowOne[i][0]];
        int piece2 = board[row][rowOne[i][1]];
        int piece3 = board[row][rowOne[i][2]];

        // If the mill found is not already checked then that's a mill else pass
        auto it = find(checkMillForRowOne.begin(), checkMillForRowOne.end(), i);
        if(it == checkMillForRowOne.end()){
            if (piece1 == player && piece2 == player && piece3 == player) {
            MorabarabaResults << " (mill = "<<"S"<<row<<"i"<<rowOne[i][0]<<", "<<"S"<<row<<"i"<<rowOne[i][1]<<", "<<"S"<<row<<"i"<<rowOne[i][2]<<") ";
            checkMillForRowOne.push_back(i);
            return true;
            }
        }
     
      
    }   
  
    }
    //Check all mills in row 2
    if(row == 1){
        for (int i = 0; i < 4; i++) {
        int piece1 = board[row][rowTwo[i][0]];
        int piece2 = board[row][rowTwo[i][1]];
        int piece3 = board[row][rowTwo[i][2]];

        // If the mill found is not already checked then that's a mill else pass
        auto it = find(checkMillForRowTwo.begin(), checkMillForRowTwo.end(), i);
        if(it == checkMillForRowTwo.end()){
            if (piece1 == player && piece2 == player && piece3 == player) {
            MorabarabaResults << " (mill = "<<"S"<<row<<"i"<<rowTwo[i][0]<<", "<<"S"<<row<<"i"<<rowTwo[i][1]<<", "<<"S"<<row<<"i"<<rowTwo[i][2]<<") ";
            checkMillForRowTwo.push_back(i);
            return true;
            }
        }
     
      
    }   
        
    }

    // Check all mills in row 2
    if(row == 2){
        for (int i = 0; i < 4; i++) {
        int piece1 = board[row][rowThree[i][0]];
        int piece2 = board[row][rowThree[i][1]];
        int piece3 = board[row][rowThree[i][2]];

        // If the mill found is not already checked then that's a mill else pass
        auto it = std::find(checkVerticalMills.begin(), checkVerticalMills.end(), i);
        if(it == checkVerticalMills.end()){
            if (piece1 == player && piece2 == player && piece3 == player) {
            MorabarabaResults << " (mill = "<<"S"<<row<<"i"<<rowThree[i][0]<<", "<<"S"<<row<<"i"<<rowThree[i][1]<<", "<<"S"<<row<<"i"<<rowThree[i][2]<<") ";
            checkVerticalMills.push_back(i);
            return true;
            }
        }
     
      
    }
    }

    // Check all vertical mills
       for (int i = 0; i < 4; i++) {
        int piece1 = board[0][verticalMills[i][0]];
        int piece2 = board[1][verticalMills[i][1]];
        int piece3 = board[2][verticalMills[i][2]];

        // If the mill found is not already checked then that's a mill else pass
        auto it = std::find(checkVerticalMills.begin(), checkVerticalMills.end(), i);
        if(it == checkVerticalMills.end()){
            if (piece1 == player && piece2 == player && piece3 == player) {
            MorabarabaResults << " (mill = "<<"S"<<0<<"i"<<verticalMills[i][0]<<", "<<"S"<<1<<"i"<<verticalMills[i][1]<<", "<<"S"<<2<<"i"<<verticalMills[i][2]<<") ";
            checkVerticalMills.push_back(i);
            return true;
            }
        }
    }

    return false; // No mill formed
}


// Capture Pieces
void removePiece(int** board, int player, ofstream& MorabarabaResults) {

    int row, col;
   generateRandomPosition(3, 8, row, col);

// Dont capture own piece
    if (board[row][col] != player && board[row][col] != 0) {
        board[row][col] = 0;
        if(player == 1){
            MorabarabaResults<<"P"<<2<<" losses cow (" <<"S"<<row<<", i"<<col<<") | ";
        }
        else{
            MorabarabaResults<<"P"<<1<<" losses cow ("<<"S"<<row<<", i"<<col<<") | ";
        }
        if (player == 1){
            int pOnePieces = countPieces(board, 2);

            MorabarabaResults << (pOnePieces) << " left";
        }
          
        else{ 
            int pTwoPieces = countPieces(board, 1);
            MorabarabaResults << (pTwoPieces) << " left";

        }
           
    } else {
        removePiece(board, player, MorabarabaResults);
    }
}


int switchPlayer(int player) {
    if (player == 1)
        player = 2;
    else
        player = 1;

    return player;
}


// Check if any piece can be moved else end game
bool canMovePiece(int **board, int row, int col) {
   
    if ((col + 1 < 8 && board[row][col + 1] == 0) ||
        (col - 1 >= 0 && board[row][col - 1] == 0) ||
        (row + 1 < 3 && board[row + 1][col] == 0) ||
        (row - 1 >= 0 && board[row - 1][col] == 0))
        return true;

    return false;
}


bool isGameOver(int **board, int piecesOffBoardPlayerOne, int piecesOffBoardPlayerTwo) {
    bool whiteCanMove = false;
    bool blackCanMove = false;
    int pTwoPieces = countPieces(board, 1);
    int pOnePieces = countPieces(board, 2);

    // Check if player has enough pieces left in the board and outside the board
    if(pOnePieces + piecesOffBoardPlayerOne  < 3 || pTwoPieces + piecesOffBoardPlayerTwo < 3){
        
        return true;
    }

// Check if any piece can be moved
    for (int i = 0; i < 3; ++i) {
        for (int j= 0; j < 8; ++j) {
            if (board[i][j] == 1) {
                if (canMovePiece(board, i, j)) {
                    whiteCanMove = true;
                    break;
                }
            } else if (board[i][j] == 2) {
                if (canMovePiece(board, i, j)) {
                    blackCanMove = true;
                    break;
                }
            }
        }
    }

    return !whiteCanMove && !blackCanMove;
}



void startGame(){
     Game game;
    // Create and Open file
    ofstream MorabarabaResults("morabarabaResults.txt");

    // Ensure random seed for random number generator
    srand((unsigned int)time(NULL));


    // Generate new board
    int player = 1;

    // Current Game Round
    int indexForGameTurn = 0; 

    while(true){

        // Check if we still have piece numbers from the input file
        if(game.readFromFile()[indexForGameTurn] < 4 || game.readFromFile()[indexForGameTurn] > 12){
            break;
        }

        //Assign piece number
        game.piecesOffBoardPlayerTwo = game.readFromFile()[indexForGameTurn];
        game.piecesOffBoardPlayerOne = game.readFromFile()[indexForGameTurn];
        

        MorabarabaResults<<endl<<game.readFromFile()[indexForGameTurn]<<"\n"; //Print the piece number before each game  
        game.board = game.createBoard(3, 8);   // Generate new board
        indexForGameTurn++; // Increment game turn



    while (true) {
        // Check if enough pieces
        if (game.piecesOffBoardPlayerTwo > 0 || game.piecesOffBoardPlayerOne > 0) {
 
            int row, col;
              generateRandomPosition(3, 8, row, col);
            if (isValidPlacement(game.board, row, col)) {
                game.board[row][col] = player;
                MorabarabaResults<<endl<<"P"<<player<<" 00-"<<"S"<<row<<", i"<<col;
                if (isMillFormed(game.board, row, col, player, MorabarabaResults)){
                    removePiece(game.board, player, MorabarabaResults);
                }
                    
                if (player == 1){
                    game.piecesOffBoardPlayerOne--;
                }
                    
                else
                    {
                      game.piecesOffBoardPlayerTwo--;  
                    }
                    
            } else {
                continue;
            }
        } else {
          int srcRow, srcCol;
             generateRandomPosition(3, 8, srcRow, srcCol);

                 int destRow, destCol;
                generateRandomPosition(3, 8, destRow, destCol);

            if (isValidMove(game.board, srcRow, srcCol, destRow, destCol, player)) {
                game.board[srcRow][srcCol] = 0;
                game.board[destRow][destCol] = player;

                
                
                    if (isMillFormed(game.board,destRow, destCol, player, MorabarabaResults)){
              
                        removePiece(game.board,player, MorabarabaResults); 
                       
                    }
                    else{
                          MorabarabaResults<<endl<<"P"<<(player % 2) + 1<<" "<<"S"<<srcRow<<", i"<<srcCol<<"-"<<"S"<<destRow<<", i"<<destCol<<" ";
                    }
                  
                    
            } else {
                continue;
            }
    
        }

        if (isGameOver(game.board, game.piecesOffBoardPlayerOne, game.piecesOffBoardPlayerTwo)) {
            MorabarabaResults << endl << endl;

            MorabarabaResults << "P";
            if (player == 1)
                MorabarabaResults << '1';
            else
                MorabarabaResults << '2';
            MorabarabaResults << " wins" << endl;
            break;
        }

        player = switchPlayer(player);
    }
    }
    MorabarabaResults.close();
}




int main() {
    startGame();
    return 0;
}
