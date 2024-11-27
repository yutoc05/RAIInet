#include "graphicsobserver.h"
#include "game.h"
#include "window.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

GraphicsObserver::GraphicsObserver() {}

void GraphicsObserver::addGame(Game* g) {
    game = g;
}

const int sizeOfBlock = 10;

void GraphicsObserver::notify() {
    Xwindow window{sizeOfBlock * 25, sizeOfBlock * 55};
    ostringstream oss;
    oss << *game;
    // Split the text into lines
    string text = oss.str();
    istringstream iss{text};
    string line;
    int currLine = 10;
    const int lineSpacing = 25;
    // Draw each line at adjusted y-coordinates
    while (getline(iss, line)) {
        window.drawString(10, currLine, line);
        currLine += lineSpacing; // Move to the next line
    }
    char c;
    cin >> c; // Wait for user input before closing the window
}
