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
  cout << "Time: " << currentTime << " Schedule Event Type: "
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
    inLightChangeTime = currentTime / lightCycleTime + eastWestGreenTime;
    inLightChangeType = EVENT_CHANGE_YELLOW_EW;
  }
  else if (currentTime % lightCycleTime 
           < (eastWestGreenTime + eastWestYellowTime))
  {
    inLightChangeTime = currentTime / lightCycleTime 
                  + (eastWestGreenTime + eastWestYellowTime);
    inLightChangeType = EVENT_CHANGE_GREEN_NS;
  }
  else if (currentTime % lightCycleTime 
           < (eastWestGreenTime + eastWestYellowTime + northSouthGreenTime))
  {
    inLightChangeTime = currentTime / lightCycleTime 
                  + (eastWestGreenTime + eastWestYellowTime 
                  + northSouthGreenTime);
    inLightChangeType = EVENT_CHANGE_YELLOW_NS;
  }
  else 
  {
    inLightChangeTime = currentTime / lightCycleTime 
                  + (eastWestGreenTime + eastWestYellowTime 
                  + northSouthGreenTime + northSouthYellowTime);
    inLightChangeType = EVENT_CHANGE_GREEN_EW;
  }

  EventClass inLightChange(inLightChangeTime, inLightChangeType);
  cout << "Time: " << currentTime << " Schedule Event Type: "
       << inLightChange << endl;
  eventList.insertValue(inLightChange);
}

