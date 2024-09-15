#include "GameOfLife.h"
 
int main(int argc, char* argv[]) {
 // Значения по умолчанию
    const int DEFAULT_WINDOW_WIDTH = 800;
    const int DEFAULT_WINDOW_HEIGHT = 600;
    const int CELL_SIZE = 10;
    const int DEFAULT_SPEED = 100;  // Скорость игры (в миллисекундах)
 
    // Переменные для хранения значений, которые могут быть заданы через аргументы
    int windowWidth = DEFAULT_WINDOW_WIDTH;
    int windowHeight = DEFAULT_WINDOW_HEIGHT;
    int speed = DEFAULT_SPEED;
 
    // Парсинг аргументов командной строки
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--width" && i + 1 < argc) {
            windowWidth = std::atoi(argv[++i]); //ширину окна
        } else if (std::string(argv[i]) == "--height" && i + 1 < argc) {
            windowHeight = std::atoi(argv[++i]); //высоту окна
        } else if (std::string(argv[i]) == "--speed" && i + 1 < argc) {
            speed = std::atoi(argv[++i]); // скорость игры
        } else {
            std::cerr << "Неизвестный аргумент: " << argv[i] << std::endl;
        }
    }
    GameOfLife game(windowWidth, windowHeight, CELL_SIZE,speed);
    game.run();
 
    return 0;
}
