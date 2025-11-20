/*
 * Copyright 2023 University of Michigan EECS183
 *
 * Person.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * <#Names#>
 * <#Uniqnames#>
 *
 * Final Project - Elevators
 */

#include "Person.h"
#include <iostream>
#include <cmath>
#include <sstream>

using namespace std;

    /*
     * Requires: inputString is correctly formatted
     * Modifies: turn, currentFloor, targetFloor, angerLevel
     * Effects:  Parses input_string to set member variables
     *           An example of input_string is "7f4t8a3".
    */
Person::Person(string inputString) : Person() {
    turn = inputString.at(0) - '0';
    currentFloor = inputString.at(2) - '0';
    targetFloor = inputString.at(4) - '0';
    angerLevel = inputString.at(6) - '0';
}

bool Person::tick(int currentTime) {
    //TODO: Implement tick

    //Returning false to prevent compilation error
    return false;
}

void Person::print(ostream &outs) {    
    //TODO: Implement print
}

//////////////////////////////////////////////////////
////// DO NOT MODIFY ANY CODE BENEATH THIS LINE //////
//////////////////////////////////////////////////////

Person::Person() {
    turn = 0;
    currentFloor = 0;
    targetFloor = 0;
    angerLevel = 0;
}

int Person::getTurn() const {
    return turn;
}

int Person::getCurrentFloor() const {    
    return currentFloor;
}

int Person::getTargetFloor() const {    
    return targetFloor;
}

int Person::getAngerLevel() const {    
    return angerLevel;
}

ostream& operator<< (ostream& outs, Person p)
{
    p.print(outs);
    return outs;
}
