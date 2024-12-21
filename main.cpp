// program name goes here
// your name goes here
// any example usage or helpful command line arguments go here

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // For output formatting
using namespace std;

// Constants
const int MAX_BOWLERS = 10; // Maximum number of bowlers
const int NUM_GAMES = 4;    // Number of games per bowler

// Define a structure for bowler data
struct Bowler {
    string name;
    int scores[NUM_GAMES];
    int average;
};

// Define a class to handle bowling data
class BowlingData {
private:
    string fileName;        // File name for input data
    Bowler bowlers[MAX_BOWLERS]; // Array to hold bowler data
    int bowlerCount;        // Number of bowlers

public:
    // Constructor to initialize file name and bowler count
    BowlingData(const string& file) : fileName(file), bowlerCount(0) {}

    // Function to read data from the file
    bool readData() {
        ifstream inFile(fileName);
        if (!inFile) {
            return false; // File could not be opened
        }

        bowlerCount = 0;
        while (inFile >> bowlers[bowlerCount].name) {
            for (int i = 0; i < NUM_GAMES; i++) {
                inFile >> bowlers[bowlerCount].scores[i];
            }
            bowlerCount++;
            if (bowlerCount >= MAX_BOWLERS) break; // Stop if we reach the maximum number of bowlers
        }

        inFile.close();
        return true;
    }

    // Function to calculate average scores
    void calculateAverages() {
        for (int i = 0; i < bowlerCount; i++) {
            int total = 0;
            for (int j = 0; j < NUM_GAMES; j++) {
                total += bowlers[i].scores[j];
            }
            bowlers[i].average = total / NUM_GAMES; // Calculate the average
        }
    }

    // Function to output results to the console and a file
    void outputResults() {
        ofstream outFile("scores.dat");
        if (!outFile) {
            cerr << "Error: Could not open scores.dat for writing." << endl;
            return;
        }

        // Print header
        cout << left << setw(15) << "Name"
            << setw(8) << "Score1"
            << setw(8) << "Score2"
            << setw(8) << "Score3"
            << setw(8) << "Score4"
            << "Average" << endl;

        outFile << left << setw(15) << "Name"
            << setw(8) << "Score1"
            << setw(8) << "Score2"
            << setw(8) << "Score3"
            << setw(8) << "Score4"
            << "Average" << endl;

        // Print bowler data
        for (int i = 0; i < bowlerCount; i++) {
            cout << left << setw(15) << bowlers[i].name;
            outFile << left << setw(15) << bowlers[i].name;

            for (int j = 0; j < NUM_GAMES; j++) {
                cout << setw(8) << bowlers[i].scores[j];
                outFile << setw(8) << bowlers[i].scores[j];
            }

            cout << bowlers[i].average << endl;
            outFile << bowlers[i].average << endl;
        }

        outFile.close();
    }
};

// Main function
int main() {
    // Create an instance of BowlingData with the input file name
    BowlingData bowlingData("BowlingScores.txt");

    // Read data from the file
    if (!bowlingData.readData()) {
        cout << "Error reading file!" << endl;
        return 1;
    }

    // Calculate average scores
    bowlingData.calculateAverages();

    // Output the results
    bowlingData.outputResults();

    return 0;
}
