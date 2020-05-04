// OOP_Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <regex>
#include <fstream>

using namespace std;

/**
* Base 'Inventory' Class
*
* Includes variables common to all derived classes, along with functions to add, edit and delete
* entries. Some functions are used to navigate the menu
*
* @author Jordan Smart <smart-j2@ulster.ac.uk>
* @license  <http://www.gnu.org/licenses/gpl-3.0.html>
* @copyright Jordan Smart 2020
*
* @todo Query about if Unique ID should be public? Kept public to be the same as other's code.
*/
class Inventory
{

private:
    string Item_Location;
    int Quantity;

public:
    Inventory();
    int Unique_ID=-1;
    void Print_Data();
    void Write_Data(ofstream &file);
    void Generate_Test_Data(string data[]);
    void Change_Unique_ID(int new_ID = -1);
    void Change_Item_Location(string New_Location = "");
    void Change_Item_Quantity(int New_Quantity = -1);
       
};

/**
* Inventory Constructor
*
* Reset to default
*
*/
Inventory::Inventory() {
    Unique_ID = -1;
    Item_Location = -1;
    Quantity = -1;
}

/**
* Print Data
*
* This function prints all the data the 
* object is holding to console.
*
* @todo Could make this dynamic to the contents of Inventory to futureproof code.
* @see
*
*/
void Inventory::Print_Data()
{

    cout << "UID: " << Unique_ID << "   ";
    cout << "Location: " << Item_Location << "   ";
    cout << "Quantity: " << Quantity << "   " << endl;

}

/**
* Write Data
*
* This function write data to file
*
* @todo Could make this dynamic to the contents of Inventory to futureproof code.
* @see
*
*/
void Inventory::Write_Data(ofstream &file)
{

    file << Unique_ID << "," << Item_Location << "," << Quantity << endl;

}

/**
* Generate Test Data
*
* This function allows the user to generate test data to use
* for debug purposes.
*
* @todo
* @see
*
*/
void Inventory::Generate_Test_Data(string data[])
{
    
    Unique_ID = stoi(data[0]);
    Item_Location = data[1];
    Quantity = stoi(data[2]);

}

/**
* Change Item Unique_ID
*
* This function allows the user to change the UID of an item
* by passing the function an int or optionally not passing the function
* anything ( or a -1 ), which will then trigger it to display a menu.
*
* @todo Add way to tell user that -1 is allowed
* @see
*
*/
void Inventory::Change_Unique_ID(int new_ID)
{
    if (new_ID == -1) {
        while (new_ID < 0) {
            cout << "Enter a new UID: ";
            cin >> new_ID;
            if (!(cin.fail())) {Unique_ID = new_ID;}
        }
    }
    else {Unique_ID = new_ID;}
}

/**
* Change Item Location Function
*
* This function allows the user to change the Location of an item
* by passing the function a string or optionally not passing the function
* anything, which will then trigger it to display a menu.
*
* @todo Add way to tell user that commas are not allowed
* @see 
*
*/
void Inventory::Change_Item_Location(string New_Location)
{
    string temp_location = ",";

    if (New_Location == "") {
        regex r(",");
        while (regex_match(temp_location, r)) {
            cout << "Enter a new Location: ";
            std::cin >> temp_location;
        }
        Item_Location = temp_location;
    }
    else {Item_Location = New_Location;}
}

/**
* Change Item Quantity Function
*
* This function allows the user to change the Quantity of an item
* by passing the function an int or optionally not passing the function
* anything ( or a -1 ), which will then trigger it to display a menu.
*
* @todo Find a way to allow for -1 to be entered too
* @see
*
*/
void Inventory::Change_Item_Quantity(int New_Quantity)
{
    if (New_Quantity == -1) {
        while (New_Quantity < 0) {
            cout << "Enter a new Quantity: ";
            cin >> New_Quantity;
            if (!(cin.fail())) {Quantity = New_Quantity;}
        }
    }
    else {Quantity = New_Quantity;}
}

/**
* Search stock for UID Function
*
* This function return the index of a value with the match UID
* if no match was found it returns -1
*
* @author Jordan Smart <smart-j2@ulster.ac.uk>
* @license <https://fsf.org>
* @copyright Jordan Smart 2020
*
* @todo Is quite unelagent. finished is not used. Could be cleaned up into a FOR loop.
* @see
*
*/
int search(Inventory items[], int n) {
    
    bool finished = 0;
    int i = 0;

    while (!finished) {

        if (i == (sizeof(*items) / sizeof(items))) {return(-1);}

        if (items[i].Unique_ID == n) {return(i);}
       
        else {i++;}
    }
}

