#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

// This is a text adventure game, where the player is a detective
// The game is structured as a series of rooms, each with a clue to find
// The player must find all the clues to solve the murder mystery.

struct Room {
    int index;
    string locationName;
    string _clue;
    string _falseClue;
};

struct Suspect {
    string name;
    string ownedHorse;
    string hairColour;
    string ownedWeapon;
    string distinctFeat;
    string clothingStyle;
    string alibi;


};

struct Game {
    vector<Room> roomArray;
    vector<Suspect> suspectArray;
    int currentRoomIndex;
    int cluesCollected;
    bool solvedCase;

};

vector<Room> loadRooms() {
    ifstream inputFile("rooms.csv"); // Open CSV File
    if (!inputFile.is_open()) {
        cerr << "Error Opening File!" << endl;
        return vector<Room>(); // Empty vector
    }

    vector<Room> rooms;

    string line;
    while (getline(inputFile, line)) {
        istringstream ss(line);
        string token;

        Room room; // Create an instance
        // Read Data
        getline(ss, token, ',');
        room.index = stoi(token);

        getline(ss, room.locationName, ',');
        getline(ss, room._clue, ',');
        getline(ss, room._falseClue, ',');

        rooms.push_back(room); // Add back to vector
    }

    // DEBUG SECTION
    //for (const auto &r : rooms) {
    //    cout << "Index: " << r.index << "\n, Location: " << r.locationName << "\n, Clue: " << r._clue << "\n, False Clue: " << r._falseClue << endl;
    //}

    return rooms;  // Return the vector
}

vector<Suspect> loadSuspects() {
    ifstream inputFile("suspects.csv"); // Open CSV File
    if (!inputFile.is_open()) {
        cerr << "Error Opening File!" << endl;
        return vector<Suspect>(); // Return empty vector
    }

    vector<Suspect> suspects;

    string line;
    while (getline(inputFile, line)) {
        istringstream ss(line);
        string token;

        Suspect suspect; // Create an instance
        // Read Data
        getline(ss, suspect.name, ',');
        getline(ss, suspect.ownedHorse, ',');
        getline(ss, suspect.hairColour, ',');
        getline(ss, suspect.ownedWeapon, ',');
        getline(ss, suspect.distinctFeat, ',');
        getline(ss, suspect.clothingStyle, ',');
        getline(ss, suspect.alibi, ',');

        suspects.push_back(suspect); // Add back to vector
    }

    // DEBUG SECTION
    //for (const auto &r : suspects) {
        //print the index of the suspect in the vector
        //cout << "Name: " << r.name << "\n Horse: " << r.ownedHorse << "\n Hair: " << r.hairColour << "\n Weapon: " << r.ownedWeapon << "\n Distinct Feature: " << r.distinctFeat << "\n Clothing Style: " << r.clothingStyle << endl;
    //}

    return suspects;  // Return the vector
}


void playGame(Game &game) {
    //print room name at array index of currentRoomIndex
    cout << "You are Sheriff TreHearty.\n" << endl;
    cout << "You come from a neighbouring town, here to investigate a double homicide.\n" << endl;
    cout << "The town sheriff Bronte has boiled it down to two suspects.\n" << endl;
    cout << "You have been given the task of finding out which one is guilty.\n" << endl;
    cout << "Investigate the town and find the clues to solve the mystery.\n" << endl;
    cout <<"You start off at: " <<game.roomArray[game.currentRoomIndex].locationName <<"."<< endl;

    //Create a loop until the player has found the killer
    while(!game.solvedCase){
        //The Player is given a choice of what to do
        //1) Investigate the room, 2) Investigate the Perimeter, 3) Read the Suspect Notes
        cout << "What would you like to do?" << endl;
        cout << "1) Investigate the room, 2) Investigate the Perimeter, 3) Read the Suspect Notes, 4) Try solve the case.\n 5) Go to next Location." << endl;
        int choice;
        cin >> choice;
        if(choice == 1){
            cout << "You have chosen to investigate the room." << endl;
            cout << "After looking around, you find something." << endl;
            cout <<game.roomArray[game.currentRoomIndex]._clue << endl;

        }
        if(choice == 2){
            //The Player is given a clue. It is either the correct clue or a false clue.
            cout << "Looking around the perimeter, details are scarce." << endl;
            cout << "However, you do manage to notice something." << endl;
            cout << game.roomArray[game.currentRoomIndex]._falseClue << endl;
        }
        if(choice == 3){
            //The Player Reads the Suspect Notes to help them solve the case.
            cout << "You look at your journal, it reads..."<<endl;
            for (const auto &s : game.suspectArray){
                cout << "Name: " << s.name << "\n Horse: " << s.ownedHorse << "\n Hair: " << s.hairColour << "\n Weapon: " << s.ownedWeapon << "\n Distinct Feature: " << s.distinctFeat << "\n Clothing Style: " << s.clothingStyle <<"\n\n"<< endl;
            }
        }
        if(choice == 4){
            //The player can try to solve the case, but they need to have collected some of the clues first.
            if(game.currentRoomIndex < 2){
                cout << "You haven't investigated enough yet!" << endl;
                cout << "Continue investigating...." << endl;
                continue;
            }
            else {
                cout << "You have chosen to try solve the case." << endl;
                cout << "You have collected enough clues to make a decision." << endl;
                cout << "Let's interrogate the two suspects we caught." << endl;

                for (auto &s : game.suspectArray) {
                    cout << "Name: " << s.name << "\n Alibi: " << s.alibi << "\n\n" << endl;
                }

                cout << "So, Who do you believe is guilty? Suspect 1 or 2?" << endl;
                int suspectChoice;
                cin >> suspectChoice;
                if (suspectChoice == 1) {
                    cout << "You have chosen Suspect 1." << game.suspectArray[0].name << endl;
                    cout << "You were correct and the serial killings stop!" << endl;
                    game.solvedCase = true;
                } else if (suspectChoice == 2) {
                    cout << "You have chosen Suspect 2: " << game.suspectArray[1].name << endl;
                    cout << "You were wrong, months after, 4 more victims popped up, and he was caught red-handed!"
                         << endl;
                    game.solvedCase = true;
                } else {
                    //The choice number is invalid.
                }
            }
        }
        if(choice == 5){
            if(game.currentRoomIndex >= 4){
                cout << "There is nowhere left to investigate!" << endl;
                cout << "Read over your notes and try solve the case." << endl;
            }
            else {
                game.currentRoomIndex++;
                cout << "You are now at: " << game.roomArray[game.currentRoomIndex].locationName << "." << endl;
            }
        }
        else{
            //The choice number is invalid.

        }

    }
    cout <<"Post Game:\n" << endl;
    cout << "It was Jack Randall, the first suspect.\nHe claims to have borrowed a gun from a friend, but then why is there a reciept?\n"
            "Also, if his clothes was torn at the Mill, why were they found at the General Store's crime scene?" << endl;
}

void defineGame() {
    Game game;
    game.roomArray = loadRooms();
    game.suspectArray = loadSuspects();
    game.currentRoomIndex = 0;
    playGame(game);
}

int main() {
    defineGame();
    return 0;
}
