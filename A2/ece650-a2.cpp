/* References:
https://www.geeksforgeeks.org/shortest-path-unweighted-graph/
https://www.geeksforgeeks.org/graph-and-its-representations/
https://www.youtube.com/watch?v=G32BB0P9vSo&t=6s
https://www.programiz.com/dsa/graph-bfs
https://en.cppreference.com/w/cpp/regex/regex_search
https://www.cplusplus.com/reference/regex/regex_search/
https://www.geeksforgeeks.org/match_results-prefix-and-suffix-in-cpp/
*/
#include <iostream>
#include <sstream>
#include <vector>
#include<regex>
#include<bits/stdc++.h>
using namespace std;
int adjacency_list(string);
int vertices=1;
void find_source_destination(string line,int *source, int *destination);

vector<int> adj_list[100000];
void bfs(vector<int>* , int, int, int);
vector<int> shortest_distance(int*,int );

int main() {
    int x;
    
    while (!cin.eof()) {
       

        
        string line;
        
        getline(cin, line);
        if (line[0]=='V')
            {
                //vertices=0;
                //vertices=stoi(line.substr(2,-1));
            for (int i=0; i<vertices+1;i++)
            {
                adj_list[i].clear();
            }    
                vertices=stoi(line.substr(2,-1));
                //cout<<vertices;
                if(vertices<=1)
                {
                    cout<<"Error: Vertices less than or equal to one"<<endl;
                    continue;
                }
                vector<int> adj_list[vertices];

            }
        else if (line[0]=='E')
        {
            x=adjacency_list(line);
            if (x==-1)
            {
            for (int i=0; i<vertices;i++)
            {
                adj_list[i].clear();
            }
            }
           
        }
        else if (line[0]=='s')
        {
            int source, destination;
            int *p_source=&source;
            int *p_destination=&destination;
            find_source_destination(line,p_source,p_destination);
            if(*p_source>vertices || *p_destination>vertices)
            {
                cout<<"Error: Source or Destination out of bounds "<<endl;
                continue;
            }
            if(*p_source==*p_destination)
            {
                cout<<"Error: Source and Destination are equal"<<endl;
                continue;
            }
            bfs(adj_list,source,destination, vertices);
        }
            

    }
    return 0;
}

int adjacency_list(string line)
{
    regex pattern("[0-9]+[,][0-9]+");
    smatch m,match;
    int point[2]={};
    string x;
    
    while (regex_search(line,m,pattern))
    {
        regex pattern1("(\\d+)");
        x=m.str();
        int i=0;
        
        while(regex_search(x,match,pattern1))
        {
            point[i]=stoi(match.str());
            x = match.suffix().str();
            i++;

        
        }
        line = m.suffix().str();
        
        if ((point[0]>vertices) || (point[1]>vertices))
        {
            cout<<"Error : Edges cannot be formed as point is more than the vertices"<<endl;
            return -1;
        }
        if (point[0] == point[1])
        {
            cout<<"Error : Both points are equal"<<endl;
            return -1;
        }
        if(point[0]==0 || point[1]==0)
        {
            cout<<"Error: Vertices with 0 is not valid"<<endl;
            return -1;
        }
        adj_list[point[0]].push_back(point[1]);
        adj_list[point[1]].push_back(point[0]);
    }

    
    return 0;
}

void find_source_destination(string line,int *source, int *destination)
{
    
    int source_destination[2]={};
    regex pattern("\\d+");
    smatch match1;
    int i=0;
    while(regex_search(line,match1,pattern))
        {
            source_destination[i]=stoi(match1.str());
            line = match1.suffix().str();
            i++;

        
        }
    *source=source_destination[0];
    *destination=source_destination[1];
        
}

void bfs(vector <int> *adj_list, int source, int destination,int vertices)
{
    list<int> queue;
    vector<int> value_shortest_distance;
    bool visited[vertices+1];
    int *distance=new int[vertices+1];
    int *parent=new int[vertices+1];
    for (int i = 0; i <= vertices; i++) {
        visited[i] = false;
        distance[i] = INT_MAX;
        parent[i] = -1;
    }
 
    
    visited[source] = true;
    distance[source] = 0;
    queue.push_back(source);
    while (!queue.empty()) {
        int first_element_queue = queue.front();
        queue.pop_front();
        for (long unsigned int i = 0; i < adj_list[first_element_queue].size(); i++) 
        {
            if (visited[adj_list[first_element_queue][i]] == false) 
            {
                visited[adj_list[first_element_queue][i]] = true;
                distance[adj_list[first_element_queue][i]] = distance[first_element_queue] + 1;
                parent[adj_list[first_element_queue][i]] = first_element_queue;
                queue.push_back(adj_list[first_element_queue][i]);
 
                
            if (adj_list[first_element_queue][i] == destination)
                {
                    
                    value_shortest_distance= shortest_distance(parent,destination);
                     
                }
            }
        }
    
    }
    
    if (value_shortest_distance.size()>0)
    {
        for(int i=value_shortest_distance.size()-1;i>=0;i--)
        {
            if(i!=0)
            {
                cout<<value_shortest_distance[i]<<"-";
            }
            else
            {
                cout<<value_shortest_distance[i];
            }
        }
        std::cout << std::endl;
    }
    else
    {
        cout<<"Error: No path exists"<<std::endl;
    }
    delete[] distance;
    delete[]  parent;
}

vector<int> shortest_distance(int parent[],int destination)
{
    vector<int> road;
    road.push_back(destination);
    while(parent[destination]!=-1)
    {
        
        destination=parent[destination];
        road.push_back(destination);
    }
    return road;
}

/*
V 8
E {<0,1>,<0,3>,<1,2>,<3,4>,<3,7>,<4,5>,<4,6>,<4,7>,<5,6>,<6,7>}
s 0 7 

V 5
E {<1,3>,<3,2>,<3,4>,<4,5>,<5,2>}
s 5 1

V 15
E {<2,6>,<2,8>,<2,5>,<6,5>,<5,8>,<6,10>,<10,8>}
s 2 10
*/
