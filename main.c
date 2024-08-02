#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

#define MAZE_SIZE 20
#define SCREEN_WIDTH 1028
#define SCREEN_HEIGHT 1028

// Define the maze structure
typedef struct {
    int data[MAZE_SIZE][MAZE_SIZE];
    int root[2];
} Maze;

// Function to initialize the maze
void init_maze(Maze* maze) {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            if (i == 0) {
                maze->data[i][j] = 4;
            } else {
                maze->data[i][j] = 1;
            }
        }
    }
    maze->root[0] = 0;
    maze->root[1] = 0;
}

// Function to print the maze
void print_maze(Maze* maze) {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            printf("%d ", maze->data[i][j]);
        }
        printf("\n");
    }
}

// Function to draw the maze using SDL
void draw_maze(Maze* maze, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set color to black
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            if (maze->data[i][j] == 1) {
                SDL_Rect rect = {j * 50 + 25, (i - 1) * 50 + 25, 25, 75};
                SDL_RenderFillRect(renderer, &rect);
            } else if (maze->data[i][j] == 2) {
                SDL_Rect rect = {j * 50 + 25, i * 50 + 25, 75, 25};
                SDL_RenderFillRect(renderer, &rect);
            } else if (maze->data[i][j] == 3) {
                SDL_Rect rect = {j * 50 + 25, i * 50 + 25, 25, 75};
                SDL_RenderFillRect(renderer, &rect);
            } else if (maze->data[i][j] == 4) {
                SDL_Rect rect = {(j - 1) * 50 + 25, i * 50 + 25, 75, 25};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }
}

// Function to update the maze
void update_maze(Maze* maze) {
    int directions[4] = {1, 2, 3, 4};
    if (maze->root[0] == 0) {
        directions[3] = 0;
    } else if (maze->root[0] == MAZE_SIZE - 1) {
        directions[1] = 0;
    }
    if (maze->root[1] == 0) {
        directions[0] = 0;
    } else if (maze->root[1] == MAZE_SIZE - 1) {
        directions[2] = 0;
    }
    int random_index = rand() % 4;
    maze->data[maze->root[1]][maze->root[0]] = directions[random_index];
    if (maze->data[maze->root[1]][maze->root[0]] == 1) {
        maze->root[1]--;
    } else if (maze->data[maze->root[1]][maze->root[0]] == 2) {
        maze->root[0]++;
    } else if (maze->data[maze->root[1]][maze->root[0]] == 3) {
        maze->root[1]++;
    } else if (maze->data[maze->root[1]][maze->root[0]] == 4) {
        maze->root[0]--;
    }
    maze->data[maze->root[1]][maze->root[0]] = 0;
}

int main() {
    srand(time(NULL)); // Initialize random number generator

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Origin Shift Maze Generation Algorithm Implementation in C by Indibar Sarkar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Initialize maze
    Maze maze;
    init_maze(&maze);

    // Print initial maze
    print_maze(&maze);
    printf("\n");

    // Main loop
    while (1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                SDL_DestroyRenderer(renderer);
                SDL_DestroyWindow(window);
                SDL_Quit();
                return 0;
            }
        }

        // Clear screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 128, 255); // Set color to dark blue
        SDL_RenderClear(renderer);

        // Draw maze
        draw_maze(&maze, renderer);

        // Update maze
        update_maze(&maze);

        // Print maze
        print_maze(&maze);
        printf("\n");

        // Update screen
        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60); // Cap framerate at 60 FPS
    }

    return 0;
}