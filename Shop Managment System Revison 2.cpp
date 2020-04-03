#include <iostream>
#include <stdlib.h>

//************************************
// Class: Item
//************************************

class Item
{
	friend class Groceries; friend class Clothig; friend class Household;

private:
	char Item_Type;
	int Unique_ID = 0;
	char Item_Name[40];
	float Item_Price;
	float Supplier_Price;
	int Reorder_Level;

	
		
public:
	virtual void New_Item(void);
	void New_Type(void);
	void Remove_Item(void); //move?
	void Edit_Item(void);   //move?
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
	float Weight;

public:
void New_Item(void);
};

//************************************
// SubClass: Clothing
//************************************

class Clothing : public Item
{
private:
	char Clothing_Type[30];
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

void Item::New_Type(void)
{
	std::cout << "ADDING NEW ITEM" << "\n\n";
	std::cout << "Specify the item type:" << "\n" << "Press '1' for Groceries" << "\n" << "Press '2' for Clothing" << "\n" << "Press '3' for Household" << "\n";
	std::cin >> Item_Type;
	//std::cout << "Item_Type is: " << Item_Type; //test

	Groceries b;
	Clothing c;
	Household d; 

	switch (Item_Type)
	{
	case 1: // Groucories
		b.New_Item();
		break;
	case 2: // Clothing
		c.New_Item();
		break;
	case 3: // Household
		d.New_Item();
		break;
	default:
		system("cls");
		std::cout << "Incorrect Input" << "\n";
		Item::New_Type();
	}
}

void Item::New_Item(void)
{
	//Input for variables common to all objects created
	Unique_ID += 1;

	std::cout << "Enter Item Name: ";
	std::cin.getline(Item_Name, 40);

	std::cout << "Enter Item Price: ";
	std::cin >> Item_Price;
}

void Groceries::New_Item(void)
{
	Groceries New_G;

	Item::New_Item();
	//Input for unique variables to Grocories objects
	std::cout << "Enter day to use by:";
	std::cin >> Use_By_Day;

	std::cout << "Enter month to use by:";
	std::cin >> Use_By_Month;

	std::cout << "Enter year to use by:";
	std::cin >> Use_By_Year;
}

void Clothing::New_Item(void)
{
	Clothing New_C;

	Item::New_Item();
	//Input for unique variables to Clothing objects
	std::cout << "Enter Clothig Type: ";
	std::cin.getline(Clothing_Type, 30);

	std::cout << "Enter Clothig Size: ";
	std::cin.getline(Clothing_Size, 4);
}

void Household::New_Item(void)
{
	Household New_H; 

	Item::New_Item();
	//Input for unique variables to Household objects
	std::cout << "Enter household product type: ";
	std::cin.getline(Household_Type, 40);

	std::cout << "Enter product weight in kilograms: ";
	std::cin >> Household_Weight;
}

void Item::Remove_Item(void)
{

}

void Item::Edit_Item(void)
{

}

//************************************
// USER MENU
//************************************
class Menu
{
	friend class Item;
private:
	

public:
	int Option;
	void Welcome();
	void Select_Option();
};

void Menu::Welcome()
{
	std::cout << "SHOP MANAGMENT SYSTEM" << "\n\n";
}

void Menu::Select_Option()
{
	
		std::cout << "Plese select an option:" << "\n";
		std::cout << "1. ADD NEW ITEM" << "\n";
		std::cout << "2. REMOVE ITEM" << "\n";
		std::cout << "3. EDIT ITEM:" << "\n";

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
		default:
			std::cout << "Incorrect Input. ";
			Menu::Select_Option();
		}
		//std::cout << "option is: " << Option; //testing
}

//************************************
// MAIN
//************************************

int main(void)
{
	system("cls");

	Menu a;
	
	a.Welcome();
	a.Select_Option();

	return(0);
}