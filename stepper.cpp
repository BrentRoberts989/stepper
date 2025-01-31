/***
 * A program to fullstep a stepper motor in C in an extensible way.
 * 
 * Written by Brent Roberts.
 */
#include <stdlib.h>
#include <math.h>
#include "stepper.h"


/**
 * @brief Function to set up a new stepper motor struct, should be used before any other functions from stepper or accessing any of the parts of a STEPPER struct.
 * 
 * @param s The STEPPER struct to be initialized
 * @param setA Function pointer to control the A channel. The int param of this functions should be a 1 or 0 indicating output or no output to the channel.
 * @param setANot Function pointer to control the ANot channel. The int param of this functions should be a 1 or 0 indicating output or no output to the channel.
 * @param setB Function pointer to control the B channel. The int param of this functions should be a 1 or 0 indicating output or no output to the channel.
 * @param setBNot Function pointer to control the BNot channel. The int param of this functions should be a 1 or 0 indicating output or no output to the channel.
 */
void setupStepper(struct STEPPER* s, void (*setA)(int), void (*setANot)(int), void (*setB)(int), void (*setBNot)(int)) {
    s->steps = 0;
    s->setA = setA;
    s->setANot = setANot;
    s->setB = setB;
    s->setBNot = setBNot;
}

/**
 * @brief Get the current steps of the Stepper
 * 
 * @param STEPPER The struct indicating the stepper to get steps from.
 * 
 * @return int The current step number of the motor where 0 is the starting step and clockwise from there is a positive value.
 */
int getCurrentStep(struct STEPPER s) {
    return s.steps;
}

/**
 * @brief Function to make the motor full step to a position
 * 
 * @param targetSteps Steps to move the motor to
 */
void setTargetStep(struct STEPPER* s, int targetSteps) {
   s->targetSteps = targetSteps;
}

/**
 * @brief A function to run every cycle to update a stepper motor with instructions based on it's struct.
 * 
 * @param s The STEPPER struct to update, should be initialized before callthiing function.
 */
void updateStepper(struct STEPPER *s) {
    int stepsToMove = s->targetSteps - s->steps; //calculate direction to move
    
    if (stepsToMove > 0 ) { //Clockwise movement needed
        s->steps++; //updates step location
    } else if (stepsToMove < 0) { //Counter clockwise movement needed
        s->steps--; //updates step location
    } else { //If it's at the target 0 power, Maybe this shouldn't exist if the motor needs to hold due to forces on it
        s->setA(0);
        s->setANot(0);
        s->setB(0);
        s->setBNot(0);
        return;//Skip the moving part of the function
    }

    int currentStep = abs(s->steps % 4); //Modulus limits currentsteps to 0 to 3 and abs ensures it's positive.
    switch(currentStep) {
        case 0:
            s->setA(1); //Set A to on
            s->setANot(0); //Set Anot to off
            s->setB(0); //Set B to off
            s->setBNot(1);//Set Bnot to on
            break;
        case 1:
            s->setA(1); //Set A to on
            s->setANot(0); //Set Anot to off
            s->setB(1); //Set B to on
            s->setBNot(0); //Set Bnot to off
            break;
        case 2:
            s->setA(0); //Set A to off
            s->setANot(1); //Set Anot to on
            s->setB(1); //Set B to on
            s->setA(0); //Set Bnot to off
            break;
        case 3:
            s->setA(0); //Set A to off
            s->setANot(1); //Set Anot to on
            s->setB(0); //Set B to off
            s->setBNot(1); //Set Bnot to on
            break;
        }
}
