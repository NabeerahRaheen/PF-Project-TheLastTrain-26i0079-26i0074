#include "level.h"
#include "util.h"
#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
using namespace std;
const char* getEntityName(char entitySymbol){
    switch(entitySymbol){
        case ENT_CABINET_TRAIN_KEY:
        return"Cabinet";
        case ENT_MASTER_KEY:
        return"Master Key";
        case ENT_ENERGY_PACK:
        return"Energy Packs";
        case ENT_EMERGENCY_TOOLKIT:
        return"Emergency Toolkit";
        case ENT_CLUE_4:
        return"Clue Digit 4";
        case ENT_FUSE:
        return"Fuse";
        case ENT_CAT:
        return"Cat";
        case ENT_CONTROL_PANEL:
        return"Control panel";
        case ENT_LIFT_PASS:
        return"Lift pass";
        case ENT_PASSENGER:
        return"injured passenger";
        case ENT_MEDICAL_KIT:
        return"medical kit";
        case ENT_EMERGENCY_CARD:
        return"emergency access card";
        case ENT_CLUE_2:
        return"clue digit 2";
        case ENT_CLUE_7:
        return"clue digit 7";
        case ENT_CAT_CARRIER:
        return"cat carrier";
        case ENT_OBSERVATION_TOKEN:
        return"observation token";
        default:
        return"Not defined";

    }
}
bool validateStartingRoom(int startFloor, int startRoom,
                          const char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1]){
                            // no need of it rn but do it later 
                            (void)horizontalConn;
                            if(startFloor<1 || startFloor>NUM_FLOORS){
                            return false;
                            }
                            if(startRoom<1 || startRoom>ROOMS_PER_FLOOR){
                                return false;
                            }
                            return true;
}
bool loadInitialState(const char* filename,
                      int& playerFloor, int& playerRoom,
                      int& energy, int& time, int& score,
                      char inventory[MAX_INVENTORY_CAPACITY], int& inventoryCount,
                      bool objectives[NUM_OBJECTIVES], int& emergencyTripsLeft){
                        ifstream file(filename);
                        if(!file.is_open()){
                            cout<<"file is not opened. Error!";
                            return false;
                        }
                        energy=INITIAL_ENERGY;
                        time=INITIAL_TIME;
                        score=INITIAL_SCORE;
                        inventoryCount=0;
                        playerFloor=1;
                        playerRoom=1;
                        emergencyTripsLeft=0;
                        for(int i=0;i<NUM_OBJECTIVES;i++){
                            objectives[i]=false;
                        }
                        (void)inventory;
                        // reading file
                      char key[MAX_NAME_LEN];        
                        char value[MAX_NAME_LEN];     

                        while(file>>key>>value){
                            if(stringEquals(key,"INITIAL_ENERGY:")){      
                                energy=atoi(value);                        
                            }
                            else if(stringEquals(key,"INITIAL_TIME:")){
                                time=atoi(value);
                            }
                            else if(stringEquals(key,"INITIAL_SCORE:")){
                                score=atoi(value);
                            }
                            else if(stringEquals(key,"START_ROOM:")){
                               

                            }

                        }
                        file.close();
                        cout<<"enter the room(1-4) where you want to go=";
                        cin>>playerRoom;
                        
                            while(cin.fail() || (!(playerRoom<=4 && playerRoom>=1))){
                                if(cin.fail()){
                                    cin.clear();
                                    cin.ignore(1000,'\n');
                                }
                                cout<<"INVALID ROOM!"<<endl;
                                cout<<"enter the room(1-4) where you want to go=";
                                cin>>playerRoom;
                            }
                            cout<<"enter the floor(1-5) where you want to go=";
                            cin>>playerFloor;
                            while(cin.fail() || (!(playerFloor<=5 && playerFloor>=1))){
                                  if(cin.fail()){
                                    cin.clear();
                                    cin.ignore(1000,'\n');
                                }
                                 cout<<"INVALID Floor!"<<endl;
                                 cout<<"enter the floor(1-5) where you want to go=";
                                 cin>>playerFloor;
                        
}       
return true;                     
                      }
bool loadBuildingMap(const char* filename,
                     char horizontalConn[NUM_FLOORS][ROOMS_PER_FLOOR - 1],
                     char roomEntities[NUM_FLOORS][ROOMS_PER_FLOOR][MAX_ENTITIES_PER_ROOM],
                     int entityCounts[NUM_FLOORS][ROOMS_PER_FLOOR]){
    ifstream file(filename);
    if(!file.is_open()){
        return false;
    }
    
    for(int i=0;i<NUM_FLOORS;i++){
        for(int j=0;j<(ROOMS_PER_FLOOR-1);j++){
            horizontalConn[i][j]=CONN_NONE;
        }
    }
    for(int i=0;i<NUM_FLOORS;i++){
        for(int j=0;j<ROOMS_PER_FLOOR;j++){
            for(int k=0;k<MAX_ENTITIES_PER_ROOM;k++){
                roomEntities[i][j][k]=ENT_NONE;
            }
        }
    }
    for(int i=0;i<NUM_FLOORS;i++){
        for(int j=0;j<ROOMS_PER_FLOOR;j++){
            entityCounts[i][j]=0;
        }
    }
// map reading
    char nameLine[MAX_LINE_LEN];
    char itemLine[MAX_LINE_LEN];
    char trash[MAX_LINE_LEN];

    
    if(!file.getline(trash,MAX_LINE_LEN)) return false;
    if(!file.getline(trash,MAX_LINE_LEN)) return false;

    
    for(int floor=NUM_FLOORS-1; floor>=0; floor--){
        if(!file.getline(nameLine,MAX_LINE_LEN)) return false;  
        if(!file.getline(itemLine,MAX_LINE_LEN)) return false;  
        if(!file.getline(trash,MAX_LINE_LEN))    return false;  

       
        int labelPos[ROOMS_PER_FLOOR];
        int found=0;
        for(int i=0; nameLine[i]!='\0' && found<ROOMS_PER_FLOOR; i++){
            if(nameLine[i]=='F'){
                labelPos[found]=i;
                found++;
            }
        }
        if(found!=ROOMS_PER_FLOOR) return false;   

        
        for(int g=0; g<ROOMS_PER_FLOOR-1; g++){
            char c=nameLine[labelPos[g+1]-2];
            if(c=='1'){                     
                horizontalConn[floor][g]=CONN_NONE;
            }
            else{
                horizontalConn[floor][g]=c;
            }
        }

        
        int len=0;
        while(itemLine[len]!='\0') len++;

        for(int r=0; r<ROOMS_PER_FLOOR; r++){
            int i=labelPos[r]-1;
            while(i<len && itemLine[i]!='|'){
                if(itemLine[i]!=' ' && entityCounts[floor][r]<MAX_ENTITIES_PER_ROOM){
                    roomEntities[floor][r][entityCounts[floor][r]]=itemLine[i];
                    entityCounts[floor][r]++;
                }
                i++;
            }
        }
    }
    file.close();
    return true;
}


                        
                        
                      
                          
// Modular implementation using primitive arrays for map parsing and verification
