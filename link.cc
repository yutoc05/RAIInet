#include "link.h"
#include <memory>
#include <iostream>
using namespace std;

Link::Link(int posX, int posY, int strength): posX{posX}, posY{posY}, strength{strength},
isRevealed{false}, isData{false}, isBoosted{false}, isDownloaded{false}, isDiagonal{false} {}
//default all booleans to false

int Link::getPosX() {return posX;}

void Link::setPosX(int x) {posX = x;}

int Link::getPosY() {return posY;}

void Link::setPosY(int y) {posY = y;}

int Link::getStrength() {return strength;}

void Link::setStrength(int s) {strength = s;}

bool Link::getIsRevealed() {return isRevealed;}

bool Link::getIsData() {return isData;}

bool Link::getIsBoosted() {return isBoosted;}

bool Link::getIsDownloaded() {return isDownloaded;}

void Link::setIsData(bool v) {isData = v;}

void Link::setIsDownloaded(bool v) {isDownloaded = v;}

void Link::setIsBoosted(bool v) {isBoosted = v;}

void Link::setIsDiagonal(bool v) {isDiagonal = v;}

bool Link::getIsDiagonal() {return isDiagonal;}

void Link::reveal() {isRevealed = true;}

void Link::moveU() {
    posY++;
}

void Link::moveD() {
    posY--;
}

void Link::moveL() {
    posX--;
}

void Link::moveR() {
    posX++;
}

/* Tested works as expected
int main() {
    unique_ptr<Link> p1 = std::make_unique<Link>(0, 0, 1);
    //test movement
    cout << "X: " << p1->getPosX() << ", Y: " <<  p1->getPosY() << endl;
    p1->setPosX(4);
    p1->setPosY(3);
    cout << "X: " << p1->getPosX() << ", Y: " <<  p1->getPosY() << endl;
    p1->setPosX(6);
    p1->setPosY(7);
    cout << "X: " << p1->getPosX() << ", Y: " <<  p1->getPosY() << endl;
    p1->moveD();
    p1->moveL();
    cout << "X: " << p1->getPosX() << ", Y: " <<  p1->getPosY() << endl;
    p1->moveR();
    p1->moveU();
    cout << "X: " << p1->getPosX() << ", Y: " <<  p1->getPosY() << endl;
    cout << "Strength: " << p1->getStrength() << endl;
    p1->setStrength(4);
    cout << "Strength: " << p1->getStrength() << endl;
    
    //test flags
    unique_ptr<Link> p2 = std::make_unique<Link>(3, 2, 1);
    p2->getIsRevealed() ? cout << "revealed" << endl : cout << "not revealed" << endl;
    p2->reveal();
    p2->getIsRevealed() ? cout << "revealed" << endl : cout << "not revealed" << endl;
    p2->getIsDiagonal() ? cout << "diagonal" << endl : cout << "not diagonal" << endl;
    p2->setIsDiagonal(true);
    p2->getIsDiagonal() ? cout << "diagonal" << endl : cout << "not diagonal" << endl;
    p2->getIsData() ? cout << "data" << endl : cout << "virus" << endl;
    p2->getIsBoosted() ? cout << "boosted" << endl : cout << "not boosted" << endl;
    p2->setIsBoosted(true);
    p2->getIsBoosted() ? cout << "boosted" << endl : cout << "not boosted" << endl;
    p2->getIsDownloaded() ? cout << "downloaded" << endl : cout << "not downloaded" << endl;
    p2->setIsDownloaded(true);
    p2->getIsDownloaded() ? cout << "downloaded" << endl : cout << "not downloaded" << endl;

}
*/
