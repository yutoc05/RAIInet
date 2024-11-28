#include "graphicsobserver.h"
#include "game.h"
#include "window.h"
#include "link.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const int sizeOfBlock = 10;

GraphicsObserver::GraphicsObserver(): window{move(make_unique<Xwindow>(sizeOfBlock * 25, sizeOfBlock * 55))} {}

void GraphicsObserver::addGame(Game* g) {
    game = g;
}

void GraphicsObserver::notify() {
    // print text over rectangles
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
        window->drawString(10, currLine, line);
        currLine += lineSpacing; // Move to the next line
    }
}

int GraphicsObserver::getColor(int i, int j) {
	char name = game->theBoard()->charAt(i, j);
	int player = 0;
	if (name == '.') {
		return Xwindow::White;
	} else if (name == 'S') {
        return Xwindow::Blue;
	} else if (name == 'M' || name == 'W') {
		return Xwindow::Purple;
	} else if (name <= 'h' && name >= 'a') {
		player = 1;
	} else if (name <= 'H' && name >= 'A') {
		player = 2;
	}
	bool linkIsRevealed = game->theBoard()->getCell(i, j)->getLink()->getIsRevealed();
	bool linkIsData = game->theBoard()->getCell(i, j)->getLink()->getIsData();
	if (player == 1 && game->getTurn() == 1) { // a-h and p1 turn
		if (linkIsData) {
			return Xwindow::Green;
		} else {
			return Xwindow::Red;
		}
	} else if (player == 1 && game->getTurn() == 2) { // a-h and p2 turn
		if (!linkIsRevealed) {
			return Xwindow::Black;
		} else if (linkIsData) {
			return Xwindow::Green;
		} else {
			return Xwindow::Red;
		}
	} else if (player == 2 && game->getTurn() == 1) { // A-H and p1 turn
		if (!linkIsRevealed) {
			return Xwindow::Black;
		} else if (linkIsData) {
			return Xwindow::Green;
		} else {
			return Xwindow::Red;
		}
	} else if (player == 2 && game->getTurn() == 2) { // A-H and p2 turn
		if (linkIsData) {
			return Xwindow::Green;
		} else {
			return Xwindow::Red;
		}
	}
}
