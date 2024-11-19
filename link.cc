#include "link.h"

const int boardSize = 8;

Link::Link(int posX, int posY, int strength): posX{posX}, posY{posY}, strength{strength},
isRevealed{false}, isData{false}, isBoosted{false}, isDownloaded{false}, isDiagonal{false} {}
//default all booleans to false

int Link::getPosX() {return posX;}

void Link::setPosX(int x) {posX = x;}

int Link::getPosY() {return posY;}

void Link::setPosY(int y) {posY = y;}

int Link::getStrenth() {return strength;}

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
    if (posY < (boardSize - 1)) {
        posY++;
    } 
}

void Link::moveD() {
    if (posY > 0) {
        posY--;
    }
}

void Link::moveL() {
    if (posX > 0) {
        posX--;
    }   
}

void Link::moveR() {
    if (posX < (boardSize - 1)) {
        posX++;
    }
}
