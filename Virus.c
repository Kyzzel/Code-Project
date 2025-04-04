#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <time.h>

#define ROWS 20 
#define COLS 20

void initializeGrid(int grid[ROWS][COLS]) { 
    srand(time(NULL)); 
    for (int i = 0; i < ROWS; i++) { 
        for (int j = 0; j < COLS; j++) { 
            grid[i][j] = rand() % 2; 
        } 
    } 
}

void displayGrid(int grid[ROWS][COLS]) { 
    system("clear"); 
    for (int i = 0; i < ROWS; i++) { 
        for (int j = 0; j < COLS; j++) { 
            printf("%c ", grid[i][j] ? 'O' : '.'); 
        } 
        printf("\n"); 
    } 
}

void copyGrid(int src[ROWS][COLS], int dest[ROWS][COLS]) { 
    for (int i = 0; i < ROWS; i++) { 
        for (int j = 0; j < COLS; j++) { 
            dest[i][j] = src[i][j]; 
        } 
    } 
}

int countLiveNeighbors(int grid[ROWS][COLS], int x, int y) { 
    int count = 0; 
    for (int i = -1; i <= 1; i++) { 
        for (int j = -1; j <= 1; j++) { 
            if (i == 0 && j == 0) continue; 
            int nx = x + i, ny = y + j; 
            if (nx >= 0 && nx < ROWS && ny >= 0 && ny < COLS) { 
                count += grid[nx][ny]; 
            } 
        } 
    } 
    return count; 
}

void updateGeneration(int grid[ROWS][COLS]) { 
    int newGrid[ROWS][COLS]; 
    for (int i = 0; i < ROWS; i++) { 
        for (int j = 0; j < COLS; j++) { 
            int neighbors = countLiveNeighbors(grid, i, j); 
            if (grid[i][j] == 1) { 
                newGrid[i][j] = (neighbors == 2 || neighbors == 3) ? 1 : 0; 
            } else { 
                newGrid[i][j] = (neighbors == 3) ? 1 : 0; 
            } 
        } 
    } 
    copyGrid(newGrid, grid); 
}

int main() { 
    int grid[ROWS][COLS]; 
    initializeGrid(grid);

    while (1) {
        displayGrid(grid);
        updateGeneration(grid);
        usleep(200000);
    }

    return 0;
}