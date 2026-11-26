#include "physics.h"
#include "util.h"

// Movement validation and resource adjustments without structures
void applyScoreDelta(int& score, int deltaScore){
    score+=deltaScore;
}
void applyResourceDelta(int& energy, int& time, int deltaEnergy, int deltaTime){
    energy+=deltaEnergy;
    time+=deltaTime;
    energy=clampInt(energy,0,MAX_ENERGY);
    time=clampInt(time,0,MAX_TIME);
}
bool hasItem(const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount, char itemSymbol){
    for(int i=0;i<inventoryCount;i++){
        if(inventory[i]==itemSymbol){
            return true;
        }
    }
    return false;
}
bool addItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol){
    if(inventoryCount>=MAX_INVENTORY_CAPACITY){
        return false;
    }
    inventoryCount++;
    inventory[inventoryCount-1]=itemSymbol;
    return true;
        
    }
    bool removeItem(char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount, char itemSymbol){
        int ind=-1;
    for(int i=0;i<inventoryCount;i++){
        if(inventory[i]==itemSymbol){
            ind=i;
        }
    }
    if(ind==-1){
    return false;
   
}
   inventoryCount--;
    for(int i=ind;i<inventoryCount;i++){
        inventory[i]=inventory[i+1];
    }


    return true;
}
bool isDirectlyConnected(int fromF, int fromR, int toF, int toR,
                         const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                         char& outConnType){
                            // validation check 
                            if(!((0<fromF &&  fromF<=NUM_FLOORS) && (0<fromR && fromR <=ROOMS_PER_FLOOR) && (0<toF && toF <=NUM_FLOORS) && (0<toR && toR <=ROOMS_PER_FLOOR))){
                                return false;
                            }
                             if ( fromF==toF && fromR == toR){
                               return false;
                             }
                             // neighbour
                             if(fromF==toF){
                             int smaller=0;
                             if(toR<fromR){
                                smaller=toR;
                             }else{
                                smaller=fromR;
                             }
                            if((toR-fromR)!=1 && (toR-fromR)!=-1){
                                return false;
                            }

                          int gi=smaller-1;
                          char l=horizontalConn[fromF-1][gi];
                          if(l==CONN_NONE || l==CONN_SOLID_WALL){
                            return false;
                          }else{
                            outConnType=l;
                            return true;
                          }

                         }
                        //  links within rooms(stairs+lifts)
                        int arr[10][4]={{1,1,2,1},{2,1,3,1},{4,1,5,1},{1,2,2,2},
                                        {1,2,2,3},{1,3,2,2},{1,3,2,3},{2,4,4,4},{2,4,5,4},
                                        {4,4,5,4}};
                        char linkage[10]={CONN_STAIRS,CONN_STAIRS,CONN_STAIRS,CONN_LIFT1,CONN_LIFT1,CONN_LIFT1,CONN_LIFT1,CONN_LIFT2,CONN_LIFT2,CONN_LIFT2}; 
             for(int i=0;i<10;i++){
             if((fromF==arr[i][0] && fromR==arr[i][1] && toF==arr[i][2] && toR==arr[i][3]) || (fromF==arr[i][2] &&  fromR==arr[i][3] && toF==arr[i][0] && toR==arr[i][1])){
                outConnType = linkage[i];
                return true;
             }             
             
                        }
                        return false;
                    }
                    bool canTraverse(int targetFloor, int targetRoom, char connType,
                 const char inventory[MAX_INVENTORY_CAPACITY], int inventoryCount,
                 int emergencyTripsLeft, bool lift2Operational){
                   (void) targetFloor;
                   (void)targetRoom;
                    if((connType==CONN_LOCKED_DOOR)  ){
                      return  hasItem(inventory,inventoryCount,'<');
                        
                    }
                        else if((connType== CONN_LIFT2) ){
                           return (lift2Operational || emergencyTripsLeft>0) ;
                       
                    }else{
                        return true;
                    }
                 }
    
