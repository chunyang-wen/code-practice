/*************************busSystem.h***********************
 * this file is the header file for Stations
 * author: Zebras Wen
 * date: 2012.11.05
 * version: 0.01
 * history:
 * copyLeft:
 *   all rights are under the GPL v3.0
 *********************************************************/
#ifndef _BUSSYTEM_
#define _BUSSYSTEM_

#include<map>
#include<string>
#include<set>
#include "comFunObj.h"

using std::string;
using std::map;
using std::set;

struct lsString;
class Station;

class BusSystem
{
public:
	BusSystem(const string& path)
	{
		readBusLine(path);
	}
	~BusSystem()
	{
		clearSystem();
	}

	void readBusLine(const string& path);

	// search function
	void searchLine(const string& lineNo);
	set<string, ltString> searchStation(const string& name);
	void printLineAssist(const string& lineNo, Station* head);
	void printLine(const string &lineNo);

private:
	void clearSystem();
	map<string, Station*, ltString> busSystem;
	map<string, Station*, ltString> busLines;

};

#endif // _BUSSYSTEM_
