#include <iostream>
#include <stdlib.h>
#include <fstream>
/**
* Shop Managment System
*
* Simple shop managment systmes that allows adding, editing and removing items from a .csv database file as well as generate simple reports
*
* @author Daniel Kraska <kraska-d1@ulster.ac>
* @license <https://fsf.org>
* @copyright Daniel Kraska 2020
*
*/

class Menu
{
public:
	void Select_Option();
};

/**
* Base 'Itme' Class
*
* Includes variables common to all derived classes, along with functions to add, edit and delete
* entries. Some functions are used to navigate the menu
*
* @author Daniel Kraska <kraska-d1@ulster.ac>
* @license <https://fsf.org>
* @copyright Daniel Kraska 2020
*
*/
class Item
{
private:
	char Item_Type;

	char Item_Name[40];
	float Item_Price;
	float Supplier_Price;
	int Reorder_Level;

public:
	static int Unique_ID;                // static variablre remains in memory throughout the life of the program 
	int* ID_pointer = &Unique_ID;
	virtual void New_Item(void); 
	void New_Type(void);
	void Remove_Item(void);
	void Edit_Item(void);
	void Edit_Item(std::ofstream& File);
	void Edit_Type(std::ofstream& File, const std::string& Current_Line);
	void Add_Another(void);
};

int Item::Unique_ID = 0;                 // Initialising a static variable has to be done 
                                         // outside of the class definition (solved Unique_ID not updating)
/**
* Derived Class 'Grouceries'
*
* Includes variables unique to this clas
*
* @author Daniel Kraska <kraska-d1@ulster.ac>
* @license <https://fsf.org>
* @copyright Daniel Kraska 2020
*
*/
class Groceries : public Item
{
private:
	int Use_By_Day;
	int Use_By_Month;
	int Use_By_Year;
	float Grocery_Weight;

public:
	void New_Item(void);
	void Edit_Item(std::ofstream& File, const std::string& Current_Line);
};

/**
* Derived Class 'Clothing'
*
* Same as above
*
* @author Daniel Kraska <kraska-d1@ulster.ac>
* @license <https://fsf.org>
* @copyright Daniel Kraska 2020
*
*/
class Clothing : public Item
{
private:
	char Clothing_Colour[30];
	char Clothing_Size[4];

public:
	void New_Item(void);
	void Edit_Item(std::ofstream& File, const std::string& Current_Line);
};

/**
* Derived Class 'Household'
*
* Same as above
*
* @author Daniel Kraska <kraska-d1@ulster.ac>
* @license <https://fsf.org>
* @copyright Daniel Kraska 2020
*
*/
class Household : public Item
{
private:
	char Household_Type[40];
	float Household_Weight;

public:
	void New_Item(void);
	void Edit_Item(std::ofstream& File, const std::string& Current_Line);
};

/**
* 'New Item' function for adding new items
*
* Once the type of the item is selected, this function is called first from inside each derived version of this function   
* to collect inforamtion common to all items types and writes them into the .csv database.
* @todo figure out a way for Unique_ID topick up the last geerated number 
* and add one to it, insed of starting from '1'
* @see New_Type, Groceries::New_Item, Clothing::New_Item and Household::New_Item
*/
void Item::New_Item()
{
	Item n;
	++(*ID_pointer);
	std::cout << "Unique ID code created for this item is: " << Unique_ID << "\n";

	std::cout << "Enter Item Name: ";
	std::cin.ignore(); // Removig new line character so getline can work. Used throughout before strings are being entered 
	std::cin.getline(Item_Name, 40);

	std::cout << "Enter Item Price: ";
	std::cin >> Item_Price;

	std::ofstream Out_File;
	Out_File.open("Data File.csv", std::ios_base::app); // append insted of overwrite the file
	Out_File << Unique_ID << "," << Item_Name << "," << Item_Price << ",";
	Out_File.close();
}

/**
* Edit Item function
*
* Once the user selects the 'Edit Typpe', this function is an expansion of the 'Item::New_Item' function above. It is called from inside each derived 
* 'Edit Item' function to collect inforamtion common to all items types and writes them to the output stream (temporary .csv file).
* @param Out_File output stream name for writing to the temporary .csv file
* @see Edit_Type, Groceries::Edit_Item, Clothing::Edit_Item and Household::Edit_Ite
*/
void Item::Edit_Item(std::ofstream& Out_File)
{
	Item n;
	//Input for variables common to all objects created
	++(*ID_pointer);
	std::cout << "Unique ID code created for this item is: " << Unique_ID << "\n";

	std::cout << "Enter Item Name: ";
	std::cin.ignore(); // Removig new line character so getline can work. Used throughout before strings are being entered 
	std::cin.getline(Item_Name, 40);

	std::cout << "Enter Item Price: ";
	std::cin >> Item_Price;

	Out_File << Unique_ID << "," << Item_Name << "," << Item_Price << ",";
}