/**
* Menu Function
*
* This function display the main menu for the program
* 
* @todo Add load from disk functionality. How create objects dynamically??? 
* @see
*
*/
void menu(Inventory items[], int Stock_Length) {

    cout << endl << "INVENTORY MANAGMENT SYSTEM" << endl;
    cout << "Please select an option:" << endl;
    cout << "1. VIEW STOCK" << endl;
    cout << "2. SEARCH STOCK" << endl;
    cout << "3. EDIT STOCK ITEM" << endl;
    cout << "4. COMMIT CHANGES TO DISK" << endl;
    cout << "5. LOAD FROM DISK" << endl;
    cout << "6. Exit" << endl << ">> ";

    int Option;
    int Option2;
    std::cin >> Option;

    switch (Option)
    {

    case 1:
        /**
        **  VIEW STOCK
        */

        for (int i = 0; i < Stock_Length; i++) { items[i].Print_Data(); }
        // RETURN TO MENU
        menu(items, Stock_Length);
        break;


    case 2:
        /**
        **  SEARCH STOCK
        */
        cout << "View item with UID: ";
        cin >> Option2;

        if ((search(items, Option2)) == -1) { cout << "Item not found."; menu(items, Stock_Length); }
        else { items[search(items, Option2)].Print_Data(); }
        // RETURN TO MENU
        menu(items, Stock_Length);
        break;

    case 3:
        /**
        **  EDIT STOCK ITEM
        */
        cout << "Edit item with UID: ";
        cin >> Option2;

        if ((search(items, Option2)) == -1) { cout << "Item not found."; menu(items, Stock_Length); }

        else {
            cout << "Please select an option:" << endl;
            cout << "1. UID" << endl;
            cout << "2. LOCATION" << endl;
            cout << "3. QUANTITY" << endl;
            cout << "4. DELETE" << endl;
            cin >> Option;
            switch (Option)
            {
            case 1:
                // CHANGE UID
                items[search(items, Option2)].Change_Unique_ID();
                break;

            case 2:
                // CHANGE LOCATION
                items[search(items, Option2)].Change_Item_Location();
                break;

            case 3:
                // CHANGE QUANTITY
                items[search(items, Option2)].Change_Item_Quantity();
                break;

            case 4: 
                {
                // DELETE

               for (int i = search(items, Option2); i < Stock_Length - 1; i++)
               {items[i] = items[i + 1];}
               Stock_Length--;
               break;
                }

            default:
                std::cout << "Incorrect Input. " << endl;
                break;
            }
            // RETURN TO MENU
            menu(items, Stock_Length);
            break;

        }

    case 4: {
          /**
          **  COMMIT CHANGES TO DISK
          */
          ofstream Out_File;
          Out_File.open("Inventory File.csv", std::ofstream::trunc);
          for (int i = 0; i < Stock_Length; i++)
          {items[i].Write_Data(Out_File);}
          Out_File.close();
          // RETURN TO MENU
          menu(items, Stock_Length);
          break;
        }

    case 5:
        /**
        **  LOAD FROM DISK - NOT YET WRITTEN, HOW DYNAMICALLY CREATE OBJECTS???
        */
        system("cls");
        menu(items, Stock_Length);
        break;

    case 6:
        /**
        **  QUIT
        */
        break;

    default:
        std::cout << "Incorrect Input. " << endl;
        // RETURN TO MENU
        menu(items, Stock_Length);
     
    }
}

int main() {

    // This is a set up for a test environment to test functions of class.

    string data_array[5][3] = { {"1","3A","5"},
                                {"2","4F","7"},
                                {"3","7C","1"},
                                {"4","2A","12"},
                                {"5","3B","20"}, };

    Inventory One;
    Inventory Two;
    Inventory Three;
    Inventory Four;
    Inventory Five;

    One.Generate_Test_Data(data_array[0]);
    Two.Generate_Test_Data(data_array[1]);
    Three.Generate_Test_Data(data_array[2]);
    Four.Generate_Test_Data(data_array[3]);
    Five.Generate_Test_Data(data_array[4]);

    Inventory Stock[] = {One, Two, Three, Four, Five};

   int Stock_Length = (sizeof(Stock) / sizeof(*Stock));

    menu(Stock,Stock_Length);
    
}



