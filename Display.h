#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <exception>
#include "Maze.h"


#define TILE_SIZE 40 //In pixels
#define WALL_WIDTH 4.0
enum
{
    WallLeft,
    WallUp,
    WallRight,
    WallDown

}Wall;


class MazeVisualizer
{
public:

    MazeVisualizer(unsigned int mazeSize):
        _mazeSize(mazeSize)
    {
        _maze = new Node*[_mazeSize];
        for(int i = 0; i < _mazeSize; ++i)
        {
            _maze[i] = new Node[_mazeSize];
        }
        for(int i = 0; i < _mazeSize; ++i)
        {
            _maze[0][i].wLeft = 1;
            _maze[i][0].wUp = 1;
            _maze[_mazeSize - 1][i].wRight = 1;
            _maze[i][_mazeSize - 1].wDown=0;

        }
    }
    ~MazeVisualizer()
    {
        for(int i = 0; i < _mazeSize; ++i)
        {
            delete [] _maze[i];
        }
        delete [] _maze;
    }

    void Init()
    {
        _window = new sf::RenderWindow(sf::VideoMode(_mazeSize * TILE_SIZE, _mazeSize * TILE_SIZE), "A* maze");
        _window->setFramerateLimit(30);
        for(int i = 0; i < 4; ++i)
        {
            _walls[i] = sf::RectangleShape(sf::Vector2f(WALL_WIDTH,TILE_SIZE));
            _walls[i].setFillColor(sf::Color::Red);
            _walls[i].setOrigin(sf::Vector2f(TILE_SIZE / 2.0 + WALL_WIDTH / 2.0, TILE_SIZE/2.0));
            _walls[i].setRotation(90.0 * i);
        }


    }
    void Draw()
    {
        if(_window == nullptr)
            throw std::logic_error("Init() not called");

        sf::RectangleShape background(sf::Vector2f(_mazeSize * TILE_SIZE, _mazeSize * TILE_SIZE));
        background.setOrigin(sf::Vector2f(0.0,0.0));
        background.setFillColor(sf::Color(255,255,255));
        _window->clear();
         _window->draw(background);
         DrawWalls();
        _window->display();

        sf::Event event;
        while (_window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                _window->close();
                break;
                case sf::Event::KeyPressed:
                switch(event.key.code)
                {
                    case sf::Keyboard::U:
                    _test = WallUp;
                    break;
                    case sf::Keyboard::D:
                    _test = WallDown;
                    break;
                    case sf::Keyboard::L:
                    _test = WallLeft;
                    break;
                    case sf::Keyboard::R:
                    _test = WallRight;
                    break;
                    default:
                    break;

                }
                break;
            default:
                break;
            }
        }
    }
    bool IsExit()
    {
        return  !_window->isOpen();
    }

private:
    struct Node
    {
    public:
        Node():
            wLeft(0),
            wRight(0),
            wUp(0),
            wDown(0)
        {

        }

        bool wLeft,wRight,wUp,wDown;
    };
    sf::Vector2f GetCenter(unsigned int x, unsigned int y)
    {
        return sf::Vector2f(x * TILE_SIZE + TILE_SIZE/2.0, y * TILE_SIZE + TILE_SIZE/2.0);
    }

    void DrawWalls()
    {

        sf::CircleShape shape((float) TILE_SIZE / 8);
        for(int i = 0; i < _mazeSize; ++i)
        {
            for(int j = 0; j < _mazeSize; ++j)
            {
                shape.setFillColor(sf::Color::Green);
                shape.setOrigin(sf::Vector2f(TILE_SIZE/8.0, TILE_SIZE/8.0));
                shape.setPosition(GetCenter(i,j));
                _walls[_test].setPosition(GetCenter(i,j));
                _window->draw(shape);
                if(1)
                    _window->draw(_walls[_test]);
            }
        }
    }
    Node **_maze;
    sf::RenderWindow *_window;
    sf::RectangleShape _walls[4];
    unsigned int _mazeSize;

    int _test = 0;
};

#endif // DISPLAY_H
