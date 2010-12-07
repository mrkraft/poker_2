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
	int money=100;

	Card cards[5];
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
			stavka=5;
			money-=stavka;

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
				cout<< "money:" << money << " stavka:" <<stavka<<endl;
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
					case 's': stavka+=5;money-=5;break;
					case 'n': cout<<endl; flag1=false; break;
				}
			}

			//change cards	
			if(!flagPass)
			{
				cout<<"change cards /(11)-nochanges"<<endl;
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
				cout<< "money:" << money << " stavka:" <<stavka<<endl;
				comb = Combo(cards);
				
				flag1=false;

				comb.PrintCombo();
				cout<<endl;
				for(int i=0; i<5; i++)
				{
					cards[i].PrintCard();
					cout<<' ';
				}
				//cout<< endl<<"(p)ass, (s)tavka,(e)nd"<<endl;
				//cin>>x;		
				//switch(x)
				//{
				//	case 'p': flag1=false; flagPass=true; break;
				//	case 's': stavka+=5;money-=5; break;
				//	case 'e': cout<<endl; flag1=false; break;
				//}
			}
			//result
			if(!flagPass)
			{
				if(comb.numCombo==1)
				{
					money+=stavka*50;
				}				
				if(comb.numCombo==2)
				{
					money+=stavka*25;
				}
								
				if(comb.numCombo==3)
				{
					money+=stavka*20;
				}				
				if(comb.numCombo==4)
				{
					money+=stavka*10;
				}
								
				if(comb.numCombo==5)
				{
					money+=stavka*5;
				}				
				if(comb.numCombo==6)
				{
					money+=stavka*4;
				}
								
				if(comb.numCombo==7)
				{
					money+=stavka*3;
				}				
				if(comb.numCombo==8)
				{
					money+=stavka*2;
				}
				if(comb.numCombo<9)
				{
					cout<<endl<<"You win"<<endl;
				}
				else
				{
					cout<<endl<<"You lose"<<endl;
				}
			}
			else
			{
				cout<< "your  passed"<<endl;
			}
		}
	}
	return 0;
}
