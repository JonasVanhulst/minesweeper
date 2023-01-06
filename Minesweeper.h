#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include "string.h"
#include "ctype.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"

#define MAX_LEN_PLAYER_NAME 20

#define COL_COUNT_START 1
#define FIELD_ROWS 8
#define FIELD_COLS 8

int userInput[2];
int minefield[9][9], emptyMinefield[9][9], gameOverMinefield[9][9];

static bool getPlayerGuess();

static bool translatePlayerInput(char row, char col);

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

static void createMinefield(int totalMines) {
    int mines = 0;
    int row, col = COL_COUNT_START;
    srand(time(NULL));

    while (col <= FIELD_COLS) {
        while (row <= FIELD_ROWS) {
            minefield[row][col] = '-';
            emptyMinefield[row][col] = minefield[row][col];
            gameOverMinefield[row][col] =  minefield[row][col];

            row++;
        }
        row = 1;
        col++;
    }

    col = 1;
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

static void printField(int (*arr)[9]) {
    printf("   ");
    for(int i = 65; i < 73; i++) {
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

static void playNewGame() {
    short totalMinesOnField = 0;
    bool isGameOver = false;

    // Ask user for total bombs
    printf("\nTime for a new game 💥, how many 💣 would you like to place on the field ? ");
    scanf("%hd", &totalMinesOnField);

    createMinefield(totalMinesOnField);
    printf("New Field was created, Have Fun !!\n\n");

    printField(gameOverMinefield);

    do {
        isGameOver = getPlayerGuess();
    } while (!isGameOver);
}

int findIndex(char val) {
    char lookup[10] = { ' ', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    int foundIndex = -1;

    for (int i = 0; i < sizeof(lookup); i++) {
        if (lookup[i] ==  val) {
            foundIndex = i;
            break;
        }
    }
    return foundIndex;
}

static bool translatePlayerInput(char row, char col) {
    if (atoi(&row) == 0) {
        userInput[1] = findIndex(tolower(row));
        userInput[0] = atoi(&col);

        printf("First entry was a char : %d,%d\n", userInput[1],userInput[0]);
    } else {
        userInput[0] = atoi(&row);
        userInput[1] = findIndex(tolower(col));

        printf("Last entry was a char : %d,%d\n", userInput[0],userInput[1]);
    }

    return (userInput[0] >= COL_COUNT_START && userInput[0] <= 8 && userInput[1] >= COL_COUNT_START &&
        userInput[1] <= 8) ? true : false;
}

static bool getPlayerGuess() {
    char moveX, moveY;

    printField(emptyMinefield);

    printf("\nPlace your move 🕵️ : ");
    scanf(" %c %c", &moveX, &moveY);
    if (translatePlayerInput(moveX,moveY)) {
        emptyMinefield[userInput[1]][userInput[0]] = '0';
        return false;
    } else if (minefield[userInput[1]][userInput[0]] == '#') {
        return true;
    } else if (emptyMinefield[userInput[1]][userInput[0]] != '-') {
        printf("You already searched for a 💣 on this field! \n\n");
    }
    return false;
}

static void initGame() {
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
            exit(EXIT_FAILURE);
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
