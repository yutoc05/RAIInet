#include "game.h"
#include "board.h"
#include "link.h"
#include "cell.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

Game::Game() : p1{nullptr}, p2{nullptr}, td{new TextDisplay}, gd{nullptr} {}

Game::~Game() {}

void Game::initPlayerOne(unique_ptr<Player> player1) { p1 = move(player1); }

void Game::initPlayerTwo(unique_ptr<Player> player2) { p2 = move(player2); }

void Game::moveLink(char id, char dir) {
    if (turn == 1) {
        Player *curPlayer = player1;
        Player *curOpponent = player2;
    } else {
        Player *curPlayer = player2;
        Player *curOpponent = player1;
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
        Player *curPlayer = player1;
        Player *opponent = player2;
    } else {
        Player *curPlayer = player2;
        Player *opponent = player1;
    }
    curPlayer->useAbility(i, *opponent);
}

int Game::turn() { return turn; }

void Game::printAbilities() {
    Player *curPlayer = theirTurn(turn);
    curPlayer->printAbilities();
}

void Game::enableGrapics() {
    showGraphic = true;
}

bool Game::isGraphicsEnabled() {
    return showGraphic;
}

string Game::playerInfo(int player) {
    stringstream ss;
    ss << "Downloaded: ";
    ss << player1->getNumData() << "D,  " << getNumVirus() << "V" << endl;

    if (player == 1) {
        int counter = 0;
        for (int i = 0; i < player1->getOwns().size(); ++i) {
            ss << player1->getOwns()[i]->getSymbol() << ": ";
            if (turn == 1) {
                //Data or virus?
                player1->getOwns()[i]->getIsData() ? ss << "D" : ss << "V";
                ss << player1->getOwns()[i]->getStrength() << " ";
            } else if (player1->getOwns()[i]->getIsRevealed()) { //turn 2 & revealed
                player1->getOwns()[i]->getIsData() ? ss << "D" : ss << "V";
                ss << player1->getOwns()[i]->getStrength() << " ";
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

