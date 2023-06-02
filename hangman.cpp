#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

// thank you ChatGPT
std::vector<std::string> readFileToList(const std::string& filename) {
    std::vector<std::string> wordList;
    std::ifstream file(filename); // Open the file
    std::string word;

    if (file.is_open()) {
        while (getline(file, word)) { // Read words from the file
            wordList.push_back(word); // Add each word to the vector
        }
        file.close(); // Close the file
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    return wordList;
}

// thank you ChatGPT again
int getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(rng);
}

void printBootArt() {
    cout << "\n";
    cout << " |````\\     /\\     /````\\ |    /   ```|``` /````\\  ```|``` |    | |````` " << "\n";
    cout << " |    |    /  \\    |      |   /       |    |    |     |    |    | |      " << "\n";
    cout << " |----<   /----\\   |      |--\\        |    |    |     |    |----| |----- " << "\n";
    cout << " |    |  /      \\  |      |   \\       |    |    |     |    |    | |      " << "\n";
    cout << " |____/ /        \\ \\____/ |    \\      |    \\____/     |    |    | |_____ " << "\n";
    cout << "\n";
    cout << " |`````` |    | ```|``` |    | |````\\  |`````  " << "\n";
    cout << " |       |    |    |    |    | |    |  |       " << "\n";
    cout << " |----   |    |    |    |    | |----/  |-----  " << "\n";
    cout << " |       |    |    |    |    | |    \\  |       " << "\n";
    cout << " |       \\____/    |    \\____/ |     \\ |_____  " << "\n";
    cout << "\n";
    cout << " |    |     /\\     |\\    | /````\\ |\\    /|     /\\     |\\    |" << "\n";
    cout << " |    |    /  \\    | \\   | |      | \\  / |    /  \\    | \\   |" << "\n";
    cout << " |----|   /----\\   |  \\  | |      |  \\/  |   /----\\   |  \\  |" << "\n";
    cout << " |    |  /      \\  |   \\ | |   `| |      |  /      \\  |   \\ |" << "\n";
    cout << " |    | /        \\ |    \\| \\____/ |      | /        \\ |    \\|" << "\n";
    cout << "\n";
}

void printWin() {
    cout << "\n\n";
    cout << "                                      \\   / /```\\ |   |  |  ||  | ``|`` |\\   |" << "\n";
	cout << "    , ,                                \\ /  |   | |   |  \\  ||  /   |   | \\  |" << "\n";
	cout << "  ,\\   /,```````````````````````````    |   |   | |   |   \\ /\\ /    |   |  \\ |" << "\n";
	cout << " \\   X   / ,,,,,,,,,,,,,,,,,,,,,,,,,,   |   \\___/ \\___/    |  |   __|__ |   \\|" << "\n";
    cout << "\n";
}

void printLose(string correctWord) {
    cout << "\n\n";
    cout << "    '0'   \\   / /```\\ |   |  |    /```\\ /```' |```" << "\n";
	cout << "  |  |/    \\ /  |   | |   |  |    |   | |___  |___" << "\n";
	cout << "  |'/|      |   |   | |   |  |    |   |     | |   " << "\n";
	cout << "  | / \\     |   \\___/ \\___/  |___ \\___/ .___/ |___" << "\n";
	cout << "\n";
	cout << "The word was: " << correctWord << "\n";
}

void printHangman(int lives, vector<char> & guesses, int difficulty=10) {
    int wrongGuesses = difficulty - lives;
    
    string spb = string(wrongGuesses, ' ');
	string spa = string(lives, ' ');
	cout << spb << "   ,____|/_____,   " << spa << "                      \n";
	cout << spb << " /' ___ ___ __  ', " << spa << "                      \n";
	cout << spb << " | |   |   |  |  \\ " << spa << "  ,    ___            \n";
	cout << spb << " |  ``` ``` ``   | " << spa << " \\ `<'__\\''>,__       \n";
	cout << spb << " |       *       } " << spa << "  |   __________''`,, \n";
	cout << spb << " `()-----------()' " << spa << "  `-()-----------()'  \n";
	cout << string(80, ' ') << "\n";
}

int main() {
    printBootArt();
    
    // select a word
    string choice = "X";
    string wordbank_filePath = "";
    bool chosen = false;

    while (!chosen) {
        cout << "Pick a category: Smash Characters (1), Minecraft Blocks (2), Random Words (3): ";
        cin >> choice;
        switch (choice.at(0)) {
        case '1':
            wordbank_filePath = "wordbanksmashchr.txt"; chosen = true;
            break;
        case '2':
            wordbank_filePath = "wordbankmcblocks.txt"; chosen = true;
            break;
        case '3':
            wordbank_filePath = "wordbankother.txt"; chosen = true;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    }
    
    // set up blanks
    vector<string> wordbank = readFileToList(wordbank_filePath);
    string word = wordbank.at(getRandomNumber(0, wordbank.size() - 1));
    
    // clean up the word
    word.pop_back();
    for (auto & c: word) c = toupper(c);

    string blanks; char replacement;
    for (auto c: word) {
        switch (c) {
            case ' ':
            case '-':
            case '.':
                replacement = c;
                break;
            case '\0':
            case '\n':
                continue;
            default:
                replacement = '_';
                break;
        }
        blanks.push_back(replacement);
    }

    // cout << word << "\n"; //Test print//
    // cout << blanks << "\n"; //Test print//

    // guessing part
    vector<char> guesses;
    string guess;
    int difficulty = 15; //TODO implement difficulty settings
    int lives = difficulty; 

    while ((lives > 0) && (word.compare(blanks) != 0)) {
        cout << "\n\nGuess a letter\n" << blanks << "\n";
        if (guesses.size() > 0) {
            cout << "Guessed letters: {";
            for (int i = 0; i < guesses.size() - 1; ++i) {
                cout << guesses.at(i) << ", ";
            }
            cout << guesses.back() << "}\n";
        }
        else {
            cout << "Guessed letters: { }\n";
        }
        
        cin >> guess; guess.at(0) = toupper(guess.at(0));
        if (guess.compare("ESC") == 0) { break; } // dev tool
        else if (guess.size() > 1) { cout << "Guess must be a single letter\n"; continue; }
        else if (!isalpha(guess.at(0))) { cout << "Guess must be a letter\n"; continue; }
        else if (find(guesses.begin(), guesses.end(), guess.at(0)) != guesses.end()) { cout << "Already guessed that\n"; continue; }
        else if (find(word.begin(), word.end(), guess.at(0)) == word.end()) {
            cout << "Not in the word. Lives: " << --lives << "\n";
            guesses.push_back(guess.at(0));
        }
        else {
            cout << "Good guess\n";
            for (int i = 0; i < word.size(); ++i) {
                if (word.at(i) == guess.at(0)) {
                    blanks.at(i) = guess.at(0);
                }
            }
            guesses.push_back(guess.at(0));
        }
        printHangman(lives, guesses, difficulty);

        // cout << "(word.compare(blanks) != 0): " << (word.compare(blanks) != 0) << "\n"; //Test print//
        // cout << "|" << word << "|" << "\n"; //Test print//
        // cout << "|" << blanks << "|" << "\n"; //Test print//
        // cout << "word size: " << word.size() << ", blanks size: " << blanks.size() << "\n"; //Test print//
    }
    
    if (word.compare(blanks) == 0) { printWin(); }
    else { printLose(word); }

    return 0;
}