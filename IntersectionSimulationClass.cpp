#include <iostream>
#include <string>
#include <fstream>
using namespace std;

#include "IntersectionSimulationClass.h"
#include "random.h"
#include "constants.h"

void IntersectionSimulationClass::readParametersFromFile(
     const string &paramFname
     )
{
  bool success = true;;
  ifstream paramF;

  paramF.open(paramFname.c_str());

  //Check that the file was able to be opened...
  if (paramF.fail())
  {
    success = false;
    cout << "ERROR: Unable to open parameter file: " << paramFname << endl;
  }
  else
  {
    //Now read in all the params, according to the specified format of
    //the text-based parameter file.
    if (success)
    {
      paramF >> randomSeedVal;
      if (paramF.fail() ||
          randomSeedVal < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set random generatsor seed" << endl;
      }
    }

    if (success)
    {
      paramF >> timeToStopSim;
      if (paramF.fail() ||
          timeToStopSim <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set simulation end time" << endl;
      }
    }

    if (success)
    {
      paramF >> eastWestGreenTime >> eastWestYellowTime;
      if (paramF.fail() ||
          eastWestGreenTime <= 0 ||
          eastWestYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east-west times" << endl;
      }
    }

    if (success)
    {
      paramF >> northSouthGreenTime >> northSouthYellowTime;
      if (paramF.fail() ||
          northSouthGreenTime <= 0 ||
          northSouthYellowTime <= 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north-south times" << endl;
      }
    }

    if (success)
    {
      paramF >> eastArrivalMean >> eastArrivalStdDev;
      if (paramF.fail() ||
          eastArrivalMean <= 0 ||
          eastArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set east arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> westArrivalMean >> westArrivalStdDev;
      if (paramF.fail() ||
          westArrivalMean <= 0 ||
          westArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set west arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> northArrivalMean >> northArrivalStdDev;
      if (paramF.fail() ||
          northArrivalMean <= 0 ||
          northArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set north arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> southArrivalMean >> southArrivalStdDev;
      if (paramF.fail() ||
          southArrivalMean <= 0 ||
          southArrivalStdDev < 0)
      {
        success = false;
        cout << "ERROR: Unable to read/set south arrival distribution" << endl;
      }
    }

    if (success)
    {
      paramF >> percentCarsAdvanceOnYellow;
      if (paramF.fail() || 
          percentCarsAdvanceOnYellow < 0 ||
          percentCarsAdvanceOnYellow > 100)
      {
        success = false;
        cout << "ERROR: Unable to read/set percentage yellow advance" << endl;
      }

      //Use the specified seed to seed the random number generator
      setSeed(randomSeedVal);
    }

    paramF.close();
  }

  //Let the caller know whether things went well or not by printing the
  if (!success)
  {
    cout << "ERROR: Parameter file was NOT read in successfully, so the " <<
            "simulation is NOT setup properly!" << endl;
    isSetupProperly = false;
  }
  else
  {
    cout << "Parameters read in successfully - simulation is ready!" << endl;
    isSetupProperly = true;
  }
}

void IntersectionSimulationClass::printParameters() const
{
  cout << "===== Begin Simulation Parameters =====" << endl;
  if (!isSetupProperly)
  {
    cout << "  Simulation is not yet properly setup!" << endl;
  }
  else
  {
    cout << "  Random generator seed: " << randomSeedVal << endl;
    cout << "  Simulation end time: " << timeToStopSim << endl;

    cout << "  East-West Timing -" <<
            " Green: " << eastWestGreenTime << 
            " Yellow: " << eastWestYellowTime <<
            " Red: " << getEastWestRedTime() << endl;

    cout << "  North-South Timing -" <<
            " Green: " << northSouthGreenTime << 
            " Yellow: " << northSouthYellowTime <<
            " Red: " << getNorthSouthRedTime() << endl;

    cout << "  Arrival Distributions:" << endl;
    cout << "    East - Mean: " << eastArrivalMean << 
            " StdDev: " << eastArrivalStdDev << endl;
    cout << "    West - Mean: " << westArrivalMean << 
            " StdDev: " << westArrivalStdDev << endl;
    cout << "    North - Mean: " << northArrivalMean << 
            " StdDev: " << northArrivalStdDev << endl;
    cout << "    South - Mean: " << southArrivalMean << 
            " StdDev: " << southArrivalStdDev << endl;

    cout << "  Percentage cars advancing through yellow: " <<
            percentCarsAdvanceOnYellow << endl;
  }
  cout << "===== End Simulation Parameters =====" << endl;
}

void IntersectionSimulationClass::scheduleArrival(
     const string &travelDir
     )
{
  int inArrTime = 0;
  int inArrType = EVENT_UNKNOWN;

  if (travelDir == EAST_DIRECTION)
  {
    inArrTime = currentTime 
                  + getPositiveNormal(eastArrivalMean, eastArrivalStdDev);
    inArrType = EVENT_ARRIVE_EAST;
  }
  else if (travelDir == WEST_DIRECTION)
  {
    inArrTime = currentTime 
                  + getPositiveNormal(westArrivalMean, westArrivalStdDev);
    inArrType = EVENT_ARRIVE_WEST;
  }
  else if (travelDir == NORTH_DIRECTION)
  {
    inArrTime = currentTime 
                  + getPositiveNormal(northArrivalMean, northArrivalStdDev);
    inArrType = EVENT_ARRIVE_NORTH;
  }
  else if (travelDir == SOUTH_DIRECTION)
  {
    inArrTime = currentTime 
                  + getPositiveNormal(southArrivalMean, southArrivalStdDev);
    inArrType = EVENT_ARRIVE_SOUTH;
  }
  
  EventClass inArrival(inArrTime, inArrType);
  cout << "Time: " << currentTime << " Scheduled "
       << inArrival << endl;
  eventList.insertValue(inArrival);
}

void IntersectionSimulationClass::scheduleLightChange(
     )
{
  int inLightChangeTime = 0;
  int inLightChangeType = EVENT_UNKNOWN;
  int lightCycleTime = eastWestGreenTime + eastWestYellowTime
                       + northSouthGreenTime + northSouthYellowTime;
  if (currentTime % lightCycleTime < eastWestGreenTime)
  {
    // Integer division 
    inLightChangeTime = currentTime / lightCycleTime * lightCycleTime
                        + eastWestGreenTime;
    inLightChangeType = EVENT_CHANGE_YELLOW_EW;
  }
  else if (currentTime % lightCycleTime 
           < (eastWestGreenTime + eastWestYellowTime))
  {
    inLightChangeTime = currentTime / lightCycleTime * lightCycleTime
                        + (eastWestGreenTime + eastWestYellowTime);
    inLightChangeType = EVENT_CHANGE_GREEN_NS;
  }
  else if (currentTime % lightCycleTime 
           < (eastWestGreenTime + eastWestYellowTime + northSouthGreenTime))
  {
    inLightChangeTime = currentTime / lightCycleTime * lightCycleTime
                        + (eastWestGreenTime + eastWestYellowTime 
                        + northSouthGreenTime);
    inLightChangeType = EVENT_CHANGE_YELLOW_NS;
  }
  else 
  {
    inLightChangeTime = currentTime / lightCycleTime * lightCycleTime
                        + (eastWestGreenTime + eastWestYellowTime 
                        + northSouthGreenTime + northSouthYellowTime);
    inLightChangeType = EVENT_CHANGE_GREEN_EW;
  }

  EventClass inLightChange(inLightChangeTime, inLightChangeType);
  cout << "Time: " << currentTime << " Scheduled "
       << inLightChange << endl;
  cout << endl;
  eventList.insertValue(inLightChange);
}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
  EventClass currentEvent;
  bool isEventWaiting = true;

  isEventWaiting = eventList.removeFront(currentEvent);
  currentTime = currentEvent.getTimeOccurs();
    
  // next event is larger than the simulation time
  if (currentTime > timeToStopSim)
  {
    cout << "Next event occurs AFTER the simulation end time ("
         << currentEvent << ")!" << endl;
    return (false);
  }
  cout << "Handling " << currentEvent << endl;
  if (currentEvent.getType() == EVENT_ARRIVE_EAST) 
  {
    CarClass inCar(EAST_DIRECTION, currentTime);
    eastQueue.enqueue(inCar);

    cout << "Time: " << currentTime;
    cout << " Car #" << inCar.getId()
         << " arrives east-bound - queue length: " 
         << eastQueue.getNumElems() << endl;
    scheduleArrival(EAST_DIRECTION);
    cout << endl;

    if (eastQueue.getNumElems() > maxEastQueueLength)
    {
      maxEastQueueLength = eastQueue.getNumElems();
    }
    return (true);
  }
  else if (currentEvent.getType() == EVENT_ARRIVE_WEST)
  {
    CarClass inCar(WEST_DIRECTION, currentTime);
    westQueue.enqueue(inCar);
    
    cout << "Time: " << currentTime;
    cout << " Car #" << inCar.getId()
         << " arrives west-bound - queue length: " 
         << westQueue.getNumElems() << endl;
    scheduleArrival(WEST_DIRECTION);
    cout << endl;

    if (westQueue.getNumElems() > maxWestQueueLength)
    {
      maxWestQueueLength = westQueue.getNumElems();
    }
    return (true);
  }
  else if (currentEvent.getType() == EVENT_ARRIVE_NORTH)
  {
    CarClass inCar(NORTH_DIRECTION, currentTime);
    northQueue.enqueue(inCar);
    
    cout << "Time: " << currentTime;
    cout << " Car #" << inCar.getId()
         << " arrives north-bound - queue length: " 
         << northQueue.getNumElems() << endl;
    scheduleArrival(NORTH_DIRECTION);
    cout << endl;

    if (northQueue.getNumElems() > maxNorthQueueLength)
    {
      maxNorthQueueLength = northQueue.getNumElems();
    }
    return (true);
  }
  else if (currentEvent.getType() == EVENT_ARRIVE_SOUTH)
  {
    CarClass inCar(SOUTH_DIRECTION, currentTime);
    southQueue.enqueue(inCar);
    
    cout << "Time: " << currentTime;
    cout << " Car #" << inCar.getId()
         << " arrives south-bound - queue length: " 
         << southQueue.getNumElems() << endl;
    scheduleArrival(SOUTH_DIRECTION);
    cout << endl;

    if (southQueue.getNumElems() > maxSouthQueueLength)
    {
      maxSouthQueueLength = southQueue.getNumElems();
    }
    return (true);
  }
  // start cases for light change event
  else if (currentEvent.getType() == EVENT_CHANGE_YELLOW_EW)
  {
    CarClass outCarEast;
    int numAdvCarEastGreen = 0;
    CarClass outCarWest;
    int numAdvCarWestGreen = 0;

    bool isCarWaitingEastBound = true;
    bool isCarWaitingWestBound = true; 
 
    cout << "Advancing cars on east-west green" << endl;

    for (int i = 0; i < eastWestGreenTime; i++)
    {
      isCarWaitingEastBound = eastQueue.dequeue(outCarEast); 
      if (isCarWaitingEastBound)
      {
        cout << "  Car #" << outCarEast.getId() 
           << " advances east-bound" << endl; 
        numAdvCarEastGreen++;
      }
    }
    for (int i = 0; i < eastWestGreenTime; i++)
    {
      isCarWaitingWestBound = westQueue.dequeue(outCarWest);  
      if (isCarWaitingWestBound)
      {
        cout << "  Car #" << outCarWest.getId()
           << " advances west-bound" << endl;
        numAdvCarWestGreen++;
      }
    }
    
    numTotalAdvancedEast += numAdvCarEastGreen;
    numTotalAdvancedWest += numAdvCarWestGreen;

    cout << "East-bound cars advanced on green: " << numAdvCarEastGreen
         << " Remaining queue: " << eastQueue.getNumElems() << endl;
    cout << "West-bound cars advanced on green; " << numAdvCarWestGreen
         << " Remaining queue: " << westQueue.getNumElems() << endl;

    scheduleLightChange();
    return (true);
  }

  else if (currentEvent.getType() == EVENT_CHANGE_GREEN_NS)
  {
    CarClass outCarEast;
    int numAdvCarEastYellow = 0;
    CarClass outCarWest;
    int numAdvCarWestYellow = 0;
    bool isCarWaitingEastBound = true;
    bool isYellowLightTrafficEndEastBound = false;
    bool isCarWaitingWestBound = true;   
    bool isYellowLightTrafficEndWestBound = false;
    
    cout << "Advancing cars on east-west yellow" << endl;

    for (int i = 0; i < eastWestYellowTime; i++)
    {
      // east bound 
      if (!isYellowLightTrafficEndEastBound)
      {
        // No car is waiting
        if (eastQueue.getNumElems() == 0)      
        {
          isYellowLightTrafficEndEastBound = true;
          cout << "  No east-bound cars waiting to advance on yellow" 
               << endl;
        }
        // some cars waiting
        else if (eastQueue.getNumElems() != 0)
        {
          if (getUniform(1, 100) <= percentCarsAdvanceOnYellow)
          {
            isCarWaitingEastBound = eastQueue.dequeue(outCarEast);
            cout << "  Next East-bound car will advance on yellow" << endl;
            cout << "  Car #" << outCarEast.getId() 
                 << " advances west-bound" << endl;
            numAdvCarEastYellow++;
          }
          else if (getUniform(1, 100) > percentCarsAdvanceOnYellow)
          {
            cout << "  Next east-bound car will NOT advance on yellow" 
                 << endl;
            isYellowLightTrafficEndEastBound = true;
          }
        }
      }
      // west bound
      if (!isYellowLightTrafficEndWestBound)
      {
        // No car is waiting
        if (westQueue.getNumElems() == 0)      
        {
          isYellowLightTrafficEndWestBound = true;
          cout << "  No west-bound cars waiting to advance on yellow" 
               << endl;
        }
        // some cars waiting
        else if (westQueue.getNumElems() != 0)
        {
          if (getUniform(1, 100) <= percentCarsAdvanceOnYellow)
          {
            isCarWaitingWestBound = westQueue.dequeue(outCarWest);
            cout << "  Next west-bound car will advance on yellow" << endl;
            cout << "  Car #" << outCarWest.getId() 
                 << " advances west-bound" << endl;
            numAdvCarWestYellow++;
          }
          else if (getUniform(1, 100) > percentCarsAdvanceOnYellow)
          {
            cout << "  Next west-bound car will NOT advance on yellow" 
                 << endl;
            isYellowLightTrafficEndWestBound = true;
          }
        }
      }
      numTotalAdvancedEast += numAdvCarEastYellow;
      numTotalAdvancedWest += numAdvCarWestYellow;
    }
    scheduleLightChange();
    return (true);
  }

  else if (currentEvent.getType() == EVENT_CHANGE_YELLOW_NS)
  {
    CarClass outCarNorth;
    int numAdvCarNorthGreen = 0;
    CarClass outCarSouth;
    int numAdvCarSouthGreen = 0;

    bool isCarWaitingNorthBound = true;
    bool isCarWaitingSouthBound = true; 
 
    cout << "Advancing cars on north-south green" << endl;

    for (int i = 0; i < northSouthGreenTime; i++)
    {
      isCarWaitingNorthBound = northQueue.dequeue(outCarNorth); 
      if (isCarWaitingNorthBound)
      {
        cout << "  Car #" << outCarNorth.getId() 
           << " advances north-bound" << endl; 
        numAdvCarNorthGreen++;
      }
    }
    for (int i = 0; i < northSouthGreenTime; i++)
    {
      isCarWaitingSouthBound = southQueue.dequeue(outCarSouth);  
      if (isCarWaitingSouthBound)
      {
        cout << "  Car #" << outCarSouth.getId()
           << " advances south-bound" << endl;
        numAdvCarSouthGreen++;
      }
    }
    numTotalAdvancedNorth += numAdvCarNorthGreen;
    numTotalAdvancedSouth += numAdvCarSouthGreen;

    cout << "North-bound cars advanced on green: " << numAdvCarNorthGreen
         << " Remaining queue: " << northQueue.getNumElems() << endl;
    cout << "South-bound cars advanced on green; " << numAdvCarSouthGreen
         << " Remaining queue: " << southQueue.getNumElems() << endl;

    scheduleLightChange();
    return (true);
  }

  else if (currentEvent.getType() == EVENT_CHANGE_GREEN_EW)
  {
    CarClass outCarNorth;
    int numAdvCarNorthYellow = 0;
    CarClass outCarSouth;
    int numAdvCarSouthYellow = 0;
    bool isCarWaitingNorthBound = true;
    bool isYellowLightTrafficEndNorthBound = false;
    bool isCarWaitingSouthBound = true;   
    bool isYellowLightTrafficEndSouthBound = false;
    
    cout << "Advancing cars on north-south yellow" << endl;

    for (int i = 0; i < northSouthYellowTime; i++)
    {
      // north bound 
      if (!isYellowLightTrafficEndNorthBound)
      {
        // No car is waiting
        if (northQueue.getNumElems() == 0)      
        {
          isYellowLightTrafficEndNorthBound = true;
          cout << "  No north-bound cars waiting to advance on yellow" 
               << endl;
        }
        // some cars waiting
        else if (northQueue.getNumElems() != 0)
        {
          if (getUniform(1, 100) <= percentCarsAdvanceOnYellow)
          {
            isCarWaitingNorthBound = northQueue.dequeue(outCarNorth);
            cout << "  Next North-bound car will advance on yellow" << endl;
            cout << "  Car #" << outCarNorth.getId() 
                 << " advances north-bound" << endl;
            numAdvCarNorthYellow++;
          }
          else if (getUniform(1, 100) > percentCarsAdvanceOnYellow)
          {
            cout << "  Next north-bound car will NOT advance on yellow" 
                 << endl;
            isYellowLightTrafficEndNorthBound = true;
          }
        }
      }
      // south bound
      if (!isYellowLightTrafficEndSouthBound)
      {
        // No car is waiting
        if (southQueue.getNumElems() == 0)      
        {
          isYellowLightTrafficEndSouthBound = true;
          cout << "  No south-bound cars waiting to advance on yellow" 
               << endl;
        }
        // some cars waiting
        else if (southQueue.getNumElems() != 0)
        {
          if (getUniform(1, 100) <= percentCarsAdvanceOnYellow)
          {
            isCarWaitingSouthBound = southQueue.dequeue(outCarSouth);
            cout << "  Next south-bound car will advance on yellow" << endl;
            cout << "  Car #" << outCarSouth.getId() 
                 << " advances south-bound" << endl;
            numAdvCarSouthYellow++;
          }
          else if (getUniform(1, 100) > percentCarsAdvanceOnYellow)
          {
            cout << "  Next south-bound car will NOT advance on yellow" 
                 << endl;
            isYellowLightTrafficEndSouthBound = true;
          }
        }
      }
      numTotalAdvancedNorth += numAdvCarNorthYellow;
      numTotalAdvancedSouth += numAdvCarSouthYellow;
    }
    scheduleLightChange();
    return (true);
  }
}

void IntersectionSimulationClass::printStatistics(
     ) const
{
  cout << "===== Begin Simulation Statistics =====" << endl;
  cout << "  Longest east-bound queue: " << maxEastQueueLength << endl;
  cout << "  Longest west-bound queue: " << maxWestQueueLength << endl;
  cout << "  Longest north-bound queue: " << maxNorthQueueLength << endl;
  cout << "  Longest south-bound queue: " << maxSouthQueueLength << endl;
  cout << "  Total cars advanced east-bound: " <<
          numTotalAdvancedEast << endl;
  cout << "  Total cars advanced west-bound: " <<
          numTotalAdvancedWest << endl;
  cout << "  Total cars advanced north-bound: " <<
          numTotalAdvancedNorth << endl;
  cout << "  Total cars advanced south-bound: " <<
          numTotalAdvancedSouth << endl;
  cout << "===== End Simulation Statistics =====" << endl;
}
