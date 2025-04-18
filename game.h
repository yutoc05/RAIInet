#ifndef _GAME_H_
#define _GAME_H_
#include "board.h"
#include "textobserver.h"
#include "graphicsobserver.h"
#include "window.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Player;

class Game {
    unique_ptr<Board> b;
    unique_ptr<Player> player1;
    unique_ptr<Player> player2;
    unique_ptr<TextObserver> td = make_unique<TextObserver>();
    unique_ptr<GraphicsObserver> gd = make_unique<GraphicsObserver>();
    bool showGraphic;
    int turn;
    Xwindow *window;
    public:
    Game();
    ~Game();
    bool checkFinished();
    void initPlayerOne(unique_ptr<Player> player1);
    void initPlayerTwo(unique_ptr<Player> player2);
    void init();
    void moveLink(char id, char dir);
    void useAbility(int i);
    int getTurn() const;
    void printAbilities();
    void enableGraphics();
    bool isGraphicsEnabled();
    void toggleTurn();
    Player* getCurrentPlayer();
    TextObserver* getTextObserver();
    GraphicsObserver* getGraphicsObserver();
    Board* theBoard();
    string playerInfo(int player);
    friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif
