/*************************Station.h***********************
 * this file is the header file for Stations
 * author: Zebras Wen
 * date: 2012.11.03
 * version: 0.01
 * history:
 * copyLeft:
 *   all rights are under the GPL v3.0
 *********************************************************/

#ifndef _STATION_
#define _STATION_

#include<string>
#include<list>
#include<vector>
#include<set>
#include "comFunObj.h"

using std::string;
using std::list;
using std::vector;
using std::set;

// struct ltString;

class Station
{
public:
    Station(void);
    explicit Station(const string&);
    ~Station(void);

    Station(const Station&);
    Station& operator=(const Station&);

    // operator==(const Station&)

    string getStationName(void)const;
    void setStationName(const string&);

    list<Station*> getNextStations(void);
    void addNextStation(Station *);
    // bool hasNext(void);

    list<Station*> getPrevStations();
    void addPrevStation(Station*);

	void setLineNo(const string&);
	string getLineNo()const;

	set<string, ltString>& getPassStationLineNo();
	void addPassStationLineNo(const string&);

private:
    string stationName_;
    list<Station*> nextStation_;
    list<Station*> prevStation_;
	set<string, ltString> lineNo_;
};

#endif // _STATION_
