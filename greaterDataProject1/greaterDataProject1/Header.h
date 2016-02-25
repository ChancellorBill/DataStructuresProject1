// Data Structures Project 1
// Team 2: William Munshaw, Cooper Kertz, Amy Curtis
// 17 February 2016
// Header.h

#pragma once
#include <iostream>
#include <fstream>
//Include statements used on Date.h. DO NOT uncomment them
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
	public:
		assignment()
		{
			
		}
		assignment(Date assignedDate, Date dueDate, assignmentStatus status, string descrition)
		{
			this->assignedDate = assignedDate;
			this->dueDate = dueDate;
			this->status = status;
			this->description = description;
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
		void editAssignedDate(Date specifiedDate)
		{
			assignedDate = specifiedDate;
		}
		void editDueDate(Date specifiedDate)
		{
			dueDate = specifiedDate;
		}
		void display()
		{
			cout << description << endl;
			cout << dueDate.toString() << endl;
			cout << assignedDate.toString() << endl;
			cout << status << endl;
		}
		friend istream &operator>>(istream &input, assignment &A)
		{
			input >> A.assignedDate >> A.dueDate >> A.description;
			return input;
		}
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
		void addAssignment(assignment givenAssignment) 
		{
			//Declarations:
			bool wasFound = false;
			///////////////
			list<assignment>::iterator itr = assigned.begin(); // Iterator is scanning to see if assignment already exists
			while (itr != assigned.end())
			{
				if (itr->getAssignedDate() == givenAssignment.getAssignedDate())
				{
					cout << "This assignment already exists in the system." << endl;
					wasFound = true;
				}
				itr++;
			}
			//need checks for date validation
			if (!wasFound)
			{
				if (givenAssignment.getDueDate() <= givenAssignment.getAssignedDate()) //Ask about this tomorrow (2/25/16), clarify with Kuhail about "Add a new assignment" 
				{
					givenAssignment.changeStatus(LATE);
					completed.push_back(givenAssignment);
				}
				else
				{
					givenAssignment.changeStatus(ASSIGNED);
					assigned.push_back(givenAssignment);
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
			//cout << "You have " << lateCount << " late assignments." << endl;
			return lateCount;
		}
		//Edit assignment function by William Munshaw
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
					do
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
					} while (userChoice != 1 || userChoice != 2);
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
			list<assignment>::iterator assignedItr = assigned.begin();
			list<assignment>::iterator completedItr = completed.begin();
			assignment tempAssignment;
			///////////////
			//sort assigned and completed list
			while (assignedItr++ != assigned.end() && completedItr++ != completed.end())
			{
				if (assignedItr->getDueDate() > assignedItr++->getDueDate())
				{
					tempAssignment = *assignedItr;
					*assignedItr = *assignedItr++;
					*assignedItr++ = tempAssignment;
					assignedItr = assigned.begin();
				}
				if (completedItr->getDueDate() > completedItr++->getDueDate())
				{
					tempAssignment = *completedItr;
					*completedItr = *completedItr++;
					*completedItr++ = tempAssignment;
					completedItr = completed.begin();
				}
				completedItr++;
				assignedItr++;
			}
			//short completed list
			/*while (completedItr++ != completed.end())
			{
				if (completedItr->getDueDate > completedItr++->getDueDate())
				{
					tempAssignment = *completedItr;
					*completedItr = *completedItr++;
					*completedItr++ = tempAssignment;
					completedItr = completed.begin();
				}
				completedItr++;
			}*/
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
					itr->changeStatus(COMPLETED);
					completed.push_back(*itr); //adds the assignment to the completed list
					//Delete from assigned list
					assigned.remove(*itr);
					wasFound = true;
				}
				itr++;
			}
		}
};
/*-----------------------------------------------------------------------------*/

/*------------------------------Prototype Definitions--------------------------*/
assignment userCreateAssignment();
/*-----------------------------------------------------------------------------*/