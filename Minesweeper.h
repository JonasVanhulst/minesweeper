#ifndef MINESWEEPER_H
#define MINESWEEPER_H

//** Include libraries
#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"

// Define constants
#define FIELD_ROWS 8
#define FIELD_COLS 8
#define COL_COUNT_START 1
#define MAX_LEN_PLAYER_NAME 20


// Minefields as global variables
int userInput[2];
int minefield[9][9], emptyMinefield[9][9], gameOverMinefield[9][9];

/**
 * Function to print the header at the start of each game
 */
static void printHeader() {
    printf("           _                                                   \n"
           "          (_)                                                  \n"
           " _ __ ___  _ _ __   ___  _____      _____  ___ _ __   ___ _ __ \n"
           "| '_ ` _ \\| | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n"
           "| | | | | | | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |   \n"
           "|_| |_| |_|_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   \n"
           "                                              | |              \n"
           "                                              |_|              ");
    printf("\n+-------------------------------------------------------------------+");
    printf("\n| Minesweeper, made by Jonas Vanhulst & Jasper Maes (PXL - Digital) |");
    printf("\n+-------------------------------------------------------------------+");
}

/**
 * Function to create the minefields based on the wanted total mines
 * @param totalMines amount of mines wanted on the field
 */
static void createMinefield(int totalMines) {
    int mines = 0;
    int row, col = COL_COUNT_START;
    srand(time(NULL));

    // Fill the field with '-' at the start of the game
    while (col <= FIELD_COLS) {
        while (row <= FIELD_ROWS) {
            minefield[row][col] = '-';
            emptyMinefield[row][col] = minefield[row][col];
            gameOverMinefield[row][col] = minefield[row][col];
            row++;
        }
        row = 1;
        col++;
    }

    col = 1;

    // Place mines randomly on field
    while (mines < totalMines) {
        row = rand() % FIELD_ROWS + 1;
        col = rand() % FIELD_COLS + 1;

        if (minefield[row][col] != '#') {
            minefield[row][col] = '#';
            gameOverMinefield[row][col] = minefield[row][col] = '#';
            mines++;
        }
    }
    row = 1;
    col = 1;
};

/**
 * Print minefield based on pointer to array
 * @param arr reference to array
 * @attention This function uses a pointer instead of array copying to save space in memory and
 * we don't have to create 3 functions to print each minefield (minefield, emptyMinefield, gameOverfield)
 */
static void printField(int (*arr)[9]) {
    printf("   ");
    for (int i = 65; i < 73; i++) {
        printf("|%c|", i);
    }
    printf("\n");
    for (int i = COL_COUNT_START; i <= FIELD_ROWS; i++) {
        printf("|%d|", i);
        for (int j = COL_COUNT_START; j <= FIELD_COLS; j++) {
            printf(" %c ", arr[i][j]);
        }
        printf("\n");
    }
}

/**
 * Function to search for a letter in the lookup table to get the index
 * @param val character value
 * @return found index or -1 if not found
 * @brief This function is used to translate input 1B to 12 so it can be
 * used directly in the program as locations in the minefield
 */
