#include<iostream>
using namespace std;

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



int main(){
    gameStart();
    currentGrid();


return 0;
}