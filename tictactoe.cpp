#include<iostream>
#include <typeinfo>
using namespace std;


//global matrix
char grid[3][3];

void gameStart(){
    char value = '1';
    for(int i = 0 ; i <3;i++){
        for(int j = 0 ; j < 3 ; j++){
            grid[i][j]=value++;
        }

    }
}

void currentGrid() {//using - instead of _
    cout << "\n";
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << grid[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
    cout << "\n";
    
}

//make a move

bool makeMove(char turn, int cellnumber ){
    int row = (cellnumber - 1) / 3;
    int col = (cellnumber - 1) % 3; //as we are starting from 1 so (-1)

        if(typeid(cellnumber).name()!="i"){// checking type 
             cout << "Invalid cell! Choose between 1 to 9.\n";
             return false;
        }

     if (cellnumber < 1 || cellnumber > 9) {
        cout << "Invalid cell! Choose between 1-9.\n";
        return false;
    }

    if (grid[row][col] == 'X' || grid[row][col] == 'O') {//is already acquired
        cout << "Cell already taken! Choose another.\n";
        return false;
    }
    grid[row][col] = turn;
    return true;

}

char checkWinner() {
    // checking  Rows
    for (int i = 0; i < 3; i++){
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
            return grid[i][0];}

    //checking  Columns
    for (int j = 0; j < 3; j++){
        if (grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j])
            return grid[0][j];}

    //checking Diagonals
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]){
        return grid[0][0];}

    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0]){
        return grid[0][2];}

    return ' ';
}



int main(){
    gameStart();
    currentGrid();


return 0;
}