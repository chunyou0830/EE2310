#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
using namespace std;

class Node
{
private:
    int id;
    int level; 				//used in BFS
    vector<Node*> neighbor; //pointers to neighbor Node

public:
    Node():neighbor(0) { id=0; level=0;}
    Node(int i):neighbor(0) { id=i; level=0;}
    void setID(int i) {  id = i; }
    int getID() { return id; }
    void setLevel(int l) {  level = l; }
    int getLevel() { return level; }
    void AddNeighbor(Node* ptr) {  neighbor.push_back(ptr); }
    int getSize() { return neighbor.size(); }
    Node* GetNeighbor(int i) { return neighbor[i]; }
};

struct Link
{
	int a;
	int b;
};

void FindLengths(vector<Node> all_nodes, int n, ofstream& output){
	vector<Node*> currentShell;	//Nodes to be processed now
	vector<Node*> nextShell;	//Store nodes to be processed next
	int distance=0;
	//Print the network list
	for(int i=0; i<all_nodes.size(); i++){
		output << "Node " << all_nodes[i].getID() << " has a neighbor of Node ";
	   	for(int j=0; j<all_nodes[i].getSize(); j++)
	   		output << all_nodes[i].GetNeighbor(j)->getID() << " ";
	   	output << endl;
	}
	
	//Reset levels of all nodes
	for(int a=0; a<all_nodes.size(); a++){
		for(int n=0; n<all_nodes[a].getSize(); n++){
			all_nodes[a].GetNeighbor(n)->setLevel(0);
		}
	}
	//Put starting node (node n) into currentShell
	currentShell.push_back(&(all_nodes[n]));
	
	//While there is nodes in currentShell
	while(!currentShell.empty()){
		nextShell.clear(); //Clear nextShell
		distance++;
		//For each node in currentShell
		for(int c=0; c<currentShell.size(); c++){
			//For each neighbor of node
			for(int n=0; n<currentShell[c]->getSize(); n++){
				//If neighbor is not processed, level of neighbor is not assigned
				if(currentShell[c]->GetNeighbor(n)->getID()!=0 && currentShell[c]->GetNeighbor(n)->getLevel()==0){
					nextShell.push_back(currentShell[c]->GetNeighbor(n));	//Append neighbor to nextShell
					currentShell[c]->GetNeighbor(n)->setLevel(distance);	//Set level of neighbor to distance;
				}
			}
		}
		currentShell=nextShell; //Copy nextShell to currentShell
     }
	cout << "max_distance = " << distance-1 << endl;
	output << "max_distance = " << distance-1 << endl << endl;
}

int main(){
	int n=0;
	ofstream output;
	output.open("result.txt");
	
	//Get the node number of the network	
	cout << "Enter Nodes: ";
	cin >> n;
	
	//Create the node vector and the list vector
    vector<Node> all_nodes(n);
    vector<Link> link_list;
    n--;
    
    //Setup nodes
    for(int i=0; i<=n; i++){
	    all_nodes[i].setID(i);
    }
    
    //Link these nodes in circle
    for(int i=0; i<=n-1; i++){
	    all_nodes[i].AddNeighbor(&(all_nodes[i+1]));
	    all_nodes[i+1].AddNeighbor(&(all_nodes[i]));
    }
    all_nodes[0].AddNeighbor(&(all_nodes[n]));
    all_nodes[n].AddNeighbor(&(all_nodes[0]));

	//Build the list of links
	for(int i=2; i<n; i++){
		Link buffer;
		buffer.a=0;	buffer.b=i;
	    link_list.push_back(buffer);
    }
    for(int i=1; i<=n-2; i++){
    	for(int j=i+2; j<=n; j++){
			Link buffer;
			buffer.a=i;	buffer.b=j;
		    link_list.push_back(buffer);
    	}
    }
    //Randomize the links list.
	for(int i=0; i<1000; i++){
		swap(link_list[rand()%link_list.size()],link_list[rand()%link_list.size()]);
    }
    
	//Find max length and add links from the randomized links list
	FindLengths(all_nodes, 0, output);
	for(int a=link_list.size()-1; a>-1; a--){
		all_nodes[link_list[a].a].AddNeighbor(&(all_nodes[link_list[a].b]));
    	all_nodes[link_list[a].b].AddNeighbor(&(all_nodes[link_list[a].a]));
    	link_list.pop_back();
	    FindLengths(all_nodes, 0, output);
	}
}
