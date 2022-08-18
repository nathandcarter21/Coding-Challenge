#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <vector>

const int ROW = 3;
const int COL = 3;
const int TURNS = 9;

void PrintBoard(char board[3][3]) // print game board
{
    std::cout << std::endl;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            std::cout << board[i][j];
            if (j < 2)
            {
                std::cout << "|";
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void PlayerTurn(char board[3][3]) // player's turn
{
    std::cout << "Player, pick which space you would like to select 1-9: ";
    int num;
    std::cin >> num;
    while (board[(num - 1) / 3][(num - 1) % 3] == 'O' || board[(num - 1) / 3][(num - 1) % 3] == 'X' || num < 1 || num > 9) // make sure selected space isn't taken
    {
        std::cout << "Please select valid square: ";
        std::cin >> num;
    }
    board[(num - 1) / 3][(num - 1) % 3] = 'X'; // fill in  selected space with X
}

void CompTurn(char board[3][3]) // computer's turn
{
    // the computer will start its turn by going through each row, column, and diagonal looking for winning moves and possible moves. If it finds a winning move it will take that square and return ending its turn. A possible move is any move that adds to a double ie it will block a win for the other player. Possible moves won't end the turn right there because the computer still wants to see if there is an opportunity to win, so it just adds possible moves to a vector with the position of the square 1-9. If the computer can't find any winning moves and the possible moves vector is empty, then it will pick a random square to fill.

    std::vector<int> possibleMoves;
    for (int i = 0; i < ROW; i++) // check for doubles in rows
    {
        if (board[i][0] == board[i][1] && board[i][2] != 'X' && board[i][2] != 'O')
        {
            if (board[i][0] == 'O') // winning move
            {
                board[i][2] = 'O';
                return;
            }
            possibleMoves.push_back((3 * i) + 3); // add possible move
        }
        if (board[i][0] == board[i][2] && board[i][1] != 'X' && board[i][1] != 'O')
        {
            if (board[i][0] == 'O')
            {
                board[i][1] = 'O';
                return;
            }
            possibleMoves.push_back((3 * i) + 2); // add possible move
        }
        if (board[i][1] == board[i][2] && board[i][0] != 'X' && board[i][0] != 'O')
        {
            if (board[i][1] == 'O')
            {
                board[i][0] = 'O';
                return;
            }
            possibleMoves.push_back((3 * i) + 1); // add possible move
        }
    }
    for (int i = 0; i < COL; i++) // check for doubles in cols
    {
        if (board[0][i] == board[1][i] && board[2][i] != 'X' && board[2][i] != 'O')
        {
            if (board[0][i] == 'O') // winning move
            {
                board[2][i] = 'O';
                return;
            }
            possibleMoves.push_back(i + 7); // add possible move
        }
        if (board[0][i] == board[2][i] && board[1][i] != 'X' && board[1][i] != 'O')
        {
            if (board[0][i] == 'O') // winning move
            {
                board[1][i] = 'O';
                return;
            }
            possibleMoves.push_back(i + 4); // add possible move
        }
        if (board[1][i] == board[2][i] && board[0][i] != 'X' && board[0][i] != 'O')
        {
            if (board[1][i] == 'O') // winning move
            {
                board[0][i] = 'O';
                return;
            }
            possibleMoves.push_back(i + 1); // add possible move
        }
    }
    // check for doubles in diagonals
    if (board[0][0] == board[1][1] && board[2][2] != 'X' && board[2][2] != 'O')
    {
        if (board[0][0] == 'O') // winning move
        {
            board[2][2] = 'O';
            return;
        }
        possibleMoves.push_back(9); // add possible move
    }
    if (board[0][0] == board[2][2] && board[1][1] != 'X' && board[1][1] != 'O')
    {
        if (board[0][0] == 'O') // winning move
        {
            board[1][1] = 'O';
            return;
        }
        possibleMoves.push_back(5); // add possible move
    }
    if (board[1][1] == board[2][2] && board[0][0] != 'X' && board[0][0] != 'O')
    {
        if (board[1][1] == 'O') // winning move
        {
            board[0][0] = 'O';
            return;
        }
        possibleMoves.push_back(1); // add possible move
    }
    if (board[0][2] == board[1][1] && board[2][0] != 'X' && board[2][0] != 'O')
    {
        if (board[0][2] == 'O') // winning move
        {
            board[2][0] = 'O';
            return;
        }
        possibleMoves.push_back(7); // add possible move
    }
    if (board[0][2] == board[2][0] && board[1][1] != 'X' && board[1][1] != 'O')
    {
        if (board[0][2] == 'O') // winning move
        {
            board[1][1] = 'O';
            return;
        }
        possibleMoves.push_back(5); // add possible move
    }
    if (board[1][1] == board[2][0] && board[0][2] != 'X' && board[0][2] != 'O')
    {
        if (board[1][1] == 'O') // winning move
        {
            board[0][2] = 'O';
            return;
        }
        possibleMoves.push_back(3); // add possible move
    }

    if (possibleMoves.size() != 0)
    {
        board[(possibleMoves[0] - 1) / 3][(possibleMoves[0] - 1) % 3] = 'O';
        return;
    }

    // if there is no doubles, pick a random square

    int num = rand() % 10;
    while (board[(num - 1) / 3][(num - 1) % 3] == 'O' || board[(num - 1) / 3][(num - 1) % 3] == 'X' || num < 1 || num > 9) // run until random space isn't taken
    {
        num = rand() % 10;
    }
    board[(num - 1) / 3][(num - 1) % 3] = 'O'; // fill in selected space with O
}

void CheckScore(char board[3][3], bool &winner) // check to see if someone has won
{
    for (int i = 0; i < ROW; i++) // check each row
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            if (board[i][0] == 'X')
            {
                PrintBoard(board);
                std::cout << "You win!" << std::endl;
            }
            else
            {
                std::cout << "Computer wins :(" << std::endl;
            }
            winner = true;
            return;
        }
    }
    for (int i = 0; i < COL; i++) // check each col
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            if (board[0][i] == 'X')
            {
                PrintBoard(board);
                std::cout << "You win!" << std::endl;
            }
            else
            {
                std::cout << "Computer wins :(" << std::endl;
            }
            winner = true;

            return;
        }
    }
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) // check top-left to btm-right diagonal
    {
        if (board[0][0] == 'X')
        {
            PrintBoard(board);
            std::cout << "You win!" << std::endl;
        }
        else
        {
            std::cout << "Computer wins :(" << std::endl;
        }
        winner = true;

        return;
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) // check top-right to btm-left diagonal
    {
        if (board[0][2] == 'X')
        {
            PrintBoard(board);
            std::cout << "You win!" << std::endl;
        }
        else
        {
            std::cout << "Computer wins :(" << std::endl;
        }
        winner = true;

        return;
    }
    return;
}

