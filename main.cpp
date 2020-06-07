#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Random.h"
#include "TextureManager.h"
#include "SpriteManager.h"
#include "Tile.h"

using namespace std;

void LoadTextures();
void LoadSprites();
int InitializeBoard(Tile board[][25]);
int InitializeBoard(Tile board[][25], string input);
void ClearBoard(Tile board[][25]);
void SetNeighbors(Tile board[][25]);
void RevealNeighbors(Tile* home);

int main()
{
    // Initalizing code
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
    int colLocation = 0, rowLocation = 0, mines = 0, tiles = 0, flags = 0, digit = 0;
    const int COL_MAX = 25, ROW_MAX = 16, NUM_MINES = 50;
    bool endGame = false, win = false, debug = false;
    Tile board[ROW_MAX][COL_MAX];
    // Load textures and set sprites
    LoadTextures();
    LoadSprites();
       
    // Initializing board
    mines = InitializeBoard(board);
    SetNeighbors(board);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }

            // Checking if a click has occured 
            if (event.type == sf::Event::MouseButtonReleased)
            {
                // If a left click
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    colLocation = (sf::Mouse::getPosition(window).x) / 32;
                    rowLocation = (sf::Mouse::getPosition(window).y) / 32;

                    if (colLocation < COL_MAX && rowLocation < ROW_MAX && !board[rowLocation][colLocation].isFlag() && !endGame && !win)
                    {
                        // If mine is clicked end game
                        if (board[rowLocation][colLocation].isMine())
                        {
                            endGame = true;
                        }

                        board[rowLocation][colLocation].setRevealed();

                        if ((board[rowLocation][colLocation].getAdjacent() == 0) && !board[rowLocation][colLocation].isMine())
                        {
                            RevealNeighbors(&board[rowLocation][colLocation]);
                        }
                    }

                    // Selecting bottom button
                    if (rowLocation >= 16 && rowLocation <= 17)
                    {
                        // Test 3
                        if (colLocation >= 23 && colLocation <= 24)
                        {
                            ClearBoard(board);
                            mines = InitializeBoard(board, "testboard3");
                            SetNeighbors(board);
                            endGame = false;
                            win = false;
                            flags = 0;
                        }

                        // Test 2
                        if (colLocation >= 21 && colLocation <= 22)
                        {
                            ClearBoard(board);
                            mines = InitializeBoard(board, "testboard2");
                            SetNeighbors(board);
                            endGame = false;
                            win = false;
                            flags = 0;
                        }

                        // Test 1
                        if (colLocation >= 19 && colLocation <= 20)
                        {
                            ClearBoard(board);
                            mines = InitializeBoard(board, "testboard1");
                            SetNeighbors(board);
                            endGame = false;
                            win = false;
                            flags = 0;
                        }

                        // Debug
                        if (colLocation >= 17 && colLocation <= 18)
                        {
                            if (debug == false)
                                debug = true;
                            else
                                debug = false;
                        }
                        
                        // Face button
                        if (colLocation >= 12 && colLocation <= 13)
                        {
                            ClearBoard(board);
                            mines = InitializeBoard(board);
                            SetNeighbors(board);
                            endGame = false;
                            win = false;
                            flags = 0;
                        }
                    }
                }

                // If a right click place flag
                if (event.mouseButton.button == sf::Mouse::Right && !endGame && !win)
                {
                    colLocation = (sf::Mouse::getPosition(window).x) / 32;
                    rowLocation = (sf::Mouse::getPosition(window).y) / 32;
                    if ((colLocation < COL_MAX && rowLocation < ROW_MAX) && !endGame)
                    {
                        if (board[rowLocation][colLocation].setFlag())
                        {
                            // Keep track of how many flags for counter
                            if (board[rowLocation][colLocation].isFlag())
                                flags++;
                            else
                                flags--;
                        }
                    }
                }
            }
        }
        
        window.clear();
        
        for (int i = 0; i < ROW_MAX; i++)
        {
            for (int j = 0; j < COL_MAX; j++)
            {
                sf::Sprite sprite = SpriteManager::GetSprite("tile_revealed");
                sprite.setPosition(sf::Vector2f(j * sprite.getTextureRect().width, i * sprite.getTextureRect().height));
                window.draw(sprite);

                if (board[i][j].isMine()) // Print mines on board
                {
                    sf::Sprite sprite = SpriteManager::GetSprite("mine");
                    sprite.setPosition(sf::Vector2f(j * sprite.getTextureRect().width, i * sprite.getTextureRect().height));
                    window.draw(sprite);
                }

                if (board[i][j].getAdjacent() > 0 && !board[i][j].isMine()) // Print number for nearby mines on board
                {
                    sf::Sprite sprite;
                    switch (board[i][j].getAdjacent())
                    {
                    case 1:
                        sprite = SpriteManager::GetSprite("number_1");
                        break;
                    case 2:
                        sprite = SpriteManager::GetSprite("number_2");
                        break;
                    case 3:
                        sprite = SpriteManager::GetSprite("number_3");
                        break;
                    case 4:
                        sprite = SpriteManager::GetSprite("number_4");
                        break;
                    case 5:
                        sprite = SpriteManager::GetSprite("number_5");
                        break;
                    case 6:
                        sprite = SpriteManager::GetSprite("number_6");
                        break;
                    case 7:
                        sprite = SpriteManager::GetSprite("number_7");
                        break;
                    case 8:
                        sprite = SpriteManager::GetSprite("number_8");
                        break;
                    }
                    sprite.setPosition(sf::Vector2f(j * sprite.getTextureRect().width, i * sprite.getTextureRect().height));
                    window.draw(sprite);
                }

                if (!board[i][j].isRevealed())
                {
                    tiles++;
                    sf::Sprite sprite = SpriteManager::GetSprite("tile_hidden");
                    sprite.setPosition(sf::Vector2f(j * sprite.getTextureRect().width, i * sprite.getTextureRect().height));
                    window.draw(sprite);
                }

                if (board[i][j].isFlag())
                {
                    sf::Sprite sprite = SpriteManager::GetSprite("flag");
                    sprite.setPosition(sf::Vector2f(j * sprite.getTextureRect().width, i * sprite.getTextureRect().height));
                    window.draw(sprite);
                }
            }
        }

        // Check if game is won
        if (tiles <= (400 - (400 - mines)) && !endGame)
            win = true;
        else
            tiles = 0;
        
        // If game is won place flags on tiles with mines
        if (win)
        {
            for (int i = 0; i < ROW_MAX; i++)
            {
                for (int j = 0; j < COL_MAX; j++)
                {
                    if (board[i][j].isMine())
                    {
                        sf::Sprite sprite2 = SpriteManager::GetSprite("flag");
                        sprite2.setPosition(sf::Vector2f(j * sprite2.getTextureRect().width, i * sprite2.getTextureRect().height));
                        window.draw(sprite2);
                    }

                }
            }
        }
        // If game is lost reveal all mines
        else if (endGame)
        {
            for (int i = 0; i < ROW_MAX; i++)
            {
                for (int j = 0; j < COL_MAX; j++)
                {
                    if (board[i][j].isMine())
                    {
                        sf::Sprite sprite = SpriteManager::GetSprite("tile_revealed");
                        sprite.setPosition(sf::Vector2f(j* sprite.getTextureRect().width, i* sprite.getTextureRect().height));
                        window.draw(sprite);

                        sf::Sprite sprite2 = SpriteManager::GetSprite("mine");
                        sprite2.setPosition(sf::Vector2f(j * sprite2.getTextureRect().width, i * sprite2.getTextureRect().height));
                        window.draw(sprite2);

                    }
                    
                }
            }
        }
        
        // If debug mode is activated print mines on top of tiles 
        if (debug)
        {
            for (int i = 0; i < ROW_MAX; i++)
            {
                for (int j = 0; j < COL_MAX; j++)
                {
                    if (board[i][j].isMine())
                    {
                        sf::Sprite sprite2 = SpriteManager::GetSprite("mine");
                        sprite2.setPosition(sf::Vector2f(j * sprite2.getTextureRect().width, i * sprite2.getTextureRect().height));
                        window.draw(sprite2);
                    }
                }
            }
        }

        sf::Sprite face;

        // Selecting face to print
        if (win)
            face = SpriteManager::GetSprite("face_win");
        else if (endGame)
            face = SpriteManager::GetSprite("face_lose");
        else
            face = SpriteManager::GetSprite("face_happy");

        face.setPosition(sf::Vector2f(32 * 12, 32 * 16));
        window.draw(face);
        
        // Set positions and print test buttons
        sf::Sprite test3 = SpriteManager::GetSprite("test_3");
        test3.setPosition(sf::Vector2f(800 - test3.getTextureRect().width, 32 * 16));
        window.draw(test3);

        sf::Sprite test2= SpriteManager::GetSprite("test_2");
        test2.setPosition(sf::Vector2f(800 - (test2.getTextureRect().width * 2), 32 * 16));
        window.draw(test2);

        sf::Sprite test1 = SpriteManager::GetSprite("test_1");
        test1.setPosition(sf::Vector2f(800 - (test1.getTextureRect().width * 3), 32 * 16));
        window.draw(test1);

        sf::Sprite debug = SpriteManager::GetSprite("debug");
        debug.setPosition(sf::Vector2f(800 - (debug.getTextureRect().width * 4), 32 * 16));
        window.draw(debug);

        // Printing counter 
        // If postive number don't include negative sign in digits
        if (!win)
        {
            digit = mines - flags;
            if (digit >= 0)
            {
                sf::Sprite digit0 = SpriteManager::GetSprite("digits");
                sf::Sprite digit1 = SpriteManager::GetSprite("digits");
                sf::Sprite digit2 = SpriteManager::GetSprite("digits");

                digit0.setPosition(sf::Vector2f(0, 32 * 16));
                digit1.setPosition(sf::Vector2f(21, 32 * 16));
                digit2.setPosition(sf::Vector2f(42, 32 * 16));


                digit2.setTextureRect(sf::IntRect(21 * (digit % 10), 0, 21, 32));
                digit /= 10;
                digit1.setTextureRect(sf::IntRect(21 * (digit % 10), 0, 21, 32));
                digit /= 10;
                digit0.setTextureRect(sf::IntRect(21 * (digit % 10), 0, 21, 32));

                window.draw(digit0);
                window.draw(digit1);
                window.draw(digit2);
            }
            else
            {
                digit *= -1;
                sf::Sprite negative = SpriteManager::GetSprite("digits");
                sf::Sprite digit0 = SpriteManager::GetSprite("digits");
                sf::Sprite digit1 = SpriteManager::GetSprite("digits");
                sf::Sprite digit2 = SpriteManager::GetSprite("digits");

                negative.setPosition(sf::Vector2f(0, 32 * 16));
                digit0.setPosition(sf::Vector2f(21, 32 * 16));
                digit1.setPosition(sf::Vector2f(42, 32 * 16));
                digit2.setPosition(sf::Vector2f(63, 32 * 16));

                negative.setTextureRect(sf::IntRect(210, 0, 21, 32));
                digit2.setTextureRect(sf::IntRect(21 * (digit % 10), 0, 21, 32));
                digit /= 10;
                digit1.setTextureRect(sf::IntRect(21 * (digit % 10), 0, 21, 32));
                digit /= 10;
                digit0.setTextureRect(sf::IntRect(21 * (digit % 10), 0, 21, 32));

                window.draw(negative);
                window.draw(digit0);
                window.draw(digit1);
                window.draw(digit2);

            }
        }
        else
        {
            sf::Sprite digit0 = SpriteManager::GetSprite("digits");

            digit0.setTextureRect(sf::IntRect(0, 0, 21, 32));

            digit0.setPosition(sf::Vector2f(0, 32 * 16));

            window.draw(digit0);

            digit0.setPosition(sf::Vector2f(21, 32 * 16));

            window.draw(digit0);

            digit0.setPosition(sf::Vector2f(42, 32 * 16));

            window.draw(digit0);

        }
        window.display(); 
    }

    // Clear maps of textures and sprites
    TextureManager::Clear();
    SpriteManager::Clear();

    return 0;
}

