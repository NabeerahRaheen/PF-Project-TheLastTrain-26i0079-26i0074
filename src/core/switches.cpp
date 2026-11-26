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







}
// Door lock mechanics, lifts, and cabinet verification without structures
