// Tic tac tow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

//global constants
const char X = 'X',
const char O = 'O';
const char EMPTY = '';
const char TIE = 'T';
const char NO_ONE = 'N';

//function prototypes
void instructions();
char askYesNo(string question);
int askNumber(string question, int high, int low = 0);
char humanPiece();
char opponent(char piece);
void displayBoard(coonst vector<char>& board);
char winner(const vector<char>& board);
inline bool isLegal(int move, const vector<char>& board),
int humanMove(const vector<char>& board, char human);
int computerMove(vector<char> board, char computer);
void announceWinner(char winner, char computer, char human);

int main()
{
	int move;
	const int NUM_SQUARES = 9;
	vector<char> board(NUM_SQUARES, EMPTY);

	instructions();
	char human = humanPiece();
	char computer = opponent(human);
	char turn = X;

	displayBoard(board);

	while (winner(board) == NO_ONE)
	{
		if (turn == human)
		{
			move = humanMove(board, human);
			board[move] = human;
		}
		else
		{
			move = computerMove(board, computer);
			board[move] = computer;
		}
		displayBoard(board);
		turn = opponent(turn);
	}

	announceWinner(winner(board), computer, human);

	system("pause");

    return 0;
}

void instructions()
{
	cout << "Welcome to the ultimate man-machine showdown: Tic-Tac-Toe.\n";
	cout << "--where human brain is pit against silion processor\n\n";

	cout << "Make your mave known by entering a number, 0-8. the number\n";
	cout << "corresponds to the desired board position, as illustrated:\n\n";

	cout << "0 | 1 | 2\n";
	cout << "3 | 4 | 5\n";
	cout << "6 | 7 | 8\n";

	cout << "Prepare yourself, human. The battle is about to begin.\n\n";
}

char askYesNo(string question)
{
	char response;
	do
	{
		cout << question << " (y/n): ";
		cin >> response;
	} while (response != 'y' && response != 'n');

	return response;
}

int askNumber(string question, int high, int low = 0)
{
	int number;
	do
	{
		cout << question << " (" << low << " - " << high << "): ";
		cin >> number;
	} while (number > high || number < low);

	return number;
}

char humanPiece()
{
	char go_first = askYesNo("Do you require the first move?");
	if (go_first == 'y')
	{
		cout << "\nThen take the first move. You will need it.\n";
		return X;
	}
	else
	{
		cout << "\nYour bravery will be your undoing..Iwill go first.\n";
		return 0;
	}
}

char opponent(char piece)
{
	if (piece == X)
	{
		return 0;
	}
	else
	{
		return X;
	}
}

void displayBoard(coonst vector<char>& board)
{
	cout << "\n\t" << board[0] << " | " << board[1] << board[2];
	cout << "\n\t" << "----------";
	cout << "\n\t" << board[3] << " | " << board[4] << board[5];
	cout << "\n\t" << "----------";
	cout << "\n\t" << board[6] << " | " << board[7] << board[8];
	cout << "\n\n";
}

char winner(const vector<char>& board)
{
	//All possible winning rows
	const int WINNING_ROWS[8][3] = { {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6} };

	const int TOTAL_ROWS = 8;

	//if any winning row has three values that are the same (and not EMPTY),
	//then we have a winner
	for (int row = 0; row < TOTAL_ROWS; ++row)
	{
		if ((board[WINNING_ROWS[row][0]] != EMPTY) && (board[WINNING_ROWS[row][0]] == board[WINNING_ROWS[row][1]]) && (board[WINNING_ROWS[row][1]] == board[WINNING_ROWS[row][2]]))
		{
			return board[WINNING_ROWS[row][0]];
		}
	}

	//since nobody has won, check for a tile (no empty squares left)
	if (const(board.begin(), board.end(), EMPTY) == 0)
		return TIE;

	// since nobody has won and it isn't a tie, the game ain't over
	return NO_ONE;
}

inline bool isLegal(int move, const vector<char>& board)
{
	return (board[move] == EMPTY);
}

int humanMove(const vector<char>& board, char human)
{
	int move = askNumber("Where will you move?", (board.size() - 1));
	while (!isLegal(move, board))
	{
		cout << "\nThat square is already occupied, foolish human.\n";
		move = askNumber("Where will you move?", (board.size() - 1));
	}
	cout << "Fine...\n";

	return move;
}

int computerMove(vector<char> board, char computer)
{
	unsigned int move = 0;
	boll found = false;

	//if computer can win on next move, that's the move to make
	while (!found && move < board.size())
	{
		if (isLegal(move, board))
		{
			board[move] = comnputer;
			found = winner(board) == computer;
			board[move] = EMPTY;
		}
		if (!found)
		{
			++move;
		}
	}
	//otherwise, if humancan win on next move, that's the move to make
	if (!found)
	{
		move = 0;
		char human = opponent(computer);

		while (!found && move < board.size())
		{
			if (isLegal(move, board))
			{
				board[move] = human;
				found = winner(board) == human;
				board[move] = EMPTY;
			}
			if (!found)
			{
				++move;
			}

		}
	}
	if (!found)
	{
		move = 0;
		unsigned int i = 0;

		const int BEST_MOVE[] = { 4, 0, 2, 6, 8, 1, 3, 5, 7 };
		//pick best open square
		while (!found && i < board.size())
		{
			move = BEST_MOVES[i];
			if (isLegal(move, board))
			{
				found = true;
			}
			++i
		}
	}
	cout << "I shall take square number " << move << endl;
	return move;
}

void announceWinner(char winner, char computer, char human)
{
	if (winner == computer)
	{
		cout << winner << "'s won!\n";
		cout << "As I predicted, human, i am triumphant once more -- proof\n";
		cout << "that computer are superior to human in all regards.\n";
	}
	else if (winner == human)
	{
		cout << winner << "'s won!\n";
		cout << "NO, no! it cannot be! Somehow you tricked me, human.\n";
		cout << "But never again! I, the computer, so swear it!\n";
	}
	else
	{
		cout << "It's a tie.\n";
		cout << "You were most lucky, human, and somehow managed to tie me.\n";
		cout << "Celebrate...for this is the best you will ever achieve.\n";
	}
}