void LoadTextures()
{
    TextureManager::LoadTexture("debug");
    TextureManager::LoadTexture("digits");
    TextureManager::LoadTexture("face_lose");
    TextureManager::LoadTexture("face_happy");
    TextureManager::LoadTexture("face_win");
    TextureManager::LoadTexture("flag");
    TextureManager::LoadTexture("mine");
    TextureManager::LoadTexture("number_1");
    TextureManager::LoadTexture("number_2");
    TextureManager::LoadTexture("number_3");
    TextureManager::LoadTexture("number_4");
    TextureManager::LoadTexture("number_5");
    TextureManager::LoadTexture("number_6");
    TextureManager::LoadTexture("number_7");
    TextureManager::LoadTexture("number_8");
    TextureManager::LoadTexture("test_1");
    TextureManager::LoadTexture("test_2");
    TextureManager::LoadTexture("test_3");
    TextureManager::LoadTexture("tile_hidden");
    TextureManager::LoadTexture("tile_revealed");
}

void LoadSprites()
{
    SpriteManager::LoadSprite("debug");
    SpriteManager::LoadSprite("digits"); 
    SpriteManager::LoadSprite("face_lose"); 
    SpriteManager::LoadSprite("face_happy");
    SpriteManager::LoadSprite("face_win");
    SpriteManager::LoadSprite("flag");
    SpriteManager::LoadSprite("mine");
    SpriteManager::LoadSprite("number_1");    
    SpriteManager::LoadSprite("number_2");
    SpriteManager::LoadSprite("number_3");
    SpriteManager::LoadSprite("number_4");
    SpriteManager::LoadSprite("number_5");    
    SpriteManager::LoadSprite("number_6");
    SpriteManager::LoadSprite("number_7");
    SpriteManager::LoadSprite("number_8");
    SpriteManager::LoadSprite("test_1");   
    SpriteManager::LoadSprite("test_2");
    SpriteManager::LoadSprite("test_3");
    SpriteManager::LoadSprite("tile_hidden");
    SpriteManager::LoadSprite("tile_revealed");
}

