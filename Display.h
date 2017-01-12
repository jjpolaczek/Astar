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
    enum Input{
        NONE,
        STEP,
        AUTO,
        POINT
    };
    
    /*
    * Constructor, only sets the values.
    */
    Display(Maze *maze):
        _maze(maze),
        _tilex(-1),
        _tiley(-1)
    {
    }
    
    ~Display()
    {
    }

    /*
    * Creates the actual window.
    */
    void Init();
    
    /*
    * Draws the maze in the window.
    * Init() must be called before this.
    * If not, it will throw a logic_error.
    * Returns the last input by calling PollEvent() at the end.
    * Draws the tiles, then the grid, then walls, finally the text.
    */
    Input Draw();
    
    /*
    * Retreives the last event (button pressed, tile clicked)
    */
    Input PollEvent();
    
    bool IsExit()
    {
        return  !_window->isOpen();
    }
    
    void GetLastClickedTile(int &x, int &y)
    {
        x = _tilex;
        y = _tiley;
    }

private:
    /*
    * Converts the left-top type of coordinates to the center type.
    */
    sf::Vector2f GetCenter(unsigned int x, unsigned int y)
    {
        return sf::Vector2f(x * TILE_SIZE + TILE_SIZE/2.0, y * TILE_SIZE + TILE_SIZE/2.0);
    }

    /*
    * Draws the actual walls of the maze.
    */
    void DrawWalls();
    
    /*
    * Draws the grid.
    */
    void DrawGrid();
    
    /*
    * Draws the tiles.
    */
    void DrawTiles();
    
    /*
    * Draws the text on the files:
    * GCOST - top left
    * HCOST - top right
    * sum of those - middle
    */
    void DrawText();
    
    sf::RenderWindow *_window;
    sf::RectangleShape _walls[4];
    Maze *_maze;
    int _tilex, _tiley;

};

#endif // DISPLAY_H
