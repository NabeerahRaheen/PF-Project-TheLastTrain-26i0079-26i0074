#include "switches.h"
#include "util.h"
#include "physics.h"
#include <iostream>
using namespace std;

// Door lock mechanics, lifts, and cabinet verification without structures

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

    bool unlockFloor3Door(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount)
    {
        bool canOpen = hasItem(inventory, inventoryCount, ENT_MASTER_KEY );
        return canOpen;
    }

    bool installFuseControlPanel(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
        bool objectives[NUM_OBJECTIVES], int& score)
    {
        bool hasFuse = hasItem(inventory, inventoryCount, ENT_FUSE  );
        if (hasFuse == false)
        {
            return false;
        }
        else
        {
            bool fuseFound = removeItem(inventory, inventoryCount, ENT_FUSE);
            applyScoreDelta(score, SCORE_INSTALL_FUSE);
            if(fuseFound == true)
            {
                objectives[OBJ_FUSE_INSTALLED]=fuseFound;        
            }
  
            bool hasPass =  hasItem(inventory, inventoryCount, ENT_LIFT_PASS); 
            if (hasPass == true)
            {
                objectives[OBJ_LIFT2_ACTIVE]=hasPass;  
            }
            return true;
        }
    }

    bool verifyCabinetCode(const char* enteredCode, const bool objectives[NUM_OBJECTIVES])
    {

        bool correctCode = stringEquals(enteredCode, "427");
        if (correctCode == true)
          {
             if (objectives[OBJ_CLUE_4] == true)
              { 
                if (objectives[OBJ_CLUE_2] == true)
                   {
                     if (objectives[OBJ_CLUE_7] == true)
                            {
                               return true;
                            }
                            else
                            {
                                return false;
                            }
                    }
                    else 
                    {
                       return false; 
                    }
              }
             else
            {
                return false;
            }
          }
          return false;
    }