/**
* Derived 'New Item' function for grocery items. 
*
* This function calls the base 'New Item' function first, then collects information 
* specifit to grocery items and writes them into the .csv database.
* 
* @see Item::Add_Another
* @todo Add code to chech if the input format for the date is correct
*/
void Groceries::New_Item(void)
{
	system("cls");
	std::cout << "ADDING A NEW GROCERY ITEM" << "\n\n";

	Item::New_Item();
	
	std::cout << "Enter day to use by: ";
	std::cin >> Use_By_Day;

	std::cout << "Enter month to use by: ";
	std::cin >> Use_By_Month;

	std::cout << "Enter year to use by: ";
	std::cin >> Use_By_Year;

	std::cout << "Enter product weight in kilograms: ";
	std::cin.ignore();
	std::cin >> Grocery_Weight;

	std::ofstream Out_File;
	Out_File.open("Data File.csv", std::ios_base::app);
	Out_File << Use_By_Day << "/" << Use_By_Month << "/" << Use_By_Year << ",,,," << Grocery_Weight << "\n";
	Out_File.close();

	Item::Add_Another();
}

/**
* Edit Item function for grocery items
*
* This function in an expansion of the 'Groceries::New_Item' function above. The passed parameter 'Row_Buffer' displays information about the
* item curently being edited. It calls the base 'Item::Edit_Item' function, then collects information 
* specifit to grocery items and writes them to the output stream (temporary .csv file).
* @param Out_File output stream name for writing to the temporary .csv file
* @param Row_Buffer string buffer containing data of the item being edited. const as it does not change and it is not modifiable
* @see Groceries::New_Item and Edit_Item
*/
void Groceries::Edit_Item(std::ofstream& Out_File, const std::string& Row_Buffer)
{
	system("cls");
	std::cout << "EDITING A GROCERY ITEM" << "\n\n";
	std::cout << Row_Buffer << "\n\n";

	Item::Edit_Item(Out_File);

	std::cout << "Enter day to use by:";
	std::cin >> Use_By_Day;

	std::cout << "Enter month to use by:";
	std::cin >> Use_By_Month;

	std::cout << "Enter year to use by:";
	std::cin >> Use_By_Year;

	std::cout << "Enter product weight in kilograms: ";
	std::cin.ignore();
	std::cin >> Grocery_Weight;

	Out_File << Use_By_Day << "/" << Use_By_Month << "/" << Use_By_Year << ",,,," << Grocery_Weight << "\n";
}

/**
* Derived 'New Item' function for clothing items.
*
* This function calls the base 'Item' function first, then collects information
* specifit to Clothing items and writes them into the .csv database.
*
* @see Item::Add_Another
* @todo Add code to select a size from a list to minimise input errors
*/
void Clothing::New_Item(void)
{
	system("cls");
	std::cout << "ADDING A NEW CLOTHING ITEM" << "\n\n";

	Item::New_Item();
	//Input for unique variables to Clothing objects
	std::cout << "Enter Clothig Colour: ";
	std::cin.ignore();
	std::cin.getline(Clothing_Colour, 30);

	std::cout << "Enter Clothig Size: ";
	std::cin.ignore();
	std::cin.getline(Clothing_Size, 4);

	std::ofstream Out_File;
	Out_File.open("Data File.csv", std::ios_base::app);
	Out_File << "," << Clothing_Colour << "," << Clothing_Size << "\n";
	Out_File.close();

	Item::Add_Another();
}

/**
* Edit Item function for clothing items
*
* This function in an expansion of the 'Clothing::New_Item' function above. The passed parameter 'Row_Buffer' displays information about the
* item curently being edited. It calls the base 'Item::Edit_Item' function, then collects information
* specifit to clothing items and writes them to the output stream (temporary .csv file).
* @param Out_File output stream name for writing to the temporary .csv file
* @param Row_Buffer string buffer containing data of the item being edited. const as it does not change and it is not modifiable
* @see Clothing::New_Item and Item::Edit_Item
*/
void Clothing::Edit_Item(std::ofstream& Out_File, const std::string& Row_Buffer)
{
	system("cls");
	std::cout << "EDITING A CLOTHING ITEM" << "\n\n";
	std::cout << Row_Buffer << "\n\n";

	Item::Edit_Item(Out_File);
	//Input for unique variables to Clothing objects
	std::cout << "Enter Clothig Colour: ";
	std::cin.ignore();
	std::cin.getline(Clothing_Colour, 30);

	std::cout << "Enter Clothig Size: ";
	std::cin.ignore();
	std::cin.getline(Clothing_Size, 4);

	Out_File << "," << Clothing_Colour << "," << Clothing_Size << "\n";
}

