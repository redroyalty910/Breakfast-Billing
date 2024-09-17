//Tim Mills, "Breakfast Billing" Lab from June 10th, 2024

#include <iostream> // this library is a requirement in every C++ file that requires standard input and output operations
#include <fstream> // this library is used in this program to read "menu.txt"
#include <iomanip> // this library is used in this program to better organize my output
#include <string> // I include this library whenever I do anything with strings

using namespace std; //tells the compiler to use the standard namespace, which allows me to refer to the c++ standard library without needing the prefix "std::" behind every input/output operation

const int MENU_ITEMS = 8; //There are eight menu items in menu.txt, we will use this later in our array for the array size

struct menuItemType { //the intended structure that contains the variables required for this program
    string menuItem; //contains the name of an item
    double menuPrice; //keeps track of the price of an item
    int Count; //keeps track of the quantity of an item that is ordered
};

void getData(menuItemType menuList[]) { //the function that opens the file and the menu within it respectivley
    ifstream infile("menu.txt");
    if (!infile) { //simple method to determine if the file we are using is being opened properly
        cout << "Error opening file." << endl;
        exit(1);
    }

    for (int i = 0; i < MENU_ITEMS; i++) { //this for loop loops through and identifies all eight menu items
        infile >> ws; //the 'ws' command discards whitespace characters from the input file stream, it's a great shortcut for organizing our output for the customer
        getline(infile, menuList[i].menuItem, '$'); //this pre-defined function stores a string up to the '$' money sign, and stores it within menuItem like we want it to
        infile >> menuList[i].menuPrice; //we store the double variable within the structure
        menuList[i].Count = 0; //we set the counter equal to zero since nothing has been purchased yet, but we know that something will be
    }

    infile.close(); //closes the input file stream after all data has been read and gathered from "menu.txt"
}

void showMenu(const menuItemType menuList[]) { //this function displays the menu on the output screen for the user
    cout << "Welcome to Johnny's Restaurant" << endl;
    cout << "Here is the menu:" << endl;
    for (int i = 0; i < MENU_ITEMS; i++) { //this for loop accesses the "menuList[]" array once again and displays all the stored food items and their respective prices
        cout << i + 1 << ". " << menuList[i].menuItem << "$" << fixed << setprecision(2) << menuList[i].menuPrice << endl;
    }
    cout << "Please enter the item number and quantity ('0 + enter' to finish your order!):" << endl;
}

void printCheck(const menuItemType menuList[]) { //this function prints the check once the customer enters "0"
    double subtotal = 0.0; //I created a subtotal variable that displays on the check

    cout << "Your order:" << endl;
    for (int i = 0; i < MENU_ITEMS; i++) {
        if (menuList[i].Count > 0) {
            cout << menuList[i].menuItem << menuList[i].Count << " $" << fixed << setprecision(2) << menuList[i].menuPrice * menuList[i].Count << endl;
            subtotal += menuList[i].menuPrice * menuList[i].Count;
        }
    }

    double tax = subtotal * 0.05; //tax is also calculated within this function
    double total = subtotal + tax;

    cout << "Subtotal: $" << fixed << setprecision(2) << subtotal << endl;
    cout << "Tax: $" << fixed << setprecision(2) << tax << endl;
    cout << "Total: $" << fixed << setprecision(2) << total << endl;
}

int main() {
    menuItemType menuList[MENU_ITEMS]; //the structure is called, and we create the array menuList[MENU_ITEMS] as the prompt requested

    getData(menuList);
    showMenu(menuList); //we call the functions that acquire the data from the menu AND the function that displays the menu

    int itemNumber, quantity;
    while (true) { //This while loop controls the entire functionality of our program, and determines what and how much of the item that the customer is purchasing
        cin >> itemNumber;
        if (itemNumber == 0) break;
        cin >> quantity;
        if (itemNumber > 0 && itemNumber <= MENU_ITEMS && quantity > 0) {
            menuList[itemNumber - 1].Count += quantity;
        }
        else {
            cout << "Invalid input. Please try again." << endl;
        }
    }

    printCheck(menuList); //finally, once this while loop is false, we call the function that prints the check and the check is displayed within the output accordingly

    return 0;
}

/* Displayed below is my full console output:

Welcome to Johnny’s Restaurant            // The menu is displayed exactly as it was intended within the lab example
Here is the menu:
1. Plain Egg:               $1.45
2. Bacon and Egg:           $2.45
3. Muffin:                  $0.99
4. French Toast:            $1.99
5. Fruit Basket:            $2.49
6. Cereal:                  $0.69
7. Coffee:                  $0.50
8. Tea:                     $0.75
Please enter the item number and quantity ('0 + enter' to finish your order!):
2
3
4
6
0
Your order:                           //The check displays everything that it was supposed to, correctly and also neatly
Bacon and Egg:          3 $7.35
French Toast:           6 $11.94
Subtotal $19.29
Tax $0.96
Total $20.25






*/