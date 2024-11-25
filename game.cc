#include "game.h"
#include "player.h"
#include "board.h"
#include "textobserver.h"
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <utility>
using namespace std;

Game::Game() : player1{nullptr}, player2{nullptr}, td{new TextObserver{}} //gd{nullptr} 
        {}

Game::~Game() {}

bool Game::checkFinished() {
    if (player1->getNumData() == 4 || player2->getNumVirus() == 4)
    {
        cout << "PLAYER 1 WINS!!" << endl;
        return true;
    }
    else if (player2->getNumData() == 4 || player1->getNumVirus() == 4)
    {
        cout << "PLAYER 2 WINS!!" << endl;
        return true;
    }
    return false;
}

void Game::initPlayerOne(unique_ptr<Player> p1) { player1 = std::move(p1); }

void Game::initPlayerTwo(unique_ptr<Player> p2) { player2 = std::move(p2); }

void Game::init()
{
    b->init(td.get());
    // server ports
    b->getCell(0, 3)->setState('S');
    b->getCell(0, 4)->setState('S');
    b->getCell(7, 3)->setState('S');
    b->getCell(7, 4)->setState('S');

    // player 1
    b->getCell(0, 0)->setState('a');
    b->getCell(0, 1)->setState('b');
    b->getCell(0, 2)->setState('c');
    b->getCell(1, 3)->setState('d');
    b->getCell(1, 4)->setState('e');
    b->getCell(0, 5)->setState('f');
    b->getCell(0, 6)->setState('g');
    b->getCell(0, 7)->setState('h');

    // player 2
    b->getCell(7, 0)->setState('A');
    b->getCell(7, 1)->setState('B');
    b->getCell(7, 2)->setState('C');
    b->getCell(6, 3)->setState('D');
    b->getCell(6, 4)->setState('E');
    b->getCell(7, 5)->setState('F');
    b->getCell(7, 6)->setState('G');
    b->getCell(7, 7)->setState('H');
}

