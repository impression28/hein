#include <iostream>
#include <string>
#include <vector>
#include <assert.h>

#define DEBUG
// This is the enum which will fill the board array
// maybe in the future more options will be added 
// for other purposes (highlighting for analysis,
// etc.)
typedef enum 
{
	EMPTY_PIECE,	// Default state with no piece
	RED_PIECE,	// Red plays first
	BLUE_PIECE,	// Blue plays second
} Piece;

std::string DrawBoard(std::vector <std::vector <Piece>> board);

int main(int argc, char *argv[])
{
	std::vector <Piece> v(11, EMPTY_PIECE);
	std::vector <std::vector <Piece>> board(11, v);
	board[2][3] = RED_PIECE;
	board[5][3] = RED_PIECE;
	board[7][6] = RED_PIECE;
	board[5][5] = BLUE_PIECE;
	board[1][10] = BLUE_PIECE;
	board[8][9] = BLUE_PIECE;
	std::cout << DrawBoard(board);
	return 0;
}

// Preconditions: 
//	* board must be 11x11
//	* all lines must have exactly 11 '.'

std::string DrawBoard(std::vector <std::vector <Piece>> board) 
{
	// Test preconditions
	#ifdef DEBUG
	assert(board.size() == 11);
	for (size_t i = 0; i < 11; i++)
		assert(board.at(i).size() == 11);
	#endif

	// #TODO: suppport boards of different sizes
	std::string board_template = std::string {\
	"   A B C D E F G H I J K\n"
	"  • • • • • • • • • • • • •\n"
	" 1 • . . . . . . . . . . . •\n"
	"  2 • . . . . . . . . . . . •\n"
	"   3 • . . . . . . . . . . . •\n"
	"    4 • . . . . . . . . . . . •\n"
	"     5 • . . . . . . . . . . . •\n"
	"      6 • . . . . . . . . . . . •\n"
	"       7 • . . . . . . . . . . . •\n"
	"        8 • . . . . . . . . . . . •\n"
	"         9 • . . . . . . . . . . . •\n"
	"         10 • . . . . . . . . . . . •\n"
	"          11 • . . . . . . . . . . . •\n"
	"              • • • • • • • • • • • • •\n"};
	size_t row = 0;
	size_t column = 0;
	for (char &c: board_template)
	{
		if (c == '.')
		{
			switch (board[row][column])
			{
				case RED_PIECE:
					c = 'R';
					break;
				case BLUE_PIECE:
					c = 'B';
					break;
				case EMPTY_PIECE:
					break;
			}
			// #TODO: check if the table was well-formated
			// for debug
			if (column < 10)
			{
				column++;
			}
			else
			{
				column = 0;
				row++;
			}
				
		}
	}
	return std::string {board_template};
}
