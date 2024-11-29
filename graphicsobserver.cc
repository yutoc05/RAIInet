#include "graphicsobserver.h"
#include "game.h"
#include "window.h"
#include "link.h"
#include "player.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

const int sizeOfBlock = 10;

GraphicsObserver::GraphicsObserver(): window{move(make_unique<Xwindow>(sizeOfBlock * 100, sizeOfBlock * 100))}, prevState{""} {}

void GraphicsObserver::addGame(Game* g) {
    game = g;
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

vector<int> getDifferingLines(const string &text1, const string &text2) {
    auto lines1 = splitIntoLines(text1);
    auto lines2 = splitIntoLines(text2);

    std::vector<int> differingLines;
    size_t maxLines = std::max(lines1.size(), lines2.size());

    for (size_t i = 0; i < maxLines; ++i) {
        // If one text has fewer lines, treat the missing lines as differing
        if (i >= lines1.size() || i >= lines2.size() || lines1[i] != lines2[i]) {
            differingLines.push_back(i);
        }
    }
    return differingLines;
}

string getLine(const string &s, int lineNumber) {
    vector<string> lines = splitIntoLines(s);
    
    // Return the line if it exists
    if (lineNumber >= 0 && lineNumber < lines.size()) {
        return lines[lineNumber];
    } else {
        return ""; // Return an empty string if lineNumber is out of range
    }
}

void GraphicsObserver::notify() {
    // Serialize the current game state
    ostringstream oss;
    oss << *game;
    string currState = oss.str();

    // Get differing line indices
    vector<int> differingLines = getDifferingLines(prevState, currState);
    // Parse lines of the current state
    vector<string> currLines = splitIntoLines(currState);

    // Process and redraw only the differing lines
    const int textSpacing = 25;
	const int boardSpacing = 50;
    const int xStart = 10; // X-coordinate for starting text/rectangles

    for (size_t l : differingLines) {
		if (l <= 5) { // p1 info
			// Calculate Y-coordinate for the line
        	int yCoord = 10 + (textSpacing * l);
        	// Erase the old line
        	window->fillRectangle(xStart, yCoord - 10, 200, textSpacing - 10, Xwindow::White); // Adjust width if necessary
        	// Draw the new line
        	if (l < currLines.size()) {
        	    window->drawString(xStart, yCoord, currLines[l]);
        	}
		} else if (l <= 13) { //board
			int yCoord = 160 + (boardSpacing * (l - 6));
			for (int i = 0; i < 8; ++i) {
				if (currLines[l][i] != getLine(prevState, l)[i]) {
					window->fillRectangle(xStart + (i * boardSpacing), yCoord - 10, boardSpacing - 5, boardSpacing - 10, getColor(i, l - 6));
				}
				window->drawString(xStart + (i * boardSpacing) + 18, yCoord + 15, string(1, currLines[l][i]));
			}
		} else { // p2 info
			int yCoord = 580 + (textSpacing * (l - 14));
			window->fillRectangle(xStart, yCoord - 10, 200, textSpacing - 10, Xwindow::White); // Adjust width if necessary
			if (l < currLines.size()) {
        	    window->drawString(xStart, yCoord, currLines[l]);
        	}
		}
    }

	// colors links
	for (int i = 0; i < 8; ++i) {
		int yCoord = 160 + (boardSpacing * i);
		for (int j = 0; j < 8; ++j) {
			char name = game->theBoard()->charAt(i, j);
			if (name == 'S' || name == '.' || name == 'w' || name == 'm') {
				continue;
			} else {
				window->fillRectangle(xStart + (j * boardSpacing), yCoord - 10, boardSpacing - 5, boardSpacing - 10, getColor(j, i));
				window->drawString(xStart + (j * boardSpacing) + 18, yCoord + 15, string(1, currLines[i + 6][j]));
			}
		}
	}




    // Update the previous state after successful processing
    prevState = currState;
}

int GraphicsObserver::getColor(int i, int j) {
	char name = game->theBoard()->charAt(j, i);
	int player = 0;
	if (name == '.') {
		return Xwindow::White;
	} else if (name == 'S') {
        return Xwindow::Blue;
	} else if (name == 'm' || name == 'w') {
		return Xwindow::Purple;
	} else if (name <= 'h' && name >= 'a') {
		player = 1;
	} else if (name <= 'H' && name >= 'A') {
		player = 2;
	}
	Link& l = game->getCurrentPlayer()->getPureLink(name);
	bool linkIsRevealed = l.getIsRevealed();
	bool linkIsData = l.getIsData();
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