#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <exception>
#include <sstream>
#include <string>
#include "Maze.h"


#define TILE_SIZE 60 //In pixels
#define WALL_WIDTH 8.0
enum
{
    WallLeft,
    WallUp,
    WallRight,
    WallDown

}Wall;


class Display
{
public:

    Display(Maze *maze):
        _maze(maze),
        _tilex(-1),
        _tiley(-1)
    {
    }
    ~Display()
    {
    }
    enum Input{
        NONE,
        STEP,
        AUTO,
        POINT
    };
    void Init();
    Input Draw();
    Input PollEvent();
    bool IsExit()
    {
        return  !_window->isOpen();
    }
    void GetLastClickedTile(int &x, int &y)
    {
        x =_tilex;
        y = _tiley;
    }

private:
    sf::Vector2f GetCenter(unsigned int x, unsigned int y)
    {
        return sf::Vector2f(x * TILE_SIZE + TILE_SIZE/2.0, y * TILE_SIZE + TILE_SIZE/2.0);
    }

    void DrawWalls();
    void DrawGrid();
    void DrawTiles();
    void DrawText();
    sf::RenderWindow *_window;
    sf::RectangleShape _walls[4];
    Maze *_maze;
    int _tilex, _tiley;

};

#endif // DISPLAY_H
