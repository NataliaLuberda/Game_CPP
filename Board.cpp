#include "Board.h"

Board::Board() {
	reset();
}


void Board::reset() {
    currentPlayer = 1;
    loadResources();
    initGameObjects();
    gameWon = false;
    showEndScreen = false;
    gameDraw = false;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            grid[i][j] = sf::RectangleShape(sf::Vector2f(200.f, 200.f));
            grid[i][j].setPosition(i * 200, j * 200);
            grid[i][j].setFillColor(sf::Color::White);
            state[i][j] = 0;
            win[i][j] = false;

            sprite[i][j].setPosition(i * 200, j * 200);
        }
    }
}
void Board::initGameObjects() {
    spriteDog.setTexture(textureDog);
    spriteDog.setScale(400.f / textureDog.getSize().x, 400.f / textureDog.getSize().y);
    spriteDog.setPosition(250, 250); // Wartoœci pozycji do dostosowania


    spriteDogTwo.setTexture(textureDogTwo);
    spriteDogTwo.setScale(300.f / textureDogTwo.getSize().x, 300.f / textureDogTwo.getSize().y);
    spriteDogTwo.setPosition(0, 250); // Wartoœci pozycji do dostosowania


    // Ustawianie tekstu
    textCongrats.setFont(font);
    textCongrats.setString("Congratulations!");
    textCongrats.setCharacterSize(30);
    textCongrats.setFillColor(sf::Color::Green);
    textCongrats.setStyle(sf::Text::Bold);
    textCongrats.setPosition(200, 50);

    // Ustawianie przycisków
    buttonRetry = sf::RectangleShape(sf::Vector2f(100, 50));  // Wymiary do dostosowania
    buttonRetry.setFillColor(sf::Color::Green);
    buttonRetry.setPosition(150, 170);  // Wartoœci pozycji do dostosowania
    buttonRetry.setOutlineThickness(5);
    buttonRetry.setOutlineColor(sf::Color::Red);

    buttonExit = sf::RectangleShape(sf::Vector2f(100, 50));  // Wymiary do dostosowania
    buttonExit.setFillColor(sf::Color::Red);
    buttonExit.setPosition(350, 170);  // Wartoœci pozycji do dostosowania
    buttonExit.setOutlineThickness(5);
    buttonExit.setOutlineColor(sf::Color::Green);

    buttonTextRetry.setString("Retry");
    buttonTextRetry.setFont(font);
    buttonTextRetry.setCharacterSize(20);
    buttonTextRetry.setFillColor(sf::Color::White);
    buttonTextRetry.setStyle(sf::Text::Bold);
    buttonTextRetry.setPosition(175, 180);  // Pozycja napisu na przycisku Retry

    buttonTextExit.setString("Exit");
    buttonTextExit.setFont(font);
    buttonTextExit.setCharacterSize(20);
    buttonTextExit.setFillColor(sf::Color::White);
    buttonTextExit.setStyle(sf::Text::Bold);
    buttonTextExit.setPosition(375, 180);  // Pozycja napisu na przycisku Exit

}
void Board::loadResources() {
    if (!font.loadFromFile("Resources\\arial.ttf")) {
        std::cout << "Failed to load font.\n";
        exit(1);
    }
    if (!textureX.loadFromFile("Resources\\cross.png")) {
        std::cout << "Failed to load cross texture.\n";
        exit(1);
    }
    if (!textureO.loadFromFile("Resources\\circle.png")) {
        std::cout << "Failed to load circle texture.\n";
        exit(1);
    }
    if (!textureDog.loadFromFile("Resources\\dog.png")) {
        std::cout << "Failed to load dog texture.\n";
        exit(1);
    }
    if (!textureDogTwo.loadFromFile("Resources\\dog_2.png")) {
        std::cout << "Failed to load dog texture.\n";
        exit(1);
    }
}
void Board::checkDraw() {
    gameDraw = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (state[i][j] == 0) {
                gameDraw = false;
                return;
            }
        }
    }
}

void Board::checkWin() {
    for (int i = 0; i < 3; ++i) {
        if (state[i][0] == state[i][1] && state[i][0] == state[i][2] && state[i][0] != 0) {
            win[i][0] = win[i][1] = win[i][2] = true;
            gameWon = true;
        }
        if (state[0][i] == state[1][i] && state[0][i] == state[2][i] && state[0][i] != 0) {
            win[0][i] = win[1][i] = win[2][i] = true;
            gameWon = true;
        }
    }
    if (state[0][0] == state[1][1] && state[0][0] == state[2][2] && state[0][0] != 0) {
        win[0][0] = win[1][1] = win[2][2] = true;
        gameWon = true;
    }
    if (state[2][0] == state[1][1] && state[2][0] == state[0][2] && state[2][0] != 0) {
        win[2][0] = win[1][1] = win[0][2] = true;
        gameWon = true;
    }
}

void Board::handlePlayerSwitch() {
    if (currentPlayer == 1) {
        currentPlayer = 2;
    }
    else {
        currentPlayer = 1;
    }
}
void Board::draw(sf::RenderWindow& window) {
    if (gameWon) { 
        std::string winner = (currentPlayer == 1) ? "O" : "X";
        textCongrats.setString("Congratulations! Player " + winner + " wins!");
        textCongrats.setPosition(80, 50);
        showEndScreen = true;
    }
    else if (gameDraw) {
        textCongrats.setString("You're both geniuses!");
        textCongrats.setPosition(150, 50);
        showEndScreen = true;
    }
    if (showEndScreen) {
        while (clock.getElapsedTime().asSeconds() < 5)
        {
            continue;
        }
        window.clear(sf::Color::White);
        window.draw(textCongrats);
        window.draw(spriteDog);
        window.draw(spriteDogTwo);
        window.draw(buttonRetry);
        window.draw(buttonExit);
        window.draw(buttonTextExit);
        window.draw(buttonTextRetry);

    }
    else {
        checkWin();
        checkDraw();
        clock.restart();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (win[i][j]) grid[i][j].setFillColor(sf::Color::Green);
                window.draw(grid[i][j]);
                if (state[i][j] != 0) {
                    if (state[i][j] == 1) {
                        sprite[i][j].setTexture(textureX);

                        sprite[i][j].setScale(200.f / textureX.getSize().x, 200.f / textureX.getSize().y);
                    }
                    else {

                        sprite[i][j].setTexture(textureO);
                        sprite[i][j].setScale(200.f / textureO.getSize().x, 200.f / textureO.getSize().y);
                    }
                    window.draw(sprite[i][j]);
                }
            }
        }
        // Rysowanie siatki
        for (int i = 1; i <= 2; i++) {
            sf::RectangleShape line(sf::Vector2f(600, 5));
            line.setPosition(0, i * 200);
            line.setFillColor(sf::Color::Black);  // Linie s¹ czarne
            window.draw(line);
        }
        for (int i = 1; i <= 2; i++) {
            sf::RectangleShape line(sf::Vector2f(5, 600));
            line.setPosition(i * 200, 0);
            line.setFillColor(sf::Color::Black);  // Linie s¹ czarne
            window.draw(line);
        }


    }
}