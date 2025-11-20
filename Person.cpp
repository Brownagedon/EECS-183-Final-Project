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

Person::Person(string inputString) {

    int fPos = inputString.find('f');
    int tPos = inputString.find('t');
    int aPos = inputString.find('a');

    // each part appears exactly once in valid input
    turn = stoi(inputString.substr(0, fPos));
    currentFloor = stoi(inputString.substr(fPos + 1, tPos - (fPos + 1)));
    targetFloor = stoi(inputString.substr(tPos + 1, aPos - (tPos + 1)));
    angerLevel = stoi(inputString.substr(aPos + 1));
}

bool Person::tick(int currentTime) {
    // every few ticks, anger goes up by 1
    if (currentTime % TICKS_PER_ANGER_INCREASE == 0) {
        angerLevel++;
    }
    // return whether this person has exploded
    return (angerLevel >= MAX_ANGER);
}

void Person::print(ostream &outs) {
    // print everything except the turn (autograder expects this format)
    outs << "f" << currentFloor
         << "t" << targetFloor
         << "a" << angerLevel;
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
