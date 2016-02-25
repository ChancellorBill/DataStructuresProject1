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
	bool inValidDate = true;
	///////////////
	cout << "Welcome to Assignment Manger" << endl;
	cout << "First, what is today?" << endl;
	while (inValidDate == true)
	{
		inValidDate = false;
		try
		{
			cin >> today;
		}
		catch (std::exception e) {
			cout << "Today is invalid, try again" << endl;
			inValidDate = true;
		}
	}	
	do
	{
		cout << "Select option: " << endl;
		cout << "(1) Display assignments" << endl;
		cout << "(2) Add assignment(s)" << endl;
		cout << "(3) Edit an assignment" << endl;
		cout << "(4) Complete assignment" << endl;
		cout << "(5) Display number of late assignments" << endl;
		cout << "(6) Save" << endl;
		cout << "(7) Re-declare today's date" << endl;
		cout << "(8) Sort assignments" << endl;
		cout << "(9) Exit" << endl;
		cin >> userChoice;
		switch (userChoice) 
		{
			case 1: //Display assignments
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
			case 2: //Add assignments(s)
				cout << "Would you like to add an assignment by typing it in (1), or bulk add assignments from the input file (2)" << endl;
				cin >> assignmentAddSpecify;
				if (assignmentAddSpecify == 1)
				{
					assignments.addAssignment(userCreateAssignment());
				}
				else if (assignmentAddSpecify == 2)
				{
					assignments.load_data("database.txt");
				}
				else
				{
					cout << "Incorrect option. Try again" << endl;
				}
				break;
			case 3: //Edit an assignment
				cout << "State the due date of the assignment you would like to edit:" << endl;
				cin >> tempDate;
				assignments.editAssignment(tempDate);
				break;
			case 4: //Complete assignment
				cout << "State the assigned date of the assignment:" << endl;
				cin >> tempDate;
				assignments.completeAssignment(tempDate, today);
				break;
			case 5: //Number of late assignments
				cout << "You have " << assignments.lateAssignmentCount() << " late assignments." << endl;
				break;
			case 6: //Save
				assignments.save("database.txt");
				cout << "Database saved!" << endl;
				break;
			case 7: //Redeclare Today's date
				cout << "What is today?" << endl;
				inValidDate = true;
				while (inValidDate == true)
				{
					inValidDate = false;
					try
					{
						cin >> today;
					}
					catch (std::exception e) {
						cout << "Today is invalid, try again" << endl;
						inValidDate = true;
					}
				}
				break;
			case 8:	//Sort
				assignments.sortAssignments();
				cout << "Assignments sorted!" << endl;
				break;
			case 9:
				//Exit
				break;
			default:
				cout << "Invalid option.  Try again." << endl;
				break;
		}	
	} while (userChoice != 9);
	
	//system("pause"); //not necessary
	return 0;
}

assignment userCreateAssignment()
{
	//Declarations:
	assignment userAssignment;
	Date tempDate;
	bool inValidDate = true;
	///////////////
	cout << "Enter the due date of the assignment" << endl;
	while (inValidDate == true)
	{
		inValidDate = false;
		try
		{
			cin >> tempDate;
		}
		catch (std::exception e)
		{
			cout << "The due date is invalid, try again:" << endl;
			inValidDate = true;
		}
	}
	userAssignment.editDueDate(tempDate);
	cout << "Enter the date assigned of the assignment" << endl;
	inValidDate = true;
	while (inValidDate == true)
	{
		inValidDate = false;
		try
		{
			cin >> tempDate;
		}
		catch (std::exception e)
		{
			cout << "The assigned date is invalid, try again:" << endl;
			inValidDate = true;
		}
	}
	userAssignment.editAssignedDate(tempDate);
	userAssignment.editDescription(); //Entering of description managed by editDescription function
	return userAssignment;
}