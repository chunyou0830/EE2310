#include <iostream>
#include <cstdlib>
#include <vector>
#include <iomanip>
using namespace std;

class Task
{
private:
    int time;
    int resource;
    int duration;
public:
    Task(){ time=rand()%101; resource=0; duration=rand()%10+1;}
    Task(int t, int r, int d){ time=t; resource=r; duration=d;}
    void SetResource(int r){ resource=r;}
    int GetTime(){ return time;}
    int GetResource(){ return resource;}
    int GetDuration(){ return duration;}
};

class Resource{
private:
	int days[110];
public:
	void SetDay(int day, int dat){ days[day] = dat;}
	int GetDay(int day){ return days[day];}
};

void Assign(vector<Task>& list, vector<Resource>& resource, int i){
	bool available = false;
	int r,d;

	//Check if any resource is available
	for(r = 0, available = false ; r < resource.size() && !available ; r++){
		for(d = list[i].GetTime() ; d <= list[i].GetDuration()+list[i].GetTime() ; d++){
			if(resource[r].GetDay(d) != 0){ available = false; break;}
			else{ available = true;}
		}
	}
	
	//If none of the existed resource is available, create a new one.
	if(!available){
		resource.resize(resource.size()+1);
		r=resource.size();
	}
	
	//Assign the work.
	for(int ai = list[i].GetTime() ; ai < list[i].GetDuration()+list[i].GetTime() ; ai++){
		resource[r-1].SetDay(ai, resource[r-1].GetDay(ai)+1);
	}
	list[i].SetResource(r-1);
}

bool ResourceCheck(vector<Resource>& resource){
	for(int r = 0 ; r < resource.size() ; r++){
		for(int d = 0 ; d < 110 ; d++){
			if(resource[r].GetDay(d) > 1)
				return false;
		}
	}
	return true;
}

int LookUp(vector<Resource>& resource, int d){
	int count = 0;
	for(int r = 0 ; r < resource.size() ; r++){
		count+=resource[r].GetDay(d);
	}
	return count;
}

int main(){
	//Generate Task List
	vector<Task> list;
	for(int i = 0 ; i < 100 ; i++){
        Task buffer;
        list.push_back(buffer);
	}
	
	//Generate Resource List
	vector<Resource> resource(1);
	
	//Assign A Task
	for(int i = 0 ; i < list.size() ; i++){
		Assign(list, resource, i);
		cout << setw(3) << list[i].GetTime() << " " << setw(3) << list[i].GetDuration() << " " << setw(3) << list[i].GetResource() << endl;
	}
	
	//Check Resources
	cout << "Check result: ";
	if(ResourceCheck(resource)){ cout << "all correct." << endl;}
	else{ cout << "error existed." << endl;}
	
	//Count Resources Needed
	int time;
	cout << "Enter a time between 0~110:";
	cin >> time;
	cout << "There are " << LookUp(resource, time) << " tasks at time " << time << " .";
	
	return 0;
}
