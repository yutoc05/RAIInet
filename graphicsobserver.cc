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
        window.drawString(10, currLine, line);
        currLine += lineSpacing; // Move to the next line
    }
    char c;
    cin >> c; // Wait for user input before closing the window
}

/*int GraphicsObserver::getColor(int i, int j) {
	char name = game->theBoard()->charAt(i, j);
	int index;
	int player = 0;
	string colourstrength;
	string colour;
	string strength;
	if (name == '.') {
		return Xwindow::White;
	} else if (name == 'S') {
        return Xwindow::Blue;
	} else if (name == 'M' || name == 'W') {
		if (name == 'M'){
			colour = "blueM";
		}else {
			colour = "blueW";
		}
		strength += "0";
	} else if (name <= 'h' && name >= 'a') {
		index = name - 'a';
		player = 1;
	} else if (name <= 'H' && name >= 'A') {
		index = name - 'A';
		player = 2;
	}

	if (player == 1 && playerTurn == 1) {
		if (p1order[index][0] == 'V') {
			colour = "red";
		} else if (p1order[index][0] == 'D') {
			colour = "green";
		}
		strength += p1order[index][1];
	} else if (player == 1 && playerTurn == 2) {
		if (p1hidden[index]) {
			colour = "black";
		} else if (p1order[index][0] == 'V') {
			colour = "red";
		} else if (p1order[index][0] == 'D') {
			colour = "green";
		}
		strength += p1order[index][1];
	} else if (player == 2 && playerTurn == 1) {
		if (p2hidden[index]) {
			colour = "black";
		} else if (p2order[index][0] == 'V') {
			colour = "red";
		} else if (p2order[index][0] == 'D') {
			colour = "green";
		}
		strength += p2order[index][1];
	} else if (player == 2 && playerTurn == 2) {
		if (p2order[index][0] == 'V') {
			colour = "red";
		} else if (p2order[index][0] == 'D') {
			colour = "green";
		}
		strength += p2order[index][1];
	}
	colourstrength = name + strength + colour;
	return colourstrength;
}*/
