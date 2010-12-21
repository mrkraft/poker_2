#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include "Combo.h"

using namespace std;

class AIPlayer {
public:

	double bluff;	// вероятнось блефа
	double risk;	// вероятность риска 

	bool is_fold;	// сфолил
	bool is_shared;	// обменял

	int money;
	int bet;
	int bet_sum;
	int min_bet;

	vector <Card> cards;

public:
	
	AIPlayer() {

		time_t t;
		struct tm *t_m;
		t=time(NULL);
		t_m=localtime(&t);

		srand ( (int) time ( NULL ) );

		srand ( t_m->tm_hour * t_m->tm_sec * t_m->tm_min * t_m->tm_mday * rand() );
		bluff = ( ( (double)rand() / (double)32767 ) + ( (double)rand() / (double)32767 ) ) / 2;
		risk = ( ( (double)rand() / (double)32767 ) + ( (double)rand() / (double)32767 ) ) / 2;

		money = 10000;
		min_bet = 10;

		reset();
	}

	~AIPlayer() {
	}

	// восстановить начальные параметры
	void reset() {
		
		is_shared = false;
		is_fold = false;
		bet = 0;
		bet_sum = 0;
	}

	// получить карты при раздаче
	void setCards ( vector<Card> _cards ) {

		cards = _cards;
	}

	// получить обменяные карты
	void addCards ( vector<Card> exchanged_cards ) {
		
		is_shared = true;

		for ( int i = 0; i < exchanged_cards.size(); i++ ) {

			cards.push_back ( exchanged_cards[i] );
		}
	}

	// карты для обмена
	int CardsToShare() {

		cardSort();
		
		vector<int> same_suit = getSameSuit();
		vector<int> cards_sequence = getCardSequence();

		if ( true /* ���� ���������� */ ) {
			/* ������ �� �������� � ����������*/
		}

		if ( same_suit.size() < 3 && cards_sequence.size() < 3 ) {
			
			if ( ( (double)rand() / (double)32767 ) + risk > 0.8 ) {	
				
				int arr[] = { 0,1,2,3,4 };
				deleteCards ( arr, 5 );
				return 5;
			}

			if ( cards[3].rang >= 10 ) {	
				
				int arr[] = { 0,1,2 };
				deleteCards ( arr, 3 );
				return 3;
			}

			if ( same_suit.size() > 1 ) {
			
				deleteCards ( getOther ( same_suit ), 3 );
				return 3; 

			}

			int arr[] = { 0,1,2,3 };
			deleteCards ( arr, 4 );
			return 4;

		} else {
			
			if ( same_suit.size() > cards_sequence.size() ) {
				
				int tmp = 5 - same_suit.size();
				deleteCards ( getOther ( same_suit ), tmp );
				return tmp; 
			} 

			if ( same_suit.size() < cards_sequence.size() ) {
				
				int tmp = 5 - cards_sequence.size();
				deleteCards ( getOther ( cards_sequence ), tmp );
				return tmp; 
			}

			if ( same_suit.size() == cards_sequence.size() ) {
				
				// ������� ��������� � �������� 2-14 ( � ���� ������ ����� ������ )
				if ( cards[cards_sequence[0]].rang > 3 && cards[cards_sequence[cards_sequence.size() - 1]].rang < 13 ) {

					int tmp = 5 - cards_sequence.size();
					deleteCards ( getOther ( cards_sequence ), tmp );
					return tmp;

				} else {
					
					int tmp = 5 - same_suit.size();
					deleteCards ( getOther ( same_suit ), tmp );
					return tmp;
				}
			}
		}

		int arr[] = { 0,1,2,3,4 };
		deleteCards ( arr, 5 );
		return 5;

	} 

	// поставить ставку первым| stage - этап ставок
	int setBet ( int stage ) {

		if ( money == 0 ) {	// пас
			is_fold = true;
			return -1;	
		}

		if ( stage == 1 ) {

			if ( ( (double)rand() / (double)32767 ) * bluff > 0.6 ) {

				bet = 2 * min_bet + ( (double)rand() / (double)32767 ) * 5 * min_bet;
				if ( bet < money ) {

					money -= bet;
					bet_sum += bet;
					return bet;

				} else {

					bet = money;
					money = 0;
					bet_sum += bet;
					return bet;
				}
			} else {
				bet = min_bet;
				if ( bet < money ) {

					money -= bet;
					bet_sum += bet;
					return bet;

				} else {

					bet = money;
					money = 0;
					bet_sum += bet;
					return bet;
				}
			}
		}

		Combo tmp( cards );

		if ( stage == 2 ) {		// ставка после раздачи
			
			if ( tmp.numCombo == 10 ) { 

				// пасуем
				if ( bluff * ( (double)rand() / (double)32767 ) < 0.04 ) {
					is_fold = true;
					return -1;	
				}

				bet = min_bet;
				if ( bluff * ( (double)rand() / (double)32767 ) > 0.52 ) {
					bet += ( (double)rand() / (double)32767 ) * min_bet * 5 ;
				}

				if ( bet < money ) {

					money -= bet;

				} else {

					bet = money;
					money = 0;
				}

				bet_sum += bet;

				return bet;

			} else {
				
				bet = min_bet + ( (double)rand() / (double)32767 ) * ( 1 + 10 - tmp.numCombo ) * min_bet;
				if ( bet < money ) {

					money -= bet;

				} else {

					bet = money;
					money = 0;
				}
				bet_sum += bet;
				return bet;
			} 
		} else if ( stage == 3 ) {		// ставка после обмена

			if ( tmp.numCombo == 10 ) {
				// пасуем
				if ( bluff * ( (double)rand() / (double)32767 ) < 0.08 ) {
					is_fold = true;
					return -1;	
				}
			}
			
			if ( tmp.numCombo >= 9 ) { 

				bet = min_bet * 2;
				if ( bluff * ( (double)rand() / (double)32767 ) > 0.5 ) {
					bet += ( (double)rand() / (double)32767 ) * min_bet * 10 ;
				}

				if ( bet < money ) {

					money -= bet;

				} else {

					bet = money;
					money = 0;
				}

				bet_sum += bet;

				return bet;

			} else {
				
				bet = min_bet + ( (double)rand() / (double)32767 ) * ( 1 + 10 - tmp.numCombo ) * min_bet;
				if ( bet < money ) {

					money -= bet;

				} else {

					bet = money;
					money = 0;
				}
				bet_sum += bet;
				return bet;
			}
		}
		
	}

