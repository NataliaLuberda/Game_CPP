#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>

struct Board {
    sf::RectangleShape grid[3][3], buttonRetry, buttonExit;
    sf::Sprite sprite[3][3], spriteDog, spriteDogTwo;
    int state[3][3];
    int currentPlayer;
    sf::Font font;
    sf::Texture textureX, textureO, textureDog, textureDogTwo;
    sf::Text textCongrats, buttonTextRetry, buttonTextExit;
    sf::Clock clock;
    bool gameWon;
    bool gameDraw;
    bool showEndScreen;
    bool win[3][3];

    Board();
    void reset();
    void initGameObjects();
    void loadResources();
    void checkDraw();
    void checkWin();
    void handlePlayerSwitch();
    void draw(sf::RenderWindow& window);
};


