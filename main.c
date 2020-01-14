#include <stdio.h>

int main(int argc, char *argv[])
{
	// This is the enum which will fill the board array
	// maybe in the future more options will be added 
	// for other purposes (highlighting for analysis,
	// etc.)
	enum Piece {
		EMPTY_PIECE,
		RED_PIECE,	// Red plays first
		BLUE_PIECE,	// Blue plays second
	};
	return 0;
}