	// принять/повысить/сбросить
	int AcceptFoldIncrease ( int stage, int new_bet ) {
		
		int bet_value = setBet ( stage );

		if ( bet_value == -1 ) {
			return -1;
		}

		if ( bet_value >= new_bet ) {

			return bet_value;

		} else if ( stage != 1 ) {
			
			if ( risk * ( bet_value / new_bet ) > 0.4 ) {
				
				int difference = new_bet - bet_value;
				if ( difference <= money ) {

					money -= difference;
					bet += difference;
					bet_sum += difference;
					return bet;

				} else {

					money += bet;
					is_fold = true;
					return -1;
				}

			} else {
				is_fold = true;
				return -1;
			}
		} else {

			if ( risk * ( (double)rand() / (double)32767 ) > 0.20 ) {

				if ( new_bet - bet_value < money ) {

					money -= new_bet - bet_value;
					bet = new_bet;
					bet_sum += new_bet - bet_value;
					return bet;

				} else {

					money += bet;
					is_fold = true;
					return -1;
				}
			} else {
				money += bet;
				is_fold = true;
				return -1;
			}
		}
	}

	// наибольшая послед. карт одной масти
	vector<int> getSameSuit() {
		
		int suit;
		vector<int> info; 
		vector<int> tmp_info;

		for ( int i = 0; i < cards.size(); i++ ) {

			suit = cards[i].suit;
			tmp_info.push_back ( i );

			for ( int j = 0; j < cards.size(); j++ ) {

				if ( i != j ) {
					
					if ( cards[j].suit == suit ) {
						
						tmp_info.push_back ( j );
					}
				}
			}

			if ( tmp_info.size() >= 3 ) {
				
				info = tmp_info;
				break;
			} else if ( tmp_info.size() > info.size() ) {

				info = tmp_info;
			}

			tmp_info.clear();
		}

		return info;
	}

	// наибольшая последовательность
	vector<int> getCardSequence() {

		vector<int> best;
		vector<int> tmp;

		tmp.push_back ( 0 );

		for ( int i = 1; i < cards.size(); i ++ ) {
			
			if ( cards[i].rang != cards[i - 1].rang + 1 ) {
				
				if ( tmp.size() > best.size() ) {
					best = tmp;
				}
				tmp.clear();

			}

			tmp.push_back ( i );
		}

		if ( tmp.size() > best.size() ) {
			best = tmp;
		}

		return best;
	}

	// сортировка карт
	void cardSort() {

		int last_index = cards.size();

		while ( last_index > 1 ) {

			for ( int i = 0; i < last_index; i++ ) {
				
				if ( i + 1 < last_index ) {

					if ( cards[i].rang > cards[i + 1].rang ) {
						swapCards ( i, i + 1 );
					}
				}
			}
			last_index--;
		}
	}

	// выдать карты из розданных, кроме mass
	int* getOther ( vector<int> mass ) {

		int* result = new int[5 - mass.size()];
		int index = 0;

		for ( int i = 0; i < cards.size(); i++ ) {

			int sum = mass.size();
			for ( int j = 0; j < mass.size(); j++ ) {
				
				if ( mass[j] != i ) { 
					sum--;
				}
			}
			if ( sum == 0 ) {
				result[index] = i;
				index++;
			}
		}

		return result;
	}

	// поменять карты местами
	void swapCards ( int ind_1, int ind_2 ) {
		
		Card tmp( cards[ind_1].suit, cards[ind_1].rang );

		cards[ind_1] = cards[ind_2];

		cards[ind_2].rang = tmp.rang;
		cards[ind_2].suit = tmp.suit;

	}

	// удалить карту
	void deleteCard ( int index ) {

		vector<Card> tmp_cards;

		for ( int i = 0; i < cards.size(); i++ ) {
			
			if ( i != index ) {
				
				tmp_cards.push_back ( cards[i] );
			}
		}

		cards = tmp_cards;
	}

	// удалить карты
	void deleteCards ( int* cards, int count ) {
		
		for ( int i = count - 1; i >= 0; i-- ) {
			
			deleteCard ( cards[i] );
		}
	}
	
};

