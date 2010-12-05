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
		
	public:
	Deck()
	{
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
		int rang =	cards[i].rang;
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
		int suit =	cards[i].suit;
		switch(suit)
		{
			case 0: cout<<'v';break;
			case 1: cout<<'b';break;
			case 2: cout<<'t';break;
			case 3: cout<<'p';break;
		}
	}

		void Shafl()
	{
        for (int i = 0; i < CountOfCards; i++)
        {
			int rndInd = rand() % CountOfCards ;
            Card tmp = cards[i];
            cards[i] = cards[rndInd];
            cards[rndInd] = tmp;
        }
	}

};

int main()
{

	Deck mD;
	//mD.Shafl();
	mD.PrintAllCards();
	return 0;
}
