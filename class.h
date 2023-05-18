#include <iostream>
using namespace std;

class Game {
    public:
        
        int piecesOffBoardPlayerTwo;
        int piecesOffBoardPlayerOne;


    public:
        int **board = new int*[3];
        int ** createBoard(int rows, int cols) 
        {
            for(int i = 0; i < rows; ++i) {
            board[i] = new int[rows]; 
        }
         for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            board[i][j] = 0;
        }
    }    
        return board;

}       
    // Read from the input file

    int * readFromFile() {
    
        int _size;
        int i = 0;

        int *boardSize = new int[i]; //Create an empty array to hold the inputs

        string size; 
        ifstream Input("input.txt"); // Opens file
        
        if(Input.is_open() && Input.peek() != Input.eof()) //Check cursor position in input file
        {
            while (!Input.eof()) 
            {
                getline(Input, size); 
                _size = stoi(size); // Convert string into integer
                boardSize[i] = _size;
                i++; 
            }
        }
        else 
        {
            exit(10);
        }
        Input.close();
        return boardSize;

    };




};

