#include </media/win_c2/PROGGA/GIT/porer_linux/cppunit/TestRunner.h>
#include "AIPlayer.h"
#include "Test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(Test);

using namespace std;

class Deck
{
	int CountOfCards;
	Card cards[52];
	int num;
		
	public:
	Deck()
	{

		time_t t;
		struct tm *t_m;
		t=time(NULL);
		t_m=localtime(&t);

		srand ( (int) time ( NULL ) );

		srand ( t_m->tm_hour * t_m->tm_sec * t_m->tm_min * t_m->tm_mday * rand() );

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
		if ( num == 52 ) {
			num = 0;
		}
		Card tmp = cards[num];
		num++;
		return tmp;
	}
};

class game {
public:

	int ai_num;
	int min_bet;
	int money;
	
	// human-player
	Card my_cards[5];
	int my_money;

	// system
	int round;
	int bet;
	int bet_sum;
	vector<AIPlayer> ai_players;
	Deck deck;

	game() {

		ai_num = 1;
		min_bet = 0;
		money = 0;
		my_money = 0;

		round = 0;
		bet = 0;
		bet_sum = 0;
	}

	~game(){
	}

	void nextTurn() {
		
		round++;
		bet = 0;
		bet_sum = 0;

		for ( int i = 0; i < ai_num; i++ ) {
			ai_players[i].reset();
		}
	}

	void createAIPlayers() {
		
		if ( ai_num > 0 ) {
			for ( int i = 0; i < ai_num; i++ ) {
				ai_players.push_back ( AIPlayer() );
				ai_players[i].min_bet = min_bet;
				ai_players[i].money = money;
			}
		}
	}

	int getActivePlayersCount() {
		int sum = 0;
		for ( int i = 0; i < ai_num; i++ ) {
			
			if ( ai_players[i].is_fold == false ) {

				sum++;
			}
		}
		return sum;
	}

	void setBets ( int stage ) {
		
		bool is_equal = false;
		while ( !is_equal ) {

			if ( getActivePlayersCount() == 0 ) {
				break;
			}
			is_equal = true;
			
			for ( int i = 0; i < ai_num; i++ ) {
				
				if ( ai_players[i].is_fold == false ) {
					
					if ( ai_players[i].bet < bet ) {
						
						is_equal = false;
						int temp = ai_players[i].AcceptFoldIncrease ( stage, bet );
						if ( temp > bet ) {
							bet = temp;
						}
					}
				}
			}
		}

		for ( int i = 0; i < ai_num; i++ ) {
			
			if ( ai_players[i].is_fold == false ) {
				bet_sum += bet;
			}
		}
	}

	void shaflDeck() {

		deck.Shafl();
	}

	void setCards() {
		
		for ( int i = 0; i < 5; i++ ) {
			my_cards[i] = deck.takeCard();
		}

		for ( int i = 0; i < ai_num; i++ ) {
			vector<Card> temp_cards;
			temp_cards.push_back ( deck.takeCard() );
			temp_cards.push_back ( deck.takeCard() );
			temp_cards.push_back ( deck.takeCard() );
			temp_cards.push_back ( deck.takeCard() );
			temp_cards.push_back ( deck.takeCard() );
			ai_players[i].setCards ( temp_cards );
		}
	}

	void printMyCards() {
		
		cout<<"my cards: ";
		for ( int i = 0; i < 5; i++ ) {
			my_cards[i].PrintCard();
			cout<<" ";
		}
		cout<<endl;
	}

	void changeCards() {
		
		for ( int i = 0; i < ai_num; i++ ) {
			
			if ( ai_players[i].is_fold == false ) {
				
				int tmp_count = ai_players[i].CardsToShare();

				vector<Card> temp_cards;
				for ( int j = 0; j < tmp_count; j++ ) {
					temp_cards.push_back ( deck.takeCard() );
				}

				ai_players[i].addCards ( temp_cards );
			}
		}
	}

	void changeMyCards ( int data ) {
		
		while ( data > 0 ) {
			
			int tmp_ind = data % 10 - 1;
			if ( tmp_ind >= 0 && tmp_ind <= 4 ) {
				
				my_cards[tmp_ind] = deck.takeCard();
			}
			data = data / 10;
		}
	}

