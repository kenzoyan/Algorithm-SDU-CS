#include <iostream>

#include<vector>
using namespace std;

const int V=20;          //max points=20
int dfn[V],low[V],parent[V];

bool vis[V],ap[V];
vector<int> graph[V];

int count=0;

void DFS_visit(int x)
{
    count++;
    int child=0;            //children of root
    dfn[x]=low[x]=count;
    vis[x]=true;

    for (vector<int>::const_iterator iter = graph[x].cbegin(); iter != graph[x].cend(); iter++)
    {
        int v=(*iter);

        //x,v is tree line
        if(!vis[v])
        {
            child++;            //compute the children tree of the root point
            parent[v]=x;
            DFS_visit(v);

            //traverse all points
            // compute low
            low[x]=min(low[x],low[v]);              //compute low:   1.minimum low of the point and son point
                                                    //2. minimum of point and son points which link the ancestor point using *back line*
                                                    //判断u是不是割点，确定u及其子孙不存在返回边能够不通过 u及其父节点的连线 回到u的祖先节点
            if (child>=2&&parent[x]==-1)
            {
                cout<<" root point="<<x<<endl;
            }
            else if(parent[x]!=-1&&low[v]>=dfn[x])
                cout<<"Articulation Point="<<x<<endl;
        }
        // u,v is back line
        else if (v != parent[x])
            low[x] = min(low[x], dfn[v]);
    }
}


void print_graph(int n)
{
	for(int i=1;i<=n;i++)
	{
	    cout<<"Point "<<i<<"---";
	    for (vector<int>::const_iterator iter = graph[i].cbegin(); iter != graph[i].cend(); iter++)
        {
            cout<<(*iter)<<" ";
        }
        cout<<endl;
	}
}
// 1 2 2 3 3 4 4 1 4 5 4 6 5 6    ex1

// 1 2 2 3 3 4 4 1 4 5 4 6 5 6 3 7    ex2

void construct_graph(int nums,int edges)
{
    int x,y;
    for(int i=0;i<edges;i++)
    {
        cin>>x>>y;
        graph[x].push_back(y);
        graph[y].push_back(x);
        cout<<"Add Edge Successfully"<<endl;
    }
}
int main(int argc, char** argv) {
	int nums,edges;
	cout<<"Number of nodes:"<<endl;
	cin>>nums;
	cout<<"Number of edges:"<<endl;
	cin>>edges;
    construct_graph(nums,edges);

    //flag root parent
    parent[1]=-1;

    print_graph(nums);

    DFS_visit(1);

	return 0;
}

