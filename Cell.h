#include "orientation.h"

class Cell{
  private:
    int NumOfRocks_;
    bool containsRock_ = false;
    bool roadNorth_ =false;
    bool roadEast_ =false;
    bool roadSouth_ =false;
    bool roadWest_ =false;

  public:
    void SetNumOfRock(int rocks){NumOfRocks_ =rocks; }
    int GetNumOfRocks(){return NumOfRocks_;}

    void setContainsRock(bool containRock){containsRock_= true;}
    bool containRock(){return containsRock_;}

    bool containsRoadNorth()const {return roadNorth_;}
    bool containsRoadEast()const {return roadEast_;}
    bool containsRoadSouth()const {return roadSouth_;}
    bool containsRoadWest()const {return roadWest_;}
    
    void AddRock(){
      containsRock_ = true;
    }

    void AddRoad(Direction roadDirection){
      switch(roadDirection){
        case Direction::North:{
          roadNorth_ = true;
          break;
        }
        case Direction::East:{
          roadEast_ = true;
          break;
        }
        case Direction::South:{
          roadSouth_ = true;
          break;
        }
        case Direction::West:{
          roadWest_ = true;
          break;
        }
      }
    }

};