#include <iostream>

#include<vector>
using namespace std;

const int V=20;          //max points=20
//const int E=20;         //max edge numbers=20
struct edge{
	int start;
	int end;
	int weight;
	edge(int a,int b,int c)
	{
		start=a;
		end=b;
		weight=c;
	}
	//edge(){}
};

bool test[V];
int graph[V][V];
int tree[V][V];


void construct_graph(int nums,int edgecount)
{

    for(int i=0;i<nums;i++)
    {
        for(int j=0;j<nums;j++)
        {
            graph[i][j]=0;
            tree[i][j]=0;
        }
        test[i]=false;
    }

    int start,end,weight;
    for(int i=0;i<edgecount;i++)
    {
        cin>>start>>end>>weight;
        graph[start][end]=weight;
        graph[end][start]=weight;

        cout<<"Add Edge Successfully"<<endl;
    }
}
void addedge(int s,int e,int w)
{
    tree[s][e]=w;
    tree[e][s]=w;
    graph[s][e]=0;
    graph[e][s]=0;
    cout<<"add "<<s<<"->"<<e<<endl;
}
vector<struct edge> edges;
void removemaxedge(int x)
{
    edge maxedge(0,0,0);
    for (vector<struct edge>::const_iterator iter = edges.cend(); iter != edges.cbegin(); iter--)
    {
        struct edge a=(*iter);
        if (a.start==x)
        {
            break;
        }
        if (a.weight>maxedge.weight)
                    {
                        maxedge=a;
                    }
    }
    for (vector<struct edge>::const_iterator iter = edges.cbegin(); iter != edges.cend(); iter++)
    {
        struct edge a=(*iter);
        if (a.start==maxedge.start&&a.end==maxedge.end&&a.weight==maxedge.weight)
        {
            edges.erase(iter);
            break;
        }
    }
    int s=maxedge.start;
    int e=maxedge.end;
    tree[s][e]=0;
    tree[e][s]=0;

    cout<<"remove "<<s<<"->"<<e<<endl;
}

void build_MST(int current,int nums,int edgecount,int fathernode)
{

        for(int j=0;j<nums;j++)
        {
            if(j==fathernode)
            {
                continue;
            }
            if((test[j]==false)&&(graph[current][j]!=0))
            {
                edges.push_back(edge(current,j,graph[current][j]));
                addedge(current,j,graph[current][j]);
                test[j]=true;
                build_MST(j,nums,edgecount,current);

            }
            else if((test[j]==true)&&(graph[current][j]!=0))
            {
                edges.push_back(edge(current,j,graph[current][j]));
                addedge(current,j,graph[current][j]);
                /*
                edge maxedge(0,0,0);
                for (vector<struct edge>::const_iterator iter = edges.cbegin(); iter != edges.cend(); iter++)
                {
                    struct edge a=(*iter);
                    if (a.weight>maxedge.weight)
                    {
                        maxedge=a;
                    }
                }*/
                removemaxedge(j);

            }
        }
        return;
}
void print_tree(int nums)
{
    for(int i=0;i<nums;i++)
    {
        for(int j=0;j<nums;j++)
        {

            cout<<tree[i][j]<<" ";
        }
        cout<<endl;
    }
}
// 0 1 1 1 2 2 2 3 2 3 0 1 0 2 3
// 0 1 2 0 2 5 0 4 1 1 2 4 1 3 3 3 4 2
int main(int argc, char** argv)
{
	int nums,edgecount;
	cout<<"Number of nodes:"<<endl;
	cin>>nums;
	cout<<"Number of edges:"<<endl;
	cin>>edgecount;


    construct_graph(nums,edgecount);
    test[0]=true;

    build_MST(0,nums,edgecount,-1);

    print_tree(nums);
    //flag root parent

    //print_graph(nums);

	return 0;
}
