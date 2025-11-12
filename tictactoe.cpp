#include <iostream>

using namespace std;

// global matrix
char grid[3][3];

void gameStart()
{
    char value = '1';
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            grid[i][j] = value++;
        }
    }
}

void currentGrid()
{ // using - instead of _
    cout << "\n";
    cout << "-------------\n";
    for (int i = 0; i < 3; i++)
    {
        cout << "| ";
        for (int j = 0; j < 3; j++)
        {
            cout << grid[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
    cout << "\n";
}

// make a move

bool makeMove(char turn, int cellnumber)
{
    int row = (cellnumber - 1) / 3;
    int col = (cellnumber - 1) % 3; // as we are starting from 1 so (-1)

    if (cellnumber < 1 || cellnumber > 9)
    {
        cout << "Invalid cell! Choose between 1-9.\n";
        return false;
    }

    if (grid[row][col] == 'X' || grid[row][col] == 'O')
    { // is already acquired
        cout << "Cell already taken! Choose another.\n";
        return false;
    }
    grid[row][col] = turn;
    return true;
}

char checkWinner()
{
    // checking  Rows
    for (int i = 0; i < 3; i++)
    {
        if (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
            return grid[i][0];
    }

    // checking  Columns
    for (int j = 0; j < 3; j++)
    {
        if (grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j])
            return grid[0][j];
    }

    // checking Diagonals
    if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
    {
        return grid[0][0];
    }

    if (grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
    {
        return grid[0][2];
    }

    return ' ';
}

// all the cells are covered
bool isDraw()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] != 'X' && grid[i][j] != 'O')
                return false;
    return true;
}

int main()
{
    char turn;
    char winner = ' ';
    int cell;

    gameStart();

    cout<<endl;

      cout << " $$$$$$$\\  $$$$$$\\  $$$$$$\\        $$$$$$$$\\  $$$$$$\\   $$$$$$\\        $$$$$$$$\\  $$$$$$\\  $$$$$$$$\\ " << endl;
    cout << " \\__$$  __|\\__$$  _|$$  __$$\\       \\__$$  __|$$  __$$\\ $$  __$$\\       \\__$$  __|$$  __$$\\ $$  _____|" << endl;
    cout << "    $$ |     $$ |  $$ /  \\__|         $$ |   $$ /  $$ |$$ /  \\__|         $$ |   $$ /  $$ |$$ |      " << endl;
    cout << "    $$ |     $$ |  $$ |               $$ |   $$$$$$$$ |$$ |               $$ |   $$ |  $$ |$$$$$\\    " << endl;
    cout << "    $$ |     $$ |  $$ |               $$ |   $$  __$$ |$$ |               $$ |   $$ |  $$ |$$  __|   " << endl;
    cout << "    $$ |     $$ |  $$ |  $$\\          $$ |   $$ |  $$ |$$ |  $$\\          $$ |   $$ |  $$ |$$ |      " << endl;
    cout << "    $$ |   $$$$$$\\ \\$$$$$$  |         $$ |   $$ |  $$ |\\$$$$$$  |         $$ |    $$$$$$  |$$$$$$$\\ " << endl;
    cout << "    \\__|   \\______| \\______/          \\__|   \\__|  \\__| \\______/          \\__|    \\______/ \\________|" << endl;
    cout << endl << endl;
    

    cout << "Player 1 -> X\nPlayer 2 -> O\n";
    cout << "Choose who makes the first move (X or O): ";
    cin >> turn;

    turn = toupper(turn);

    currentGrid();

    while (true)
    {
        cout << "Player " << turn << ", enter a cell (1-9): ";
        cin >> cell;

        if (!makeMove(turn, cell))
            continue;
        currentGrid();

        winner = checkWinner();

        if (winner != ' ')
        {
            cout << " Player " << winner << " wins! \n";
            break;
        }
        else if (isDraw())
        {
            cout << "It's a draw! \n";
            break;
        }

        // Switching  turn
        turn = (turn == 'X') ? 'O' : 'X';
    }

    cout << "\nThanks for playing!\n";
    return 0;
}