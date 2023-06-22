#include "Game.h"
#include "Board.h"

int main() {
    Game game;
    Board board;

    while (game.window.isOpen()) {
        sf::Event event;
        while (game.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                game.window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (board.showEndScreen) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(game.window);

                        // czy myszka jest nad buttonRetry
                        if (board.buttonRetry.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            board.reset();
                        }

                        //  czy myszka jest nad buttonExit
                        if (board.buttonExit.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                            game.window.close();
                        }
                    }
                    else {
                        int x = event.mouseButton.x / 200;
                        int y = event.mouseButton.y / 200;
                        if (board.state[x][y] == 0) {
                            board.state[x][y] = board.currentPlayer;
                            board.handlePlayerSwitch();
                        }
                    }
                }
            }
        }

        game.window.clear(sf::Color::White);
        board.draw(game.window);
        game.window.display();
    }

    return 0;
}
