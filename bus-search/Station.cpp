/*************************Station.cpp***********************
 * this file is the implementing file for Stations
 * author: Zebras Wen
 * date: 2012.11.03
 * version: 0.01
 * history:
 * copyLeft:
 *   all rights are under the GPL v3.0
 *********************************************************/

#include "Station.h"
#include<list>
#include<string>
#include<algorithm>
#include<iostream>
#include "comFunObj.h"

using namespace std;

/**
  * constructor
  * @param void
  * @return no return
  * @author Zebras Wen
  */
Station::Station(void) {}

/**
  * constructor
  * @param const string &name, name of a station
  * @return no return
  * @author Zebras Wen
  */
Station::Station(const string& name):stationName_(name)
{
    // this->setstationName_(name);
}

/**
  * destructor
  * @param void
  * @param no return
  * @author Zebras Wen
  */
Station::~Station() {}

/**
  * copy constructor of Station
  * @param const Station &station, an instance of Station
  * @return no return
  * @author Zebras Wen
  */
Station::Station(const Station& station)
{
    this->setStationName(station.getStationName());
}

/**
  * overloading operator= of Station
  * @param const Station &station, an instance of Station
  * @return Station&, in order to continue to do assignment
  * @author Zebras Wen
  */
Station& Station:: operator=(const Station& station)
{
    this->setStationName(station.getStationName());
    return *this;
}

/**
  * get the name of the station
  * @param void
  * @return string, name of the station
  * @author Zebras Wen
  */
string Station::getStationName()const
{
    return stationName_;
}

/**
  * set the name of the station
  * @param const string& name, name of the station
  * @return void
  * @author Zebras Wen
  */
void Station::setStationName(const string &name)
{
    stationName_ = name;
}

/**
  * add a next station
  * @param Station* station, a pointer of a station.
  * @return void
  * @author Zebras Wen
  */
void Station::addNextStation(Station* station)
{
    list<Station*>::iterator iteBegin = (this->nextStation_).begin();
    list<Station*>::iterator iteEnd = (this->nextStation_).end();
    if (find(iteBegin,iteEnd,station) == iteEnd)
    {
        (this->nextStation_).push_back(station);
    }
}

/**
  * get the list of next stations
  * @param void
  * @return list<Station*>, list of next stations
  * @author Zebras Wen
  */
list<Station*> Station::getNextStations()
{
    return this->nextStation_;
}

/**
  * add a previous station
  * @param Station* station, a pointer of a station.
  * @return void
  * @author Zebras Wen
  */
void Station::addPrevStation(Station* station)
{
    list<Station*>::iterator iteBegin = (this->prevStation_).begin();
    list<Station*>::iterator iteEnd = (this->prevStation_).end();
    if (find(iteBegin,iteEnd,station) == iteEnd)
    {
        (this->prevStation_).push_back(station);
    }
}

/**
  * get the list of previous stations
  * @param void
  * @return list<Station*>, list of previous stations
  * @author Zebras Wen
  */
list<Station*> Station::getPrevStations()
{
    return this->prevStation_;
}

set<string, ltString>& Station::getPassStationLineNo()
{
	return lineNo_;
}
void Station::addPassStationLineNo(const string &lineNo)
{
	lineNo_.insert(lineNo);
}



