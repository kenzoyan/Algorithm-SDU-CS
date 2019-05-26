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

int dis[V];
int pre[V];
int graph[V][V];
vector<struct edge>edges;
vector<int> ring;

void construct_graph(int nums,int edgecount)
{


    int start,end,weight;
    for(int i=0;i<edgecount;i++)
    {
        cin>>start>>end>>weight;
        edge temp(start,end,weight);
        edges.push_back(temp);
        cout<<"Add Edge Successfully"<<endl;
    }
}

void print_tree()
{
    for(int i=0;i<edges.size();i++)
    {
        int s=edges[i].start;
        int e=edges[i].end;
        int w=edges[i].weight;
        cout<<s<<"-->"<<e<<" "<<"w="<<w<<endl;
    }
}
bool if_ring(int nodenum);
bool get(int x );
bool find_minus_ring(int nodenum,int edgenum)
{
    for(int j=0;j<nodenum;j++)          //初始化
        {
            dis[j]=INF;
            pre[j]=-1;
        }

    dis[0]=0;               //从0点开始

    bool flag;

    for(int i=0;i<nodenum;i++)              //没有化简 采用bellmanford 复杂度较高EV， 如果采用spfa可以降低复杂度
    {
        for(int j=0;j<edgenum;j++)
        {
            if(dis[edges[j].end]>dis[edges[j].start]+edges[j].weight)           //relax
            {
                dis[edges[j].end]=dis[edges[j].start]+edges[j].weight;
                pre[edges[j].end]=edges[j].start;

            }
        }
    }

    for(int j=0;j<edgenum;j++)                                              //判断有无负环 有返回true
        {
            if(dis[edges[j].end]>dis[edges[j].start]+edges[j].weight)
            {
                return true;
            }
        }
    return false;
}
int st=-1;                                          //寻找负环
bool get(int x )                                    //递归寻找前驱点，如果前驱点存在循环重复了，则代表有了负环
{
    ring.push_back(x);

    if (x==-1)      //no minus ring
        return false;
    if (x==st)
        return true;
    return get(pre[x]);
}
bool if_ring(int nodenum)                   //找到返回true，存在cycle中
{
    for(int i=0;i<nodenum;i++)
    {
        //cout<<"dasd"<<i<<endl;
        if(pre[i]==-1)
            continue;
        st=pre[i];
        if(get(pre[pre[i]]))
        {
            return true;
        }
        ring.clear();
    }
    return false;
}


// 0 1 1 1 2 2 2 3 2 3 0 1 0 2 3
// 0 1 1 1 2 2 2 3 1 3 4 2 4 0 1 4 2 -5
// 0 1 3 0 4 -1 4 2 2 2 1 1 1 3 2 3 2 -5
// 0 1 3 1 0 -2 1 4 7 1 3 1 2 1 4 3 2 -5 3 0 2 4 3 6 0 4 -4 1 3 8
int main(int argc, char** argv)
{
	int nums,edgecount;
	cout<<"Number of nodes:"<<endl;
	cin>>nums;
	cout<<"Number of edges:"<<endl;
	cin>>edgecount;


    construct_graph(nums,edgecount);
    print_tree();

    if(find_minus_ring(nums,edgecount))
    {
        cout<<"Exsiting minus ring"<<endl;
    }
    else{
        cout<<"No minus ring"<<endl;
    }
    cout<<endl<<"dis: ";
    for(int i=0;i<nums;i++)
    {
        cout<<dis[i]<<" ";
    }
    cout<<endl<<"pre: ";
    for(int i=0;i<nums;i++)
    {
        cout<<pre[i]<<" ";
    }

    cout<<endl<<"ring: ";;
    if(if_ring(nums))
    {
        for(int i=0;i<ring.size();i++)
        {
        cout<<ring[i]<<" ";
        }
    }

	return 0;
}