bool IntersectionSimulationClass::handleNextEvent(
     )
{
  EventClass currentEvent;
  bool isEventWaiting = true;

  isEventWaiting = eventList.removeFront(currentEvent);
  currentTime = currentEvent.getTimeOccurs();

  cout << "Handling Event Type: " << currentEvent << endl;
  cout << "Time: " << currentTime;
  
  // next event is larger than the simulation time
  if (currentTime > timeToStopSim)
  {
    return (false);
  }
  else if (currentEvent.getType() == EVENT_ARRIVE_EAST) 
  {
    CarClass inCar(EAST_DIRECTION, currentTime);
    eastQueue.enqueue(inCar);

    cout << " Car #" << inCar.getId()
         << " arrives east-bound - queue length: " 
         << eastQueue.getNumElems() << endl;
    scheduleArrival(EAST_DIRECTION);
    cout << endl;
    return (true);
  }
  else if (currentEvent.getType() == EVENT_ARRIVE_WEST)
  {
    CarClass inCar(WEST_DIRECTION, currentTime);
    westQueue.enqueue(inCar);
    
    cout << " Car #" << inCar.getId()
         << " arrives west-bound - queue length: " 
         << westQueue.getNumElems() << endl;
    scheduleArrival(WEST_DIRECTION);
    cout << endl;
    return (true);
  }
  else if (currentEvent.getType() == EVENT_ARRIVE_NORTH)
  {
    CarClass inCar(NORTH_DIRECTION, currentTime);
    northQueue.enqueue(inCar);
    
    cout << " Car #" << inCar.getId()
         << " arrives north-bound - queue length: " 
         << northQueue.getNumElems() << endl;
    scheduleArrival(NORTH_DIRECTION);
    cout << endl;
    return (true);
  }
  else if (currentEvent.getType() == EVENT_ARRIVE_SOUTH)
  {
    CarClass inCar(SOUTH_DIRECTION, currentTime);
    southQueue.enqueue(inCar);
    
    cout << " Car #" << inCar.getId()
         << " arrives south-bound - queue length: " 
         << southQueue.getNumElems() << endl;
    scheduleArrival(SOUTH_DIRECTION);
    cout << endl;
    return (true);
  }

  else if (currentEvent.getType() == EVENT_CHANGE_YELLOW_EW)
  {
    CarClass outCar;
    bool isCarWaitingEastBound = true;
    bool isCarWaitingWestBound = true; 
 
    for (int i = 0; i < eastWestGreenTime; i++)
    {
      if (isCarWaitingEastBound)
      {
        isCarWaitingEastBound = eastQueue.dequeue(outCar); 
        cout << "Car #" << outCar.getId() 
           << " advances east-bound" << endl; 
      }
    }
    for (int i = 0; i < eastWestGreenTime; i++)
    {
      if (isCarWaitingWestBound)
      {
        isCarWaitingWestBound = westQueue.dequeue(outCar);
        cout << "Car #" << outCar.getId()
           << " advances west-bound" << endl;
      }
    }
    return (true);
  }

  else if (currentEvent.getType() == EVENT_CHANGE_GREEN_NS)
  {
    CarClass outCar;
    bool isCarWaitingEastBound = true;
    bool isYellowLightTrafficStopEastBound = false;
    bool isCarWaitingWestBound = true;   
    bool isYellowLightTrafficStopWestBound = false;

    for (int i = 0; i < eastWestYellowTime; i++)
    {
      // east bound 
      if (isYellowLightTrafficStopEastBound)
      {
        if (getUniform(1, 100) <= percentCarsAdvanceOnYellow)
        {
          isCarWaitingEastBound = eastQueue.dequeue(outCar);
          if (!isCarWaitingEastBound) 
          {
            cout << "No east-bound cars waiting to advance on yellow" 
                 << endl;
            isYellowLightTrafficStopEastBound = true;
          }
        }
        else if (getUniform(1, 100) > percentCarsAdvanceOnYellow)
        {
          cout << "Next east-bound car will NOT advance on yellow" << endl;
          isYellowLightTrafficStopEastBound = true;
        }
      }
      // west bound
      if (isYellowLightTrafficStopWestBound)
      {
        if (getUniform(1, 100) <= percentCarsAdvanceOnYellow)
        {
          isCarWaitingWestBound = westQueue.dequeue(outCar);
          if (!isCarWaitingWestBound) 
          {
            cout << "No west-bound cars waiting to advance on yellow" 
                 << endl;
            isYellowLightTrafficStopWestBound = true;
          }
        }
        else if (getUniform(1, 100) > percentCarsAdvanceOnYellow)
        {
          cout << "Next west-bound car will NOT advance on yellow" << endl;
          isYellowLightTrafficStopWestBound = true;
        }
      }
    }
    return (true);
  }

  else if (currentEvent.getType() == EVENT_CHANGE_YELLOW_NS)
  {
    CarClass outCar;
    bool isCarWaitingNorthBound = true;
    bool isCarWaitingSouthBound = true; 
 
    for (int i = 0; i < northSouthGreenTime; i++)
    {
      isCarWaitingNorthBound = northQueue.dequeue(outCar);
      if (isCarWaitingNorthBound)
      { 
        cout << "Car #" << outCar.getId() 
             << " advances north-bound" << endl; 
      }
    }

    for (int i = 0; i < northSouthGreenTime; i++)
    {
      if (isCarWaitingSouthBound)
      {
        isCarWaitingSouthBound = southQueue.dequeue(outCar);
        cout << "Car #" << outCar.getId()
           << " advances south-bound" << endl;
      }
    }
    return (true);
  }

  else if (currentEvent.getType() == EVENT_CHANGE_GREEN_EW)
  {
    CarClass outCar;
    bool isCarWaitingNorthBound = true;
    bool isYellowLightTrafficStopNorthBound = false;
    bool isCarWaitingSouthBound = true;   
    bool isYellowLightTrafficStopSouthBound = false;

    for (int i = 0; i < northSouthYellowTime; i++)
    {
      // north bound 
      if (isYellowLightTrafficStopNorthBound)
      {
        if (getUniform(1, 100) <= percentCarsAdvanceOnYellow)
        {
          isCarWaitingNorthBound = northQueue.dequeue(outCar);
          if (!isCarWaitingNorthBound) 
          {
            cout << "No north-bound cars waiting to advance on yellow" 
                 << endl;
            isYellowLightTrafficStopNorthBound = true;
          }
        }
        else if (getUniform(1, 100) > percentCarsAdvanceOnYellow)
        {
          cout << "Next north-bound car will NOT advance on yellow" << endl;
          isYellowLightTrafficStopNorthBound = true;
        }
      }
      // south bound
      if (isYellowLightTrafficStopSouthBound)
      {
        if (getUniform(1, 100) <= percentCarsAdvanceOnYellow)
        {
          isCarWaitingSouthBound = southQueue.dequeue(outCar);
          if (!isCarWaitingSouthBound) 
          {
            cout << "No south-bound cars waiting to advance on yellow" 
                 << endl;
            isYellowLightTrafficStopSouthBound = true;
          }
        }
        else if (getUniform(1, 100) > percentCarsAdvanceOnYellow)
        {
          cout << "Next south-bound car will NOT advance on yellow" << endl;
          isYellowLightTrafficStopSouthBound = true;
        }
      }
    }
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
