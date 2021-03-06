#include "Display.h"


void Display::Init()
{
    //Initializes a window and sets precomputed shapes in memory//
    _window = new sf::RenderWindow(sf::VideoMode(_maze->getSize() * TILE_SIZE, _maze->getSize() * TILE_SIZE), "A* maze - Select start and end tiles, press 'a' for auto mode and 's' for step");
    _window->setFramerateLimit(30);
    for(int i = 0; i < 4; ++i)
    {
        _walls[i] = sf::RectangleShape(sf::Vector2f(WALL_WIDTH,TILE_SIZE + WALL_WIDTH));
        _walls[i].setOrigin(sf::Vector2f(TILE_SIZE / 2.0 + WALL_WIDTH / 2.0, (TILE_SIZE + WALL_WIDTH)/2.0));
        _walls[i].setRotation(90.0 * i);
    }

}
Display::Input Display::Draw()
{
    if(_window == nullptr)
        throw std::logic_error("Init() not called");
    //Main drawing loop//
    sf::RectangleShape background(sf::Vector2f(_maze->getSize() * TILE_SIZE, _maze->getSize() * TILE_SIZE));
    background.setOrigin(sf::Vector2f(0.0,0.0));

    background.setFillColor(sf::Color(255,255,255));
    _window->clear();
     _window->draw(background);
     DrawTiles();
     DrawGrid();
     DrawWalls();
     DrawText();
    _window->display();
    return PollEvent();
}
Display::Input Display::PollEvent()
{
    sf::Event event;
    Input retval = NONE;
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
               case sf::Keyboard::A:
                    retval = AUTO;
                break;
                case sf::Keyboard::S:
                     retval = STEP;
                 break;
                default:
                break;
            }
            break;
        case sf::Event::MouseButtonPressed:
            if(event.mouseButton.button == sf::Mouse::Left)
            {
                _tilex = event.mouseButton.x / TILE_SIZE;
                _tiley = event.mouseButton.y / TILE_SIZE;
                retval = POINT;
            }
            break;
        default:
            break;
        }
    }
    return retval;

}

void Display::DrawTiles()
{
    sf::RectangleShape tile(sf::Vector2f(TILE_SIZE,TILE_SIZE));
    sf::Texture txtFloor, txtFloorRed, txtFloorGreen, txtFloorBlue;
    if(!txtFloor.loadFromFile("resources/floor.png") || !txtFloorRed.loadFromFile("resources/floor_red.png")
            || !txtFloorGreen.loadFromFile("resources/floor_green.png")|| !txtFloorBlue.loadFromFile("resources/floor_blue.png"))
    {
        throw std::runtime_error("Cannot load texture floor.jpg");
    }
    tile.setTexture(&txtFloor);
    tile.setOrigin(sf::Vector2f((TILE_SIZE)/2.0, (TILE_SIZE)/2.0));
    //Draw all tiles individaully with appropriate texture//
    for(int i = 0; i < _maze->getSize(); ++i)
    {
        for(int j = 0; j < _maze->getSize(); ++j)
        {
            switch(_maze->getNode(i,j)->color)
            {
                case Node::NONE:
                    tile.setTexture(&txtFloor);
                break;

                case Node::GREEN:
                    tile.setTexture(&txtFloorGreen);
                break;

                case Node::RED:
                    tile.setTexture(&txtFloorRed);
                break;
                case Node::BLUE:
                    tile.setTexture(&txtFloorBlue);
                break;

                default:
                    tile.setTexture(&txtFloor);
                break;
            }

            tile.setPosition(GetCenter(i,j));
            //Place for logic like changing the color, for now a sample texture//
            _window->draw(tile);
        }
    }
}

