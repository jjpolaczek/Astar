#include "Display.h"


void Display::Init()
{
    _window = new sf::RenderWindow(sf::VideoMode(_maze->getSize() * TILE_SIZE, _maze->getSize() * TILE_SIZE), "A* maze");
    _window->setFramerateLimit(30);
    for(int i = 0; i < 4; ++i)
    {
        _walls[i] = sf::RectangleShape(sf::Vector2f(WALL_WIDTH,TILE_SIZE));
        _walls[i].setFillColor(sf::Color::Red);
        _walls[i].setOrigin(sf::Vector2f(TILE_SIZE / 2.0 + WALL_WIDTH / 2.0, TILE_SIZE/2.0));
        _walls[i].setRotation(90.0 * i);
    }


}
void Display::Draw()
{
    if(_window == nullptr)
        throw std::logic_error("Init() not called");

    sf::RectangleShape background(sf::Vector2f(_maze->getSize() * TILE_SIZE, _maze->getSize() * TILE_SIZE));
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
void Display::DrawWalls()
{

    sf::CircleShape shape((float) TILE_SIZE / 8);
    for(int i = 0; i < _maze->getSize(); ++i)
    {
        for(int j = 0; j < _maze->getSize(); ++j)
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
