// Data Structures Project 1
// Team 2: William Munshaw, Cooper Kertz, Amy Curtis
// 17 February 2016
// Source.cpp


#include "Header.h"

int main()
{
	//Declarations:
	int userChoice;
	//Date tempDate;
	//assignmentManager assignments;
	//File I/O
	ifstream fin("input.txt");
	//if input file not found, quit with an error message
	if (!fin)
	{ 
		cout << "Input file not opened!" << endl;
		exit(1);
	}
	///////////////

	do
	{
		cout << "Select option: " << endl;
		cout << "(1) Display assignments" << endl;
		cout << "(2) Add assignment" << endl;
		cout << "(3) Edit an assignment" << endl;
		cout << "(4) Complete assignment" << endl;
		cout << "(5) Number of late assignments" << endl;
		cout << "(6) Save" << endl;
		cout << "(7) Exit" << endl;
		cin >> userChoice;

		switch (userChoice) 
		{
			case '1':
				//assignments.displayAssignments();
				break;
			case '2':
				// add prompts for the assignment to be added
				//assignments.addAssignment();
				break;
			case '3':
				cout << "State the due date of the assignment you would like to edit:" << endl;
				//cin >> tempDate;
				//assignments.editAssignment(tempDate);
				break;
			case '4':

				break;
			case '5':

				break;
			case '6':

				break;
			case '7':
				break;
			default:
				cout << "Invalid option.  Try again." << endl;
		}	
	} while (userChoice != 7);
	
	system("pause"); //not necessary
	return 0;
}