void Game::moveLink(char id, char dir) {
    Player *curPlayer;
    Player *curOpponent;
    if (turn == 1) {
        curPlayer = player1.get();
        curOpponent = player2.get();
    } else {
        curPlayer = player2.get();
        curOpponent = player1.get();
    }

    // old position
    int posX = curPlayer->getPureLink(id).getPosX();
    int posY = curPlayer->getPureLink(id).getPosY();

    // prepare opposite direction in case of throw
    char oppDir;
    if (dir == 'n') oppDir = 's';
    if (dir == 'e') oppDir = 'w';
    if (dir == 's') oppDir = 'n';
    if (dir == 'w') oppDir = 'e';

    // change old cell
    // if was on firewall:
    if (b->getCell(posX, posY)->isFirewall(1)) {
        b->getCell(posX, posY)->setState('m');
    } else if (b->getCell(posX, posY)->isFirewall(1)) {
        b->getCell(posX, posY)->setState('w');
    } else  { //if normal cell
        b->getCell(posX, posY)->setState('.');
    }

    // moving
    curPlayer->moveLink(id, dir, turn);

    //  new position
    posX = curPlayer->getPureLink(id).getPosX();
    posY = curPlayer->getPureLink(id).getPosY();

    // cout << posX << posY;

    // if lands on Server port / download edge
    if (turn == 1) { // p1's turn
        if ((posX == 3 || posX == 4) && posY == 7) { // p2's server ports
            curOpponent->downloadLink(curPlayer->getPureLink(id));
        }
        else if ((posY == 8 && posX != 3 && posX != 4)) { // p2's download edge
            curPlayer->downloadLink(curPlayer->getPureLink(id));
        }
        else if ((posX == 3 || posX == 4) && posY == 0) { // own server port!?
            curPlayer->moveLink(id, oppDir, turn);
            posX = curPlayer->getPureLink(id).getPosX();
            posY = curPlayer->getPureLink(id).getPosY();
            b->getCell(posX, posY)->setState(id);
            throw logic_error {"You can't move your link onto your own Server Port. Try again."};
        }
        else if (posX > 7 || posY > 7 || posX < 0 || posY < 0)
        { // off the map!!?
            curPlayer->moveLink(id, oppDir, turn);
            posX = curPlayer->getPureLink(id).getPosX();
            posY = curPlayer->getPureLink(id).getPosY();
            b->getCell(posX, posY)->setState(id);
            throw logic_error {"You can't move your link off the board. Try again."};
        }
    }
    else if (turn == 2) { // p2's turn
        if ((posX == 3 || posX == 4) && posY == 0) { // p1's server ports
            curOpponent->downloadLink(curPlayer->getPureLink(id));
        }
        else if ((posY == -1) && posX != 3 && posX != 4) { // p1's download edge
            curPlayer->downloadLink(curPlayer->getPureLink(id));
        }
        else if ((posX == 3 || posX == 4) && posY == 7) { // own server port!?
            curPlayer->moveLink(id, oppDir, turn);
            posX = curPlayer->getPureLink(id).getPosX();
            posY = curPlayer->getPureLink(id).getPosY();
            b->getCell(posX, posY)->setState(id);
            throw logic_error {"You can't move your link onto your own Server Port. Try again."};
        } else if (posX > 7 || posY > 7 || posX < 0 || posY < 0) { // off the map!!?
            curPlayer->moveLink(id, oppDir, turn);
            posX = curPlayer->getPureLink(id).getPosX();
            posY = curPlayer->getPureLink(id).getPosY();
            b->getCell(posX, posY)->setState(id);
            throw logic_error {"You can't move your link off the board. Try again."};
        }
    }

    // if it lands on other player's firewall
    if ((turn == 1 && b->getCell(posY, posX)->isFirewall(2)) ||
        (turn == 2 && b->getCell(posY, posX)->isFirewall(1))) {
        cout << "You've moved onto your opponent's Firewall!" << endl;
        curPlayer->getPureLink(id).reveal();
        if (curPlayer->getPureLink(id).getIsData() == false)
        {
            curPlayer->downloadLink(curPlayer->getPureLink(id));
        }
        else b->getCell(posX, posY)->setState(id);
    } //if it lands on a player's blackhole
    else if ((turn == 1 && b->getCell(posY, posX)->isBlackhole(2)) ||
        (turn == 2 && b->getCell(posY, posX)->isBlackhole(1))) {
        cout << "You've moved onto your opponent's Blackhole!" << endl;
        curPlayer->getPureLink(id).reveal();
        if (curPlayer->getPureLink(id).getIsData() == false)
        {
            curPlayer->removeLink(id);
        }
        else b->getCell(posX, posY)->setState(id);
    }
    // if it lands on other player's link = BATTLE!!
    // the only cell states left should be '.' and '[link]'
    else if (b->getCell(posY, posX)->getState() != '.') {
        char linkState = b->getCell(posY, posX)->getState();
        if ((turn == 1 && (linkState == 'a' || linkState == 'b' || linkState == 'c' 
                                    || linkState == 'd' || linkState == 'e' || linkState == 'f' 
                                    || linkState == 'g' || linkState == 'h'))
            || (turn == 2 && (linkState == 'A' || linkState == 'B' || linkState == 'C' 
                                    || linkState == 'D' || linkState == 'E' || linkState == 'F' 
                                    || linkState == 'G' || linkState == 'H'))) { // try to attack own link!?!?
            curPlayer->moveLink(id, oppDir, turn);
            posX = curPlayer->getPureLink(id).getPosX();
            posY = curPlayer->getPureLink(id).getPosY();
            b->getCell(posX, posY)->setState(id);
            throw logic_error {"Don't attack your own link! Try again."};
        }
        // at this point, it should be certain that the cell's state is the other player's link
        int curLinkLevel = curPlayer->getPureLink(id).getStrength();
        int oppLinkLevel = curOpponent->getPureLink(b->getCell(posY, posX)->getState()).getStrength();
        curPlayer->getPureLink(id).reveal();
        curOpponent->getPureLink(b->getCell(posY, posX)->getState()).reveal();

        if (curLinkLevel >= oppLinkLevel) { // if curPlayer wins
            curPlayer->downloadLink(curOpponent->getPureLink(b->getCell(posY, posX)->getState()));
            b->getCell(posX, posY)->setState(id);
        } else { // if curOpponent wins
            curOpponent->downloadLink(curPlayer->getPureLink(id));
        }
    } else { // lands on an empty cell: '.'
        b->getCell(posX, posY)->setState(id);
    }
}

void Game::useAbility(int i) {
    if (i < 0 || i > 5) throw logic_error {"Ability index out of range. Try again."};
    if (turn == 1) {
        player1->useAbility(i, *player2);
    } else {
        player2->useAbility(i, *player1);
    }
}

int Game::getTurn() const{ return turn; }

void Game::printAbilities() {
    if (turn == 1) {
        player1->printAbilities();
    } else {
        player2->printAbilities();
    }
}

void Game::toggleTurn() {
    turn == 1 ? turn = 2 : turn = 1;
}

Player* Game::getCurrentPlayer() {
    if (turn == 1) {
        return player1.get();
    }
    return player2.get();
}

TextObserver* Game::getTextObserver() {
    return td.get();
}

Board* Game::theBoard() {
    return b.get();
}

std::ostream &operator<<(std::ostream &out, const Game &g) {
    cout << "test";
    return out;
}

