#include "Game.h"

Game::Game() : window(sf::VideoMode(600, 600), "Tic Tac Toe") {
    window.clear(sf::Color::White);  // Ustawienie t�a na bia�e
}
