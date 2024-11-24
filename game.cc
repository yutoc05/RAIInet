#include "game.h"
#include "board.h"
#include "link.h"
#include "cell.h"
#include "player.h"
#include <iostream>
#include <sstream>
#include <string>
#include <memory>
using namespace std;

Game::Game() : p1{nullptr}, p2{nullptr}, td{new TextDisplay}, gd{nullptr} {}

Game::~Game() {}

void Game::initPlayerOne(unique_ptr<Player> player1) { p1 = move(player1); }

void Game::initPlayerTwo(unique_ptr<Player> player2) { p2 = move(player2); }

void Game::moveLink(char id, char dir) {
    Player *curPlayer;
    Player *curOpponent;
    if (turn == 1) {
        curPlayer = player1->get();
        curOpponent = player2->get();
    } else {
        curPlayer = player2->get();
        curOpponent = player1->get();
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
    if (b->getCell(posX, posY).isPlayer1Firewall()) {
        b->getCell(posX, posY).setState('m');
    } else if (b->getCell(posX, posY).isPlayer1Firewall()) {
        b->getCell(posX, posY).setState('w');
    } else  { //if normal cell
        b->getCell(posX, posY).setState('.');
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
            b->getCell(posX, posY).setState(id);
            throw logic_error {"You can't move your link onto your own Server Port. Try again."};
        }
        else if (posX > 7 || posY > 7 || posX < 0 || posY < 0)
        { // off the map!!?
            curPlayer->moveLink(id, oppDir, turn);
            posX = curPlayer->getPureLink(id).getPosX();
            posY = curPlayer->getPureLink(id).getPosY();
            b->getCell(posX, posY).setState(id);
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
            b->getCell(posX, posY).setState(id);
            throw logic_error {"You can't move your link onto your own Server Port. Try again."};
        } else if (posX > 7 || posY > 7 || posX < 0 || posY < 0) { // off the map!!?
            curPlayer->moveLink(id, oppDir, turn);
            posX = curPlayer->getPureLink(id).getPosX();
            posY = curPlayer->getPureLink(id).getPosY();
            b->getCell(posX, posY).setState(id);
            throw logic_error {"You can't move your link off the board. Try again."};
        }
    }

    // if it lands on other player's firewall
    if ((turn == 1 && b->getCell(posY, posX)->isFirewall(2)) ||
        (turn == 2 && b->getCell(posY, posX)->isFirewall(1))) {
        cout << "You've moved onto your opponent's Firewall!" << endl;
        curPlayer->getPureLink(id).reveal();
        if (curPlayer->getPureLink(id).checkIfData() == false)
        {
            curPlayer->downloadLink(curPlayer->getPureLink(id));
        }
        else b->getCell(posX, posY).setState(id);
    } else if ((turn == 1 && b->getCell(posY, posX)->isBlackhole(2)) ||
        (turn == 2 && b->getCell(posY, posX)->isBlackhole(1))) {
        cout << "You've moved onto your opponent's Blackhole!" << endl;
        curPlayer->getPureLink(id).reveal();
        if (curPlayer->getPureLink(id).checkIfData() == false)
        {
            curPlayer->removeLink(curPlayer->getPureLink(id));
        }
        else b->getCell(posX, posY).setState(id);
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
            b->getCell(posX, posY).setState(id);
            throw logic_error {"Don't attack your own link! Try again."};
        }
        // at this point, it should be certain that the cell's state is the other player's link
        int curLinkLevel = curPlayer->getPureLink(id).getStrength();
        int oppLinkLevel = curOpponent->getPureLink(b->getCell(posY, posX)->getState()).getStrength();
        curPlayer->getPureLink(id).reveal();
        curOpponent->getPureLink(b->getCell(posY, posX)->getState()).reveal();

        if (curLinkLevel >= oppLinkLevel) { // if curPlayer wins
            curPlayer->downloadLink(curOpponent->getPureLink(b->getCell(posY, posX)->getState()));
            b->getCell(posX, posY).setState(id);
        } else { // if curOpponent wins
            curOpponent->downloadLink(curPlayer->getPureLink(id));
        }
    } else { // lands on an empty cell: '.'
        b->getCell(posX, posY).setState(id);
    }
}

void Game::useAbility(int i) {
    if (i < 0 || i > 5) throw logic_error {"Ability index out of range. Try again."};
    if (turn == 1) {
        Player *curPlayer = player1->get();
        Player *opponent = player2->get();
        player1->useAbility(i, *opponent);
    } else {
        Player *curPlayer = player2->get();
        Player *opponent = player1->get();
        curPlayer->useAbility(i, *opponent);
    }
}

int Game::getTurn() { return turn; }

void Game::printAbilities() {
    if (turn == 1) {
        player1->printAbilities();
    } else {
        player2->printAbilities();
    }
}

/*
void Game::enableGraphics() {
    showGraphic = true;
}

bool Game::isGraphicsEnabled() {
    return showGraphic;
}
*/

string Game::playerInfo(int player) {
    Player *curPlayer;
    if (turn == 1) {
        curPlayer = player1->get();
    } else {
        curPlayer = player2->get();
    }

    stringstream ss;
    ss << "Downloaded: ";
    

    if (player == 1) {
        ss << curPlayer->getNumData() << "D,  " << curPlayer->getNumVirus() << "V" << endl;
        int counter = 0;
        for (int i = 0; i < curPlayer->getOwns().size(); ++i) {
            ss << curPlayer->getOwns()[i]->getSymbol() << ": ";
            if (turn == 1) {
                //Data or virus?
                curPlayer->getOwns()[i]->getIsData() ? ss << "D" : ss << "V";
                ss << curPlayer->getOwns()[i]->getStrength() << " ";
            } else if (curPlayer->getOwns()[i]->getIsRevealed()) { //turn 2 & revealed
                curPlayer->getOwns()[i]->getIsData() ? ss << "D" : ss << "V";
                ss << curPlayer->getOwns()[i]->getStrength() << " ";
            } else { //turn 2 & not revealed
                ss << "? ";
            }
            counter++;
            if (counter >= 4) {
                counter = 0;
                ss << endl;
            }
        }
    } else (player == 2) {
        ss << player2->getNumData() << "D,  " << player2->getNumVirus() << "V" << endl;
        int counter = 0;
        for (int i = 0; i < player2->getOwns().size(); ++i) {
            ss << player2->getOwns()[i]->getSymbol() << ": ";
            if (turn == 2) {
                //Data or virus?
                player2->getOwns()[i]->getIsData() ? ss << "D" : ss << "V";
                ss << player2->getOwns()[i]->getStrength() << " ";
            } else if (player2->getOwns()[i]->getIsRevealed()) { //turn 1 & revealed
                player2->getOwns()[i]->getIsData() ? ss << "D" : ss << "V";
                ss << player2->getOwns()[i]->getStrength() << " ";
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

