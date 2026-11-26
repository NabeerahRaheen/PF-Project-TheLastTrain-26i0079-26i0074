#include "switches.h"
#include "util.h"
#include <iostream>
using namespace std;

    bool canUseLift1(int fromFloor, int toFloor)
    {
        bool allowed = false;
        if(fromFloor == 1 && toFloor == 2 )
          { 
            allowed = true;
          }
         if(fromFloor == 2 && toFloor == 1)
          { 
            allowed = true;
          }
        return allowed;
    }

    bool canUseLift2(int fromFloor, int toFloor, bool lift2Operational, int emergencyTripsLeft)
    {
        bool lift2allowed = false;
        if ((fromFloor == 2 || fromFloor == 4 ||fromFloor == 5)&&(toFloor == 2 || toFloor == 4 || toFloor == 5))
        {
            if(lift2Operational == true ||emergencyTripsLeft >= 1)
                {
                    lift2allowed = true;
                }
        }
        if(fromFloor == toFloor)
        {
            lift2allowed = false;
        }

        return lift2allowed;
    
    }









// Door lock mechanics, lifts, and cabinet verification without structures
