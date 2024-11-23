#ifndef GAME_H
#define GAME_H
#include "board.h"

class Game {
    unique_ptr<Board> b;
    const int height, width;
    unique_ptr<Player> player1;
    unique_ptr<Player> player2;
    unique_ptr<TextDisplay> td = make_unique<TextDisplay>();
    unique_ptr<GraphicsDisplay> gd;
    bool showGraphic;
    int turn;
    public:
    Game();
    ~Game();
    void initPlayerOne(unique_ptr<Player> player1);
    void initPlayerTwo(unique_ptr<Player> player2);
    void move(char id, char dir);
    void useAbility(int i);
    int turn();
    void printAbilities();
    void enableGraphics();
    bool isGraphicsEnabled();
    string playerInfo(int player);
};

#endif