	// ����� ������ ����������� ai - �� �������
	void findOneWinner() {

		for ( int i = 0; i < ai_num; i++ ) {
			
			if ( ai_players[i].is_fold == false ) {
				cout<<"WINNER player " << i + 1 <<endl;
				ai_players[i].money += bet_sum;
				break;
			}
		}
	}

	void printAICards() {

		for ( int i = 0; i < ai_num; i++ ) {
			
			if ( ai_players[i].is_fold == false ) {
				
				cout<<"cards of player" << i + 1 << " : ";
				for ( int j = 0; j < 5; j++ ) {
					ai_players[i].cards[j].PrintCard();
					cout<<" ";
				}
				cout<<endl;
			}
		}
	}

	void checkCombinationsWithMe() {
		
		vector<Combo> tmp_combo;
		tmp_combo.push_back ( Combo ( my_cards ) );

		for ( int i = 0; i < ai_num; i++ ) {
			tmp_combo.push_back ( Combo ( ai_players[i].cards ) );
		}

		int index = 0;
		vector<int> winners;
		winners.push_back ( 0 );
		for ( int i = 1; i < ai_num + 1; i++ ) {
			if ( ai_players[i - 1].is_fold == false ) {
				int tmp = tmp_combo[index].sravnenie ( tmp_combo[index], tmp_combo[i] );

				if ( tmp == 1 ) {

					winners.push_back ( i );

				} else if ( tmp == 0 ) {
					
					winners.clear();
					index = i;
					winners.push_back ( i );
				}
			}
		}

		cout<< "WINNER(S):" << endl;
		if ( winners.size() > 1 ) {

			int prize = bet_sum / winners.size();


			for ( int i = 0; i < winners.size(); i++ ) {
				if ( i == 0 ) {
					if ( winners[0] == 0 ) {
						cout<< "you" << endl;
						my_money += prize;
					} else {
						cout<< "player" << winners[i] << endl;
						ai_players[winners[i] - 1].money += prize;
					}
				} else {
					cout<< "player" << winners[i] << endl;
					ai_players[winners[i] - 1].money += prize;
				}
			}
		} else if ( winners.size() == 1 ){
			
			if ( winners[0] == 0 ) {
				cout<< "you" << endl;
				my_money += bet_sum;
			} else {
				cout<< "player" << winners[0] << endl;
				ai_players[winners[0] - 1].money += bet_sum;
			}
		}
	}

	void checkCombinations() {
		
		vector<Combo> tmp_combo;

		int index = -1;
		for ( int i = 0; i < ai_num; i++ ) {
			if ( index == -1 && ai_players[i].is_fold == false ) {
				index = i;
			}
			tmp_combo.push_back ( Combo ( ai_players[i].cards ) );
		}

		vector<int> winners;
		winners.push_back ( index );
		for ( int i = 1; i < ai_num; i++ ) {
			if ( ai_players[i].is_fold == false ) {
				int tmp = tmp_combo[index].sravnenie ( tmp_combo[index], tmp_combo[i] );

				if ( tmp == 1 ) {

					winners.push_back ( i );

				} else if ( tmp == 0 ) {
					
					winners.clear();
					index = i;
					winners.push_back ( i );
				}
			}
		}

		cout<< "WINNER(S):" << endl;
		int prize = bet_sum / winners.size();
		for ( int i = 0; i < winners.size(); i++ ) {
			cout<< "player" << winners[i] << endl;
			ai_players[winners[i]].money += prize;
		}
	}
	

};

int StrToNum ( char* str ) {

	int res_num = 0;
	for ( int i = 0 ; str[i] != 0; i++ ) {
		
		if ( i != 0 ) {
			res_num *= 10;
		}

		switch ( str[i] ) {
			case '1' : res_num += 1; break;
			case '2' : res_num += 2; break;
			case '3' : res_num += 3; break;
			case '4' : res_num += 4; break;
			case '5' : res_num += 5; break;
			case '6' : res_num += 6; break;
			case '7' : res_num += 7; break;
			case '8' : res_num += 8; break;
			case '9' : res_num += 9; break;
		}

	}

	return res_num;
}