int InitializeBoard(Tile board[][25])
{
    const int COL_MAX = 25, ROW_MAX = 16, NUM_MINES = 50;
    int randRow, randCol, numMines = 0;

    for (int i = 0; i < ROW_MAX; i++)
    {
        for (int j = 0; j < COL_MAX; j++)
        {
            Tile tile(j, i);
            board[i][j] = tile;
        }
    }
    
    while (numMines < NUM_MINES)
    {
        randRow = Random::Int(0, 15);
        randCol = Random::Int(0, 24);

        if (board[randRow][randCol].setMine())
            numMines++;
    }

    return NUM_MINES;
}

int InitializeBoard(Tile board[][25], string fileName)
{
    const int COL_MAX = 25, ROW_MAX = 16;

    string filePath = "boards/" + fileName + ".brd", input;
    fstream file;
    file.open(filePath);
    int value, numMines = 0, count = 0;
    vector<int> xCoords;
    vector<int> yCoords;

    while (count < ROW_MAX)
    {
        getline(file, input);

        for (int i = 0; i < COL_MAX; i++)
        {
            if (input.at(i) == '1')
            {
                xCoords.push_back(i);
                yCoords.push_back(count);
            }
        }
        count++;
    }

    for (int i = 0; i < xCoords.size(); i++)
    {
        if (board[yCoords.at(i)][xCoords.at(i)].setMine())
            numMines++;
    }

    file.close();
    return numMines;
}