/**
* Derived 'New Item' function for household items.
*
* This function calls the base 'New Item' function first, then collects information
* specifit to Household items and writes them into the .csv database.
*
* @see Item::Add_Another
* @todo Add code to select a product type from a list to minimise input errors
*/
void Household::New_Item(void)
{
	system("cls");
	std::cout << "ADDING A NEW HOUSEHOLD ITEM" << "\n\n";

	Item::New_Item();

	std::cout << "Enter household product type: ";
	std::cin.ignore();
	std::cin.getline(Household_Type, 40);

	std::cout << "Enter product weight in kilograms: ";
	std::cin.ignore();
	std::cin >> Household_Weight;

	std::ofstream Out_File;
	Out_File.open("Data File.csv", std::ios_base::app);
	Out_File << ",,," << Household_Type << "," << Household_Weight << "\n";
	Out_File.close();

	Item::Add_Another();
}

/**
* Edit Item function for household items
*
* This function in an expansion of the 'Household::New_Item' function above. The passed parameter 'Row_Buffer' displays information about the
* item curently being edited. It calls the base 'Item::Edit_Item' function, then collects information
* specifit to household items and writes them to the output stream (temporary .csv file).
* @param Out_File output stream name for writing to the temporary .csv file
* @param Row_Buffer string buffer containing data of the item being edited. const as it does not change and it is not modifiable
* @see Clothing::New_Item and Item::Edit_Item
*/
void Household::Edit_Item(std::ofstream& Out_File, const std::string& Row_Buffer)
{
	system("cls");
	std::cout << "EDITING A HOUSEHOLD ITEM" << "\n\n";
	std::cout << Row_Buffer << "\n\n";

	Item::Edit_Item(Out_File);

	std::cout << "Enter household product type: ";
	std::cin.ignore();
	std::cin.getline(Household_Type, 40);

	std::cout << "Enter product weight in kilograms: ";
	std::cin.ignore();
	std::cin >> Household_Weight;

	Out_File << ",,," << Household_Type << "," << Household_Weight << "\n";
}

/**
* 'New Type' function for selecting the new item type
*
* This function is used to select the type of the item that is about to be added and runs the corresponding 
* version of the 'New_Item' function based on user input. Incorrect input gives an error and re-runs the function.
* As requested by other team members, it writes the type of the item (e.g. Clothing) in the firs column of the .csv file
* to simplyfy the process of generating reports.
* 
* @todo integrate this function to functions listed in 'see' below to simplify the code
* @see Groceries::New_Item, Clothing::New_Item and Household::New_Item
*/
void Item::New_Type(void)
{
	std::cout << "ADDING NEW ITEM\n\n";
	std::cout << "Specify the item type:\n" 
		<< "1. Groceries\n" << "2. Clothing\n" << "3. Household\n";
	std::cin >> Item_Type;

	if (Item_Type == '1')
	{
		std::ofstream Out_File;
		Out_File.open("Data File.csv", std::ios_base::app);
		Out_File << "Grocery,";
		Out_File.close();
		Groceries b;
		b.New_Item();
	}
	else if (Item_Type == '2')
	{
		std::ofstream Out_File;
		Out_File.open("Data File.csv", std::ios_base::app);
		Out_File << "Clothing,";
		Out_File.close();
		Clothing c;
		c.New_Item();
	}
	else if (Item_Type == '3')
	{
		std::ofstream Out_File;
		Out_File.open("Data File.csv", std::ios_base::app);
		Out_File << "Household,";
		Out_File.close();
		Household d;
		d.New_Item();
	}
	else
	{
		system("cls");
		std::cout << "Incorrect Input\n";
		Item::New_Type();
	}
}

