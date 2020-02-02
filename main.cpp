#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <cctype>
#include <cstdlib>

#define DEBUG

const size_t BOARD_SIZE = 11;
const char placeholder_char = '.';

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

void GameLoop(std::vector <std::vector <Piece>> &board);

int main(int argc, char *argv[])
{
    std::vector <Piece> v(BOARD_SIZE, EMPTY_PIECE);
    std::vector <std::vector <Piece>> board(BOARD_SIZE, v);

    GameLoop(board);

    return 0;
}

void GameLoop(std::vector <std::vector <Piece>> &board)
{
    bool game_over = false;
    Piece current_piece = RED_PIECE;
    std::string command = "";
	size_t move_number = 0;
    while (!game_over)
    {
        std::cout << DrawBoard(board) << std::endl;
        std::cout << ">> ";
        getline(std::cin, command);
        // #TODO: suppport boards of different sizes
        if (command.size() == 2)
        {
            char column_char = command[0];
            char row_char = command[1];
            size_t column = 0;
            size_t row = 0;
            if ((islower(column_char) != 0) && (isdigit(row_char) != 0))
            {
                column = column_char - 'a';
                row = row_char - '1';
                if (0 <= row    && row    < BOARD_SIZE && 
                    0 <= column && column < BOARD_SIZE &&
                    (board[row][column]  ==  EMPTY_PIECE ||
					 // This will allow the pie rule
					 move_number == 1))
                {
                    board[row][column] = current_piece;
                    switch (current_piece)
                    {
                        case RED_PIECE:
                            current_piece = BLUE_PIECE;
                            break;
                        case BLUE_PIECE:
                            current_piece = RED_PIECE;
                            break;
                    }
					move_number++;
                    continue;
                }
            }
        }
        std::cout << "Invalid command, try again";
    }
}


// Preconditions: 
//	* board must be 11x11
//	* all lines which have places must have exactly 11 '.'

std::string DrawBoard(std::vector <std::vector <Piece>> board) 
{
    // Test preconditions
#ifdef DEBUG
    assert(board.size() == BOARD_SIZE);
    for (size_t i = 0; i < BOARD_SIZE; i++)
        assert(board.at(i).size() == BOARD_SIZE);
#endif

    // #TODO: suppport boards of different sizes
    std::string board_template = std::string {\
        "\n   A B C D E F G H I J K\n"
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

#ifdef DEBUG
    unsigned int place_count = 0;
    for (const char &c: board_template)
    {
        switch (c)
        {
            case placeholder_char:
                place_count++;
                break;
            case '\n':
                assert(place_count == BOARD_SIZE || place_count == 0);
                place_count = 0;
                break;
        }
    }
#endif

    for (char &c: board_template)
    {
        if (c == placeholder_char)
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
                    c = '-';
                    break;
            }
            if (column < BOARD_SIZE - 1)
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
