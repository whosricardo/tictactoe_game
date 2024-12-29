#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>


typedef struct
{
    char action;

} Player;

char board[3][3]; // Board

char winningCheck(char board[3][3], Player player, Player computer, char *pWinner); // Will return winner (function prototype)
void playerAction(Player player); // Player action (function prototype)
void computerAction(Player computer); // Computer action (function prototype)
void printBoard(char board[3][3]); // Prints board (function prototype)
void resetboard(char board[3][3]); // Resets board (function prototype)
int checkFreeSpaces(char board[3][3], int action[2], Player player); // Checks for spaces (function prototype)

int main()
{
    srand(time(0)); // Defines seed 
    Player player = {'X'}; // Default
    Player computer = {'O'}; // Default
    char winner = ' '; // Default
    char *pWinner = &winner; // Pointer for winner
    char winningMessage[25]; // Winner Message
    int gameRunning = 0; // Game runner controller
    int *pGameRunning = &gameRunning; // Game runner controller pointer
    int totalMoves = 0; // Tie Checker
    char restart = 0; // Restart controller

    // Asks if player wants to change character
    char player_response;
    printf("\nYou want to play as 'X' or 'O'(Default: X). If 'O' insert O, if 'ENTER'");
    scanf("%c", &player_response);
    player_response = toupper(player_response);

    // Changes char based on the response
    if (player_response == 'O')
    {
        player.action = 'O'; // Defines new char for player
        computer.action = 'X'; // Defines new char for computer

        printf("\nDebugging: User selected 'O'");
    }

    resetboard(board);
    // Main Loop 
    while (*pGameRunning == 0)
    {
        // Player takes action
        playerAction(player);

        // Checks if after player moves it's a win
        if (winningCheck(board, player, computer, pWinner) != 0)
        {
            *pGameRunning = 1;
            break;
        }

        // Tie checker
        if (totalMoves == 9)
        {
            printf("\nIt's a tie!\n");

            *pGameRunning = 1;

            break;
        }

        // Computer takes action
        computerAction(computer);
        totalMoves++;

        // Checks if after computer moves it's a win
        if (winningCheck(board, player, computer, pWinner) != 0)
        {
            *pGameRunning = 1;
            break;
        }
    }
    

    printf("Winner is %c", *pWinner);
    
    return 0;
}

// Function to check win
char winningCheck(char board[3][3], Player player, Player computer, char *pWinner)
{
    for (int i = 0; i < 3; i++)
    {
        // Checks player rows
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == player.action) 
        {
            *pWinner = player.action; // Assigns new value to pointer of winner
            return 1;
        }

        // Checks computer rows
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] == computer.action) 
        {
            *pWinner = computer.action; // Assigns new value to pointer of winner
            return 1;
        }

        // Checks player columns
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == player.action) 
        {
            *pWinner = player.action; // Assigns new value to pointer of winner
            return 1;
        }

        // Checks computer columns
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] == computer.action) 
        {
            *pWinner = computer.action; // Assigns new value to pointer of winner
            return 1;
        }

    }
    // Check player diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == player.action)
    {
        *pWinner = player.action;
        return 1;
    }
    // Check player diagonals
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == player.action)
    {
        *pWinner = player.action;
        return 1;
    }

    // Check computer diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == computer.action)
    {
        *pWinner = computer.action;
        return 1;
    }
    // Check computer diagonals
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == computer.action)
    {
        *pWinner = computer.action;
        return 1;
    }

    return 0; // No winner yet
}

// Function to control player action
void playerAction(Player player)
{
    int actions[2]; // Action
    int action_taken = 0; // Verifier

    printBoard(board); // Prints board to player see spaces

    while (!action_taken)
    {
        printf("\nSelect your move, rows (0-2): ");
        scanf("%d", &actions[0]); // Assigns row value 

        printf("\nSelect your move, columns (0-2): ");
        scanf("%d", &actions[1]); // Assigns column value

        // Action Verifier
        if (checkFreeSpaces(board, actions, player) == 0)
        {
            printf("\nMove has been registered successfully");
            printBoard(board); // Remember to remove this

            action_taken = 1; // Action has been taken, stopping the loop
        }
        else
        {
            printf("\nYou can't do this move");

            action_taken = 0; // Action hasn't been taken, continuing the loop
        }
    }
}

// Function to control computer action
void computerAction(Player computer)
{
    int actions[2]; // Action
    int action_taken = 0; // Verifier

    while (!action_taken)
    {

        int row_move = rand() % 3 - 1; // Random number between 0 - 2
        int column_move = rand() % 3 - 1; // Random number between 0 - 2

        actions[0] = row_move; // Assigns row
        actions[1] = column_move; // Assigns column

        if (checkFreeSpaces(board, actions, computer) == 0)
        {
            printf("\nComputer actions has been taken");
            printBoard(board); // Remember to remove this 

            action_taken = 1; // Computer selected a free space and took his action
        }
        else
        {
            action_taken = 0; // Computer selected a existing space
        }
    }
}

// Function to print board 
void printBoard(char board[3][3])
{
    printf("\n %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n---|---|---\n");
    printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

// Function to reset board
void resetboard(char board[3][3])
{
    for (int i = 0; i < 3; i++) // Rows
    {
        for (int j = 0; j < 3; j++) // Columns
        {
            board[i][j] = ' '; // Assigns blank characters to board spaces
        }
    }
}

// Checks for free spaces before completing a move
int checkFreeSpaces(char board[3][3], int action[2], Player player)
{
    if (board[action[0]][action[1]] == ' ') // Checks if the space is free
    {
        board[action[0]][action[1]] = player.action; // Replaces the blank space with player char
        return 0;
    }
    else
    {
        return 1;
    }
}