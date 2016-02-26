// Data Structures Project 1
// Team 2: William Munshaw, Cooper Kertz, Amy Curtis
// 17 February 2016
// Header.h

#pragma once
#include <iostream>
#include <fstream>
#include <istream>
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
		assignmentStatus getStatus()
		{
			return status;
		}
		void editDescription()
		{
			cout << "Enter new description for the assignment" << endl;
			cin.ignore(2, '\0');
			getline(cin, description);
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
			cout << "Description: " << description << endl;
			cout << "Due date: " << dueDate.toString() << endl;
			cout << "Date assigned: " << assignedDate.toString() << endl;
			cout << "Status: ";
			switch (status)
			{
			case ASSIGNED:
				cout << "ASSIGNED" << endl;
				break;
			case COMPLETED:
				cout << "COMPLETED" << endl;
				break;
			case LATE:
				cout << "LATE" << endl;
				break;
			}
			cout << endl;
		}
		friend istream &operator>>(istream &input, assignment &A) //meant for File I/O only, not user interaction
		{
			//Declarations:
			int statusType;
			///////////////
			input >> A.assignedDate >> A.dueDate >> A.description >> statusType;
			switch (statusType)
			{
				case 1:
					A.status = ASSIGNED;
					break;
				case 2:
					A.status = COMPLETED;
					break;
				case 3:
					A.status = LATE;
					break;
			}
			return input;
		}
		friend ostream &operator<<(ostream &output, assignment &A) //meant for File I/O only, not user interaction
		{
			
			output << A.assignedDate.toString() << ", " << A.description << ", " << A.dueDate.toString() << ", ";
			switch (A.status)
			{
				case ASSIGNED:
					output << "assigned" << endl;
					break;
				case COMPLETED:
					output << "completed" << endl;
					break;
				case LATE:
					output << "late" << endl;
					break;
			}
			return output;
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
		bool modified;
	public:
		//Default constructor
		assignmentManager()
		{
			modified = false;
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
			if (!wasFound)
			{
				if (givenAssignment.getDueDate() <= givenAssignment.getAssignedDate())
				{
					givenAssignment.changeStatus(LATE);
					completed.push_back(givenAssignment);
				}
				else
				{
					givenAssignment.changeStatus(ASSIGNED);
					assigned.push_back(givenAssignment);
				}
				modified = true;
			}			
		}
		//Display assignments function by Cooper Kertz, modified for the new assignmentManger class by William Munshaw
		void displayAssignments(int rootMenuChoice)
		{
			//cout << "Here1" << endl;
			//Declarations:
			list<assignment>::iterator assignedItr = assigned.begin();
			list<assignment>::iterator completedItr = completed.begin();
			///////////////
			switch (rootMenuChoice)
			{
				//cout << "Here2" << endl;
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
			int lateCount = 0;
			list<assignment>::iterator itr = completed.begin();
			///////////////
			while (itr != completed.end())
			{
				if (itr->getDueDate() <= itr->getAssignedDate())
				{
					lateCount++;
				}
				if (itr->getStatus() == LATE)
				{
					lateCount++;
				}
				itr++;
			}
			//cout << "You have " << lateCount << " late assignments." << endl;
			return lateCount;
		}

		string trim(const string& the_string)
		{
			size_t p = the_string.find_first_not_of(" ");
			if (p == string::npos) return "";
			size_t q = the_string.find_last_not_of(" ");
			return the_string.substr(p, q - p + 1);
		}

		//Edit assignment function by William Munshaw
		void editAssignment(Date specifiedDate)
		{
			//Declarations:
			list<assignment>::iterator itr = assigned.begin();
			int userChoice;
			Date tempDate;
			bool wasFound = false;
			bool inValidDate = true;
			//////////////
			while (itr != assigned.end())
			{
				if (itr->getDueDate() == specifiedDate)
				{
					cout << "Would you like to edit the due date (1) or the description (2)?" << endl;
					cin >> userChoice;
					switch (userChoice)
					{
						case 1:
							cout << "Enter new due date:" << endl;
							while (inValidDate == true)
							{
								inValidDate = false;
								try
								{
									cin >> tempDate;
								}
								catch (std::exception e) {
									cout << "Today is invalid, try again" << endl;
									inValidDate = true;
								}
							}
							itr->editDueDate(tempDate);
							modified = true;
							break;
						case 2:
							itr->editDescription();
							cout << "Description edited!" << endl;
							modified = true;
							break;
						default:
							cout << "Invalid option!" << endl;
							break;
					}
					wasFound = true;
				}
				itr++;
			}
			if (wasFound == false)
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
			assignment tempAssignment1, tempAssignment2;
			///////////////
			//sort assigned list
			while (assignedItr != assigned.end())
			{
				tempAssignment1 = *assignedItr;
				assignedItr++;
				if (assignedItr != assigned.end())
				{
					if (tempAssignment1.getDueDate() > assignedItr->getDueDate())
					{
						tempAssignment2 = *assignedItr;
						*assignedItr = tempAssignment1;
						assignedItr--;
						*assignedItr = tempAssignment2;
						assignedItr = assigned.begin();
					}
				}				
				modified = true;
			}
			//short completed list
			while (completedItr != completed.end())
			{
				tempAssignment1 = *completedItr;
				completedItr++;
				if (completedItr != completed.end())
				{
					if (tempAssignment1.getDueDate() > completedItr->getDueDate())
					{
						tempAssignment2 = *completedItr;
						*completedItr = tempAssignment1;
						completedItr--;
						*completedItr = tempAssignment2;
						completedItr = completed.begin();
					}
				}
				modified = true;
			}
		}
		//Complete Assignments function by William Munshaw
		void completeAssignment(Date specifiedDate, Date currentDate)
		{
			//Declarations:
			list<assignment>::iterator itr = assigned.begin();
			bool wasFound = false;
			///////////////
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
			cout << "Assignment completed!" << endl;
		}
		void load_data(const string& source_name)
		{

			// Create an input stream for this file.
			ifstream in(source_name);
			if (in) { // Stream exists.
				Date givenDueDate;
				string givenDescription;
				Date givenAssignedDate;
				assignmentStatus givenStatus;
				string line;
				while (getline(in, line)) { //read the next line in the file, if no more lines are availble, the while loop will exist.
					String_Tokenizer st(line, ","); //a tokenizer for parsing a line of tokens (the tokens are seperated by commas)
					givenDueDate = Date(trim(st.next_token()));
					givenDescription = trim(st.next_token());
					givenAssignedDate = Date(trim(st.next_token()));
					string status = trim(st.next_token());
					if (status == "late")
						givenStatus = assignmentStatus::LATE;
					else if (status == "assigned")
					{
						givenStatus = assignmentStatus::ASSIGNED;
					}
					else if (status == "completed")
					{
						givenStatus = assignmentStatus::COMPLETED;
					}
					assignment new_assignment = assignment(givenAssignedDate, givenDueDate, givenStatus, givenDescription);
					if (givenStatus == assignmentStatus::COMPLETED || givenStatus == assignmentStatus::LATE)
						completed.push_back(new_assignment);
					else
						assigned.push_back(new_assignment);
				}
			}
			// Close the file.
			in.close();
		}
		void save(const string& source_name) //Need to edit this
		{
			if (modified) {  // if not modified, do nothing
							 // Create an output stream.
				ofstream out(source_name.c_str());
				list<assignment>::iterator assignedITR = assigned.begin();
				list<assignment>::iterator completedITR = completed.begin();
				while (assignedITR != assigned.end())
				{
					/*out << assignedITR->getDueDate << ", ";
					out << assignedITR->getDescription << ", ";
					out << assignedITR->getAssignedDate << ", ";*/
					out << *assignedITR;
					assignedITR++;
				}
				while (completedITR != completed.end())
				{
					/*out << completedITR->getDueDate << ", ";
					out << completedITR->getDescription << ", ";
					out << completedITR->getAssignedDate << ", ";*/
					out << *completedITR;
					completedITR++;
				}
				// Close the output stream.
				out.close();
				modified = false;
			}
		}
};
/*-----------------------------------------------------------------------------*/

/*------------------------------Prototype Definitions--------------------------*/
assignment userCreateAssignment();
/*-----------------------------------------------------------------------------*/