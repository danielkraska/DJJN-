/**
*  reports.cpp file
*
* Includes functions to read/write product detail reports from details stored in
* .csv file.
*
* @author James Goodall <goodall-j6@ulster.ac.uk>
*
* @license <http://www.gnu.org/licenses/gpl-3.0.html>
*
* @copyright James Goodall 2020
*
*/

#include "reports.hpp"  //Include reports header file

/**
* "Input" Function used as a simple sub menu
* This function enables the user to select the type of the Report they would
* like to view such as grocery products, clothing products or houshold products..
*
* @todo add the 'RETURN' function to main menu rather than exiting the program.
*
* @see Grocery_Report, Clothing_Report, Household_Report
*/
void Report::Input()
{
  // Request user input
  std::cout << "WHAT REPORT WOULD YOU LIKE TO VIEW?"<<"\n";
  std::cout << "1. GROCERY REPORT"<<"\n";
  std::cout << "2. CLOTHING REPORT"<<"\n";
  std::cout << "3. HOUSEHOLD REPORT"<<"\n";
  std::cout << "4. EXIT"<<"\n";
  std::cin >> choice;
  Report a;

  switch (choice)
  {
    case 1:
      a.Grocery_Report();
      break;
    case 2:
      a.Clothing_Report();
      break;
    case 3:
      a.Household_Report();
      break;
    case 4:
      return;
    default:
      std::cout << "Incorrect Input. "<<"\n";
      Report::Input();
  }
}

/**
* "Grocery_Report" Function.
* This function attempts to open the data file, read a string in from the data file
* print the contents of the string to the console and then creates a new file
* for grocery items only to store in the new file.
*
* @todo improve the functions ability to read specific key words "Grocery" or "ID"
* that will enable the entire line belonging to the keyword to be output to file.
*
*/
void Report::Grocery_Report(void)
{
  std::cout << "You Selected: Grocery Report" <<"\n";
    
    //Input from main csv data file
    ifstream infile;                // declare in file stream variable
    infile.open("Data File.csv" );  // Open the data file to receive input
    
    
    if(infile.fail())
    {
      cout << "Error: File failed to open..."<<endl;    // Error handling
      
    }
    string groc;
    while (infile.good())
    {
      getline( infile, groc, ',');    // read a string until next comma
      cout << string(groc);           //Testing display string in console to check received
    }
    
    //Output to grocery data csv file
    ofstream outfile;                           // declare out file stream variable
    outfile.open("Grocery_Data.csv",ios::app);  // Open the data file to send appended output
    
    
    if(outfile.fail())
    {
      cout << "Error: Writing to file..."<<endl;    // Error handling
    }
    // If no errors, proceed to output to file
    else
    {
      outfile << string(groc);                      //Send string to ouput file
      cout << "Wrote to Grocery CSV File!!"<<"\n";  //Confirm file wrote
    }
    infile.close();     //close the input data file
    outfile.close();    //close the outfile data file
    infile.clear();     //flush the infile stream
    outfile.clear();    //flush the outfile stream
    Report::Input();    //Return to Input Function
}

/**
* "Clothing_Report" Function.
* This function attempts to open the data file, read a string in from the data file
* print the contents of the string to the console and then creates a new file
* for clothing items only to store in the new file.
*
* @todo improve the functions ability to read specific key word "Clothing" or "ID"
* that will enable the entire line belonging to the keyword to be output to file.
*
*/
void Report::Clothing_Report(void)
{
  std::cout << "You Selected: Clothing Report" <<"\n";
  
  //Input from total data file
  ifstream infile;                  // declare in file stream variable
  infile.open("Data File.csv" );    // Open the data file to receive input
  
  if(infile.fail())
  {
    cout << "Error: File failed to open..."<<endl;  // Error handling
  }
  string cloth;
  while (infile.good())
  {
    getline ( infile, cloth, ',' );   // read to a string from file
    cout << string(cloth);           //Testing display string in console
  }
  
  //Output to clothing data csv file
  ofstream outfile;                            // Declare out file stream variable
  outfile.open("Clothing_Data.csv",ios::app);  // Open the data file to send appended output
  
  if(outfile.fail())
  {
    cout << "Error: Writing to file..."<<endl;  // Error handling
  }
  // If no errors, proceed to output to file
  else
  {
    outfile << cloth;                               //Send string to ouput file
    cout << "Wrote to Clothing CSV File!!"<<"\n";   //Confirm file wrote
  }
  infile.close();     //close the input data file
  outfile.close();    //close the outfile data file
  infile.clear();     //flush the infile stream
  outfile.clear();    //flush the outfile stream
  Report::Input();    //Return to Input Function
}

/**
* "Household_Report" Function.
* This function attempts to open the data file, read a string in from the data file
* print the contents of the string to the console and then creates a new file
* for household items only to store in the new file.
*
* @todo improve the functions ability to read specific key word "Household" or "ID"
* that will enable the entire line belonging to the keyword to be output to file.
*
*/
void Report::Household_Report(void)
{
  std::cout << "You Selected: Household Report" <<"\n";
  
  //Input from total data csv file
  ifstream infile;                  // declare in file stream variable
  infile.open("Data File.csv" );    // Open the data file to receive input
  
  // Error handling
  if(infile.fail())
  {
    cout << "Error: File failed to open..."<<endl;  //Error handling
    
  }
  string house;
  while (infile.good())
  {
    getline ( infile, house, ',' );    //Read a string until next comma
    cout << string(house);           //Testing display string in console
  }
    
  //Output to household data csv file
  ofstream outfile;                             // declare out file stream variable
  outfile.open("Household_Data.csv",ios::app);  // Open the data file to send appended output
  
  if(outfile.fail())
  {
    cout << "Error: Writing to file..."<<endl;  //Error handling
  }
  // If no errors, proceed to output to file
  else
  {
    outfile << house;                               //Send string to ouput file
    cout << "Wrote to Household CSV File!!"<<"\n";  //Confirm file wrote
  }
  infile.close();     //close the input data file
  outfile.close();    //close the outfile data file
  infile.clear();     //flush the infile stream
  outfile.clear();    //flush the outfile stream
  Report::Input();    //Return to Input Function
}

int main(void)
{
  // Make an object of type Report called Report1
  Report Report1;
  Report1.Input();
  return (0);
}

