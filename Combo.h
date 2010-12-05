#pragma once
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Card
{
	int rang;
	int suit;


	Card()
	{
	}

	Card(int i, int j)
	{
		rang = j;
		suit = i;
	}
	    
};


class Combo
{
public:
	//������ ���� �� �����
	Card plCards[5];

	//����� ������ ����������
	int numCombo;
	string nameCombo;

	//��������������� ���������� ��� ���������� ����������
	bool testFlush;
	bool testStrit;
	int massiv[5][2];

	Combo()
	{
		numCombo=11;
		testFlush=true;
		testStrit=false;
		int tmp=0;
		//	����� ����� ������������
		for(int i=0;i<5;i++)
		{
			massiv[i][0]=plCards[i].rang;
			massiv[i][1]=1;
		}
		for(int i=0; i<5; i++)
		{
			for(int j=5-i; j>i; j--)
			{
				if(massiv[j-1][0] > massiv[j][0])
				{
					tmp=massiv[j-1][0];
					massiv[j-1][0] = massiv[j][0];
					massiv[j][0]=tmp; 
				}
			}
		}
		for(int i=4; i>0; i--)
		{
			if(massiv[i][0] = massiv[i-1][0])
			{
				massiv[i-1][1] += massiv[i][1];
				massiv[i][1]=0;
			}
		}
		for(int i=0; i<5; i++)
		{
			for(int j=5-i; j>i; j--)
			{
				if(massiv[j-1][1] > massiv[j][1])
				{
					tmp=massiv[j-1][1];
					massiv[j-1][1] = massiv[j][1];
					massiv[j][1] = tmp; 
				}
			}
		}
		//���� �� ����	
		for(int i=0; i<4; i++)
		{
			if(plCards[i].suit != plCards[i+1].suit)
			{
				testFlush=false;
			}
		}
		//���� �� �����;
		for(int i=0; i<4; i++)
		{
			if(massiv[i][0]!=massiv[i][0]-1)
			{
				testStrit=false;
			}
		}

		Funk();
	}


	void Funk()
	{

		if(testFlush==true && testStrit==true)
		{
			if(massiv[0][0]=14)
			{
				numCombo = 1;
				nameCombo ="Royal Flush";
				return;
			}else{
				numCombo = 2;
				nameCombo ="Straight Flush";
				return;
			}
		}
		if(massiv[0][1]==3 && massiv[0][2]==2)
		{
			numCombo = 3;
			nameCombo ="Full House";
			return;
		}
		if(massiv[0][1]==4)
		{
			numCombo = 4;
			nameCombo ="Kare";
			return;
		}
		if(testFlush==true)
		{
			numCombo = 5;
			nameCombo ="Flush";
			return;
		}	
		if(testStrit==true)
		{
			numCombo = 6;
			nameCombo ="Straight";
			return;
		}
		if(massiv[0][1]==3)
		{
			numCombo =7;
			nameCombo ="3 of a kind";
			return;
		}
			
		if(massiv[0][1]==2 && massiv[0][2]==2)
		{
			numCombo = 8;
			nameCombo ="2 Pair";
			return;
		}
		if(massiv[0][1]==3)
		{
			numCombo =9;
			nameCombo ="Pair";
			return;
		}
		else
		{	
			numCombo =10;
			nameCombo ="high card";
			return;
		}
	}
	//���� �1 ������ �� 0, ���� ����� �� 1, ���� ������ �� 2
	int sravnenie(Combo c1, Combo c2)
{
	if(c1.numCombo > c2.numCombo)
	{
		return 0;
	}
	if(c1.numCombo < c2.numCombo)
	{
		return 2;
	}
	for(int i=0; i<5; i++)
	{
		if(c1.massiv[1][i]>c2.massiv[1][i])
		{
			return 0;
		}	
		if(c1.massiv[1][i]<c2.massiv[1][i])
		{
			return 2;
		}
	}
	return 1;
}
	//��������� ������� �������
	vector<int> getIndex()
	{
		vector<int> res;
		if(testFlush==true || testStrit==true)
		{
			for(int i=0; i<5;i++)
			{
				res[i]=i;
			}
			return res;
		}	

		int tmp = massiv[0][0];
		int tmpI = 0;
		//for(int i=0; i<4; i++)
		//{
		//	if(plCards[i]==tmp)
		//	{
		//		//??? �������� ����� � ������� 
		//		res[tmpI]=i;
		//		tmpI++;
		//	}
		//}
	}

};