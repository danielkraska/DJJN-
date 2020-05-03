#ifndef reports_hpp
#define reports_hpp

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>

using namespace std;

/**
*  "Report" Class
*
* Includes functions to read/write product detail reports from details stored in
* .csv file.
*
* @author James Goodall <goodall-j6@ulster.ac.uk>
* @license <http://www.gnu.org/licenses/gpl-3.0.html>
* @copyright James Goodall 2020
*
*/
class Report
{
private:
  int choice;
  
public:
  void Input();
  void Grocery_Report();
  void Clothing_Report();
  void Household_Report();
  
};


#endif /* reports_hpp */
