/*
 * graph.h
 *
 *  Created on: 12/11/2023
 *      Author: Diego Quezada Colorado
 *      Matricula A01710024
 */

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    	vector<int> *adjList;
		int *adjMatrix;

public:
		void loadGraphMat(string, int, int);//
		Graph(int);//
		Graph();//
		void addEdgeAdjMatrix(int, int);//
		void addEdgeAdjList(int, int);//
		string printAdjMat();//
		string printAdjList();//
		string printAdjMat_clean();//
		void sortAdjList();//
		void loadGraphList(string, int);//
		string DFS(int, int);//
		string depthHelper(int, int, stack<int>&, list<int>&, vector<vector<int>>&);//
		string BFS(int, int);//
		string breadthHelper(int, int, queue<int>&, list<int>&, vector<vector<int>>&);//
		string print_visited(list<int>);//
		string print_path(vector<vector<int>>&,int ,int);//
		bool contains(list<int>, int);

};


void Graph::loadGraphMat(string data, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
	int u, v, i = 0;
	while (i < data.size()) {
		u = (int)data[i+1] - 48;
		v = (int)data[i+3] - 48;
		i = i + 6;
		addEdgeAdjMatrix(u,v);
	}
}

Graph::Graph() {
	edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

void Graph::addEdgeAdjList(int u, int v){
	adjList[u].push_back(v);
	adjList[v].push_back(u);
	edgesList++;
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
			sortAdjList();
	    }
    
		return aux.str();

}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}

bool Graph::contains(list<int> q, int n){
	list <int> :: iterator it;
	it = find(q.begin(), q.end(), n);
	if (it != q.end())
		return true;
	else
	return false;
}

void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++)
		sort(adjList[i].begin(),adjList[i].end());
}

void Graph::loadGraphList(string data, int a){
	adjList = new vector<int>[a];
	nodes = a;
	int u, v, i = 0;
	while ( i < data.size()) {
			u = (int)data[i+1] - 48;
			v = (int)data[i+3] - 48;
			i = i + 6;
			addEdgeAdjList(u,v);
//			cout << "u  "  << u << " v " << v << endl;
	}
	sortAdjList();
}

string Graph::DFS(int start, int goal){
	stack<int> stack;
	list<int> visited;
	vector<vector<int>> path(nodes, vector<int>(1,0));
	stack.push(start);
	string ans = depthHelper(start, goal, stack, visited, path);
	ans += print_path(path, start, goal);
	return ans;
}

string Graph::depthHelper(int current, int goal, stack<int>& stack, list<int>& visited, vector<vector<int>>& path){
	if (current == goal) {
		return print_visited(visited);
	} else if (stack.empty()) {
		return " node not found";
	} else {
		current = stack.top();
		stack.pop();
		visited.push_back(current);
		for (int i = 0; i < adjList[current].size(); i++) {
			if (!contains(visited, adjList[current][i])) {
				stack.push(adjList[current][i]);
				path[adjList[current][i]][0] = current;
			}
		}
		return depthHelper(current, goal, stack, visited, path);
	}
}

string Graph::BFS(int start, int goal){
	stringstream aux;
	queue<int> queue;
	list<int> visited;
	vector<vector<int>> path;
	queue.push(start);
	aux << "visited: ";
	while (!queue.empty()){
		int current = queue.front();
		queue.pop();
		if (!contains(visited, current)){
			visited.push_back(current);
			aux << current << " ";
			if (current == goal){
				return aux.str() + print_path(path, start, goal);
			}
			for (int i = 0; i < adjList[current].size(); i++){
				if (!contains(visited, adjList[current][i])){
					queue.push(adjList[current][i]);
					path.push_back({current, adjList[current][i]});
				}
			}
		}
	}
	return aux.str();
}

string Graph::breadthHelper(int start, int goal, queue<int>& queue, list<int>& visited, vector<vector<int>>& path){
	stringstream aux;
	queue.push(start);
	aux << "visited: ";
	while (!queue.empty()){
		int current = queue.front();
		queue.pop();
		if (!contains(visited, current)){
			visited.push_back(current);
			aux << current << " ";
			if (current == goal){
				aux << "\n";
				return aux.str() + print_path(path, start, goal);
			}
			for (int i = 0; i < adjList[current].size(); i++){
				if (!contains(visited, adjList[current][i])){
					queue.push(adjList[current][i]);
					path.push_back({current, adjList[current][i]});
				}
			}
		}
	}
	return aux.str();
}


string Graph::print_visited(list<int> q){
	stringstream aux;
	aux << "visited: ";
	while (!q.empty()){
		aux << q.front() << " ";
		q.pop_front();
  }
	return aux.str();
}

string Graph::print_path(vector<vector <int>> &path, int start, int goal){
	int node =  path[goal][0];
	stack<int> reverse;
	reverse.push(goal);
	stringstream aux;
	aux  << "path:";
	while (node != start) {
		reverse.push(node);
		node = path[node][0];
	}
	reverse.push(start);
	while (!reverse.empty()){
		aux << " " << reverse.top();
		reverse.pop();
	}
	return aux.str();
}








#endif /* Graph_H_ */
