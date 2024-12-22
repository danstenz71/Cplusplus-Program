/*
 * Author: Daniel Stenzel
 * Date: December 15, 2024
 * Description: This program tracks and analyzes the frequency of items purchased at a grocery store.
 * It reads data from an input file, allows users to query the frequency of specific items,
 * displays all item frequencies, and prints a histogram of the frequencies. The program also
 * saves this data to a backup file for future reference. This solution is implemented with
 * a class and uses maps for efficient data storage and retrieval.
 */

#include <iostream>
#include <fstream>
#include <map>
#include <string>
using namespace std;

class GroceryTracker {
private:
    map<string, int> frequencyMap;
    string inputFileName;
    string backupFileName;

    // Helper to load data from input file
    void LoadData() {
        ifstream inputFile(inputFileName);
        if (!inputFile) {
            cerr << "Error: Unable to open input file." << endl;
            return;
        }
        string item;
        while (inputFile >> item) {
            ++frequencyMap[item]; // Increment frequency
        }
        inputFile.close();
    }

public:
    // Constructor
    GroceryTracker(string inputFile, string backupFile)
        : inputFileName(inputFile), backupFileName(backupFile) {
        LoadData(); // Populate frequency map
    }

    // Get frequency of a specific item
    int CountFrequency(const string& item) const {
        if (frequencyMap.find(item) != frequencyMap.end()) {
            return frequencyMap.at(item);
        }
        return 0; // Item not found
    }

    // Print all items and their frequencies
    void PrintFrequencyList() const {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Print histogram of items
    void PrintHistogram() const {
        for (const auto& pair : frequencyMap) {
            cout << pair.first << " " << string(pair.second, '*') << endl;
        }
    }

    // Save frequency data to a backup file
    void SaveToFile() const {
        ofstream outputFile(backupFileName);
        if (!outputFile) {
            cerr << "Error: Unable to open backup file for writing." << endl;
            return;
        }
        for (const auto& pair : frequencyMap) {
            outputFile << pair.first << " " << pair.second << endl;
        }
        outputFile.close();
    }
};

int main() {
    // Program initialization
    GroceryTracker tracker("CS210_Project_Three_Input_File.txt", "frequency.dat");
    int choice = 0;

    do {
        // Display menu
        cout << "\nMenu:" << endl;
        cout << "1. Search for an item's frequency" << endl;
        cout << "2. Display frequency list" << endl;
        cout << "3. Display histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Handle menu choices
        switch (choice) {
        case 1: {
            string item;
            cout << "Enter item name: ";
            cin >> item;
            int frequency = tracker.CountFrequency(item);
            if (frequency > 0) {
                cout << item << " appears " << frequency << " times." << endl;
            }
            else {
                cout << item << " does not appear in the data." << endl;
            }
            break;
        }
        case 2:
            cout << "\nFrequency List:" << endl;
            tracker.PrintFrequencyList();
            break;
        case 3:
            cout << "\nHistogram:" << endl;
            tracker.PrintHistogram();
            break;
        case 4:
            cout << "Exiting program. Data saved to frequency.dat." << endl;
            tracker.SaveToFile();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
