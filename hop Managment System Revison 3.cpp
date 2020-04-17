#include <iostream>
#include <stdlib.h>
#include <fstream>

//************************************
// Class: File
//************************************

//************************************
// CLASS: MENU
//************************************
class Menu
{
public:
	void Welcome();
	void Select_Option();
};

//************************************
// Class: Item
//************************************

class Item
{
private:
	char Item_Type;
	
	char Item_Name[40];
	float Item_Price;
	float Supplier_Price;
	int Reorder_Level;
	
public:
    int Unique_ID=0;
	int* ID_pointer = &Unique_ID;
	virtual void New_Item(void);
	void New_Type(void);
	void Remove_Item(void); 
	void Edit_Item(void);  
	void Add_Another(void);
};


//************************************
// SubClass: Groceries
//************************************

class Groceries : public Item
{
private:
	int Use_By_Day;
	int Use_By_Month;
	int Use_By_Year;
	float Grocery_Weight;

public:
void New_Item(void);
};

//************************************
// SubClass: Clothing
//************************************

class Clothing : public Item
{
private:
	char Clothing_Colour[30];
	char Clothing_Size[4];

public:
void New_Item(void);
};

//************************************
// SubClass: Household
//************************************

class Household : public Item
{
private:
	char Household_Type[40];
	float Household_Weight;

public:
void New_Item(void);
};

//************************************
// FUNCTIONS
//************************************


void Item::New_Item()
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

	std::ofstream Out_File;
	Out_File.open("Data File.csv", std::ios_base::app); // append insted of overwrite the file
	Out_File << Unique_ID << "," << Item_Name << "," << Item_Price << ",";
	//Out_File << "ID: " << Unique_ID << "\n" << "Item Name: " << Item_Name << "\n" << "Item Price: £" << Item_Price << "\n";
	Out_File.close();
}

void Groceries::New_Item(void)
{
	system("cls");
	std::cout << "ADDING A NEW GROCERY ITEM" << "\n\n";

	Item::New_Item();
	//Input for unique variables to Grocories objects
	std::cout << "Enter day to use by:";
	std::cin >> Use_By_Day;

	std::cout << "Enter month to use by:";
	std::cin >> Use_By_Month;

	std::cout << "Enter year to use by:";
	std::cin >> Use_By_Year;

	std::cout << "Enter product weight in kilograms: ";
	std::cin.ignore();
	std::cin >> Grocery_Weight;

	std::ofstream Out_File;
	Out_File.open("Data File.csv", std::ios_base::app); 
	Out_File << Use_By_Day << "/" << Use_By_Month << "/" << Use_By_Year << ",,,," << Grocery_Weight << "\n";
	//Out_File << "Use by date: " << Use_By_Day << "/" << Use_By_Month << "/" << Use_By_Year << "\n" << "-----------------\n";
	Out_File.close();

	Item::Add_Another();
}

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
	//Out_File << "Clothung type: " << Clothing_Type << "\n" << "Clothing size: " << Clothing_Size <<"\n" << "-----------------\n";
	Out_File.close();

	Item::Add_Another();
}

void Household::New_Item(void)
{
	system("cls");
	std::cout << "ADDING A NEW HOUSEHOLD ITEM" << "\n\n";

	Item::New_Item();
	//Input for unique variables to Household objects
	std::cout << "Enter household product type: ";
	std::cin.ignore();
	std::cin.getline(Household_Type, 40);

	std::cout << "Enter product weight in kilograms: ";
	std::cin.ignore();
	std::cin >> Household_Weight;

	std::ofstream Out_File;
	Out_File.open("Data File.csv", std::ios_base::app);
	Out_File << ",,," << Household_Type << "," << Household_Weight << "\n";
	//Out_File << "Household type: " << Household_Type << "\n" << "Weight: " << Household_Weight << " kg" << "\n" << "-----------------\n";
	Out_File.close();

	Item::Add_Another();
}

void Item::New_Type(void)
{

	std::cout << "ADDING NEW ITEM\n\n";
	std::cout << "Specify the item type:\n" << "1. Groceries\n" << "2. Clothing\n" << "3. Household\n";
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

void Item::Remove_Item(void)
{

}

void Item::Edit_Item(void)
{

}

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

	//std::cout << "option is: " << Option; //testing 
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
	case 4:
		//return(0);
	default:
		std::cout << "Incorrect Input. ";
		Menu::Select_Option();
	}
	//std::cout << "option is: " << Option; //testing	
}

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

//************************************
// MAIN
//************************************

int main(void)
{
	system("cls");

	Menu a;
	
	a.Select_Option();

	return(0);
}
