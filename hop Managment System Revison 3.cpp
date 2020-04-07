#include <iostream>
#include <stdlib.h>
#include <fstream>

//************************************
// Class: File
//************************************

/*class File
{
public:
	void File_Write()
	{
		std::ofstream Write;
		Write.open("Data File.txt");
		Write << "Test";
		Write.close();
	};
};*/

//************************************
// Class: Item
//************************************

class Item
{
	//friend class Groceries; friend class Clothig; friend class Household;

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
	void Remove_Item(void); 
	void Edit_Item(void);  
	void Rerun(void);
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


void Item::New_Item(void)
{
	Item n;
	//Input for variables common to all objects created
    Unique_ID += 1; 
	std::cout << "Unique ID code created for this item is: " << Unique_ID << "\n";
	
	std::cout << "Enter Item Name: ";
	std::cin.ignore(); // Removig new line character so getline can work. Used throughout before strings are being entered 
	std::cin.getline(Item_Name, 40);

	std::cout << "Enter Item Price: ";
	std::cin >> Item_Price;

	std::ofstream Out_File;
	Out_File.open("Data File.txt", std::ios_base::app); // append insted of overwrite the file
	Out_File << "ID: " << Unique_ID << "\n" << "Item Name: " << Item_Name << "\n" << "Item Price: £" << Item_Price << "\n";
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

	std::ofstream Out_File;
	Out_File.open("Data File.txt", std::ios_base::app); 
	Out_File << "Use by date: " << Use_By_Day << "/" << Use_By_Month << "/" << Use_By_Year << "\n" << "-----------------\n";
	Out_File.close();
}

void Clothing::New_Item(void)
{
	system("cls");
	std::cout << "ADDING A NEW CLOTHING ITEM" << "\n\n";

	Item::New_Item();
	//Input for unique variables to Clothing objects
	std::cout << "Enter Clothig Type: ";
	std::cin.ignore();
	std::cin.getline(Clothing_Type, 30);

	std::cout << "Enter Clothig Size: ";
	std::cin.ignore();
	std::cin.getline(Clothing_Size, 4);

	std::ofstream Out_File;
	Out_File.open("Data File.txt", std::ios_base::app);
	Out_File << "Clothung type: " << Clothing_Type << "\n" << "Clothing size: " << Clothing_Size <<"\n" << "-----------------\n";
	Out_File.close();
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
	Out_File.open("Data File.txt", std::ios_base::app);
	Out_File << "Household type: " << Household_Type << "\n" << "Weight: " << Household_Weight << " kg" << "\n" << "-----------------\n";
	Out_File.close();

	Item::Return();
}

void Item::New_Type(void)
{

	std::cout << "ADDING NEW ITEM\n\n";
	std::cout << "Specify the item type:\n" << "Press '1' for Groceries\n" << "Press '2' for Clothing\n" << "Press '3' for Household\n";
	std::cin >> Item_Type;

	if (Item_Type == '1')
	{
		Groceries b;
		b.New_Item();
	}
	else if (Item_Type == '2')
	{
		Clothing c;
		c.New_Item();
	}
	else if (Item_Type == '3')
	{
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

void Rerun(void)
{
	std::cout << "ITEM HAS BEEN ADDED \n\n";
	std::cout << "1. Add item of a different Type\n" << "2. Exit\n";
	int Option;

	if (Option == 1)
	{
		Item a;
		a.New_Type();
	}
	else if (Option == 2)
	{
		Menu a;
		a.Select_Option;
	}
	else
	{
		std::cout << "Please select a correct option";
		Rerun();
	}
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
	//friend class Item;
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