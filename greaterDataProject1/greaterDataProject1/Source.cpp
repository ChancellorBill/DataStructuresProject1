// Data Structures Project 1
// Team 2: William Munshaw, Cooper Kertz, Amy Curtis
// 17 February 2016
// Source.cpp

#include "Header.h"

int main()
{
	//Declarations:
	int userChoice; //menu selection
	int assignmentDisplaySpecify; //used to determine if the assigned assignments or completed assignments lists will be displayed
	int assignmentAddSpecify; //used to determine if assignments will be added by the user or by bulk with File I/O
	Date tempDate; //used for searching the assignment manager lists
	Date today; //declare what to today is to determine if an assignment is late or not
	assignmentManager assignments;
	//File I/O
	//ifstream fin("input.txt");
	////if input file not found, quit with an error message
	//if (!fin)
	//{
	//	cout << "Input file not opened!" << endl;
	//	exit(1);
	//}
	///////////////
	cout << "Welcome to Assignment Manger" << endl;
	cout << "First, what is today?" << endl;
	cin >> today;
	do
	{
		cout << "Select option: " << endl;
		cout << "(1) Display assignments" << endl;
		cout << "(2) Add assignment" << endl;
		cout << "(3) Edit an assignment" << endl;
		cout << "(4) Complete assignment" << endl;
		cout << "(5) Number of late assignments" << endl;
		cout << "(6) Save" << endl;
		cout << "(7) Re-declare today's date" << endl;
		cout << "(8) Exit" << endl;
		cin >> userChoice;
		switch (userChoice) 
		{
			case 1:
				cout << "Would you like to see assigned assignments (1) or completed assignments (2)?" << endl;
				cin >> assignmentDisplaySpecify;
				if (assignmentDisplaySpecify == 1 || assignmentDisplaySpecify == 2)
				{
					assignments.displayAssignments(assignmentDisplaySpecify);
				}
				else
				{
					cout << "Incorrect option. Try again" << endl;
				}
				break;
			case 2:
				// add prompts for the assignment to be added
				//assignments.addAssignment();
				break;
			case 3:
				cout << "State the due date of the assignment you would like to edit:" << endl;
				cin >> tempDate;
				assignments.editAssignment(tempDate);
				break;
			case 4:
				cout << "State the assigned date of the assignment:" << endl;
				cin >> tempDate;
				assignments.completeAssignment(tempDate, today);
				break;
			case 5:
				cout << "You have " << assignments.lateAssignmentCount() << " late assignments." << endl;
				break;
			case 6:

				break;
			case 7:
				cout << "What is today?" << endl;
				cin >> today;
				break;
			case 8:
				break;
			default:
				cout << "Invalid option.  Try again." << endl;
				break;
		}	
	} while (userChoice != 8);
	
	//system("pause"); //not necessary
	return 0;
}

assignment userCreateAssignment()
{
	//Declarations:
	assignment userAssignment;
	Date tempDate;
	///////////////
	cout << "Enter the due date of the assignment" << endl;
	cin >> tempDate;
	userAssignment.editDueDate(tempDate);
	cout << "Enter the date assigned of the assignment" << endl;
	userAssignment.editAssignedDate(tempDate);
	userAssignment.editDescription();
	return userAssignment;
}