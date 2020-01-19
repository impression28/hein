#include <iostream>
#include <string>
#include <vector>

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

	return 0;
}

std::string DrawBoard(std::vector <std::vector <Piece>> board) 
{
	return std::string {""};
}
