#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Link{ int a; int b;};
class Student;
class Node
{
private:
    int id;
    int level; //used in BFS
    vector<Student*> neighbor; //pointers to neighbor Node
public:
    Node():neighbor(0) { id=0; level=0;}
    Node(int i):neighbor(0) { id=i; level=0;}
    void setID(int i) {  id = i; }
    int getID() { return id; }
    void setLevel(int l) {  level = l; }
    int getLevel() { return level; }
    void AddNeighbor(Student* ptr) {  neighbor.push_back(ptr); }
    int getSize() { return neighbor.size(); }
    Student* GetNeighbor(int i) { return neighbor[i]; }
};

class Student: public Node
{
private:
    int id;
public:
    Student():Node(){ id=0;}
    Student(int i, int ID):Node(i) { id=ID;}
    void setStudentID(int i) {  id = i; }
    int getStudentID() { return id; }
    int getYear(){ return id/1000000; }
    int getDepartment(){ return id/10000-getYear()*100; }
};

int FindLengths(vector<Student> students, int startNode, int endNode, int process){
	vector<Student*> currentShell;	//Nodes to be processed now
	vector<Student*> nextShell;	//Store nodes to be processed next
	int distance=0;
	bool nFound=true;
	
	//Put starting node into currentShell
	currentShell.push_back(&(students[startNode]));
	
	//While there is nodes in currentShell
	while(!currentShell.empty() && nFound){
		nextShell.clear(); //Clear nextShell
		distance++;
		//For each node in currentShell
		for(int c=0; c<currentShell.size() && nFound; c++){
			//For each neighbor of node
			for(int n=0; n<currentShell[c]->getSize() && nFound; n++){
				if(process==0 || process==1){
					//If neighbor is not processed, level of neighbor is not assigned
					if(currentShell[c]->GetNeighbor(n)->getID()!=startNode && currentShell[c]->GetNeighbor(n)->getLevel()==0){
						nextShell.push_back(currentShell[c]->GetNeighbor(n));	//Append neighbor to nextShell
						currentShell[c]->GetNeighbor(n)->setLevel(distance);	//Set level of neighbor to distance;
					}
				}
				else if(process==2){
					//If neighbor is not processed, level of neighbor is not assigned
					if(currentShell[c]->GetNeighbor(n)->getID()!=startNode && currentShell[c]->GetNeighbor(n)->getLevel()==0 && currentShell[c]->GetNeighbor(n)->getID()==endNode){
						nextShell.push_back(currentShell[c]->GetNeighbor(n));	//Append neighbor to nextShell
						currentShell[c]->GetNeighbor(n)->setLevel(distance);	//Set level of neighbor to distance;
						nFound=false;
					}
					else if(currentShell[c]->GetNeighbor(n)->getID()!=startNode && currentShell[c]->GetNeighbor(n)->getLevel()==0){
						nextShell.push_back(currentShell[c]->GetNeighbor(n));	//Append neighbor to nextShell
						currentShell[c]->GetNeighbor(n)->setLevel(distance);	//Set level of neighbor to distance;
					}
				}
			}
		}
		currentShell=nextShell; //Copy nextShell to currentShell
    }
    if(process==2 && nFound)
    	return -1;
    else
		return distance-1;
}

int main(){
	//Data structure setup
	int n,startNode,endNode,department,treeCount=0;
	cout << "Total students number: ";			cin >> n;
	cout << "Select a student as start node: ";	cin >> startNode;
	cout << "Select a student as end node: ";	cin >> endNode;
	cout << "Select a department: ";			cin >> department;
    vector<Student> students(n);
    vector<Student*> sptr[n]; //temporary Student pointers
    vector<Link> links;
    n--;
    
    //Target file setup
	ofstream output;
	output.open("result.csv");
    output << "StudentID,FriendsID\n";
    
    //Create students
    for(int i=0; i<=n; i++){
	    int tempID = (rand()%5+99)*1000000 + (rand()%9)*10000 + (rand()%3)*1000 + (rand()%2+1)*100 + (rand()%50+1);
	    students[i].setID(i);
	    students[i].setStudentID(tempID); 
    }
    
    //Build the links
    for(int i=0; i<=n-1; i++){
    	for(int j=i+1; j<=n; j++){
			Link buffer;
			buffer.a=i;	buffer.b=j;
		    links.push_back(buffer);
    	}
    }
	srand(time(NULL));
	for(int i=0; i<n*1000; i++){
		swap(links[rand()%links.size()],links[rand()%links.size()]);
    }
    //Assign links
    int lim=links.size()*0.5;
	for(int i=links.size()-1; i>lim; i--){
		students[links[i].a].AddNeighbor(&(students[links[i].b]));
    	students[links[i].b].AddNeighbor(&(students[links[i].a]));
    	links.pop_back();
	}
    for(int i=0; i<=n; i++){
    	for(int j=0; j<students[i].getSize(); j++){
    		sptr[i].push_back(static_cast<Student*>(students[i].GetNeighbor(j)));
    	}
    }
    
    //Output the whole network
	for(int i=0; i<students.size(); i++){
		output << students[i].getStudentID() << ",";
		//cout << students[i].getID() << ",";
	   	for(int j=0; j<students[i].getSize(); j++){
	   		output << sptr[i][j]->getStudentID() << ",";
	   		//cout << sptr[i][j]->getID() << ",";
	   	}
	   	output << endl;
	   	//cout << endl;
	}
	
	//Find the distance between startNode and endNode
	int dis=FindLengths(students,startNode,endNode,2);
	if(dis<0)
		cout << "There are no friend relationship between student " << students[startNode].getStudentID() << " and student " << students[endNode].getStudentID() << " ." << endl;
	else
		cout << "The distance between student " << students[startNode].getStudentID() << " and student " << students[endNode].getStudentID() << " is " << dis+1 << " ." << endl;
	
	//Reset levels of all students
	for(int a=0; a<students.size(); a++){
		for(int n=0; n<students[a].getSize(); n++){
			students[a].GetNeighbor(n)->setLevel(0);
		}
	}
	
	//Count trees for a department
	for(startNode=0; startNode<=n; startNode++){
		if(students[startNode].getDepartment()==department && students[startNode].getLevel()==0){
			FindLengths(students,startNode,0,1);
			treeCount++;
		}
	}
	cout << "Need " << treeCount << " trees to link all the students in department " << department << "." << endl;
    return 0;
}
