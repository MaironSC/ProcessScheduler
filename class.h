#include <iostream>
#include <array>
#include <list>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;


class Processo {
private:
	int arrival;
	int duration;
	int launch = -1;
	int slices;
	int ac_slices;
	int memory;
	int priority;
	int static_priority;
	int watch;
	int mark;
public:
	int getArrival();
	void setArrival(int c);
	int getDuration();
	void setDuration(int d);
	int getLaunch();
	void setLaunch(int l);
	int getSlices();
	void setSlices(int s);
	int getAc_slices();
	void setAc_slices(int as);
	int getMemory();
	void setMemory(int m);
	int getPriority();
	void setPriority(int p);
	int getStatic_priority();
	void setStatic_priority(int pe);
	int getWatch();
	void setWatch(int o);
	int getMark();
	void setMark(int mc);
};

void StringSplit(string str, string delim, vector<string>& results); 
Processo CPU(Processo process, int lanc); 