#include <SDL2/SDL.h>
#include <vector>

const int WIDTH = 800;
const int HEIGHT = 600;
const int CELL_SIZE = 10;
const int GRID_WIDTH = WIDTH / CELL_SIZE;
const int GRID_HEIGHT = HEIGHT / CELL_SIZE;

class GameOfLife {
public:
    GameOfLife();
    ~GameOfLife();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void toggleCell(int x, int y);
    bool isAlive(int x, int y) const;
    int countNeighbors(int x, int y) const;

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    std::vector<std::vector<bool>> grid;
};

GameOfLife::GameOfLife()
    : running(true), grid(GRID_WIDTH, std::vector<bool>(GRID_HEIGHT, false)) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

GameOfLife::~GameOfLife() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void GameOfLife::run() {
    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(100); // Adjust delay for simulation speed
    }
}

void GameOfLife::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            toggleCell(x / CELL_SIZE, y / CELL_SIZE);
        }
    }
}

void GameOfLife::update() {
    std::vector<std::vector<bool>> newGrid = grid;
    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            int neighbors = countNeighbors(x, y);
            if (isAlive(x, y)) {
                newGrid[x][y] = neighbors == 2 || neighbors == 3;
            } else {
                newGrid[x][y] = neighbors == 3;
            }
        }
    }
    grid = newGrid;
}

void GameOfLife::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            if (grid[x][y]) {
                SDL_Rect cellRect = { x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE };
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void GameOfLife::toggleCell(int x, int y) {
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        grid[x][y] = !grid[x][y];
    }
}

bool GameOfLife::isAlive(int x, int y) const {
    if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
        return grid[x][y];
    }
    return false;
}

int GameOfLife::countNeighbors(int x, int y) const {
    int count = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            if (isAlive(x + dx, y + dy)) {
                ++count;
            }
        }
    }
    return count;
}

int main(int argc, char* argv[]) {
    GameOfLife game;
    game.run();
    return 0;
}
