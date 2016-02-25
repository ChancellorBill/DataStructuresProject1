// Data Structures Project 1
// Team 2: William Munshaw, Cooper Kertz, Amy Curtis
// 17 February 2016
// Header.h

#pragma once
#include <iostream>
#include <fstream>
//#include <stdexcept> 
//#include <algorithm> 
//#include <functional> 
//#include <cctype>
//#include <locale>
//#include <sstream>
//#include <iomanip>
//#include <string>
#include <list>
//#include "StringTokenizer.h"
#include "Date.h"
using namespace std;

/*-------------------------------------Enums-----------------------------------*/
enum assignmentStatus { LATE, COMPLETED, ASSIGNED };
/*-----------------------------------------------------------------------------*/

/*-----------------------------------Classes-----------------------------------*/
class assignment
{
	private:
		Date assignedDate;
		Date dueDate;
		assignmentStatus status;
		string description;
		bool isLate; //to be depricated
	public:
		assignment(Date assignedDate, Date dueDate, assignmentStatus status, string descrition)
		{
			this->assignedDate = assignedDate;
			this->dueDate = dueDate;
			this->status = status;
			this->description = description;
			isLate = false; // to be depricated
		}
		Date getAssignedDate()
		{
			return assignedDate;
		}
		Date getDueDate()
		{
			return dueDate;
		}
		string getDescription()
		{
			return description;
		}
		void editDescription()
		{
			cout << "Enter new description for the assignment" << endl;
			cin >> description;
		}
		void editDueDate(Date specifiedDate)
		{
			dueDate = specifiedDate;
		}
		void display()
		{
			//to be done
		}
		/*friend istream& operator>>(istream& input, assignment &A)
		{
			input >> A.assignedDate >> A.dueDate >> A.status >> A.description;
		}*/
		bool operator==(assignment givenAssignment)
		{
			//Declarations:
			bool isEqual = true;
			///////////////
			if (assignedDate == givenAssignment.getAssignedDate())
			{
				isEqual = false;
			}
			return isEqual;
		}
		void changeStatus(assignmentStatus givenStatus)
		{
			status = givenStatus;
		}
};

//assignmentManager Class, this is a second version and replaces the older Assignment_Manager class
class assignmentManager
{
	private:
		list<assignment>assigned;
		list<assignment>completed;
	public:
		//Default constructor
		assignmentManager()
		{

		}
		//Add assignment function by Cooper Kertz, modified for the new assignmentManger class by William Munshaw
		void addAssignment(Date givenAssignedDate, Date giveDueDate, assignmentStatus givenStatus, string givenDescription) 
		{
			//Declarations:
			bool wasFound = false;
			///////////////
			//Take parameters. If it already exists, reject it. If it is late, push back onto completed, otherwise push back onto assigned
			/*cout << "What is your assignment's assigned date?" << endl;
			cin >> assigned_date;
			cout << "What is your assignment's name?" << endl;
			cin >> description;
			cout << "What is your assignment's due date?" << endl;
			cin >> due_date;*/

			list<assignment>::iterator itr = assigned.begin(); // Iterator is scanning to see if assignment already exists
			while (itr != assigned.end())
			{
				assignment assignment = *itr;

				if (assignment.getDescription() == givenDescription)
				{
					cout << "This assignment already exists in the system." << endl;
					wasFound = true;
				}
			}
			if (!wasFound)
			{
				if (giveDueDate <= givenAssignedDate)
				{
					givenStatus = LATE;
					assignment assignment(givenAssignedDate, giveDueDate, givenStatus, givenDescription);
					completed.push_back(assignment);
				}
				else
				{
					givenStatus = ASSIGNED;
					assignment assignment(givenAssignedDate, giveDueDate, givenStatus, givenDescription);
					assigned.push_back(assignment);
				}
			}			
		}
		//Display assignments function by Cooper Kertz, modified for the new assignmentManger class by William Munshaw
		void displayAssignments(int rootMenuChoice)
		{
			//Declarations:
			list<assignment>::iterator assignedItr = assigned.begin();
			list<assignment>::iterator completedItr = completed.begin();
			///////////////
			switch (rootMenuChoice)
			{
				case 1: // for displaying the assigned list
					while (assignedItr != assigned.end())
					{
						assignedItr->display();
						assignedItr++;
					}
					break;
				case 2: // for displaying the completed list
					while (completedItr != completed.end())
					{
						completedItr->display();
						completedItr++;
					}
					break;
			}
		}
		//Late Assignment Count by Cooper Kertz, modified for the new assignmentManger class by William Munshaw
		int lateAssignmentCount()
		{
			//Declarations:
			int lateCount;
			list<assignment>::iterator itr = completed.begin();
			///////////////			
			while (itr != completed.end())
			{
				if (itr->getDueDate() <= itr->getAssignedDate())
				{
					lateCount++;
				}

			}
			cout << "You have " << lateCount << " late assignments." << endl;
		}
		void editAssignment(Date specifiedDate)
		{
			//Declarations:
			list<assignment>::iterator itr = assigned.begin();
			int userChoice;
			Date tempDate;
			bool wasFound = false;
			//////////////

			//need to add checks for if due date is invalid

			while (itr != assigned.end())
			{
				if (itr->getDueDate() == specifiedDate)
				{
					cout << "Would you like to edit the due date (1) or the description (2)?" << endl;
					while (userChoice != 1 || userChoice != 2)
					{
						cin >> userChoice;
						switch (userChoice)
						{
						case 1:
							cout << "Enter new due date:" << endl;
							cin >> tempDate;
							itr->editDueDate(tempDate);
							break;
						case 2:
							itr->editDescription();
							cout << "Description edited!" << endl;
							break;
						default:
							cout << "Invalid option, try again" << endl;
							break;
						}
					}
					wasFound = true;
				}
				itr++;
			}
			if (wasFound = false)
			{
				cout << "Assignment is not in the list. Try again" << endl;
			}
		}
		//Sort Assignments function by William Munshaw
		void sortAssignments()
		{
			//Declarations:
			list<assignment>::iterator itr = assigned.begin();
			Date dueSoon = itr->getDueDate();
			///////////////

		}
		//Complete Assignments function by William Munshaw
		void completeAssignment(Date specifiedDate, Date currentDate)
		{
			//Declarations:
			list<assignment>::iterator itr = assigned.begin();
			bool wasFound = false;
			///////////////

			//add checks for date validation

			while (itr != assigned.end())
			{
				if (itr->getAssignedDate() == specifiedDate)
				{	
					//Delete from assigned list
					completed.push_back(*itr); //adds the assignment to the completed list
					wasFound = true;
				}
				itr++;
			}
		}
};
/*-----------------------------------------------------------------------------*/