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

void testMove();
void testMoveIsValidMove();
void testMoveSetPeopleToPickup();
void testFloor();
void testGame();
void testBuilding();

void start_tests() {
    testMove();
    testBuilding();
    //testFloor();
    testGame();
    
    return;
}

// write test functions here
void testGame() {
     return;
}
    
void testBuilding() {
    cout << "Testing Building class\n";

    // testing spawnPerson with an up request from floor 0
    Building b1;
    // turn 0, current 0, target 3
    Person pUp("0f0t3a0");
    b1.spawnPerson(pUp);

    Floor f0 = b1.getFloorByFloorNum(0);
    cout << "Expected numPeople: 1, Actual "
         << f0.getNumPeople() << "\n";
    cout << "Expected hasUpRequest: 1, Actual "
         << f0.getHasUpRequest() << "\n\n";

    // testing tick with Pass move (tests update pass case too)
    Move passMove("");
    int explodedPass = b1.tick(passMove);
    Elevator e0Pass = b1.getElevatorById(0);

    cout << "tick(pass): Expected time: 1, Actual "
         << b1.getTime() << "\n";
    cout << "Expected exploded: 0, Actual "
         << explodedPass << "\n";
    cout << "Expected servicing: 0, Actual "
         << e0Pass.isServicing() << "\n\n";

    // testing tick with Service move (tests update service case too)
    Building b2;
    // send elevator 0 to floor 4
    Move serviceMove("e0f4");
    b2.tick(serviceMove);

    Elevator e0Serv = b2.getElevatorById(0);
    cout << "tick(service e0f4): Expected time: 1, Actual "
         << b2.getTime() << "\n";
    cout << "Expected servicing: 1, Actual "
         << e0Serv.isServicing() << "\n";
    cout << "Expected targetFloor: 4, Actual "
         << e0Serv.getTargetFloor() << "\n\n";

    // testing tick with Pickup move (tests update pickup case too)
    Building b3;
    // two people on floor 0: one to 3, one to 5
    Person pA("0f0t3a0");
    Person pB("0f0t5a0");
    b3.spawnPerson(pA);
    b3.spawnPerson(pB);

    Floor beforePickup = b3.getFloorByFloorNum(0);
    cout << "Before pickup, Expected numPeople: 2, Actual "
         << beforePickup.getNumPeople() << "\n";

    Move pickupMove("e0p");
    Floor pickupFloor = b3.getFloorByFloorNum(0);
    // pick up just index 0
    pickupMove.setPeopleToPickup("0", 0, pickupFloor);

    int explodedPickup = b3.tick(pickupMove);

    Floor afterPickup = b3.getFloorByFloorNum(0);
    Elevator e0Pick = b3.getElevatorById(0);

    cout << "tick(pickup): Expected numPeople: 1, Actual "
         << afterPickup.getNumPeople() << "\n";
    cout << "Expected servicing: 1, Actual "
         << e0Pick.isServicing() << "\n";
    cout << "Expected exploded: 0, Actual "
         << explodedPickup << "\n";
    cout << "Expected elevator targetFloor == Move targetFloor: "
         << "Move " << pickupMove.getTargetFloor()
         << ", Elevator " << e0Pick.getTargetFloor() << "\n\n";
    return;
}

void testMove() {
    Elevator testElevators[3];
    Move testMove("e1f4");
    Move test2("e1p");
    Move test3("");
    Floor testFloor;
    Person testPerson("7f0t5a3");
    cout << "Testing non-default Move constructor\nExpected: 14\nActual: " 
    << testMove.getElevatorId() << testMove.getTargetFloor() << endl << endl;
    
    cout << "Expecting: 1 1. Actual: " << test2.getElevatorId() << " " << test2.isPickupMove() << endl << endl;

    cout << "Expecting: 1. Actual: " << test3.isPassMove() << endl << endl;

    cout << "Testing isValidMove()\nExpecting: 1. Actual: " << test2.isValidMove(testElevators) << endl;
    testMove.setTargetFloor(0);
    cout << "Expecting: 0. Actual: " << testMove.isValidMove(testElevators) << endl;

    testFloor.addPerson(testPerson, 5);
    test2.setPeopleToPickup("0", 0, testFloor);
    cout << "Testing setPeopleToPickup()\nExpecting: 5. Actual: " << test2.getTargetFloor() << endl;
}

void testFloor() {
    Floor test;
    Person testP;
    Person test2;
    Person test3;
    Person test4;
    Person test5;
    Person test6;
    Person test7;
    int testInts[4] = {2, 4,1,3};
    test.addPerson(testP, 1);
    cout << "Testing add person.\nExpected: 1. Actual: " << test.getHasUpRequest() << endl << endl;

    cout<< "Testing remove.";
    test.addPerson(test2, 1);
    test.addPerson(test3, 1);
    test.addPerson(test4, 1);
    test.addPerson(test5, 1);
    
    test.addPerson(test6, 1);
    test.addPerson(test7, 1);
    test.removePeople(testInts, 4);
    cout << test.getNumPeople() << endl;
    test.printFloorPickupMenu(cout);
}