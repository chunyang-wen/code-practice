/*************************main.cpp***********************
 * this file is the test file for Stations
 * author: Zebras Wen
 * date: 2012.11.05
 * version: 0.01
 * history:
 * copyLeft:
 *   all rights are under the GPL v3.0
 *********************************************************/

#include<iostream>
#include "BusSystem.h"
#include<string>

using namespace std;

typedef set<string, ltString> LineNoSet;

int main()
{
	BusSystem bs("bus.txt");
	bs.printLine("12");
	bs.printLine("129");
	LineNoSet lineNoset = bs.searchStation("µ¾Ïã´å");
	LineNoSet::iterator iteB = lineNoset.begin();
	LineNoSet::iterator iteE = lineNoset.end();
	while (iteB != iteE)
	{
	    cout<<"line: "<<*iteB<<endl;
	    ++iteB;
	}
	return 0;
}
