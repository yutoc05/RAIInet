#include "link.h"

Link::Link(int posX, int posY, int strength): posX{posX}, posY{posY}, strength{strength},
isRevealed{false}, isData{false}, isBoosted{false}, isDownloaded{false}, isDiagonal{false} {}
//default all booleans to false

int Link::getPosX() {return posX;}

void Link::setPosX(int x) {posX = x;}

int Link::getPosY() {return posY;}

void Link::setPosY(int y) {posY = y;}

int Link::getStrenth() {return strength;}

int Link::setStrength(int s) {strength = s;}

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

void Link::moveU() {posY++;}

void Link::moveD() {posY--;}

void Link::moveL() {posX--;}

void Link::moveR() {posX++;}
