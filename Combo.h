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
		suit = i;
		rang = j;
	}	
	void PrintCard()
	{
		if(rang <11)
		{
			cout<< rang;
		}else{
			switch(rang)
			{
				case 11: cout<<"J";break;
				case 12: cout<<"D";break;
				case 13: cout<<"K";break;
				case 14: cout<<"T";break;
			}
		}
		cout<< '-';
		switch(suit)
		{
			case 0: cout<<'c';break;
			case 1: cout<<'b';break;
			case 2: cout<<'t';break;
			case 3: cout<<'p';break;
		}
	}
};


class Combo
{
public:
	//массив карт на руках
	Card plCards[5];

	//кака€ именно комбинаци€
	int numCombo;
	string nameCombo;

	//вспомогательные переменные дл€ вычислени€ комбинации
	bool testFlush;
	bool testStrit;
	int massiv[5][2];

	Combo()
	{
	}

	Combo ( vector<Card> cards ) {

		for(int i=0; i<5;i++)
		{
			plCards[i] = cards[i];
		}

		numCombo=11;
		testFlush=true;
		testStrit=false;
		int tmp=0;

		//	какие карты повтор€ютьс€
		for(int i=0;i<5;i++)
		{
			massiv[i][0]=plCards[i].rang;
			massiv[i][1]=1;
		}
		for(int j=0; j<4; j++)
		{
			for(int i=0; i<4-j; i++)
			{
				if(massiv[i][0] < massiv[i+1][0])
				{
					tmp = massiv[i][0];
					massiv[i][0] = massiv[i+1][0];
					massiv[i+1][0]=tmp; 
				}

			}
		}
		for(int i=4; i>0; i--)
		{
			if(massiv[i][0] == massiv[i-1][0])
			{
				massiv[i-1][1] += massiv[i][1];
				massiv[i][1]=0;
			}
		}
		for(int i=0; i<5; i++)
		{
			if(massiv[i][1]==0)
			{
				for(int j=i; j<4; j++)
				{
					tmp = massiv[j][1];
					massiv[j][1] = massiv[j+1][1];
					massiv[j+1][1] = tmp; 
				
					tmp = massiv[j][0];
					massiv[j][0] = massiv[j+1][0];
					massiv[j+1][0] = tmp; 
				}
				massiv[4][0]=0;
				massiv[4][1]=0;
			}
		}

		for(int j=0; j<4; j++)
		{
			for(int i=0; i<4-j; i++)
			{
				if(massiv[i][1] < massiv[i+1][1])
				{
					tmp = massiv[i][1];
					massiv[i][1] = massiv[i+1][1];
					massiv[i+1][1]=tmp; 
										
					tmp = massiv[i][0];
					massiv[i][0] = massiv[i+1][0];
					massiv[i+1][0]=tmp; 
				}

			}
		}
		//тест на флэш	
		for(int i=0; i<4; i++)
		{
			if(plCards[i].suit != plCards[i+1].suit)
			{
				testFlush=false;
			}
		}
		//тест на стрит;
		testStrit=true;
		for(int i=0; i<4; i++)
		{
			if(massiv[i][0]!=massiv[i+1][0]+1)
			{
				testStrit=false;
			}
		}

		GetCombo();
	}

	Combo(Card _plCards[5])
	{
		for(int i=0; i<5;i++)
		{
			plCards[i] = _plCards[i];
		}
		numCombo=11;
		testFlush=true;
		testStrit=false;
		int tmp=0;

		//	какие карты повтор€ютьс€
		for(int i=0;i<5;i++)
		{
			massiv[i][0]=plCards[i].rang;
			massiv[i][1]=1;
		}
		for(int j=0; j<4; j++)
		{
			for(int i=0; i<4-j; i++)
			{
				if(massiv[i][0] < massiv[i+1][0])
				{
					tmp = massiv[i][0];
					massiv[i][0] = massiv[i+1][0];
					massiv[i+1][0]=tmp; 
				}

			}
		}
		for(int i=4; i>0; i--)
		{
			if(massiv[i][0] == massiv[i-1][0])
			{
				massiv[i-1][1] += massiv[i][1];
				massiv[i][1]=0;
			}
		}
		for(int i=0; i<5; i++)
		{
			if(massiv[i][1]==0)
			{
				for(int j=i; j<4; j++)
				{
					tmp = massiv[j][1];
					massiv[j][1] = massiv[j+1][1];
					massiv[j+1][1] = tmp; 
				
					tmp = massiv[j][0];
					massiv[j][0] = massiv[j+1][0];
					massiv[j+1][0] = tmp; 
				}
				massiv[4][0]=0;
				massiv[4][1]=0;
			}
		}

		for(int j=0; j<4; j++)
		{
			for(int i=0; i<4-j; i++)
			{
				if(massiv[i][1] < massiv[i+1][1])
				{
					tmp = massiv[i][1];
					massiv[i][1] = massiv[i+1][1];
					massiv[i+1][1]=tmp; 
										
					tmp = massiv[i][0];
					massiv[i][0] = massiv[i+1][0];
					massiv[i+1][0]=tmp; 
				}

			}
		}
		//тест на флэш	
		for(int i=0; i<4; i++)
		{
			if(plCards[i].suit != plCards[i+1].suit)
			{
				testFlush=false;
			}
		}
		//тест на стрит;
		testStrit=true;
		for(int i=0; i<4; i++)
		{
			if(massiv[i][0]!=massiv[i+1][0]+1)
			{
				testStrit=false;
			}
		}

		GetCombo();
	}


	void GetCombo()
	{

		if(testFlush==true && testStrit==true)
		{
			if(massiv[0][0]==14)
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
		if(massiv[0][1]==3 && massiv[1][1]==2)
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
			
		if(massiv[0][1]==2 && massiv[1][1]==2)
		{
			numCombo = 8;
			nameCombo ="2 Pair";
			return;
		}
		if(massiv[0][1]==2)
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

	//если с1 больше то 0, если равны то 1, если меньше то 2
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

	//возращ€ет удачные индексы
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
		//		//??? ƒќЅј¬»“№ „»—Ћќ   ¬≈ “ќ–” 
		//		res[tmpI]=i;
		//		tmpI++;
		//	}
		//}
	}

	void PrintCombo()
	{
		//cout << "str=" << nameCombo;
		
		for(int i=0;nameCombo[i]!=0;i++)
		{
			cout <<nameCombo[i];
		}
	}
};