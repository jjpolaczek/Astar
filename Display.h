#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <exception>
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
        _maze(maze)
    {
    }
    ~Display()
    {
    }

    void Init();
    void Draw();
    bool IsExit()
    {
        return  !_window->isOpen();
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

};

#endif // DISPLAY_H
