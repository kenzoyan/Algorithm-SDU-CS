#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
#define MAX_IN 10

class Tsp
{
	private:
		int city_number;		//���и���
		int **distance;			//���о������
		int **process;			//�����·���Ĺ��̾���
	public:
		Tsp(int city_number);		//���캯��
		void correct();			//��������ĳ��д��۾���
		void printCity();		//��ӡ���еľ������
		void getShoretstDistance();	//��̬�滮�������·��
		void printProcess();		//��ӡ���̾���

};

//���캯��
Tsp::Tsp(int city_num)
{
	int i=0,j=0;
	city_number=city_num;

	//��ʼ�����о������
	distance=new int*[city_number];
	cout<<"������"<<city_number<<"������֮��ľ���"<<endl;
	for(i=0;i<city_number;i++)
	{
		distance[i]=new int[city_number];
		for(j=0;j<city_number;j++)
			cin>>distance[i][j];
	}

	//���ɹ��̾���
	process=new int*[city_number];
	for(i=0;i<city_number;i++)
	{
		process[i]=new int[1<<(city_number-1)];
	}


}

//�����û�����ĳ��д��۾���
void Tsp::correct()
{
	int i;
	for(i=0;i<city_number;i++)
	{
		distance[i][i]=0;
	}
}

//��ӡ���о���
void Tsp::printCity()
{
	int i,j;
	//��ӡ���۾���
	cout<<"������ĳ��о�������"<<endl;
	for(i=0;i<city_number;i++)
	{
		for(j=0;j<city_number;j++)
			cout<<setw(3)<<distance[i][j];
		cout<<endl;
	}
}

//��̬�滮�������·��
void Tsp::getShoretstDistance()
{
	int i,j,k;
	//��ʼ����һ��
	for(i=0;i<city_number;i++)
	{
		process[i][0]=distance[i][0];
	}
	//��ʼ��ʣ����
	for(j=1;j<(1<<(city_number-1));j++)         //<<�õ��������еĸ��� ����
	{
		for(i=0;i<city_number;i++)
		{
			process[i][j]=0x7ffff;//��0x7ffffΪ�����

			//��������x��Ҫ�����ĵ�iλ�ǲ���1��ͨ���жϲ������ʽ (((x >> (i - 1) ) & 1) == 1����ֵ��ʵ��

			if(((j>>(i-1))&1)==1)
			{
				continue;
			}
			for(k=1;k<city_number;k++)
			{
				//���ܴﵽk����
				if(((j>>(k-1))&1)==0)
				{
					continue;
				}
				if(process[i][j]>distance[i][k]+process[k][j ^ (1 << (k - 1))])
				{
					process[i][j]=distance[i][k]+process[k][j ^ (1 << (k - 1))];
					//cout<<i<<"��"<<j<<"��Ϊ��"<<process[i][j]<<endl;
				}
			}
		}
	}
	cout<<"���·��Ϊ"<<process[0][(1<<(city_number-1))-1]<<endl;

}

//��ӡ���̾���
void Tsp::printProcess()
{
	int i,j;
	for(j=0;j<1<<(city_number-1);j++)
	{
		cout<<setw(3)<<j;
	}
	cout<<endl;
	for(i=0;i<city_number;i++)
	{
		for(j=0;j<1<<(city_number-1);j++)
		{
			if(process[i][j]==0x7ffff)
				process[i][j]=-1;
			cout<<setw(3)<<process[i][j];
		}
		cout<<endl;

	}
}

//������
int main(void)
{
	cout<<"��ӭ������̬�滮�����������⣬��������и���";
	int city_number;
	while(cin>>city_number)
	{
       Tsp tsp(city_number);		//��ʼ�����д��۾���
	   //tsp.correct();					//�����û�����Ĵ��۾���
	   tsp.printCity();				//��ӡ����
	   tsp.getShoretstDistance();		//������·��
	   tsp.printProcess();			//��ӡ�������
	   cout<<"---------------------------------------"<<endl;
	   cout<<"��ӭ������̬�滮�����������⣬��������и���";
	}

	return 0;
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
        56, 22, 16,20, 12,  0��
*/
