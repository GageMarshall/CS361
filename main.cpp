#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>    // For file reading/writing

using namespace std;

// Simple struct to hold card data
struct Card {
    string name;      // Pokémon name
    string rarity;    // Card rarity
    string set;       // Set name
    int quantity;     // Number of copies
};

// Load cards from a text file into the collection
void loadCollection(vector<Card>& collection) {
    ifstream infile("cards.txt");
    if (!infile) return;  // No file yet, start empty

    Card c;
    while (infile >> c.name >> c.rarity >> c.set >> c.quantity) {
        collection.push_back(c);
    }
    infile.close();
}

// Save all cards back to the text file
void saveCollection(const vector<Card>& collection) {
    ofstream outfile("cards.txt");
    for (const Card& c : collection) {
        outfile << c.name << " "
                << c.rarity << " "
                << c.set << " "
                << c.quantity << "\n";
    }
    outfile.close();
}

// Show the home screen; return true to go to collection, false to quit
bool showHomeScreen(vector<Card>& collection) {
    int choice;
    while (true) {
        cout << endl << "=== Pokemon Collection App ===" << endl << endl;
        cout << "Welcome to The Pokemon Collection App!" << endl;
        cout << "Here you can add/remove pokemon cards from you collection," << endl;
        cout << "as well as view your collection and quantity of each card." << endl;
        cout << "Cards must be entered individually so it is recommended for" << endl;
        cout << "this program to be used only for cards in your personal collection." << endl;
        cout << endl << "1) Go to Collection" << endl;
        cout << "2) Quick Info" << endl;
        cout << "3) Quit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (cin.fail()) {  // Input not an integer
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number.\n";
            continue;
        }
        if (choice == 1) {
            return true;
        }
        if (choice == 2) {
            // Quick Info: show counts
            int unique = collection.size();
            int totalCards = 0;
            for (const Card& c : collection) {
                totalCards += c.quantity;
            }
            cout << "\nYou have " << unique
                 << " Unique Pokemon and " << totalCards
                 << " total cards in your collection.\n";
            continue;  // Back to home menu
        }
        if (choice == 3) {
            return false;
        }
        cout << "Invalid option.\n";
    }
}

// Collection menu with help/view/add/remove/back options
void collectionMenu(vector<Card>& collection) {
    while (true) {
        cout << "\n-- Collection Menu --" << endl;
        cout << "1) Help" << endl;
        cout << "2) View collection" << endl;
        cout << "3) Add card" << endl;
        cout << "4) Remove card" << endl;
        cout << "5) Back to Home" << endl;
        cout << "Enter choice: ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number.\n";
            continue;
        }
        
        if (choice == 1){
            cout << endl << "-= Collection Help =-" << endl;
            cout << "- To view the cards added to the collection, press 2 and hit enter." << endl;
            cout << "- To add a card, press 3 and hit enter. You will then be asked to" << endl;
            cout << "enter the required card information for the database one at a time." << endl;
            cout << "- To remove a card, poress 4 and hit enter. You will then be asked" << endl;
            cout << "for the id number in the collection and to confirm the removal." << endl;
        }

        if (choice == 2) {
            // VIEW: print each card on its own line
            cout << "\nYour Collection:" << endl;
            for (size_t i = 0; i < collection.size(); i++) {
                Card& c = collection[i];
                cout << i+1 << ") "
                     << c.name << " | "
                     << c.rarity << " | "
                     << c.set << " | Qty: "
                     << c.quantity << endl;
            }
        }
        else if (choice == 3) {
            // ADD: prompt four separate values
            Card c;
            cout << "Enter Name: ";
            cin >> c.name;
            cout << "Enter Rarity: ";
            cin >> c.rarity;
            cout << "Enter Set: ";
            cin >> c.set;
            cout << "Enter Quantity: ";
            cin >> c.quantity;
            collection.push_back(c);
            cout << "Added " << c.name << "!\n";
        }
        else if (choice == 4) {
            // REMOVE: by index with confirmation
            cout << "Enter the number of the card to remove: ";
            int idx;
            cin >> idx;
            if (!cin.fail() && idx >= 1 && idx <= (int)collection.size()) {
                // Display selected card details for confirmation
                Card& toRemove = collection[idx-1];
                cout << "\nYou selected to remove:" << endl;
                cout << "Name: " << toRemove.name << " | "
                     << "Rarity: " << toRemove.rarity << " | "
                     << "Set: " << toRemove.set << " | "
                     << "Quantity: " << toRemove.quantity << endl;
                cout << "Are you sure you want to remove this card? (y/n): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    collection.erase(collection.begin() + idx - 1);
                    cout << "Removed " << toRemove.name << "!\n";
                } else {
                    cout << "Removal canceled.\n";
                }
            } else {
                cout << "Invalid index.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else if (choice == 5) {
            // BACK: return to home screen
            return;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }
}

int main() {
    vector<Card> collection;        // vector for the card collection
    loadCollection(collection);     // Load existing card data

    // Main loop until user quits
    while (showHomeScreen(collection)) {
        collectionMenu(collection);
    }
    saveCollection(collection);     // Save on exit
    cout << "Collection saved. Goodbye!\n";
    return 0;
}