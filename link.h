#ifndef LINK_H
#define LINK_H

class Link {
    int posX, posY, strength;
    char symbol;
    bool isRevealed, isData, isBoosted, isDownloaded, isDiagonal;
    public:
    Link(int posX, int posY, int strength, char symbol);
    ~Link() = default;
    char getSymbol();
    void setSymbol(char c);
    int getPosX();
    void setPosX(int x);
    int getPosY();
    void setPosY(int y);
    int getStrength();
    void setStrength(int s);
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
    bool getIsRevealed();
    void moveU();
    void moveD();
    void moveL();
    void moveR();
};

#endif