int main ( int argc, char* argv[] ) 
{
  
	CppUnit::TextUi::TestRunner runner;
   	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
  	runner.addTest( registry.makeTest() );
   	runner.run();

	if ( argv[1][0] == '1' ) {	// lets TEST

		game the_game;
		the_game.shaflDeck();
		
		Card plCards[5];
		vector<Card> cards;
		for ( int i = 0; i < 5; i++ ) {

			plCards[i] = the_game.deck.takeCard();
			cards.push_back ( the_game.deck.takeCard() );
		}

		Combo combo ( plCards );
		combo.GetCombo();
		combo.PrintCombo();
		combo.sravnenie ( combo, combo );

		AIPlayer player;
		player.setCards ( cards );
		player.AcceptFoldIncrease ( 2, 200 );
		player.cardSort();
		player.getCardSequence();
		player.getSameSuit();
		player.CardsToShare();
		
		cout<<"\r\n";


	} else {					// lets PLAY
		
		game the_game;

		//ai players count
		if ( argc > 2 ) {

			the_game.ai_num = StrToNum ( argv[2] );

		} else {

			the_game.ai_num = 3;
		}

		//start money
		if ( argc > 3 ) {

			int num = StrToNum ( argv[3] );
			the_game.money = num;
			the_game.my_money = num;

		} else {

			the_game.money = 1000;
			the_game.my_money = 1000;
		}

		//min bet
		if ( argc > 4 ) {
			
			the_game.min_bet = StrToNum ( argv[4] );

		} else {

			the_game.min_bet = 10;
		}
		the_game.createAIPlayers();

	
		Combo comb;
		bool StopGame=false;
		bool flag1;
		bool flagPass;
		char x;

		bool i_play = true;		// ��������� �� � ����
		bool stage_1 = true;
		bool stage_2 = true;
		bool stage_3 = true;
		int data;

		while(!StopGame)
		{

			//new game?
			flag1=true;	
			while(flag1)
			{
				cout<<"-> (q)uit,(n)ew game"<<endl;
				cin>>x;		
				switch(x)
				{
					case 'q': StopGame=true; flag1=false; break;
					case 'n': cout<<endl; flag1=false; break;
				}
			}
			if(StopGame==false)
			{	


				i_play = true;
				stage_1 = true;
				stage_2 = true;
				stage_3 = true;
				the_game.nextTurn();
				cout<<"ROUND #"<< the_game.round <<endl;

				// PERED RAZDACHEY
				cout<<"####### BEFOR PLAY" << endl;
				cout<< "your money:" << the_game.my_money <<endl;
				flag1=true;
				while(flag1)
				{	
					cout<< "-> enter a bet"<<endl;
					cin>> data;
					if ( data >= the_game.min_bet && data < the_game.my_money ) {
						the_game.bet = data;
						the_game.setBets(1);
						the_game.my_money -= data;
						the_game.bet_sum += data;
					} else {
						data = 10;
						the_game.bet = data;
						the_game.setBets(1);
						the_game.my_money -= data;
						the_game.bet_sum += data;
					}

					if ( the_game.getActivePlayersCount() == 0 ) {
						stage_1 = false;
						cout<<"You WIN :" << data << endl;
						the_game.my_money += data;
						break;
					}

					// esli stavku povisil comp
					if ( the_game.bet > data )  {
						cout<< "bet is chenged:"<< the_game.bet <<endl;
						cout<< "-> are you raise the bet? ( (y)es, (n)o )"<<endl;
						cin>> x;

						if ( x != 'y' ) {

							i_play = false;

						} else {

							the_game.my_money -= the_game.bet - data;
							the_game.bet_sum += the_game.bet - data;
						}
					}

					flag1 = false;
				}
				
				// RAZDACHA KART
				if ( stage_1 ) {

					cout<<"####### TAKE CARDS" << endl;

					the_game.shaflDeck();
					the_game.setCards();
					if ( i_play ) {
						the_game.printMyCards();

						cout<< "my money:" << the_game.my_money << " bank:" << the_game.bet_sum<<endl;
					}

					//pass, stavka ,next
					flag1=true;
					while(flag1)
					{	
						if ( i_play ) {
							cout<< "-> enter a bet ( 0 - pass )"<<endl;
							cin>> data;
						} else {
							data = 0;
						}

						if ( data <= 0 || the_game.my_money < 10 ) {
							i_play = false;
							the_game.bet = 0;
							the_game.setBets(2);
							the_game.bet_sum += data;

						} if ( data >= the_game.min_bet && data < the_game.my_money ) {

							the_game.bet = data;
							the_game.setBets(2);
							the_game.my_money -= data;
							the_game.bet_sum += data;
						} else {
							data = 10;
							the_game.bet = data;
							the_game.setBets(2);
							the_game.my_money -= data;
							the_game.bet_sum += data;
						}

						if ( the_game.getActivePlayersCount() == 0 ) {

							stage_2 = false;

							if ( i_play ) {
								cout<<"You WIN :" << the_game.bet_sum << endl;
								the_game.my_money += the_game.bet_sum;
							} else {
								cout<<"There's n winners in this round !!!" << endl;
							}
							break;
						}

						if ( !i_play ) {

							if ( the_game.getActivePlayersCount() == 1 ) {
								the_game.findOneWinner();
								stage_2 = false;
							}
							break;
						}

						// esli stavku povisil comp
						if ( the_game.bet > data )  {
							cout<< "bet is chenged:"<< the_game.bet <<endl;
							cout<< "-> are you raise the bet? ( (y)es, (n)o )"<<endl;
							cin>> x;

							if ( x != 'y' ) {

								i_play = false;

							} else {

								the_game.my_money -= the_game.bet - data;
								the_game.bet_sum += the_game.bet - data;
							}
						}

						flag1 = false;
					}
					
					// OBMEN KART
					if ( stage_2 ) {

						cout<<"####### CHANGE CARDS" << endl;

						the_game.changeCards();
						if ( i_play ) {
							the_game.printMyCards();

							cout<< "-> enter numbers of cards for exchange:"<<endl;
							cin>> data;
							if ( data < 55555 && data >= 1 ) {
								the_game.changeMyCards ( data );
							}

							the_game.printMyCards();

							cout<< "my money:" << the_game.my_money << " bank:" << the_game.bet_sum<<endl;
						}

						//pass, stavka ,END
						flag1=true;	
						while(flag1)
						{	
							if ( i_play ) {
								cout<< "-> enter a bet ( 0 - pass )"<<endl;
								cin>> data;
							} else {
								data = 0;
							}

							if ( data <= 0 || the_game.my_money < 10 ) {
								i_play = false;
								the_game.bet = 0;
								the_game.setBets(3);
								the_game.bet_sum += data;

							} if ( data >= the_game.min_bet && data < the_game.my_money ) {

								the_game.bet = data;
								the_game.setBets(3);
								the_game.my_money -= data;
								the_game.bet_sum += data;
							} else {
								data = 10;
								the_game.bet = data;
								the_game.setBets(3);
								the_game.my_money -= data;
								the_game.bet_sum += data;
							}

							if ( the_game.getActivePlayersCount() == 0 ) {

								stage_3 = false;

								if ( i_play ) {
									cout<<"You WIN :" << the_game.bet_sum << endl;
									the_game.my_money += the_game.bet_sum;
								} else {
									cout<<"There's n winners in this round !!!" << endl;
								}
								break;
							}

							if ( !i_play ) {

								if ( the_game.getActivePlayersCount() == 1 ) {
									the_game.findOneWinner();
									stage_3 = false;
								}

								break;
							}

							// esli stavku povisil comp
							if ( the_game.bet > data )  {
								cout<< "bet is chenged:"<< the_game.bet <<endl;
								cout<< "-> are you raise the bet? ( (y)es, (n)o )"<<endl;
								cin>> x;

								if ( x != 'y' ) {

									i_play = false;

								} else {

									the_game.my_money -= the_game.bet - data;
									the_game.bet_sum += the_game.bet - data;
								}
							}

							flag1 = false;
						}

						if ( stage_3 ) {

							cout<<"####### FIND WINNERS" << endl;
							
							if ( i_play ) {
							  
								the_game.printMyCards();
								the_game.printAICards();
								the_game.checkCombinationsWithMe();
							} else {
							  
								the_game.printAICards();
								the_game.checkCombinations();
							}
						}


						//result
					}
				}
			}
		}

	}

	return 0;
}
