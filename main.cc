#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <ctime>
#include "game.h"
#include "player.h"
#include "ability/ability.h"
#include "textobserver.h"
//#include "graphicsdisplay.h"

using namespace std;

int main(int argc, char* argv[]) {
    unique_ptr<Game> gp = make_unique<Game> ();
    unique_ptr<Player> p1 = make_unique<Player>(gp.get());
    unique_ptr<Player> p2 = make_unique<Player>(gp.get());
    gp->getTextObserver()->addGame(gp.get());
    std::cout << "Welcome to RAIInet!" << endl;
    // setup
    bool linksSpecifiedOne = false;
    bool linksSpecifiedTwo = false;
    
    for (int i = 1; i < argc; ++i) {
        string command = argv[i];

        if (command == "-ability1") {
            if (i != argc-1 && argv[i+1][0] != '-') {
                for (int j = 0; j < 5; ++j) {
                    p1->addAbility(argv[i+1][j]);
                }
            }
            else {
                p1->addAbility('L');
                p1->addAbility('F');
                p1->addAbility('D');
                p1->addAbility('S');
                p1->addAbility('P');
            }
        }

        else if (command == "-ability2") {
            if (i != argc-1 && argv[i+1][0] != '-') {
                for (int j = 0; j < 5; ++j) {
                    p2->addAbility(argv[i+1][j]);
                }
            }
            else {
                p2->addAbility('L');
                p2->addAbility('F');
                p2->addAbility('D');
                p2->addAbility('S');
                p2->addAbility('P');
            }
        }

        else if (command == "-link1") {
            linksSpecifiedOne = true;
            string fileName;
            char ids[8] = {'a','b','c','d','e','f','g','h'};
            fileName = argv[i+1];
            fstream f {fileName};
            for (int i = 0; i < 8; ++i) {
                string link;
                f >> link;
                p1->addLink(ids[i], link);
            }
        }

        else if (command == "-link2") {
            linksSpecifiedTwo = true;
            string fileName;
            char ids[8] = {'A','B','C','D','E','F','G','H'};
            fileName = argv[i+1];
            fstream f {fileName};
            for (int i = 0; i < 8; ++i) {
                string link;
                f >> link;
                p2->addLink(ids[i], link);
            }
        }

        /*
        else if (command == "-graphics") {
            Xwindow w;
            gp->enableGraphics();
        }
        */
    } // for loop

    // if the links are not specified for each player
    if (!linksSpecifiedOne) {
        char ids[8] = {'a','b','c','d','e','f','g','h'};
        vector<string> theLinks = {"D1", "D2", "D3", "D4", "V1", "V2", "V3", "V4"};
        for (int i = 0; i < 8; ++i) {
            srand((int)time(0)); // seed for random based on time
            int index = (rand() % (8-i)); // get index of the link we take from theLinks randomly
            p1->addLink(ids[i], theLinks[index]); // add this link to p1's links
            theLinks.erase(theLinks.begin()+index); // remove this link from theLinks so no duplicate
        } // for
    }

    if (!linksSpecifiedTwo) {
        char ids[8] = {'A','B','C','D','E','F','G','H'};
        vector<string> theLinks = {"D1", "D2", "D3", "D4", "V1", "V2", "V3", "V4"};
        for (int i = 0; i < 8; ++i) {
            srand((int)time(0) + 1); // seed for random based on time
            int index = (rand() % (8-i)); // get index of the link we take from theLinks randomly
            p2->addLink(ids[i], theLinks[index]); // add this link to p1's links
            theLinks.erase(theLinks.begin()+index); // remove this link from theLinks so no duplicate
        } // for
    }

    gp->initPlayerOne(move(p1));
    gp->initPlayerTwo(move(p2));
    gp->init();
    std::cout << *gp << endl;

    std::cout << "Player 1's turn." << endl;

    // setup finished
    // interactions
    string command;
    bool usedAbility = false;

    while (cin >> command) {
        try {
            if (gp->checkFinished()) { // Game::checkFinished might produce output
                cout << "GAME FINISHED." << endl;
                return 0;
            }
            if (command == "move") {
                char linkId;
                char direction;
                cin >> linkId >> direction;
                // directions can be 'north', 'east', 'south', 'west'
                gp->moveLink(linkId, direction); // (*) check valid id, direction, 
                // check if finished
                if (gp->checkFinished()) {
                    cout << "GAME FINISHED." << endl;
                    return 0;
                }

                gp->toggleTurn();
                std::cout << *gp;
                
                usedAbility = false;
                    // print whose turn
                if (gp->getTurn() == 1) std::cout << "Player 1's turn." << endl;
                else std::cout << "Player 2's turn." << endl;
            }

            else if (command == "abilities") {
                gp->printAbilities();
            }

            else if (command == "ability") {
                if (usedAbility) { // if ability has been used this turn
                    throw logic_error {"ability has already been used this turn."};
                }
                int index;
                cin >> index;
                gp->useAbility(index-1); // (*) check valid index, not used yet
                usedAbility = true; // ability has now been used this turn
            }

            else if (command == "board") {
                std::cout << *gp;
            }

            else if (command == "sequence") {
                string fileName;
                cin >> fileName;
                fstream f {fileName};

                if (!f.is_open()) {
                    cerr << "Error opening file: " << fileName << endl;
                    continue;  // Go to the next iteration of the loop
                }

                while (f >> command) {
                    try {

                    if (gp->checkFinished()) { // Game::checkFinished might produce output
                        cout << "GAME FINISHED." << endl;
                        return 0;
                    }
                    if (command == "move") {
                        char linkId;
                        char direction;
                        f >> linkId >> direction;
                        
                        gp->moveLink(linkId, direction); // (*) check valid id, direction, 
                        // check if finished
                        if (gp->checkFinished()) {
                            cout << "GAME FINISHED." << endl;
                            return 0;
                        }

                        gp->toggleTurn();
                        std::cout << *gp;
                        
                        usedAbility = false;
                            // print whose turn
                        if (gp->getTurn() == 1) std::cout << "Player 1's turn." << endl;
                        else std::cout << "Player 2's turn." << endl;
                    }

                    else if (command == "abilities") {
                        gp->printAbilities();
                    }

                    else if (command == "ability") {
                        if (usedAbility) { // if ability has been used this turn
                            throw logic_error {"ability has already been used this turn."};
                        }
                        int index;
                        f >> index;
                        gp->useAbility(index-1); // (*) check valid index, not used yet
                        usedAbility = true; // ability has now been used this turn
                    }

                    else if (command == "board") {
                        std::cout << *gp;
                    }

                    // TODO:
                    // else if (command == "sequence") { // NESTED file
                    //     string nestedFileName;
                    //     f >> nestedFileName;
                    //     ifstream nestedFile {nestedFileName};
                    //     if (nestedFile.is_open()) {
                    //         // Read commands from the nested file
                    //         f = nestedFile;
                    //         continue;  // Go to the next iteration of the loop
                    //     }
                    // }

                    else if (command != "quit") {
                        cerr << "Invalid command, try again." << endl;
                    }

                    if (command == "quit" || cin.eof()) {
                        cout << "Quitting RAIInet." << endl;
                        return 0;
                    }
                    cout << command << endl;
                    } // try
                    catch (std::logic_error& r) {
                        cerr << r.what() << endl;
                        continue;
                    } // catch
                }
            }

            else if (command == "quit" || cin.eof()) {
                return 0;
            }

            else {
                cerr << "Invalid command, try again." << endl;
            }
        } // try
        catch (std::logic_error& r) {
            cerr << r.what() << endl;
            continue;
        } // catch
    } // while
    
}

