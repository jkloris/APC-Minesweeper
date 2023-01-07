
#include <iostream>
#include <vector>
#include <optional>
#include <string>
#include <cmath>

#define MINE 'P'
#define EMPTY 'o'
#define ZERO '.'

uint8_t readBoard(std::vector<std::vector<char>>* board, uint16_t rows, uint16_t columns) {

	
	std::string row;
	char ch = 0;

	for (uint16_t r = 0; r < rows; r++) {
		std::getline(std::cin, row);
		if (row.size() == 0)
			return 1;
		if (row.size() != columns )
			return 3;

		for (uint16_t c = 0; c < columns; c++) {
			ch = row[c];
			// moze byt 9? TODO
			if (!isdigit(ch) && ch != MINE && ch != EMPTY && ch != ZERO)
				return 3;
			(*board)[r][c] = ch;
		}
	}

	return 0;
}



std::vector<int> printAction(std::vector<std::vector<char>> board, uint16_t* globalMines) {

	uint8_t emptyN = 0, mines = 1;
	std::vector<int>emptyPos(2);

	size_t rows = board.size(), cols = board[0].size();
	for (uint16_t c = 0, r = 0; r < rows; r++) {
		for( c = 0; c < cols; c++) {
			
			if (isdigit(board[r][c])) {
				emptyN = 0;
				mines = 1;
				// finding empty spaces around the cell
				if (r > 0 && (mines += (board[r - 1][c] == MINE)) && board[r - 1][c] == EMPTY  ) {
					emptyPos[0] = r-1;
					emptyPos[1] = c;
					emptyN++;
				}
				if (r > 0 && c > 0 && (mines += (board[r - 1][c - 1] == MINE))&& board[r - 1][c-1] == EMPTY  )  {
					emptyPos[0] = r-1;
					emptyPos[1] = c-1;
					emptyN++;
				}
				if (r > 0 && c < cols-1 && (mines += (board[r - 1][c + 1] == MINE)) && board[r - 1][c+1] == EMPTY) {
					emptyPos[0] = r-1;
					emptyPos[1] = c+1;
					emptyN++;
				}
				if (r < rows-1 && (mines += (board[r + 1][c] == MINE)) && board[r + 1][c] == EMPTY ) {
					emptyPos[0] = r+1;
					emptyPos[1] = c;
					emptyN++;;
				}
				if (r < rows-1 && c > 0 && (mines += (board[r + 1][c - 1] == MINE)) && board[r + 1][c - 1] == EMPTY  ) {
					emptyPos[0] = r+1;
					emptyPos[1] = c-1;
					emptyN++;
				}
				if (r < rows-1 && c < cols-1 && (mines += (board[r + 1][c + 1] == MINE)) && board[r + 1][c + 1] == EMPTY  ) {
					emptyPos[0] = r+1;
					emptyPos[1] = c+1;
					emptyN++;
				}
				if ( c < cols-1 && (mines += (board[r][c + 1] == MINE)) && board[r][c + 1] == EMPTY  ) {
					emptyPos[0] = r;
					emptyPos[1] = c+1;
					emptyN++;
				}
				if (c > 0 && (mines += (board[r][c - 1] == MINE)) && board[r][c - 1] == EMPTY ) {
					emptyPos[0] = r;
					emptyPos[1] = c-1;
					emptyN++;
				}

				mines--;
				//posible bomb check
				if ((emptyN == board[r][c] - '0' - mines) && emptyN > 0) {
					//if (emptyN == board[r][c] - '0' - mines) {
						(*globalMines)--;
						std::cout << "mark " << emptyPos[0] << " " << emptyPos[1] <<   "\n";
						return emptyPos;
					//}
					

				}else if(emptyN > 0 && (board[r][c] - '0') - mines == 0) {
					std::cout << "step " << emptyPos[0] << " " << emptyPos[1] << "\n";
					return emptyPos;
				}
			}
		}
	}


	for (uint16_t c = 0, r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++) {
			if (board[r][c] == EMPTY) {
				std::cout << "random step" << r << c << "\n"; //TODO del
				return std::vector<int> {r, c};

			}
		}
	}
	return emptyPos;
}



//TODO del
//void gaussElimination(std::vector<std::vector<int>> a) {
//
//	for (int i = 0; i < a.size()-1; i++) {
//		// Find the pivot row
//		int pivot = i;
//		for (int j = i + 1; j < a.size(); j++) {
//			if (std::abs(a[j][i]) > std::abs(a[pivot][i])) {
//				pivot = j;
//			}
//		}
//
//		// Swap the current row with the pivot row
//		for (int j = 0; j < a[0].size(); j++) {
//			std::swap(a[i][j], a[pivot][j]);
//		}
//
//		// Perform elimination for each row
//		for (int j = i + 1; j < a.size(); j++) {
//			double factor = a[j][i] / a[i][i];
//			for (int k = i; k < a[0].size(); k++) {
//				a[j][k] -= factor * a[i][k];
//			}
//		}
//	}
//
//	return;
//}



//int main(int argc, char* argv[])
int main()
{

	//std::vector<std::vector<int>> a = { {2, -1, 1, 5},
	//				  {1, -2, 2, 3},
	//				  {1, 1, 1, 6} };

	//gaussElimination(a);




	//.............
	uint16_t rows = 9, columns = 9, minesleft = 10 ;
	std::vector<std::vector<char>> board(rows, std::vector<char>(columns));
	std::vector<int> lastPos(2);

	uint8_t ret = 0;

	while (true)
	{

		ret = readBoard(&board, rows, columns);
		if (ret == 3)
			return EXIT_FAILURE;
		if (ret == 1)
			return EXIT_SUCCESS;
		//if (board[lastPos[0]][lastPos[1]] == MINE) {
		//	std::cout << "mine found\n"; //TODO del
		//	return EXIT_SUCCESS;
		//}
		lastPos = printAction(board, &minesleft);

		//if (minesleft == 0) {
		//	std::cout << "all mines marked\n"; //TODO del
		//	return EXIT_SUCCESS;
		//}
	}

	return 0;
}
