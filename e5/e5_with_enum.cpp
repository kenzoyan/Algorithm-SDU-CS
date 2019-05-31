#include <iostream>
#include<vector>
#include<algorithm>
using namespace std;
int min_dis=100000;
int dis[10][10];

void construct_graph(int nums)
{
    for(int i=0;i<nums;i++)
    {
        for(int j=0;j<nums;j++)
        {
            cin>>dis[i][j];
        }
    }
}
int nums;
vector<int> ring;
void enumPath(int currentNode,int distance)
{
    vector<int>::iterator it;
    for(int i=0;i<nums;i++)
    {
        if(i==currentNode)
            continue;
        it=find(ring.begin(),ring.end(),i);
        if(it==ring.end())
        {
            ring.push_back(i);
            distance=distance+dis[currentNode][i];
            enumPath(i,distance);
            distance=distance-dis[currentNode][i];
            ring.pop_back();
        }
        else{
            if(ring.size()==nums)
            {
                distance=distance+dis[currentNode][0];
                if(min_dis>distance)
                    min_dis=distance;
                else return;
            }
        }
    }
}

int main()
{
    cout<<"NODES:"<<endl;
    cin>>nums;

    cout<<"CONSTRUCT GRAPH:"<<endl;
    construct_graph(nums);

    ring.push_back(0);
    enumPath(0,0);
    cout<<min_dis<<endl;
    return 0;
    //existing problems
}

/*0 3 3 2 6
3 0 7 3 2
3 7 0 2 5
2 3 2 0 3
6 2 5 3 0
*/
/*
        0, 10, 20, 30, 40, 50,
        12, 0 ,18, 30, 25, 21,
        23, 19, 0, 5,  10, 15,
        34, 32, 4, 0,  8,  16,
        45, 27, 11,10, 0,  18,
        56, 22, 16,20, 12,  0£¬
*/
