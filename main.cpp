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

// Prototypes
std::string DrawBoard(const std::vector <std::vector <Piece>> &board);
void GameLoop(std::vector <std::vector <Piece>> &board);
bool CheckWin(const std::vector <std::vector <Piece>> &board);
bool DecodeCommand(const std::string &command, size_t &row, size_t &column);

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
    std::cout << "\033[H" << "\033[J" << "\033[H";
    while (!game_over)
    {
        std::cout << DrawBoard(board) << std::endl;
        std::cout << ">> ";
        getline(std::cin, command);
        // #TODO: suppport boards of different sizes
        size_t column = 0;
        size_t row = 0;
        if (DecodeCommand(command, row, column))
        {
            if (0 <= row    && row    < BOARD_SIZE   && 
                0 <= column && column < BOARD_SIZE   &&
                // This will allow the pie rule
                (board[row][column]  ==  EMPTY_PIECE || move_number == 1))
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
                game_over = CheckWin(board) || CheckWin(board);
                std::cout << "\033[H" << "\033[J" << "\033[H";
                continue;
            }
        }
        std::cout << "\033[H" << "\033[J" << "\033[H" << "Invalid command, try again";
    }
}


// Preconditions: 
//	* board must be 11x11
//	* all lines which have places must have exactly 11 '.'

std::string DrawBoard(const std::vector <std::vector <Piece>> &board) 
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
            "  • \033[31m• • • • • • • • • • •\033[0m •\n"
            " 1 \033[34m•\033[0m . . . . . . . . . . . \033[34m•\033[0m 1\n"
            "  2 \033[34m•\033[0m . . . . . . . . . . . \033[34m•\033[0m 2\n"
            "   3 \033[34m•\033[0m . . . . . . . . . . . \033[34m•\033[0m 3\n"
            "    4 \033[34m•\033[0m . . . . . . . . . . . \033[34m•\033[0m 4\n"
            "     5 \033[34m•\033[0m . . . . . . . . . . . \033[34m•\033[0m 5\n"
            "      6 \033[34m•\033[0m . . . . . . . . . . . \033[34m•\033[0m 6\n"
            "       7 \033[34m•\033[0m . . . . . . . . . . . \033[34m•\033[0m 7\n"
            "        8 \033[34m•\033[0m . . . . . . . . . . . \033[34m•\033[0m 8\n"
            "         9 \033[34m•\033[0m . . . . . . . . . . . \033[34m•\033[0m 9\n"
            "         10 \033[34m•\033[0m . . . . . . . . . . . \033[34m•\033[0m 10\n"
            "          11 \033[34m•\033[0m . . . . . . . . . . . \033[34m•\033[0m 11\n"
            "              • \033[31m• • • • • • • • • • •\033[0m • \n"
            "                 A B C D E F G H I J K\n"};
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

// #TODO use depth-first search to check for wins
bool CheckWin(const std::vector <std::vector <Piece>> &board)
{
    return false;
}

// Return true if decoding is succesful and false otherwise.
// Will output row and column via the parameters passed by
// mutable reference if successful and zero to both if not 
// successful.
bool DecodeCommand(const std::string &command, size_t &row, size_t &column)
{
    row = 0;
    column = 0;

    if (command.size() < 2)
        return false;

    // #TODO support boardsizes of length greater than 26 even if SGF doesn't

    // This i will scan the string
    size_t i = 0;
    if ( islower(command[i]) == 0 )
    {
        return false;
    }
    // No need for a loop since only one character is allowed
    // for columns
    column = command[i] - 'a';
    i++;

    if ( isdigit(command[i] == 0) )
    {
        column = 0;
        return false;
    }

    while ( isdigit(command[i]) != 0 || i < command.size() )
    {
        row *= '9' - '0' + 1;
        row += command[i] - '0';
        i++;
    }
    row--;
    if (row < 0)
    {
        row = 0;
        column = 0;
        return false;
    }

    if (i != command.size())
    {
        row = 0;
        column = 0;
        return false;
    }

    return true;
}
