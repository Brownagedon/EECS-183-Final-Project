/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Floor.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Grey Sato
 * greysato
 *
 * Final Project - Elevators
 */


#include "Floor.h"
#include "Utility.h"

using namespace std;

int Floor::tick(int currentTime) {
	int numExplode = 0;
	int explodeArray[MAX_PEOPLE_PER_FLOOR];
    for (int i = 0; i < numPeople; i++) {
		if (people[i].tick(currentTime)) {
			explodeArray[numExplode] = i;
			numExplode++;
		}
	}
	removePeople(explodeArray, numExplode);
    return numExplode;
}

void Floor::addPerson(Person newPerson, int request) {
    if (numPeople < MAX_PEOPLE_PER_FLOOR) {
		people[numPeople] = newPerson;
		if (request > 0) {
			hasUpRequest = true;
		}
		if (request < 0) {
			hasDownRequest = true;
		}
		numPeople++;
	}
}

void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR],
                         int numPeopleToRemove) {

	//list of people to copy to, and how many good people there are						
	Person newPeopleList[numPeople - numPeopleToRemove];
	int goodPeople = 0;

	for (int i = 0; i < numPeople; i++) {
		bool needRemoved = false;
		for (int j = 0; j < numPeopleToRemove; j++) {
			if (i == indicesToRemove[j]) {
				needRemoved = true;	
			}
		}
		if (!needRemoved) {
			newPeopleList[goodPeople] = people[i];
			goodPeople++;
		}
	}
	for (int i = 0; i < numPeople; i++) {
		Person newPerson;
		people[i] = newPerson;
	}
	for (int i = 0; i < numPeople - numPeopleToRemove; i++) {
		people[i] = newPeopleList[i];
	}
	numPeople -= numPeopleToRemove;
	resetRequests();
}

void Floor::resetRequests() {
	hasUpRequest = false;
	hasDownRequest = false;
    for (int i = 0; i < numPeople; i++) {
		if (people[i].getTargetFloor() - people[i].getCurrentFloor() > 0){
			hasUpRequest = true;
		}
		if (people[i].getTargetFloor() - people[i].getCurrentFloor() < 0) {
			hasDownRequest = true;
		}
	}
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Floor::Floor() {
    hasDownRequest = false;
    hasUpRequest = false;
    numPeople = 0;
}

void Floor::prettyPrintFloorLine1(ostream& outs) const {
	string up = "U";
	outs << (hasUpRequest ? up : " ") << " ";
	for (int i = 0; i < numPeople; ++i){
		outs << people[i].getAngerLevel();
		outs << ((people[i].getAngerLevel() < MAX_ANGER) ? "   " : "  ");
	}
	outs << endl;
}

void Floor::prettyPrintFloorLine2(ostream& outs) const {
	string down = "D";
	outs << (hasDownRequest ? down : " ") << " ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "o   ";
	}
	outs << endl;
}

void Floor::printFloorPickupMenu(ostream& outs) const {
	cout << endl;
	outs << "Select People to Load by Index" << endl;
	outs << "All people must be going in same direction!";
	/*  O   O
	// -|- -|-
	//  |   |
	// / \ / \  */
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " O   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "-|-  ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " |   ";
	}
	outs << endl << "              ";
	for (int i = 0; i < numPeople; ++i) {
		outs << "/ \\  ";
	}
	outs << endl << "INDEX:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << i << "   ";
	}
	outs << endl << "ANGER:        ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getAngerLevel() << "   ";
	}
	outs << endl << "TARGET FLOOR: ";
	for (int i = 0; i < numPeople; ++i) {
		outs << " " << people[i].getTargetFloor() << "   ";
	}
}

void Floor::setHasUpRequest(bool hasRequest) {
    hasUpRequest = hasRequest;
}

bool Floor::getHasUpRequest() const {
	return hasUpRequest;
}

void Floor::setHasDownRequest(bool hasRequest) {
    hasDownRequest = hasRequest;
}

bool Floor::getHasDownRequest() const {
	return hasDownRequest;
}

int Floor::getNumPeople() const {
    return numPeople;
}

Person Floor::getPersonByIndex(int index) const {
    return people[index];
}
