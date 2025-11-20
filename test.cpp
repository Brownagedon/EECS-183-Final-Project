/*
 * Copyright 2023 University of Michigan EECS183
 *
 * test.cpp
 * Project UID 848fee0125dbb5eb53ed294f20dbef81
 *
 * Final Project - Elevators
 */
 
////////////////////////////////////////////////
// You will submit test.cpp to the autograder //
// FOR LAB 8, but NOT the final project Core  //
////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <string>
#include "AI.h"
#include "Building.h"
#include "BuildingState.h"
#include "Elevator.h"
#include "Floor.h"
#include "Game.h"
#include "Move.h"
#include "Person.h"
#include "SatisfactionIndex.h"
#include "Utility.h"

using namespace std;

void testMoveConstructor();
void testMoveIsValidMove();
void testMoveSetPeopleToPickup();
void testFloor();

void start_tests() {
    testMoveConstructor();
    testFloor();
    
    return;
}

// write test functions here

void testMoveConstructor() {
    Move testMove("e1f4");
    Move test2("e1p");
    cout << "Testing non-default Move constructor\nExpected: 14\nActual: " 
    << testMove.getElevatorId() << testMove.getTargetFloor() << endl << endl;
    
    cout << "Expecting: 1 1. Actual: " << test2.getElevatorId() << " " << test2.isPickupMove() << endl << endl;
}

void testFloor() {
    Floor test;
    Person testP;
    test.addPerson(testP, 1);
    cout << "Testing add person.\nExpected: 1. Actual: " << test.getHasUpRequest() << endl;

    test.tick(1);
}