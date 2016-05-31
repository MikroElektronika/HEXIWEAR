/**
 * keynetik global variables
 */

#pragma once

#include "keynetik_types.h"

extern activitylevel_t
  keynetikActivityLevel;

/*
* Pedometer statistics since last KeynetikInitialize,
* populated by the latest call to KeynetikHandleIncomingEvent
 */

// Step count
extern unsigned int keynetikStepCount;

// Distance covered (in meters)
extern unsigned int keynetikDistance;

// Average speed (in meters per hour)
extern unsigned short keynetikSpeed;

// Calories burned
extern unsigned int keynetikCalories;
