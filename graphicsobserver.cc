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

struct charDifference {
	int lineNumber;
	int charPosition;
	char newChar;
}

vector<string> splitIntoLines(const string &s) {
	vector<string> lines;
	istringstream iss{s};
	string line;
	while (getline(iss, line)) {
        lines.push_back(line);
    }
	return lines;
}

vector<charDifference> getCharDifferences(const string &s1, const string &s2) {
	vector<string> lines1 = splitIntoLines(s1);
	vector<string> lines2 = splitIntoLines(s2);
	vector<charDifference> differences;
	for (int i = 0; i < lines1.size(); ++i) {
		const string &line1 = lines1[i];
		const string &line2 = lines2[i];
		for (j = 0; j < line1.size(); ++j) {
			char char1 = line1[j];
			char char2 = line2[j];
			if (char1 != char2) {
				differences.push_back(charDifference{
					i, // line number (0-indexed)
					j, // character position (0-indexed)
					char2 // new character
				})
			}
		}
	}
	return differences;
}

void GraphicsObserver::notify() {
    ostringstream oss;
    oss << *game; // uses operator<< to retrieve stringstream
    string currState = oss.str();
	const int xSpacing = 5; // don't know the spacing between letters yet (ffs y the servers smoking)
    const int ySpacing = 25;
	const int xBoardSpacing = 40;
	const int yBoardSpacing = 40;
	if (prevState) { // only uses chardifference if prevState is not ""
		vector<charDifference> charDifferences = getCharDifferences(prevState, currState);
		prevState = currState;
		for (const charDifference &diff : charDifferences) { // iterates through charDifferences, so will rewrite as little as possible
			if (diff.lineNumber >= 6 && diff.lineNumber <= 13) { // board
				int x = 10 + xBoardSpacing * diff.charPosition;
				int y = 10 + yBoardSpacing * diff.lineNumber;
				int color = getColor(diff.charPosition, diff.lineNumber - 6);
				if (color == Xwindow::White && color == Xwindow::Blue && color == Xwindow::Black) { // avoid drawing character for servers, unknowns, empty cells
					window->fillRectangle(x, y, xBoardSpacing, yBoardSpacing, color);
				} else {
					window->fillRectangle(x, y, xBoardSpacing, yBoardSpacing, color);
					window->drawString(x, y, diff.newChar);
				}
			} else {
				int x = 10 + xSpacing * diff.charPosition;
				int y = 10 + ySpacing * diff.lineNumber;
				window->fillRectangle(x, y, xSpacing, ySpacing, Xwindow::White); // erases
				window->drawString(x, y, diff.newChar);
			}
		}
	} else { // runs if this is first time we print to window
		istringstream iss{text};
    	string line;
    	int currLine = 10;
    	const int lineSpacing = 25;
    	// draw each line at adjusted y-coordinates
    	while (getline(iss, line)) {
    	    window->drawString(10, currLine, line);
    	    currLine += lineSpacing; // move to the next line
    	}
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
