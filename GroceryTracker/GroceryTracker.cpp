//Hector Ofarrill
//8/10/2025
#include "GroceryTracker.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>

class GroceryTracker {
private:
    std::map<std::string, int> frequencyMap;

public:
    //Load file into frequencyMap
    void loadDataFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        std::string item;

        //Checks for file
        if (!inFile) {
            std::cerr << "Error: Could not open " << filename << "\n";
            return;
        }

        while (inFile >> item) {
            frequencyMap[item]++;
        }

        inFile.close();
    }

    // Backup data to file
    void writeBackupFile(const std::string& filename) {
        std::ofstream outFile(filename);

        if (!outFile) {
            std::cerr << "Error: Could not write to " << filename << "\n";
            return;
        }

        for (auto& pair : frequencyMap) {
            outFile << pair.first << " " << pair.second << "\n";
        }

        outFile.close();
    }

    // Get frequency of a single item
    int getFrequency(const std::string& item) {
        if (frequencyMap.find(item) != frequencyMap.end()) {
            return frequencyMap[item];
        }
        return 0;
    }

    // Print all items and their frequencies
    void printFrequencies() {
        for (auto& pair : frequencyMap) {
            std::cout << std::setw(12) << std::left << pair.first << pair.second << "\n";
        }
    }

    // Print histogram
    void printHistogram() {
        for (auto& pair : frequencyMap) {
            std::cout << std::setw(12) << std::left << pair.first;
            for (int i = 0; i < pair.second; ++i) {
                std::cout << "*";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    GroceryTracker tracker;
    tracker.loadDataFromFile("CS210_Project_Three_Input_File.txt");
    tracker.writeBackupFile("frequency.dat");

    int choice = 0;
    std::string itemName;

    while (true) {
        std::cout << "\n====== Corner Grocer Menu ======\n";
        std::cout << "1. Search for an item\n";
        std::cout << "2. Display all item frequencies\n";
        std::cout << "3. Display histogram\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            //Clear error flag
            std::cin.clear(); 
            //Discard bad input
            std::cin.ignore(1000, '\n'); 
            std::cout << "Invalid input. Please enter a number 1–4.\n";
            continue;
        }

        switch (choice) {
        case 1:
            std::cout << "Enter item name: ";
            std::cin >> itemName;
            std::cout << "Frequency: " << tracker.getFrequency(itemName) << "\n";
            break;
        case 2:
            tracker.printFrequencies();
            break;
        case 3:
            tracker.printHistogram();
            break;
        case 4:
            std::cout << "Exiting program...\n";
            return 0;
        default:
            std::cout << "Invalid choice. Please enter 1–4.\n";
        }
    }
}
