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

void renderDashboard(int playerFloor, int playerRoom, int energy, int time, int score, const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, int emergencyTripsLeft)
{
    printHeader ("Status");
    cout << "Location(Floor-Room) F: "<< playerFloor << " -R " << playerRoom << endl;
    cout << "Energy: " << energy << " / " << MAX_ENERGY << endl;
    cout << "Time: " << time << " / " << MAX_TIME << endl;
    cout << "Score: " << score << endl;
    cout << "Emergency Lift Trips: " << emergencyTripsLeft << endl;
    cout << "Items Left in Backpack: (" << inventoryCount << " / " << MAX_INVENTORY_CAPACITY << " ):";
    if (inventoryCount == 0)
    {
        cout << "Inventory is Empty";
    }
    else
    {
        for (int j = 0; j < inventoryCount; j++)
        {
            cout << inventory[j] << " ";
        }
    }
    cout << endl;
}
void renderRoomDetails(int floor, int room, const char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM], int entityCount)
{



}

