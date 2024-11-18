#ifndef LINK_H
#define LINK_H

class Link {
    int posX, posY, strength;
    bool isRevealed, isData, isBoosted, isDownloaded, isDiagonal;
    public:
    int getPosX();
    void setPosX(int x);
    int getPosY();
    void setPosY(int y);
    int getStrenth();
    int setStrength(int s);
    bool getIsRevealed();
    bool getIsData();
    bool getIsBoosted();
    bool getIsDownloaded();
    void setIsData(bool value);
    void setIsDownloaded(bool value);
    void setIsBoosted(bool value);
    void setIsDiagonal(bool value);
    bool getIsDiagonal();
    void reveal();
    void moveU();
    void moveD();
    void moveL();
    void moveR();
};

#endif
