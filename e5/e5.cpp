#include <iostream>
#include<cstring>
#include<vector>
using namespace std;
#define INF 1111111
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
int nums,edgecount;
bool test[V];
int pre[V];
int graph[V][V];
//vector<struct edge>edges;


//贪心算法不一定能够得到最优解，当前情况下尽量好的解
vector<int> ring;
int min_sum=0;
void construct_graph()
{
    for(int i=0;i<nums;i++)
    {
        for(int j=0;j<nums;j++)
        {
            cin>>graph[i][j];
        }
    }
    cout<<"Add Edges Successfully"<<endl;
}

void print_tree()
{
    cout<<"THE GRAPH:"<<endl;
    for(int i=0;i<nums;i++)
    {
        for(int j=0;j<nums;j++)
        {
            cout<<graph[i][j]<<" ";
        }
        cout<<endl;
    }

}
int find_next(int start)
{
    int min_num=10000;
    int min_index=-1;
    for(int i=0;i<nums;i++)
    {
        if (test[i]==true)
            continue;
        if (graph[start][i]<min_num)
        {
            min_num=graph[start][i];
            min_index=i;
        }
    }
    return min_index;
}
void TSP_Ring(int start)
{
    test[start]=true;
    ring.push_back(start);
    if (ring.size()==nums)
        return;
    else{
        int next=find_next(start);
        cout<<"from "<<start<<" go to "<<next<<" distance="<<graph[start][next]<<endl;
        min_sum=min_sum+graph[start][next];
        TSP_Ring(next);
    }
}

//0 1 2 5 2  3 0 2 1 1   5 10 0 2 3   1 2 1 0 4   2 2 3 1 0
int main(int argc, char** argv)
{

	cout<<"Number of nodes:"<<endl;
	cin>>nums;
	//cout<<"Number of edges:"<<endl;
	//cin>>edgecount;
    edgecount=nums*(nums-1);

    construct_graph();
    print_tree();
    int start=0;
    TSP_Ring(start);
    min_sum+=graph[ring.back()][start];
    cout<<"minsum="<<min_sum<<endl;

    for(int i=0;i<ring.size();i++)
    {
        cout<<ring[i]<<" ";
    }

	return 0;
}
