#include <iostream>
#include<math.h>
#include<vector>
#include<list>
using namespace std;

#define white 0
#define gray 1
#define black 2
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
	edge(){}
};



void print(vector<vector<int> > &T,int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<T[i][j]<<"   ";
		}
		cout<<endl;
	}
}



edge DFS_visit(vector<vector<int> > &T,int *color,int currentNode,int fatherNode,int n,vector<edge> edges)
{
	edge flag(0,0,0);
	color[currentNode]=gray;
	edge a(0,0,0);
	for(int i=0;i<n;i++)
	{
		if(T[currentNode][i]!=0&&i!=fatherNode)             //��ͨ·�Ҳ��Ǹ��ڵ�
		{
			a.start=currentNode;
			a.end=i;
			a.weight=T[currentNode][i];                     //a��Ϊ��ǰ���ʱ�
			edges.push_back(a);
			if(color[i]==white)                                 //δ���ʵĽڵ�
			{
				a=DFS_visit(T,color,i,currentNode,n,edges);
				if(a.weight!=0)                       //û���γɻ������Է��ص���0
				{
					flag=a;
					break;                                       //����flag��
				}
				else                                            //ȨֵΪ0��˵�����ɻ���pop����
				{
					edges.pop_back();
				}
			}
			else if(color[i]==gray)                            //�ҵ�����ߣ�˵���л� ,����maxedge
			{

				int max=0;
				int max_weight=0;
				for(int j=0;j<edges.size();j++)
				{

					if(max_weight<edges[j].weight)
					{
						max=j;
						max_weight=edges[j].weight;
					}
				}
				flag=edges[max];
				break;
			}
		}
	}
	color[currentNode]=black;
	return flag;
}


edge add_edge(vector<vector<int> > &T,edge e,int n)
{
	T[e.start][e.end]=e.weight;
	T[e.end][e.start]=e.weight;
	int colors[n];
	for(int i=0;i<n;i++)
	{
		colors[i]=white;
	}
	colors[e.start]=grey;
	vector<edge> edges;
	edge zero(0,0,0);
	edge a=DFS_visit(T,colors,e.start,e.start,n,edges);  //����0����û�ɻ���������ֵ�ʹ���ɻ�֮��ɾ��һ����
	if(a.weight==0)
	{
		return zero;
	}
	else {
		return a;
	}

}

// 0 1 1 1 2 2 2 3 2 3 0 1 0 2 3
// 0 1 2 0 2 5 0 4 1 1 2 4 1 3 3 3 4 2
/*
1 2 4
1 8 8
2 3 8
2 8 11
3 4 7
3 6 4
3 9 2
4 5 9
4 6 14
5 6 10
6 7 2
7 8 1
7 9 6
8 9 7
*/
int main(int argc, char** argv) {
	int n,m;
	int start,end,weight;
	cout<<"NODES?"<<endl;
	cin>>n;
	int color[n];
	int forward[n];
	for(int i=0;i<n;i++)
	{
		color[i]=white;
		forward[i]=0;
	}
	vector<vector<int> > T(n,vector<int>(n,0));
	cout<<"EDGES"<<endl;
	cin>>m;
	vector<edge> edges(m);
	for(int i=0;i<m;i++)
	{
		cin>>start>>end>>weight;
		edges[i].start=start-1;
		edges[i].end=end-1;
		edges[i].weight=weight;
	}
	edge a(0,0,0);

	for(int i=0;i<m;i++)
	{
		edge a=add_edge(T,edges[i],n); //����0�ʹ�����ӳɹ���������ֵ�ʹ������֮��ɾ��������
		if(a.weight!=0)
		{
			T[a.start][a.end]=0;
			T[a.end][a.start]=0;
			cout<<"remove"<<a.start<<"-->"<<a.end<<endl;
		}
	}
	print(T,n);
	return 0;
}
