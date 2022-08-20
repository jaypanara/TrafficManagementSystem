/* References:
https://www.geeksforgeeks.org/shortest-path-unweighted-graph/
https://www.geeksforgeeks.org/graph-and-its-representations/
https://www.youtube.com/watch?v=G32BB0P9vSo&t=6s
https://www.programiz.com/dsa/graph-bfs
https://en.cppreference.com/w/cpp/regex/regex_search
https://www.cplusplus.com/reference/regex/regex_search/
https://www.geeksforgeeks.org/match_results-prefix-and-suffix-in-cpp/
https://www.geeksforgeeks.org/vector-in-cpp-stl/

*/
#include <iostream>
#include <sstream>
#include <vector>
#include<regex>
#include<bits/stdc++.h>
#include <memory>

#include "minisat/core/SolverTypes.h"
#include "minisat/core/Solver.h"


using namespace std;
int adjacency_list(string);
int vertices=1;
void vertex_cover(int vertices, std::vector<int> *adj_list,int sum);

vector<int> adj_list[100000];

int main() {
    int x;

    while (!cin.eof()) {



        string line;

        getline(cin, line);
        if (line[0]=='V')
            {
               // cout<<line<<endl;
            //vertices=0;
                //vertices=stoi(line.substr(2,-1));
            for (int i=0; i<vertices+1;i++)
            {
                adj_list[i].clear();
            }
                vertices=stoi(line.substr(2,-1));
                //cout<<vertices;
                if(vertices<1)
                {
                    cout<<"Error: Vertices less than one"<<endl;
                    continue;
                }
                vector<int> adj_list[vertices];

            }
        else if (line[0]=='E')
        {
           // cout<<line<<endl;
        x=adjacency_list(line);
            if (x==-1)
            {
            for (int i=0; i<vertices;i++)
            {
                adj_list[i].clear();
            }
            }
      int sum = 0;
             for(int i=1;i<=vertices;i++){
            sum += adj_list[i].size();
            }

       if(x!=-1)
           {
                         vertex_cover(vertices,adj_list,sum);
                for(int i=0; i< vertices; i++){
                adj_list[i].clear();
                                }
                if (sum==0){
                    cout<<endl;
                }
            }

        //if(sum==0)
        //{
           // cout<<endl;
        //}
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


void vertex_cover(int vertices, std::vector<int> *adj_list,int sum){


    int k = 1;
if(sum>0)
{

    while(k <= vertices){
        Minisat::Var atomic_proposition[vertices][k];
        std::unique_ptr<Minisat::Solver> solver(new Minisat::Solver());

        //initializing the atomic proposition
        for(int i=1; i<=vertices; i++){
            for(int j=1; j<=k; j++){
                atomic_proposition[i][j] = solver->newVar();
            }
        }

        //Clause 1
        for(int j=1; j<=k; j++){
            Minisat::vec<Minisat::Lit> clause1;
            for(int i=1; i<=vertices; i++){
                clause1.push(Minisat::mkLit(atomic_proposition[i][j], false));
            }
            solver->addClause(clause1);
        }

        //Clause 2

            for(int m=1; m<=vertices; m++){
                for(int q=1; q<=k; q++){
                    for(int p=1; p<q ;p++){
                        solver->addClause(Minisat::mkLit(atomic_proposition[m][p], true),Minisat::mkLit(atomic_proposition[m][q], true));
                    }
                }
            }


        //Clause 3

        for(int m=1; m<=k; m++){
            for(int q=1; q<=vertices; q++){
                for(int p=1; p<q ;p++){
                    solver->addClause(Minisat::mkLit(atomic_proposition[p][m], true),Minisat::mkLit(atomic_proposition[q][m], true));
                }
            }
        }

        //Clause 4
        for(int source=1; source<=vertices ;source++ ){
            for(int destination : adj_list[source]){
                Minisat::vec<Minisat::Lit> clause4;
                for(int x=1; x<=k; x++){
                    clause4.push(Minisat::mkLit(atomic_proposition[source][x], false));
                    clause4.push(Minisat::mkLit(atomic_proposition[destination][x], false));
                }
                solver->addClause(clause4);
            }
        }

        //Solving above logic
        bool sat = solver->solve();
        if(sat){
            std::vector<int> final_result;
            for(int i=1; i<=vertices; i++){
                for(int j=1; j<=k; j++){
                    if(solver->modelValue(atomic_proposition[i][j]) == Minisat::l_True){

                        final_result.push_back(i);
                    }
                }
            }

            std::sort(final_result.begin(), final_result.end());



        //printing the vertex cover
              int sum = 0;
             for(int i=1;i<=vertices;i++){
            sum += adj_list[i].size();
            }
        if(sum>0)

        {
            for (std::vector<int>::iterator it = final_result.begin(); it != final_result.end(); ++it)
                        {
                std::cout << *it << " ";
                        }
                        cout<<endl;
            break;
        }

        }

        k++;
    }


}
}
