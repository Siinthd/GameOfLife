#include "GameOfLife.h"


 
GameOfLife::GameOfLife(int windowWidth, int windowHeight, int cellSize,int speed)
    : m_windowWidth(windowWidth), m_windowHeight(windowHeight), m_cellSize(cellSize), m_running(true), m_paused(true),m_speed(speed) {
    m_gridWidth = m_windowWidth / m_cellSize;
    m_gridHeight = m_windowHeight / m_cellSize;
 
    SDL_Init(SDL_INIT_VIDEO);
 
    m_window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowWidth, m_windowHeight, 0);
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
 
    m_grid.resize(m_gridWidth, std::vector<bool>(m_gridHeight, false));
}
 
GameOfLife::~GameOfLife() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}
 
void GameOfLife::run() {
    while (m_running) {
        processEvents();
        if (!m_paused) {
            update();
        }
        render();
        SDL_Delay(m_speed); // Задержка между кадрами
    }
}
 
void GameOfLife::processEvents() {
    while (SDL_PollEvent(&m_event)) {
        if (m_event.type == SDL_QUIT) {
            m_running = false;
        }
 
        if (m_event.type == SDL_MOUSEBUTTONDOWN && m_paused) {
            int mouseX, mouseY;
            SDL_GetMouseState(&mouseX, &mouseY);
            int gridX = mouseX / m_cellSize;
            int gridY = mouseY / m_cellSize;
            m_grid[gridX][gridY] = !m_grid[gridX][gridY]; // Инвертировать клетку
        }
 
        if (m_event.type == SDL_KEYDOWN) {
            if (m_event.key.keysym.sym == SDLK_SPACE) {
                m_paused = !m_paused; // Пауза или запуск игры
            }
        }
    }
}
 
void GameOfLife::update() {
    m_grid = computeNextGeneration();
}
 
std::vector<std::vector<bool>> GameOfLife::computeNextGeneration() {
    std::vector<std::vector<bool>> nextGrid = m_grid;
 
    for (int x = 0; x < m_gridWidth; ++x) {
        for (int y = 0; y < m_gridHeight; ++y) {
            int liveNeighbors = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    if (i == 0 && j == 0) continue;
                    int nx = (x + i + m_gridWidth) % m_gridWidth;
                    int ny = (y + j + m_gridHeight) % m_gridHeight;
                    if (m_grid[nx][ny]) liveNeighbors++;
                }
            }
 
            if (m_grid[x][y]) {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    nextGrid[x][y] = false; // Клетка умирает
                }
            } else {
                if (liveNeighbors == 3) {
                    nextGrid[x][y] = true; // Клетка рождается
                }
            }
        }
    }
 
    return nextGrid;
}
 
void GameOfLife::render() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

         // Рисуем сетку
        SDL_SetRenderDrawColor(m_renderer, 70, 70, 70, 180);
        for (int x = 0;x<m_windowWidth;x+=m_cellSize)
            SDL_RenderDrawLine(m_renderer,x,0,x,m_windowHeight);
        for (int y = 0;y<m_windowHeight;y+=m_cellSize)
            SDL_RenderDrawLine(m_renderer,0,y,m_windowWidth,y);

    // Рисуем клетки
    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    for (int x = 0; x < m_gridWidth; ++x) {
        for (int y = 0; y < m_gridHeight; ++y) {
            if (m_grid[x][y]) {
                SDL_Rect cell = {x * m_cellSize, y * m_cellSize, m_cellSize, m_cellSize};
                SDL_RenderFillRect(m_renderer, &cell);
            }
        }
    }
 
    SDL_RenderPresent(m_renderer);
}
