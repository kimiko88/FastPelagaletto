#include "pch.h"
#include "FastestPelagaletto.h"
#include <stdio.h>
#include <chrono>


namespace Pelagaletto {

#define swap(a,b) do { \
        __int8 __tmp = a; \
        a = b; \
        b = __tmp; \
    } while(0)

	static __int8  tail, index, jindex;

	static bool perm_next(__int8  *n) {
		for (index = 40 - 1; index > 0 && n[index - 1] >= n[index]; index--);
		tail = index;

		if (tail > 0) {
			for (jindex = 40 - 1; jindex > tail && n[jindex] <= n[tail - 1]; jindex--);
			swap(n[tail - 1], n[jindex]);
		}
		for (index = tail, jindex = 40 - 1; index < jindex; index++, jindex--) {
			swap(n[index], n[jindex]);
		}
		return (tail != 0);
	}

	static void CreateStartDeck(__int8* player1, __int8* startPlayer1, __int8* player2, __int8* startPlayer2, __int8* actualDeck)
	{
		if (!perm_next(actualDeck)) { printf("%s", "END"); }
		for (__int8 i = 0; i < 10; i++)
		{
			player1[i] = actualDeck[i];
			player1[i + 10] = actualDeck[i + 10];
			startPlayer1[i] = actualDeck[i];
			startPlayer1[i + 10] = actualDeck[i + 10];
			player2[i] = actualDeck[i + 20];
			player2[i + 10] = actualDeck[i + 30];
			startPlayer2[i] = actualDeck[i + 20];
			startPlayer2[i + 10] = actualDeck[i + 30];
		}
	}

	static void Print40Cards(__int8* cards)
	{
		for (__int8 i = 0; i < 40; i++)
		{
			printf("%d", cards[i]);
		}
		printf("%c", '\n');
	}


	void PlayFromTo(__int8 from[40], __int8 to[40], __int8 bestCatch[40], __int8 bestPlayedCards[40], int &winsPlayer1, int &winsPlayer2, int &maxCatch, int &maxCardPlayed)
	{
		long long matches = 0;
		maxCatch = 0;
		maxCardPlayed = 0;
		winsPlayer1 = 0;
		winsPlayer2 = 0;

		int cardPlayed;
		int catches;

		bool start;
		bool end;
		__int8 table[40];
		__int8 player1[40];
		__int8 player2[40];
		__int8 startPlayer1[20];
		__int8 startPlayer2[20];
		__int8 tableLength;
		__int8 player1Length;
		__int8 player1Index;
		__int8 player2Length;
		__int8 player2Index;
		__int8 _cardToPlay1;
		__int8 _cardToPlay2;
		__int8 _percentual = 0;
		__int8 src[40];
		bool isEqual = true;

		for (__int8 i = 0; i < 40; i++)
		{
			src[i] = from[i];
		}

		while (true)
		{
			CreateStartDeck(player1, startPlayer1, player2, startPlayer2, src);
			isEqual = true;
			for (__int8 i = 0; i < 40; i++)
			{
				if (src[i] != to[i])
				{
					isEqual = false;
					break;
				}
			}

			if (isEqual) {
				return;
			}

			matches++;
			tableLength = 0;
			player1Length = 20;
			player1Index = 0;
			player2Length = 20;
			player2Index = 0;

			if (matches % 100000000 == 0) {
				_percentual += 10;
				printf("%d\n", _percentual);
			}

			cardPlayed = 0;
			catches = 0;
			start = true;
			end = false;
			while (end == false)
			{
				catches++;
				_cardToPlay1 = 0;
				_cardToPlay2 = 0;
			inizio:
				if (start)
				{
					if (player1Length == 0)
					{
						end = true;
						start = false;
						goto fine;
					}
					__int8 carta1 = player1[player1Index];
					table[tableLength] = carta1;
					tableLength++;
					player1Index = (player1Index + 1) % 40;
					player1Length--;
					_cardToPlay2 = carta1;
					if (_cardToPlay2 == 0 && _cardToPlay1 == 1)
					{
						start = false;
						goto fine;
					}
					if (_cardToPlay2 == 0 && _cardToPlay1 == 2)
					{
						if (player1Length == 0)
						{
							end = true;
							start = false;
							goto fine;
						}
						carta1 = player1[player1Index];
						table[tableLength] = carta1;
						tableLength++;
						player1Index = (player1Index + 1) % 40;
						player1Length--;
						_cardToPlay2 = carta1;
						if (_cardToPlay2 == 0)
						{
							start = false;
							goto fine;
						}
						start = false;
						goto inizio;
					}
					if (_cardToPlay2 == 0 && _cardToPlay1 == 3)
					{
						if (player1Length == 0)
						{
							end = true;
							start = false;
							goto fine;
						}
						carta1 = player1[player1Index];
						table[tableLength] = carta1;
						tableLength++;
						player1Index = (player1Index + 1) % 40;
						player1Length--;
						_cardToPlay2 = carta1;
						if (_cardToPlay2 != 0)
						{
							start = false;
							goto inizio;
						}
						if (player1Length == 0)
						{
							end = true;
							start = false;
							goto fine;
						}
						carta1 = player1[player1Index];
						table[tableLength] = carta1;
						tableLength++;
						player1Index = (player1Index + 1) % 40;
						player1Length--;
						_cardToPlay2 = carta1;
						if (_cardToPlay2 == 0)
						{
							start = false;
							goto fine;
						}
						start = false;
						goto inizio;
					}
					start = false;
					goto inizio;
				}
				if (player2Length == 0)
				{
					end = true;
					start = true;
					goto fine;
				}
				__int8 carta2 = player2[player2Index];
				table[tableLength] = carta2;
				tableLength++;
				player2Index = (player2Index + 1) % 40;
				player2Length--;
				_cardToPlay1 = carta2;
				if (_cardToPlay1 == 0 && _cardToPlay2 == 1)
				{
					start = true;
					goto fine;
				}
				if (_cardToPlay1 == 0 && _cardToPlay2 == 2)
				{
					if (player2Length == 0)
					{
						end = true;
						start = true;
						goto fine;
					}
					carta2 = player2[player2Index];
					table[tableLength] = carta2;
					tableLength++;
					player2Index = (player2Index + 1) % 40;
					player2Length--;
					_cardToPlay1 = carta2;
					if (_cardToPlay1 == 0)
					{
						start = true;
						goto fine;
					}
					start = true;
					goto inizio;
				}
				if (_cardToPlay1 == 0 && _cardToPlay2 == 3)
				{
					if (player2Length == 0)
					{
						end = true;
						start = true;
						goto fine;
					}
					carta2 = player2[player2Index];
					table[tableLength] = carta2;
					tableLength++;
					player2Index = (player2Index + 1) % 40;
					player2Length--;
					_cardToPlay1 = carta2;
					if (_cardToPlay1 != 0)
					{
						start = true;
						goto inizio;
					}
					if (player2Length == 0)
					{
						end = true;
						start = true;
						goto fine;
					}
					carta2 = player2[player2Index];
					table[tableLength] = carta2;
					tableLength++;
					player2Index = (player2Index + 1) % 40;
					player2Length--;
					_cardToPlay1 = carta2;
					if (_cardToPlay1 == 0)
					{
						start = true;
						goto fine;
					}
					start = true;
					goto inizio;
				}
				start = true;
				goto inizio;
			fine:
				cardPlayed += tableLength;
				if (start)
				{
					for (__int8 i = 0; i < tableLength; i++)
					{
						player1[(player1Length + player1Index + i) % 40] = table[i];
					}
					player1Length += tableLength;
					tableLength = 0;
				}
				else
				{
					for (__int8 i = 0; i < tableLength; i++)
					{
						player2[(player2Length + player2Index + i) % 40] = table[i];
					}
					player2Length += tableLength;
					tableLength = 0;
				}
				if (catches > 1000)//euristic limit to detect infinite matches
				{
					break;
					printf("%d\n", catches);
				}
			}
			player1Length == 0 ? winsPlayer2++ : winsPlayer1++;
			if (catches > maxCatch)
			{
				maxCatch = catches;
				for (__int8 i = 0; i < 20; i++)
				{
					bestCatch[i] = startPlayer1[i];
					bestCatch[i + 20] = startPlayer2[i];
				}
				Print40Cards(bestCatch);
			}
			if (cardPlayed > maxCardPlayed)
			{
				maxCardPlayed = cardPlayed;
				for (__int8 i = 0; i < 20; i++)
				{
					bestPlayedCards[i] = startPlayer1[i];
					bestPlayedCards[i + 20] = startPlayer2[i];
				}
				Print40Cards(bestCatch);
			}
		}
		return;
	}
}