/**
* Remove Item function used to delete entries from the .csv file
*
* This function creates two strings to store characters, opens the database file for reading and creates a temporary file for writing.
* It runs in a loop and reads the original file line by line and essentially copies each row of data to the temporary file.
* As this happens, it compereach the row that it is currently reading agains the 'Row_To_Delete' specified by the user.
* When the two values match, i.e. 'Row_To_Delete' eaquals the 'Unique_ID' of the product the re-writing procedure is omitted. 
* Once each row of the .csv has been read, and all the information was re-written, the orginal file is removed and the temporary fine
* is renamed to the orginal file name.
*
* @todo Modify the function so it deletes the item based on the 'Unique_ID' assigned to the item insted of the row number that the
* item is placed in.
*/
void Item::Remove_Item()
{
	std::string DB_Name = "Data File.csv";
	std::string Tmp_Name = "tmp.csv";
	std::ifstream In_File;
	std::ofstream Out_File;

	In_File.open(DB_Name, std::ios::in);
	Out_File.open(Tmp_Name, std::ios::out);

	int Row_To_Delete;
	std::cout << "Enter the ID of the product to be deleted: ";
	std::cin >> Row_To_Delete;

	bool Found = false;
	int Current_Line = 1;

	while (!In_File.eof())                                  // If NOT at the end of the file, continue...
	{
		char Line[8 * 1024];                                // buffer for reading each row from the .csv file with additional space for other tememebers data
		In_File.getline(Line, 8 * 1024);                    // Read the row with no more than (8 * 1024) characters into Row_Buffer stopping at "\n"
		//std::cout << Line << "sizeof1: " << sizeof(Line) << "strlen1: " << strlen(Line); system("pause"); //test

		if (Current_Line++ == Row_To_Delete && !Found) 
		{
			Found = true;                                   // change the bool var to true for error detection later
			//std::cout << Line << "sizeof2: " << sizeof(Line) << "strlen2: " << strlen(Line); system("pause"); // test
			continue;                                       // skip the rest of the while loop, avoid re-writting selectd row
		}
		//std::cout << Line << "sizeof3: " << sizeof(Line) << "strlen3: " << strlen(Line); system("pause"); //test
		if (strlen(Line) > 0)                               // if the buffer is not empty
			Out_File << Line << "\n";                       // write the contents of the buffere to the tmp.csv
	}

	system("cls");
	if (Found)                                              // if bool var was chaneged to true...
		std::cout << "Item has been removed\n";
	else
		std::cout << "Item not found\n";

	In_File.close();
	Out_File.close();

	remove("Data File.csv");
	rename("tmp.csv", "Data File.csv");

	Menu b;
	b.Select_Option();                                       // returns to main menu
}

/**
* Edit Type function is used to select the type of the replaceemnt item 
*
* This function in an expansion of the 'Edit_Type' function. The passed parameter 'Row_Buffer' displays information about the 
* item curently being edited. It is used to select the type of the item that is about to be edited, writes item type in the first column and runs the corresponding 
* version of the 'Edit_Item' function based on user input. Incorrect input gives an error and re-runs the function.
*
* @param Out_File output stream name for writing to the temporary .csv file 
* @param Row_Buffer string buffer containing data of the item being edited. const as it does not change and it is not modifiable
* @see New_Type and Edit_Item 
*/
void Item::Edit_Type(std::ofstream& Out_File, const std::string& Row_Buffer)
{
	std::cout << "EDITING ITEM: \n\n";
	std::cout << Row_Buffer << "\n\n";
	std::cout << "Specify new item type:\n" 
		<< "1. Groceries\n" << "2. Clothing\n" << "3. Household\n";
	std::cin >> Item_Type;

	if (Item_Type == '1')
	{
		std::ofstream Out_File;
		Out_File << "Grocery,";
		Groceries b;
		b.Edit_Item(Out_File, Row_Buffer);
	}
	else if (Item_Type == '2')
	{
		std::ofstream Out_File;
		Out_File << "Clothing,";
		Clothing c;
		c.Edit_Item(Out_File, Row_Buffer);
	}
	else if (Item_Type == '3')
	{
		std::ofstream Out_File;
		Out_File << "Household,";
		Household d;
		d.Edit_Item(Out_File, Row_Buffer);
	}
	else
	{
		system("cls");
		std::cout << "Incorrect Input\n";
		Item::Edit_Type(Out_File, Row_Buffer);
	}
}

