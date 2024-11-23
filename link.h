#ifndef LINK_H
#define LINK_H

class Link {
    int posX, posY, strength;
    char symbol;
    bool isRevealed = false;
    bool isData =false;
    bool isBoosted = false;
    bool isDownloaded = false 
    bool isDiagonal = false;

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

        void setIsDiagonal(bool value) { isDiagonal = value; }
        bool getIsDiagonal() const { return isDiagonal; }
        void reveal();
        void moveU();
        void moveD();
        void moveL();
        void moveR();
};

#endif
