#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <cstdlib>

class GameOfLife {
public:
    GameOfLife(int windowWidth, int windowHeight, int cellSize,int speed);
    ~GameOfLife();
    void run();
 
private:
    void processEvents();
    void update();
    void render();
    std::vector<std::vector<bool>> computeNextGeneration();
 
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Event m_event;
 
    int m_windowWidth;
    int m_windowHeight;
    int m_cellSize;
    int m_gridWidth;
    int m_gridHeight;
    int m_speed;
 
    bool m_running;
    bool m_paused;
 
    std::vector<std::vector<bool>> m_grid;
};