int findIndex(char val) {
    // create lookup table according to positioning of the minefield
    char lookup[10] = {' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int foundIndex = -1;

    for (int i = 0; i < sizeof(lookup); i++) {
        if (lookup[i] == val) {
            foundIndex = i;
            break;
        }
    }
    return foundIndex;
}

/**
 * Translate user input from <int><char> or <char><int> to <int><int> so it can be used in the minefield as location
 * @param row Player's chosen row
 * @param col Player's chosen col
 * @return true or false if the input is valid
 */
static bool translatePlayerInput(char row, char col) {
    if (atoi(&row) == 0) {
        userInput[1] = findIndex(tolower(row));
        userInput[0] = atoi(&col);
        // printf("First entry was a char : %d,%d\n", userInput[1], userInput[0]);
    } else {
        userInput[0] = atoi(&row);
        userInput[1] = findIndex(tolower(col));
        // printf("Last entry was a char : %d,%d\n", userInput[0], userInput[1]);
    }

    // check if guess is between valid boundaries
    return (userInput[0] >= COL_COUNT_START && userInput[0] <= 8 && userInput[1] >= COL_COUNT_START &&
            userInput[1] <= 8) ? true : false;
}

/**
 * Function to check how many fields are cleared
 * @return number of cleared fields
 */
int checkClearedFields() {
    int counter = 0;
    for (int i = 1; i < 9; i++) {
        for (int j = 1; j < 9; j++) {
            if (emptyMinefield[i][j] != '-') {
                counter++;
            }
        }
    }
    return counter;
}

/**
 * Function to count the surrounding mines
 * @param rowToCheck
 * @param colToCheck
 * @return
 */
int countSurroundingMines(int rowToCheck, int colToCheck) {
    int counter = 0;
    for (int i = rowToCheck-1; i <= rowToCheck + 1; i++) {
        for (int j = colToCheck -1 ; j <= colToCheck + 1 ; j++) {
            if ((i>0) && (i<9) && (j>0) && (j<9) && (minefield[i][j] =='#')) {
                counter++;
            }
        }
    }
    return counter;
}

/**
 * Function to reveal near scores when a guess is made (flood fill) (this uses recursion)
 * @param row row of the minefield
 * @param col col of the minefield
 */
void revealNearScores(int row, int col) {
    if (countSurroundingMines(row, col) != 0) {
        emptyMinefield[row][col] = countSurroundingMines(row, col) + 48;
        return;
    } else {
        for (int i = row-1; i <= row + 1; i++) {
            for (int j = col -1 ; j <= col + 1 ; j++) {
                if (emptyMinefield[i][j] == '-') {
                    emptyMinefield[row][col] = countSurroundingMines(row, col) + 48;
                    revealNearScores(i, j);
                }
            }
        }
    }
}

/**
 * Get the move from the player
 * @return true/false if player hit a mine else false and game can continue
 */
static bool getPlayerGuess() {
    char moveX, moveY;

    printField(emptyMinefield);

    printf("\nPlace your move 🕵️ : ");
    scanf(" %c %c", &moveX, &moveY);

    // Call function to translate <int><char> or <char><int> to <int><int>
    if (translatePlayerInput(moveX, moveY)) {
        if (emptyMinefield[userInput[0]][userInput[1]] != '-') {
            printf("You already searched for a 💣 on this field! \n\n");
        } else if (minefield[userInput[0]][userInput[1]] == '#') {
            return true;
        } else {
            // emptyMinefield[userInput[0]][userInput[1]] = '0';
            revealNearScores(userInput[0], userInput[1]);
        }
        return false;
    }
    return false;
}

/**
 * Function to check for win condition and print progress
 * @param totalMineOnField
 * @param guessCount amount of guesses
 * @return true/false player has won or not
 */
bool checkForWin(int totalMineOnField, int guessCount) {
    // Calculate percentage to complete
    float percentComplete = (((float) checkClearedFields() + totalMineOnField) / 64) * 100;
    printf("\n+-----------------------------------------------------+\n| Amount of "
           "moves = %3.d              Progress = %2.2f%% "
           "|\n+-----------------------------------------------------+\n\n",
           guessCount, percentComplete);

    if ((totalMineOnField + checkClearedFields()) == 64) {
        printField(gameOverMinefield);
        printf("\nCongratulations, You Won ! 🏁💪\n");
        return true;
    }
    return false;
}

/**
 * Function to print game over art
 * @return void
 */
static void gameOver() {
    printf("\n     .-^^---....,,--       \n _--                  --  \n<       "
           "                 >)\n|                         | \n \\._             "
           "      _./  \n    ```--. . , ; .--'''       \n          | |   |       "
           "      \n       .-=||  | "
           "|=-.   \n       `-=#$%&%$#=-'   \n          | ;  :|     \n "
           "___.,-#%&$@%#&#~,._____\n");
    printf("\nGAME OVER ❌, you hit a 💣 !\n\n");
    printField(gameOverMinefield);
    printf("\nBetter luck next time 👍 !\n");
}

/**
 * Function to start a new game
 * @return void
 */
static void playNewGame() {
    int guessCount = 0;
    short totalMinesOnField = 0;

    bool isGameOver = false;
    bool isWin = false;

    // Ask user for total bombs
    printf("\nTime for a new game 💥, how many 💣 would you like to place on the field ? ");
    scanf("%hd", &totalMinesOnField);

    createMinefield(totalMinesOnField);
    printf("New Field was created, Have Fun !!\n\n");

    printField(gameOverMinefield);

    while (!isGameOver && !isWin) {
        // Check if player hit a mine
        isGameOver = getPlayerGuess();
        guessCount++;
        // Check for win condition
        isWin = checkForWin(totalMinesOnField, guessCount);

        // If player lost end game
        if (isGameOver) gameOver();
    }
}

/**
 * Initial function to start the game
 * @return void
 */
static void playMinesweeper() {
    char playerName[MAX_LEN_PLAYER_NAME];
    char menuChoice;

    // Ask player for name
    printf("\nWelcome to the game! What is your name ?: ");
    fgets(playerName, MAX_LEN_PLAYER_NAME, stdin);

    // Print choice menu
    printf("Please select an option from the menu:\n\t - New game, press 'N'\n\t - Load game, press 'L'\n\t - Quit game, press 'Q'\n");

    do {
        printf("Enter choice : ");
        scanf(" %c", &menuChoice);
        menuChoice = tolower(menuChoice);

    } while (menuChoice != 'n' && menuChoice != 'l' && menuChoice != 'q');

    // Valid user input captured
    switch (menuChoice) {
        case 'q':
            exit(EXIT_SUCCESS);
        case 'n':
            playNewGame();
            break;
        case 'l':
            printf("Load Game");
            break;
        default:
            exit(EXIT_FAILURE);
    }
}

#endif //MINESWEEPER_H