void ClearBoard(Tile board[][25])
{
    const int COL_MAX = 25, ROW_MAX = 16;

    for (int i = 0; i < ROW_MAX; i++)
    {
        for (int j = 0; j < COL_MAX; j++)
        {
            board[i][j].resetTile();
        }
    }
}

void SetNeighbors(Tile board[][25])
{
    const int COL_MAX = 25, ROW_MAX = 16;

    for (int i = 0; i < ROW_MAX; i++)
    {
        for (int j = 0; j < COL_MAX; j++)
        {
            if ((i - 1) >= 0 && (j - 1) >= 0)
                board[i][j].setNeighbor(&board[i - 1][j - 1]);

            if ((i - 1) >= 0)
                board[i][j].setNeighbor(&board[i - 1][j]);

            if ((i - 1 >= 0) && (j + 1) < COL_MAX)
                board[i][j].setNeighbor(&board[i - 1][j + 1]);

            if ((j - 1) >= 0)
                board[i][j].setNeighbor(&board[i][j - 1]);

            if ((j + 1) < COL_MAX)
                board[i][j].setNeighbor(&board[i][j + 1]);

            if ((i + 1) < ROW_MAX && (j - 1) >= 0)
                board[i][j].setNeighbor(&board[i + 1][j - 1]);

            if ((i + 1) < ROW_MAX)
                board[i][j].setNeighbor(&board[i + 1][j]);

            if ((i + 1) < ROW_MAX && (j + 1) < COL_MAX)
                board[i][j].setNeighbor(&board[i + 1][j + 1]);
            
        }
    }
}

void RevealNeighbors(Tile* home)
{
    if (home->isNumber() || home->isRecursive())
        return;

    vector<Tile*> neighbors = home->getVector();
    for (int i = 0; i < neighbors.size(); i++)
    {
        neighbors.at(i)->setRevealed();
        RevealNeighbors(neighbors.at(i));
    }
}
