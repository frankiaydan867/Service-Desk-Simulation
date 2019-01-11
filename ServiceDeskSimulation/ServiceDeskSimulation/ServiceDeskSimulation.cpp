/*
	Module 2 - Lab Assignment
	Title: Service Desk Simulation
	Coded by: Franki Micheo on 1.11.19
	Class: COP2570C - Programming Data Structures
*/


#include "pch.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <stack>
#include <stdlib.h>
#include <stdio.h>
#include <queue>
#include <iterator>
#include <iomanip>
#include <windows.h>

using namespace std;

//Examples
//Random number from 1 to 1000: 1 + rand() % 999;

//Class to create service request objects. These hold priorities and times
class ServiceRequest {
private:
	string priority;
	int time;

public:
	void setPriority(string n) {
		priority = n;
	}
	void setTime(int t) {
		time = t;
	}
	string getPriority() {
		return priority;
	}
	int getTime() {
		return time;
	}
};

/*
	Methods
*/
//Create random number between 5 and 8
int GenerateRandomTime();

//Create random value between 1 and 3
int GenerateRandomPriority();

//Update the time and priority deques
void UpdateDeques(deque<string> &p, deque<int> &t, int c);

//Create Service Requests objects using the updated deques
void CreateServiceRequests(queue<ServiceRequest> &sr, deque<string> p, deque<int> t, int c);

//Display the Service requests
void ShowRequests(queue<ServiceRequest> sr, deque<string> p, deque<int> t, int c);

//Delete all values on all deques
void ClearDeques(deque<string> &p, deque<int> &t);

//Delete all values on all queues
void ClearQueues(queue<ServiceRequest> &sr);

//Main Program
int main()
{
	//Variables
	queue<ServiceRequest> servicerequests; //Queue to organize service request using FIFO
	deque<string> priorities; //Hold priorities
	deque<int> times; //Hold times
	int customers = 100; //Total customers


	/*
	Run the program for 100 customers on one station
	*/
	UpdateDeques(priorities, times, customers); //Fill the deques with Data;
		
	CreateServiceRequests(servicerequests, priorities, times, customers); //Generate Service Requests with random priorities and times
		
	ShowRequests(servicerequests, priorities, times, customers); //Display the Requests



	/*
	Run the program for 50 customers using two stations
	*/
	ClearDeques(priorities, times); //Clear the deques
	ClearQueues(servicerequests);  //Clear the queue
	
	customers = 50; 
	
	UpdateDeques(priorities, times, customers);  //50 random priorities and times
	
	CreateServiceRequests(servicerequests, priorities, times, customers); //Load the first 50 service requests for station A
	
	ClearDeques(priorities, times); //Reset the deques
	
	UpdateDeques(priorities, times, customers);  //Reload the deques with new data for the next set of requests
	
	CreateServiceRequests(servicerequests, priorities, times, customers); //Load the next 50 requests for station B
	
	ShowRequests(servicerequests, priorities, times, customers); //Display all requests for both stations


}

//Method
int GenerateRandomTime() {
	return 5 + rand() % 4;
}

int GenerateRandomPriority() {
	return (1 + rand() % 3);
}

void UpdateDeques(deque<string> &p, deque<int> &t, int c) {
	for (int i = 0; i < c; i++) {
		int time = GenerateRandomTime();
		int priority = GenerateRandomPriority();
		deque<string>::iterator it1 = p.begin() + (i/2);
		deque<int>::iterator it2 = t.begin() + (i / 2);
		
		switch (priority) {
		case 1:
			p.push_back("Low");
			t.push_back(time);
			break;
		case 2:
			p.insert(it1,"Medium");
			t.insert(it2, time);
			break;
		case 3:
			p.push_front("High");
			t.push_back(time);
			break;

		}
	}

	deque<int> splitTime;

	if (c == 50) {

	}

	
}

void CreateServiceRequests(queue<ServiceRequest> &sr, deque<string> p, deque<int> t, int c) {
	
	//Object to hold the values for each index before pushing into SR stack.
	ServiceRequest n;
	
	//Fill up x number of service requests with random data
	for (int i = 0; i < c; i++) {
		n.setPriority(p[i]);
		n.setTime(t[i]);
		sr.push(n);
	}
}

