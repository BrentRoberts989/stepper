#ifndef stepper.h
#define stepper.h
// Header file for stepper motor demo

/**
 * @brief Stepper struct to contain needed variables to control a stepper motor
 * 
 * @todo add degrees to step conversion
 */
struct STEPPER
{
    // I think this is the best way to store data values for controlling the stepper motor but it will have access issues

    //Float to track steps
    int steps;

    //Float to track the current target
    int targetSteps;


    //Function pointers to control each channel. The int param of each these functions should be a 1 or 0 indicating output or no output to the channel.
    void (*setA)(int);
    void (*setANot)(int);
    void (*setB)(int);
    void (*setBNot)(int);

};

/**
 * @brief Function to set up a new stepper motor struct, should be used before any other functions from stepper or accessing any of the parts of a STEPPER struct.
 * 
 * @param s The STEPPER struct to be initialized
 * @param setA Function pointer to control the A channel. The int param of this functions should be a 1 or 0 indicating output or no output to the channel.
 * @param setANot Function pointer to control the ANot channel. The int param of this functions should be a 1 or 0 indicating output or no output to the channel.
 * @param setB Function pointer to control the B channel. The int param of this functions should be a 1 or 0 indicating output or no output to the channel.
 * @param setBNot Function pointer to control the BNot channel. The int param of this functions should be a 1 or 0 indicating output or no output to the channel.
 */
void setupStepper(struct STEPPER* s, void (*setA)(int), void (*setANot)(int), void (*setB)(int), void (*setBNot)(int));

/**
 * @brief Get the current steps of the Stepper
 * 
 * @param STEPPER The struct indicating the stepper to get steps from.
 * 
 * @return float The current step number of the motor where 0 is the starting step.
 */
int getCurrentStep(struct STEPPER s);

/**
 * @brief Function to make the motor full step to a position
 * 
 * @param targetSteps Steps to move the motor to
 */
void setTargetStep(struct STEPPER* s, int targetSteps);

/**
 * @brief A function to run every cycle to update a stepper motor with instructions based on it's struct.
 * 
 * @param s The STEPPER struct to update, should be initialized before callthiing function.
 */
void updateStepper(struct STEPPER *s);

#endif