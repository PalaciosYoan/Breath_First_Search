//I used textbook's pseudocode as a guide (BFS) and YOUTUBE
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include <stdlib.h>
#include <set>
#include <climits>

using namespace std;

struct Graph {
    list<string> vertices;
    map<pair<string,string>,int> edges;
    void vertex(list<string>);
    void PrintOut(void);
    void AddEdge(string,string,int);
    bool FindVertex(string);
    int FindEdgeCost(string vert1, string vert2);
    int IsReachable(string vert1, string vert2);
};

void Graph::PrintOut(void) {
    list<string>::iterator it;
    map<pair<string,string>,int>::iterator eit;
    
    for(it=vertices.begin(); it!=vertices.end(); it++) {
        cout << *it << endl;
    }
    
    for(eit = edges.begin(); eit != edges.end(); eit++) {
        cout << (*eit).first.first << " " << (*eit).first.second << " " << (*eit).second << endl;
    }
}
void Graph::vertex(list<string> v)
{
    vertices = v;
}

void Graph::AddEdge(string vert1,string vert2,int weight) {
    pair<string,string> st;
    st.first = vert1, st.second = vert2;

    if (FindVertex(st.first) == true && FindVertex(st.second) == true)
        edges.insert(make_pair(st,weight));
}

bool Graph::FindVertex(string vert1) {
    list<string>::iterator i;
    for(i=vertices.begin(); i != vertices.end(); i++)
        if(vert1 == (*i))
            return true;

    return false;
}

int Graph::FindEdgeCost(string vert1, string vert2) {
    for(map<pair<string,string>,int>::iterator eit = edges.begin(); eit != edges.end(); eit++)
        if(vert1 == (*eit).first.first && vert2 == (*eit).first.second)
            return (*eit).second;
        
    return -1;
}


int Graph::IsReachable(string vert1, string vert2) {
    string node="";
    map<string, int> d;
    set<string> visited;
    list<string> queue;
    list<string>::iterator i;
    map<pair<string, string>, int>::iterator j;

    for (i = vertices.begin(); i != vertices.end(); i++)
        d[*i] = INT_MAX;
    

    visited.insert(vert1);
    d[vert1] = 0;
    queue.push_back(vert1);

    while(!queue.empty())
    {
        node = queue.front();
        queue.pop_front();

        for (j = edges.begin(); j != edges.end(); j++)
            if((*j).first.first == node)
            {
                bool is_in = visited.find((*j).first.second) != visited.end();
                if(!is_in)
                {
                    d[(*j).first.second] = d[node]+1;
                    visited.insert((*j).first.second);
                    queue.push_back((*j).first.second);
                }
            }
    }
    if (d[vert2] != INT_MAX)
    {
        return d[vert2];
    }

    return -1;
}

int main() {
    Graph G;

    list<string> a;
    string t; 
    cin>>t;
    while(t!="END")
    {
        a.push_back(t);
        cin>>t;
    }
    G.vertex(a);

    string one;
    string two;
    int three;
    cin>>t;
    int count =0;
    while(t!="END")
    {
        if(count == 0)
        {
            one=t;
            count++;
        }
        else if(count ==1)
        {
            two=t;
            count++;
        }

        else if(count == 2)
        {
            stringstream ss;
            ss << t;
            ss >> three;
            count++;
        }
        
        if(count==3)
        {
            count =0;
            G.AddEdge(one, two, three);
        }

        cin>>t;
    }
    G.PrintOut();
    int i;
    cin>>i;
    while(i!=0)
    {
        if(i==1)
        {
            cin>>one;
            cout<<G.FindVertex(one)<<endl;
        }
        else if (i==2)
        {
            cin>>one;
            cin>>two;
            cout<<G.FindEdgeCost(one, two)<<endl;;
        }
        else if (i==3)
        {
            cin>>one;
            cin>>two;
            cout<<G.IsReachable(one, two)<<endl;
        }
        cin>>i;
    }

    return 0;
}
