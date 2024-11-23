#ifndef _GAME_H_
#define _GAME_H_
#include <iostream>
#include <string>
#include <memory>
#include "player.h"
#include "board.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "window.h"

using namespace std;

class Player;
class Board; 

class Game {
    unique_ptr<Player> p1 = make_unique<Player>(nullptr); // for more than two players, can do an arr/vec of players
    unique_ptr<Player> p2 = make_unique<Player>(nullptr);
    bool whoseTurn = true;     // true for playerOne, false for playerTwo 

    unique_ptr<Board> b = make_unique<Board>();
    
    unique_ptr<TextDisplay> td = make_unique<TextDisplay>();
    unique_ptr<GraphicsDisplay> gd;
    bool GDEnabled = false; // true if graphics display is enabled

    public:
    Game();
    ~Game();
    Player* getCurrentPlayer();
    Player* theirTurn(bool who); // returns player1 if true, player2 otherwise
    void initPlayerOne(unique_ptr<Player> player1);
    void initPlayerTwo(unique_ptr<Player> player2);
    bool checkWhoseTurn(); // returns true if player 1's turn, false otherwise
    Board* getBoard(); // returns the board by pointer
    bool checkFinished();   // check if the game has finished- check if any player
                            // has 4 viruses or 4 data
    void toggleTurn(); // switch to other player's turn
    void init(); // attaches td as an observer to every Cell on theBoard
    void useAbility(int i); // uses the current player's ability at index i (0-4)
    void moveLink(char id, char dir);   // moves the current player's link by id in the dir direction
                                        // dir can be 'n', 'e', 's', 'w'
                                        // edits the board
    void printAbilities(); // prints the availability of each ability of the cur player
    void enableGD(); // sets GDEnabled to true
    bool isGDEnabled(); // returns true if GD is enabled
    friend std::ostream &operator<<(std::ostream &out, const Game &g);
};

#endif
