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
    /*
     * Requires: nothing
     * Modifies: people
     * Effects:  Ticks each person on this floor
     *           Also removes any Person who explodes
     *           Returns the number of exploded people
     */
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

    /*
     * Requires: request != 0
     * Modifies: hasUpRequest, hasDownRequest, numPeople, people
     * Effects:  If there is still room, add newPerson to people.
     *           Updates hasUpRequest or hasDownRequest based on value of request
     */
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
    /*
     * Requires: numPeopleToRemove >= 0, 
     *           numPeopleToRemove <= MAX_PEOPLE_PER_FLOOR,
     *           numPeopleToRemove >= 0, numPeopleToRemove <= numPeople,
     *           for all values of i such that 0 <= i < numPeopleToRemove, 
     *           indicesToRemove[i] < numPeople
     * Modifies: people[], numPeople, hasUpRequest, hasDownRequest
     * Effects:  Removes objects from people[] at indices specified 
     *           in indicesToRemove[].
     *           The size of indicesToRemove[] is given by numPeopleToRemove.
     *           After removals, calls resetRequests() to update hasUpRequest 
     *           and hasDownRequest.
     */
void Floor::removePeople(const int indicesToRemove[MAX_PEOPLE_PER_FLOOR],
                         int numPeopleToRemove) {
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

    /*
     * Requires: nothing
     * Modifies: hasUpRequest, hasDownRequest
     * Effects: Search through people to find if there are any
     *          pending up requests or down requests. Set the
     *          values of hasUpRequest and hasDownRequest appropriately.
     *          This function is used to recalculate requests whenever
     *          the people on this floor are added or removed.
     */
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
