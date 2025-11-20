/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Move.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */
 
#include <cmath>
#include <sstream>
#include <stdio.h>      
#include <stdlib.h>
#include "Move.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;


Move::Move(string commandString) : Move() {
    if (commandString == "") { //check for empty string comes first, to not reference out of bounds 
        isPass = true;
    } else if (commandString.at(0) == 'e' && commandString.at(2) == 'f') {
        elevatorId = commandString.at(1) - '0';
        targetFloor = commandString.at(3) - '0';
    } else if (commandString.at(0) == 'e' && commandString.at(2) == 'p') {
        elevatorId = commandString.at(1) - '0';
        isPickup = true;
    } else if (commandString == "S") {
        isSave = true;
    } else if (commandString == "Q") {
        isQuit = true;
    }
}

bool Move::isValidMove(Elevator elevators[NUM_ELEVATORS]) const {
    if (isPass || isQuit || isSave) {
        return true;
    } else if ((elevatorId >= 0 && elevatorId < NUM_ELEVATORS) 
                && !elevators[elevatorId].isServicing()) {
        if (isPickup) {
            return true;
        } else if (targetFloor != elevators[elevatorId].getCurrentFloor()) {
            return true;
        }
    } else {
        return false;
    }
    return false;
}

void Move::setPeopleToPickup(const string& pickupList, const int currentFloor, 
                             const Floor& pickupFloor) {
    targetFloor = currentFloor;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
    for (int i = 0; i < pickupList.length(); i++) {
        peopleToPickup[i] = pickupList.at(i) - '0';
        totalSatisfaction += MAX_ANGER - pickupFloor.getPersonByIndex(peopleToPickup[i]).getAngerLevel();
        if (abs(pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor() - currentFloor) 
            > abs(targetFloor - currentFloor)) {
            targetFloor = pickupFloor.getPersonByIndex(peopleToPickup[i]).getTargetFloor();
        }
        numPeopleToPickup++;
    }
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Move::Move() {
    elevatorId = -1;
    targetFloor = -1;
    numPeopleToPickup = 0;
    totalSatisfaction = 0;
	isPass = false;
    isPickup = false;
    isSave = false;
    isQuit = false;
}

bool Move::isPickupMove() const {
    return isPickup;
}

bool Move::isPassMove() const {
	return isPass;
}

bool Move::isSaveMove() const {
	return isSave;
}

bool Move::isQuitMove() const {
	return isQuit;
}

int Move::getElevatorId() const {
    return elevatorId;
}

int Move::getTargetFloor() const {
    return targetFloor;
}

int Move::getNumPeopleToPickup() const {
    return numPeopleToPickup;
}

int Move::getTotalSatisfaction() const {
    return totalSatisfaction;
}

void Move::setTargetFloor(int inTargetFloor) {
    targetFloor = inTargetFloor;
}

void Move::copyListOfPeopleToPickup(int newList[MAX_PEOPLE_PER_FLOOR]) const {
    for (int i = 0; i < numPeopleToPickup; ++i) {
        newList[i] = peopleToPickup[i];
    }
}