int main(int argc, char *argv[])
{
    srand(time(0)); // get random seed
    std::cout << "Welcome to Nathan's Tic Tac Toe game" << std::endl;
    std::cout << "Type 1 to go first, 2 to go second, and 3 to quit: ";
    int num;
    std::cin >> num;
    while (num != 3) // runs while user still wants to play
    {
        char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}}; // initialize board
        bool winner = false;

        if (num == 1) // player goes first
        {
            PrintBoard(board);

            for (int i = 0; i < TURNS; i++) // loop 9 times for each turn
            {
                if (i % 2 == 0) // alternates between the player's and computer's turn
                {
                    PlayerTurn(board);
                }
                else
                {
                    CompTurn(board);
                    PrintBoard(board);
                }
                if (i > 3) // check score once at least 3 turns have been taken
                {
                    CheckScore(board, winner);
                }
                if (winner) // break out of loop if winner is detected
                {
                    break;
                }
            }
            if (!winner) // if there was no winner, it was a tie game
            {
                PrintBoard(board);
                std::cout << "Tie Game" << std::endl;
            }
        }
        else if (num == 2) // computer goes first
        {
            PrintBoard(board);
            // player second
            for (int i = 0; i < TURNS; i++) // loop 9 times for each turn
            {
                if (i % 2 == 0) // alternates between the player's and computer's turn
                {
                    CompTurn(board);
                    PrintBoard(board);
                }
                else
                {
                    PlayerTurn(board);
                }
                if (i > 3) // check score once at least 3 turns have been taken
                {
                    CheckScore(board, winner);
                }
                if (winner) // break out of loop if winner is detected
                {
                    break;
                }
            }
            if (!winner) // if there was no winner, it was a tie game
            {
                PrintBoard(board);
                std::cout << "Tie Game" << std::endl;
            }
        }
        else
        {
            break; // break out of while loop and end program
        }
        std::cout << "Would you like to play again?" << std::endl;
        std::cout << "Type 1 to go first, 2 for the computer to go first, and 3 to quit: ";
        std::cin >> num;
    }
    std::cout << "Thanks for playing! Goodbye" << std::endl;
    return 0;
}