/**
* 'Edit Item' function used to edit an item on the .csv file
*
* This function creates two strings to store characters, opens the database file for reading and creates a temporary file for writing. 
* It runs in a loop and reads the original file line by line and essentially copies each row of data to the temporary file. 
* As this happens, it compereach the row that it is currently reading agains the 'Row_To_Edit' specified by the user.
* When the two values match, i.e. 'Row_To_Edit' eaquals the 'Unique_ID' of the product it runs the 'Edit_Type' function and passes two parameters.
* Once each row of the .csv has been read, and all the information was re-written, the orginal file is removed and the temporary fine 
* is renamed to the orginal file name. 
*
* @see Edit_Type
* @todo Modify the function so it edits the item based on the 'Unique_ID' assigned to the item insted of the row number that the 
* item is placed in. 
*/
void Item::Edit_Item()
{
	std::string DB_Name = "Data File.csv";
	std::string Tmp_Name = "tmp.csv";
	std::ifstream In_File;
	std::ofstream Out_File;

	In_File.open(DB_Name, std::ios::in);
	Out_File.open(Tmp_Name, std::ios::out);

	int Row_To_Edit;
	std::cout << "Enter the ID number of the product to be edited: ";
	std::cin >> Row_To_Edit;

	bool Found = false;
	int Current_Line = 1;

	while (!In_File.eof())                                  // If NOT at the end of the file, continue...
	{
		char Row_Buffer[8 * 1024];                          // buffer for reading each row from the .csv file with additional space for other tememebers data
		In_File.getline(Row_Buffer, 8 * 1024);              // Read the row with no more than (8 * 1024) characters into Row_Buffer stopping at "\n"
		//std::cout << Line << "sizeof1: " << sizeof(Line) << "strlen1: " << strlen(Line); system("pause"); //test
		if (Current_Line++ == Row_To_Edit && !Found)
		{
			Found = true;                                   // change the bool var to true for error detection later
			//std::cout << Line << "sizeof2: " << sizeof(Line) << "strlen2: " << strlen(Line); system("pause"); // test
			Edit_Type(Out_File, std::string(Row_Buffer));
			continue;                                       // skip the rest of the while loop
		}
    //std::cout << Line << "sizeof3: " << sizeof(Line) << "strlen3: " << strlen(Line); system("pause"); //test
		if (strlen(Row_Buffer) > 0)                         // if the buffer is not empty
			Out_File << Row_Buffer << "\n";                 // write the contents of the buffere to the tmp.csv
	}

	system("cls");
	if (Found)                                              // if bool var was chaneged to true...
		std::cout << "Item has been edited\n";
	else
		std::cout << "Item not found\n";

	In_File.close();
	Out_File.close();

	remove("Data File.csv");
	rename("tmp.csv", "Data File.csv");

	Menu b;
	b.Select_Option();                                        // returns to main menu
}

/**
* 'Select Option' function used as a simple menu
*
* This function is used to select the type of the item that is about to be added and runs the corresponding
* version of the 'New_Item' function based on user input.
* As requested by other team members, it writes the type of the item (e.g. Clothing) in the firs column of the .csv file
* to simplyfy the process of generating reports.
*
* @todo add the 'EXIT' fuction which will close the comand window
* @see New_Type, Remove_Item and Edit_Item
*/
void Menu::Select_Option()
{
	std::cout << "SHOP MANAGMENT SYSTEM" << "\n\n";
	std::cout << "Plese select an option:" << "\n";
	std::cout << "1. ADD NEW ITEM" << "\n";
	std::cout << "2. REMOVE ITEM" << "\n";
	std::cout << "3. EDIT ITEM" << "\n";
	std::cout << "4. Exit" << "\n";

	int Option;
	std::cin >> Option;
	system("cls");
	Item a;

	switch (Option)
	{
	case 1:
		a.New_Type();
		break;
	case 2:
		a.Remove_Item();
		break;
	case 3:
		a.Edit_Item();
		break;
	default:
		std::cout << "Incorrect Input. ";
		Menu::Select_Option();
	}
}

/**
* 'Add Another' function
*
* This function is runned after all the information about an item was collected and allows the user
* to add another item or return to the main menu
*
* @see New_Type and Select_Option
*/
void Item::Add_Another(void)
{
	system("cls");
	std::cout << "Item Added to the file.\n\n" << "1. Add another item\n" << "2. Back to main menu\n";
	int Option;
	std::cin >> Option;

	if (Option == 1)
	{
		system("cls");
		Item a;
		a.New_Type();
	}
	else if (Option == 2)
	{
		system("cls");
		Menu b;
		b.Select_Option();
	}
	else
	{
		Item::Add_Another();
		std::cout << "Incorrect Input\n";
	}
}

int main(void)
{
	system("cls");

	Menu a;

	a.Select_Option();

	return(0);
}