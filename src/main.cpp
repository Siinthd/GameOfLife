#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

// Параметры игры
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int CELL_SIZE = 10;  // Размер клетки
const int GRID_WIDTH = WINDOW_WIDTH / CELL_SIZE;
const int GRID_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;

// Функция для вычисления следующего поколения
std::vector<std::vector<bool>> computeNextGeneration(const std::vector<std::vector<bool>>& grid) {
    std::vector<std::vector<bool>> nextGrid = grid;

    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            int liveNeighbors = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0) continue;
                    int nx = (x + i + GRID_WIDTH) % GRID_WIDTH;
                    int ny = (y + j + GRID_HEIGHT) % GRID_HEIGHT;
                    if (grid[nx][ny]) liveNeighbors++;
                }
            }

            if (grid[x][y] && (liveNeighbors < 2 || liveNeighbors > 3)) {
                nextGrid[x][y] = false; // Клетка умирает
            } else if (!grid[x][y] && liveNeighbors == 3) {
                nextGrid[x][y] = true; // Клетка рождается
            }
        }
    }
    return nextGrid;
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    bool paused = true;
    SDL_Event event;

    std::vector<std::vector<bool>> grid(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false));

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && paused) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                int gridX = mouseX / CELL_SIZE;
                int gridY = mouseY / CELL_SIZE;
                grid[gridX][gridY] = !grid[gridX][gridY]; // Инвертировать клетку
            }

            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_SPACE) {
                    paused = !paused; // Пауза или запуск игры
                }
            }
        }

        if (!paused) {
            grid = computeNextGeneration(grid);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Рисуем сетку
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for (int x = 0; x < GRID_WIDTH; ++x) {
            for (int y = 0; y < GRID_HEIGHT; ++y) {
                if (grid[x][y]) {
                    SDL_Rect cell = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};
                    SDL_RenderFillRect(renderer, &cell);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(100); // Задержка между кадрами
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
