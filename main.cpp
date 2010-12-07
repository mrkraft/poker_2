#pragma once
#include "Combo.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>

using namespace std;

class Deck
{
	int CountOfCards;
	Card cards[52];
	int num;
		
	public:
	Deck()
	{
		num=0;
		CountOfCards = 52;
		int n = 0;
		for (int i = 0; i < 4; i++)
		{
		    for (int j = 2; j <= 14; j++)
		    {
		        cards[n] = Card(i, j);
				n++;
		    }
		}
	}

	void PrintAllCards()
	{
		for(int i=0; i<52; i++)
		{
			cout<< i << ":";
			PrintCard(i);
			cout<<" ";
		}
	}		
	void PrintCard(int i)
	{
		cards[i].PrintCard();
	}

	void Shafl()
	{
		num=0;
        for (int i = 0; i < CountOfCards; i++)
        {
			int rndInd = rand() % CountOfCards ;
            Card tmp = cards[i];
            cards[i] = cards[rndInd];
            cards[rndInd] = tmp;
        }
	}
	Card takeCard()
	{
		Card tmp = cards[num];
		num++;
		return tmp;
	}


};
int main()
{

	Deck mD;
	int stavka = 0;

	Card cards[5];

	//cards[0] = Card(1, 9);
	//cards[1] = Card(3, 4);
	//cards[2] = Card(1, 4);
	//cards[3] = Card(1, 5);
	//cards[4] = Card(1, 9);
	//Combo mC(cards);
	Combo comb;
	bool StopGame=false;
	bool flag1;
	bool flagPass;
	char x;
	while(!StopGame)
	{
			


		//new game?
		flag1=true;	
		while(flag1)
		{
			cout<<"(q)uit,(n)ew game"<<endl;
			cin>>x;		
			switch(x)
			{
				case 'q': StopGame=true; flag1=false; break;
				case 'n': cout<<endl; flag1=false; break;
			}
		}
		if(StopGame==false)
		{	
			mD.Shafl();
			for(int i=0; i<5; i++)
			{
				cards[i] = mD.takeCard();
			}
			comb = Combo(cards);
			flagPass=false;

			//pass, stavka ,next
			flag1=true;
			while(flag1)
			{	
				comb.PrintCombo();
				cout<<endl;
				for(int i=0; i<5; i++)
				{
					cards[i].PrintCard();
					cout<<' ';
				}
				cout<< endl <<"(p)ass, (s)tavka,(n)ext"<<endl;
				cin>>x;		
				switch(x)
				{
					case 'p': flag1=false; flagPass=true; break;
					case 's': break;
					case 'n': cout<<endl; flag1=false; break;
				}
			}

			//change cards	
			if(!flagPass)
			{
				cout<<"change cards"<<endl;
				//cards[2]=mD.takeCard();
				int i=0;
				scanf("%d", &i);
				
					while ( i > 0 ) {

					int tmp = i % 10;
					cards[tmp-1]=mD.takeCard();
					i /= 10;
					}

			}
			//pass, stavka ,END
			flag1=true;	
			while(flag1 && !flagPass)
			{	
				comb = Combo(cards);
				comb.PrintCombo();
				cout<<endl;
				for(int i=0; i<5; i++)
				{
					cards[i].PrintCard();
					cout<<' ';
				}
				cout<< endl<<"(p)ass, (s)tavka,(e)nd"<<endl;
				cin>>x;		
				switch(x)
				{
					case 'p': flag1=false; flagPass=true; break;
					case 's':  break;
					case 'e': cout<<endl; flag1=false; break;
				}
			}
			//result
			if(!flagPass)
			{
			}
			else
			{
				cout<< "your  passed"<<endl;
			}
		}
	}
	return 0;
}