/*
std::ostream &operator<<(std::ostream &out, const Game &g) {
    out << "\nPlayer 1:" << endl;
    out << "Downloaded: " << g.player1->getNumData() << "D, " << g.player1->getNumVirus() << "V" << endl;
    out << "Abilities: " << g.player1->getNumAbilities() << endl;
    // printLinks
    for (int i = 0; i < 4; ++i) {
        char ch = "abcd"[i];
        string linkType;
        // check type of link
        if (g.player1->getPureLink(ch).getIsData()) linkType = "D";
        else linkType = "V";
        // print depends on whether the link has been revealed
        if (g.getTurn() == 2 && !g.player1->getPureLink(ch).getIsRevealed()) {
            out << ch << ": " << "? " << " ";
        }
        else out << ch << ": " << linkType << g.player1->getPureLink(ch).getStrength() << " ";
    }
    out << endl;
    for (int i = 0; i < 4; ++i) {
        char ch = "efgh"[i];
        string linkType;
        if (g.player1->getPureLink(ch).getIsData()) linkType = "D";
        else linkType = "V";
        if (!g.whoseTurn && !g.player1->getPureLink(ch).getIsRevealed()) {
            out << ch << ": " << "? " << " ";
        }
        else out << ch << ": " << linkType << g.player1->getPureLink(ch).getStrength() << " ";
    }
    out << endl;

    if (g.b) {      // check if the smart pointer actually points to an object
        out << *(g.b); // dereference the smart pointer to get the Board object
    } else{
        out << "Board not initialized." << endl;
    }
    out << "Player 2:" << endl;
    out << "Downloaded: " << g.player2->getNumData() << "D, " << g.player2->getNumVirus() << "V" << endl;
    out << "Abilities: " << g.player2->getNumAbilities() << endl;
    // printLinks
    for (int i = 0; i < 4; ++i) {
        char ch = "ABCD"[i];
        string linkType;
        if (g.player2->getPureLink(ch).getIsData()) linkType = "D";
        else linkType = "V";
        if (g.getTurn() == 1 && !g.player2->getPureLink(ch).getIsRevealed()) {
            out << ch << ": " << "? " << " ";
        }
        else out << ch << ": " << linkType << g.player2->getPureLink(ch).getStrength() << " ";
    }
    out << endl;
    for (int i = 0; i < 4; ++i) {
        char ch = "EFGH"[i];
        string linkType;
        if (g.player2->getPureLink(ch).getIsData()) linkType = "D";
        else linkType = "V";
        if (g.getTurn() == 1 && !g.player2->getPureLink(ch).getIsRevealed()) {
            out << ch << ": " << "? " << " ";
        }
        else out << ch << ": " << linkType << g.player2->getPureLink(ch).getStrength() << " ";
    }
    return out << endl << endl;
}
*/

/*
void Game::enableGraphics() {
    showGraphic = true;
}

bool Game::isGraphicsEnabled() {
    return showGraphic;
}
*/

string Game::playerInfo(int player) {
    return "playerInfo needs to be changed";
}

/*
string Game::playerInfo(int player) {
    Player *curPlayer;
    if (turn == 1) {
        curPlayer = player1.get();
    } else {
        curPlayer = player2.get();
    }

    stringstream ss;
    ss << "Downloaded: ";
    

    if (player == 1) {
        ss << curPlayer->getNumData() << "D,  " << curPlayer->getNumVirus() << "V" << endl;
        int counter = 0;
        for (int i = 0; i < (int)curPlayer->getOwns().size(); ++i) {
            ss << curPlayer->getOwns()[i].getSymbol() << ": ";
            if (turn == 1) {
                //Data or virus?
                curPlayer->getOwns()[i].getIsData() ? ss << "D" : ss << "V";
                ss << curPlayer->getOwns()[i].getStrength() << " ";
            } else if (curPlayer->getOwns()[i].getIsRevealed()) { //turn 2 & revealed
                curPlayer->getOwns()[i].getIsData() ? ss << "D" : ss << "V";
                ss << curPlayer->getOwns()[i].getStrength() << " ";
            } else { //turn 2 & not revealed
                ss << "? ";
            }
            counter++;
            if (counter >= 4) {
                counter = 0;
                ss << endl;
            }
        }
    } else if (player == 2) {
        ss << player2->getNumData() << "D,  " << player2->getNumVirus() << "V" << endl;
        int counter = 0;
        for (int i = 0; i < (int)player2->getOwns().size(); ++i) {
            ss << player2->getOwns()[i].getSymbol() << ": ";
            if (turn == 2) {
                //Data or virus?
                player2->getOwns()[i].getIsData() ? ss << "D" : ss << "V";
                ss << player2->getOwns()[i].getStrength() << " ";
            } else if (player2->getOwns()[i].getIsRevealed()) { //turn 1 & revealed
                player2->getOwns()[i].getIsData() ? ss << "D" : ss << "V";
                ss << player2->getOwns()[i].getStrength() << " ";
            } else { //turn 1 & not revealed
                ss << "? ";
            }
            counter++;
            if (counter >= 4) {
                counter = 0;
                ss << endl;
            }
        }
    }
    return ss.str();
}

*/