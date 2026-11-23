// Terminal UI and dashboard rendering using primitive parameters

#include "viewer_iface.h"
#include "util.h"
#include <iostream>
using namespace std;

void renderObjectivesChecklist(const bool objectives[NUM_OBJECTIVES])
{
    printHeader ("MISSION OBJECTIVES");
    const char* obj_names[NUM_OBJECTIVES] = {"Collect Master Key", "Find Digit Clue 4", "Find Digit Clue 2", "Find Digit Clue 7", "Unlock Cabinet", "Find Train Key", "Collect Fuse", "Install Fuse", "Collect Lift Pass", "Activate Lift 2", "Rescue Passenger", "Collect Cat Carrier", "Secure Cat", "Prepare Train", "Mission Won", "Mission Failed"};
    for (int i = 0; i < NUM_OBJECTIVES; i++ )
    {
        if (objectives[i])
        {
            cout << "[X] " << obj_names[i] << endl;
        }
        else
        {
            cout << "[ ] " << obj_names[i] << endl;
        }
    }
}