void ShowRequests(queue<ServiceRequest> sr, deque<string> p, deque<int> t, int c) {

	ServiceRequest n;
	int totalHigh = 0;
	int totalMid = 0;
	int totalLow = 0;
	int avgHigh = 0;
	int avgMid = 0; 
	int avgLow = 0;


	cout << "List of Service Requests for " << c << " customers\n-----------------------------------------\n";

	cout << "*****Station A*****\n\n";

	for (int i = 0; i < c; i++) {
		n = sr.front();

		if (n.getPriority() == "High") {
			totalHigh++;
			avgHigh += n.getTime();
		}
		if (n.getPriority() == "Medium") {
			totalMid++;
			avgMid += n.getTime();
		}
		if (n.getPriority() == "Low") {
			totalLow++;
			avgLow += n.getTime();
		}

		string msg1 = "Request #" + to_string(i + 1) + " --> ";
		string msg2 = "Priority: " + n.getPriority();
		string msg3 = "Wait Time: " + to_string(n.getTime()) + "min";

		cout << left << setw(20) << msg1
			<< left << setw(20) << msg2
			<< left << setw(20) << msg3  << endl;
		sr.pop();
	}

	try {
		avgHigh != 0 ? avgHigh = avgHigh / totalHigh : avgHigh = 0;
		avgMid != 0 ? avgMid = avgMid / totalMid : avgMid = 0;
		avgLow != 0 ? avgLow = avgLow / totalLow : avgLow = 0;
	}
	catch(exception e){
		e.what();
	}
	
	cout << "\n\nStats: " << c << " customers\n\n";

	//Print Stats
	cout << "High Priority\n-----------------------------\n";
	cout << left << setw(7) << "Total: "
		<< left << setw(7) << totalHigh
		<< left << setw(7) << "Average Time: "
		<< left << setw(7) << avgHigh << endl;


	cout << "\nMedium Priority\n-----------------------------\n";
	cout << left << setw(7) << "Total: "
		<< left << setw(7) << totalMid
		<< left << setw(7) << "Average Time: "
		<< left << setw(7) << avgMid << endl;

	cout << "\nLow Priority\n-----------------------------\n";
	cout << left << setw(7) << "Total: "
		<< left << setw(7) << totalLow
	<< left << setw(7) << "Average Time: "
		<< left << setw(7) << avgLow << "\n\n\n";

	//If there are 50 customres on the first set, load the next 50.
	if (c == 50) {
		cout << "\n\n*****Station B*****\n\n";
		ServiceRequest n;
		int totalHigh = 0;
		int totalMid = 0;
		int totalLow = 0;
		int avgHigh = 0;
		int avgMid = 0;
		int avgLow = 0;

		for (int i = 50; i < 100; i++) {
			n = sr.front();

			if (n.getPriority() == "High") {
				totalHigh++;
				avgHigh += n.getTime();
			}
			if (n.getPriority() == "Medium") {
				totalMid++;
				avgMid += n.getTime();
			}
			if (n.getPriority() == "Low") {
				totalLow++;
				avgLow += n.getTime();
			}

			string msg1 = "Request #" + to_string(i + 1) + " --> ";
			string msg2 = "Priority: " + n.getPriority();
			string msg3 = "Wait Time: " + to_string(n.getTime()) + "min";

			cout << left << setw(20) << msg1
				<< left << setw(20) << msg2
				<< left << setw(20) << msg3 << endl;
			sr.pop();
		}

		try {
			avgHigh != 0 ? avgHigh = avgHigh / totalHigh : avgHigh = 0;
			avgMid != 0 ? avgMid = avgMid / totalMid : avgMid = 0;
			avgLow != 0 ? avgLow = avgLow / totalLow : avgLow = 0;
		}
		catch (exception e) {
			e.what();
		}

		cout << "\n\nStats: " << c << " customers\n\n";

		//Print Stats
		cout << "High Priority\n-----------------------------\n";
		cout << left << setw(7) << "Total: "
			<< left << setw(7) << totalHigh
			<< left << setw(7) << "Average Time: "
			<< left << setw(7) << avgHigh << endl;


		cout << "\nMedium Priority\n-----------------------------\n";
		cout << left << setw(7) << "Total: "
			<< left << setw(7) << totalMid
			<< left << setw(7) << "Average Time: "
			<< left << setw(7) << avgMid << endl;

		cout << "\nLow Priority\n-----------------------------\n";
		cout << left << setw(7) << "Total: "
			<< left << setw(7) << totalLow
			<< left << setw(7) << "Average Time: "
			<< left << setw(7) << avgLow << "\n\n\n";
		for (int l = 0; l < 50; l++) {
			cout << "-";
		}
		cout << endl;
	}
}	

void ClearDeques(deque<string> &p, deque<int> &t) {
	p.clear();
	t.clear();
}

void ClearQueues(queue<ServiceRequest> &sr) {
	while (!sr.empty()) {
		sr.pop();
	}
}