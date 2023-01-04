
#include <iostream>
#include <vector>
#include <optional>
#include <string>

#define MINE 'P'
#define UNKNOWN 'o'
#define EMPTY '.'

bool readBoard(std::vector<std::vector<char>>* board, uint16_t rows, uint16_t columns) {

	
	std::string row;
	char ch = 0;

	for (uint16_t r = 0; r < rows; r++) {
		std::getline(std::cin, row);
		if (row.size() != columns)
			return false;

		for (uint16_t c = 0; c < columns; c++) {
			ch = row[c];
			// moze byt 9? TODO
			if (!isdigit(ch) && ch != MINE && ch != EMPTY && ch != UNKNOWN)
				return false;
			(*board)[r][c] = ch;
		}
	}

	return board;
}




//int main(int argc, char* argv[])
int main()
{
	uint16_t rows = 4, columns = 10;
	std::vector<std::vector<char>> board(rows, std::vector<char>(columns));

	while (true)
	{

		 
		if (!readBoard(&board, 4, 10))
			return EXIT_FAILURE;

	}

	return 0;
}
