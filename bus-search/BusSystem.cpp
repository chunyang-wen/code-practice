/*************************busSystem.cpp***********************
 * this file is the test file for Stations
 * author: Zebras Wen
 * date: 2012.11.05
 * version: 0.01
 * history:
 * copyLeft:
 *   all rights are under the GPL v3.0
 *********************************************************/

#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<string>
#include<cstdlib>

#include "Station.h"
#include "BusSystem.h"
#include "comFunObj.h"

using namespace std;

typedef map<string, Station*, ltString> BusSystemMap;
typedef set<string, ltString> LineNoSet;

// clear all the information after quit
void BusSystem::clearSystem(void)
{
	BusSystemMap::iterator iteB = busSystem.begin();
	BusSystemMap::iterator iteE = busSystem.end();
	while(iteB != iteE)
	{
		delete iteB->second;
		++iteB;
	}
	busSystem.clear();
}

/** bus.txt format
 * #
 * lineNo station1 station2 ... #
 * lineNo station1 station2 ... #
 * read bus line from text files
 */
void BusSystem::readBusLine(const string& path)
{
	fstream in(path.c_str());
	if (!in) {
		cerr<< "error in reading" <<endl;
	}
	string lineNo;
	bool flag = false;
	string input1;
	string input2;
	while(!in.eof())
	{

		in>>input1; // read in mark
		 // read in line number
		if (!input1.compare("#"))
		{
			in>>lineNo;
			if (in.eof())
			{
				break;
			}
			flag = true;
			in>>input1;
		}

		if (busSystem.find(input1) == busSystem.end())
		{
		    busSystem[input1] = new Station(const_cast<string&>(input1));
		}
		if (flag)
		{
			busLines[lineNo] = busSystem[input1];
			busSystem[input1]->addPassStationLineNo(lineNo);
			flag = false;
			input2 = input1;
			continue;
		}
		busSystem[input1]->addPassStationLineNo(const_cast<string&>(lineNo));
		busSystem[input2]->addNextStation(busSystem[input1]);
		busSystem[input1]->addPrevStation(busSystem[input2]);
		input2 = input1;
	}
	in.close();
}

/**
  * search a spcified line
  * @param const string& lineNo, line number
  * @return void
  * @author Zebras Wen
  */
void BusSystem::searchLine(const string& lineNo)
{
    printLine(lineNo);
}

/**
  * search the specified station
  * @param const string& name, station name
  * @return LineNoSet, a set contains lines that pass through
  * the station
  *@author Zebras Wen
  */
LineNoSet BusSystem::searchStation(const string& name)
{
    BusSystemMap::iterator ite = busSystem.find(name);
    if (ite != busSystem.end())
    {
        return (ite->second)->getPassStationLineNo();
    }
    else
    {
        return LineNoSet();
    }
}

/** printLine
 *
 */

void BusSystem::printLineAssist(const string& lineNo, Station* head)
{
	cout<<head->getStationName();
	list<Station*> nextStations = head->getNextStations();
	if (nextStations.empty())
		return;
	cout<<"->";
	// find next number of lineNo
	list<Station*>::iterator ite = nextStations.begin();
	list<Station*>::iterator iteE = nextStations.begin();
	while (ite != iteE)
	{
		LineNoSet lineNoSet= (*ite)->getPassStationLineNo();
		if (lineNoSet.find(lineNo) != lineNoSet.end())
		{
			break;
		}
		++ite;
	}
	printLineAssist(lineNo, *ite);
}

void BusSystem::printLine(const string &lineNo)
{
	if (busLines.end() == busLines.find(lineNo))
	{
		cerr<<"Not inlcuded"<<endl;
		return;
	}
	cout<<lineNo<<"路，路线为："<<endl;
	printLineAssist(lineNo, busLines[lineNo]);
	cout<<endl;

}