void Display::DrawWalls()
{
    Node *tmp;
    sf::Texture txtWall;
    if(!txtWall.loadFromFile("resources/wall.png"))
    {
        throw std::runtime_error("Cannot load wall texture");
    }
    for(int i = 0; i < 4; ++i)
    {
        _walls[i].setTexture(&txtWall);
        _walls[i].setTextureRect(sf::IntRect(10,10,500,500));
    }
    //Draw required walls for each node separately (contains duplicate walls)//
    for(int i = 0; i < _maze->getSize(); ++i)
    {
        for(int j = 0; j < _maze->getSize(); ++j)
        {
            tmp = _maze->getNode(i,j);
            for(int w = 0; w < 4; ++w)
            {
                if(tmp->next[w] == nullptr)
                {
                    //_walls[w].setTexture(&txtWall);
                    _walls[w].setPosition(GetCenter(i,j));
                    _window->draw(_walls[w]);
                }
            }
        }
    }
}
void Display::DrawGrid()
{
    //Draw grid separating the tiles//
    for(int i = 0; i < _maze->getSize(); ++i)
    {
        sf::Vertex linev[] =
        {
            sf::Vertex(sf::Vector2f(i * TILE_SIZE, 0)),
            sf::Vertex(sf::Vector2f(i * TILE_SIZE, TILE_SIZE * _maze->getSize()))
        };
        linev[0].color = linev[1].color = sf::Color::Cyan;
        sf::Vertex lineh[] =
        {
            sf::Vertex(sf::Vector2f(0, i * TILE_SIZE)),
            sf::Vertex(sf::Vector2f(TILE_SIZE * _maze->getSize(),i * TILE_SIZE))
        };
        lineh[0].color = lineh[1].color = sf::Color::Cyan;
        _window->draw(linev,2,sf::Lines);
        _window->draw(lineh,2,sf::Lines);
    }

}
void Display::DrawText()
{
    sf::Font font;
    sf::Text gCost, hCost, sum;
    std::ostringstream oss;
    gCost.setFont(font);
    hCost.setFont(font);
    sum.setFont(font);
    gCost.setCharacterSize(TILE_SIZE / 5);
    hCost.setCharacterSize(TILE_SIZE / 5);
    sum.setCharacterSize(TILE_SIZE/3);
    gCost.setColor(sf::Color::Black);
    hCost.setColor(sf::Color::Black);
    sum.setColor(sf::Color::Black);

    if(!font.loadFromFile("resources/arial-black.ttf"))
    {
        throw std::runtime_error("Cannot load text font arial-black.ttf");
    }
    for(int i = 0; i < _maze->getSize(); ++i)
    {
        for(int j = 0; j < _maze->getSize(); ++j)
        {
            Node *tmp = _maze->getNode(i,j);
            if(tmp->color != Node::NONE && tmp->color != Node::BLUE)
            {
                oss.str(std::string());
                oss.clear();
                //GCOST - top left corner//
                oss<<tmp->gCost;
                gCost.setString(oss.str());
                sf::FloatRect textRect = gCost.getLocalBounds();
                gCost.setOrigin(textRect.left + textRect.width/2.0f,
                               textRect.top  + textRect.height/2.0f);
                gCost.setPosition(GetCenter(i,j) - sf::Vector2f((float)TILE_SIZE / 4.0, (float)TILE_SIZE / 3.5));
                oss.str(std::string());
                //HCOST - top right corner//
                oss<<(tmp->totalCost - tmp->gCost);
                hCost.setString(oss.str());
                textRect = hCost.getLocalBounds();
                hCost.setOrigin(textRect.left + textRect.width/2.0f,
                               textRect.top  + textRect.height/2.0f);
                hCost.setPosition(GetCenter(i,j) - sf::Vector2f((float)-TILE_SIZE / 4.0, (float)TILE_SIZE / 3.5));
                oss.str(std::string());
                //SUM//
                oss<<(tmp->totalCost);
                sum.setString(oss.str());
                textRect = sum.getLocalBounds();
                sum.setOrigin(textRect.left + textRect.width/2.0f,
                               textRect.top  + textRect.height/2.0f);
                sum.setPosition(GetCenter(i,j) - sf::Vector2f(0.0, (float)-TILE_SIZE / 8.0));
                oss.str(std::string());

                _window->draw(gCost);
                _window->draw(hCost);
                _window->draw(sum);
            }
        }
    }
}
