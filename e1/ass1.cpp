#include <iostream>
#include<list>

#define white 0
#define grey  1
#define black 2

using namespace std;
void DFS_visit(list<int> *graph,int *color,int *father,int currentNode,int num_nodes)
{
	color[currentNode]=grey;
	list<int>::iterator iter=graph[currentNode].begin();
	for(;iter!=graph[currentNode].end();iter++)             //遍历当前点的所有边查看点的颜色情况
	{
		if(color[*iter]==white)                             //白色 继续dfs
		{
			DFS_visit(graph,color,father,*iter,num_nodes);
		}
		else if(color[*iter]==black)
		{
			return;
		}
		else {
			cout<<"erase:"<<*iter<<endl;                    // 灰色删除该条边

			iter=graph[currentNode].erase(iter);
			iter--;
		}
	}
	color[currentNode]=black;
}
void DFS(list<int> *graph,int *color,int *father,int num_nodes)
{
	for(int i=0;i<num_nodes;i++)
	{
		if(color[i]==white)
		{
			DFS_visit(graph,color,father,i,num_nodes);
		}
	}
}
void print(list<int> *graph,int num_nodes)
{
	for(int i=0;i<num_nodes;i++)
	{
		list<int>::iterator iter;
		for(iter=graph[i].begin();iter!=graph[i].end();iter++)
		{
			cout<<*iter<<' ';
		}
		cout<<endl;
	}
}
//0 1 1 0 0 2 0 3 2 3 3 2
int main(int argc, char** argv) {
	int num_nodes,num_edges;
	int startP,endP;
	bool start=1;
	int currentNode=0;
	cout<<"Number of nodes:"<<endl;
	cin>>num_nodes;
	cout<<"Number of edges:"<<endl;
	cin>>num_edges;
	list<int> graph[num_nodes];
	print(graph,num_nodes);
	int color[num_nodes];
	int father[num_nodes];
	for(int i=0;i<num_nodes;i++)
	{
		color[i]=white;
		father[i]=0;
	}
	for(int i=0;i<num_edges;i++)
	{
		cout<<"Edge "<<i<<" :"<<endl;
		cin>>startP>>endP;
		graph[startP].push_back(endP);
	}
	print(graph,num_nodes);
	DFS(graph,color,father,num_nodes);
	print(graph,num_nodes);
	return 0;
}

