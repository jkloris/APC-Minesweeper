
#include <iostream>
#include <vector>
#include <optional>
#include <string>
#include <cmath>
#include <map>

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
	for (c = 0; c < cols; c++) {

		if (isdigit(board[r][c])) {
			emptyN = 0;
			mines = 1;
			// finding empty spaces around the cell
			if (r > 0 && (mines += (board[r - 1][c] == MINE)) && board[r - 1][c] == EMPTY) {
				emptyPos[0] = r - 1;
				emptyPos[1] = c;
				emptyN++;
			}
			if (r > 0 && c > 0 && (mines += (board[r - 1][c - 1] == MINE)) && board[r - 1][c - 1] == EMPTY) {
				emptyPos[0] = r - 1;
				emptyPos[1] = c - 1;
				emptyN++;
			}
			if (r > 0 && c < cols - 1 && (mines += (board[r - 1][c + 1] == MINE)) && board[r - 1][c + 1] == EMPTY) {
				emptyPos[0] = r - 1;
				emptyPos[1] = c + 1;
				emptyN++;
			}
			if (r < rows - 1 && (mines += (board[r + 1][c] == MINE)) && board[r + 1][c] == EMPTY) {
				emptyPos[0] = r + 1;
				emptyPos[1] = c;
				emptyN++;;
			}
			if (r < rows - 1 && c > 0 && (mines += (board[r + 1][c - 1] == MINE)) && board[r + 1][c - 1] == EMPTY) {
				emptyPos[0] = r + 1;
				emptyPos[1] = c - 1;
				emptyN++;
			}
			if (r < rows - 1 && c < cols - 1 && (mines += (board[r + 1][c + 1] == MINE)) && board[r + 1][c + 1] == EMPTY) {
				emptyPos[0] = r + 1;
				emptyPos[1] = c + 1;
				emptyN++;
			}
			if (c < cols - 1 && (mines += (board[r][c + 1] == MINE)) && board[r][c + 1] == EMPTY) {
				emptyPos[0] = r;
				emptyPos[1] = c + 1;
				emptyN++;
			}
			if (c > 0 && (mines += (board[r][c - 1] == MINE)) && board[r][c - 1] == EMPTY) {
				emptyPos[0] = r;
				emptyPos[1] = c - 1;
				emptyN++;
			}

			mines--;
			//posible bomb check
			if ((emptyN == board[r][c] - '0' - mines) && emptyN > 0) {
				//if (emptyN == board[r][c] - '0' - mines) {
				(*globalMines)--;
				std::cout << "mark " << emptyPos[0] << " " << emptyPos[1] << "\n";
				return emptyPos;
				//}


			}
			else if (emptyN > 0 && (board[r][c] - '0') - mines == 0) {
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


bool wasVisited(std::vector<std::pair<int, int>>& visitedCells, std::pair<int, int> x) {
	if (std::find(visitedCells.begin(), visitedCells.end(), x) != visitedCells.end()) {
		return true;
	}
	return false;
}

void getBorder(std::vector<std::vector<char>> board, std::vector<std::vector<std::pair<int, int>>>* visitedCells, uint16_t r, uint16_t c);

void getBorderEmpty(std::vector<std::vector<char>> board, std::vector<std::vector<std::pair<int, int>>>* visitedCells, uint16_t r, uint16_t c) {

	size_t rows = board.size(), cols = board[0].size();



	// finding empty spaces around the cell
	if (r > 0 && isdigit(board[r - 1][c]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r - 1, c}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r - 1,c });
		getBorder(board, visitedCells, r - 1, c);
	}
	if (r > 0 && c > 0 && isdigit(board[r - 1][c - 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r - 1, c - 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r - 1,c - 1 });
		getBorder(board, visitedCells, r - 1, c - 1);
	}
	if (r > 0 && c < cols - 1 && isdigit(board[r - 1][c + 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r - 1, c + 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r - 1, c + 1 });
		getBorder(board, visitedCells, r - 1, c + 1);
	}
	if (r < rows - 1 && isdigit(board[r + 1][c]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r + 1, c}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r + 1, c });
		getBorder(board, visitedCells, r + 1, c);
	}
	if (r < rows - 1 && c > 0 && isdigit(board[r + 1][c - 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r + 1, c - 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r + 1, c - 1 });
		getBorder(board, visitedCells, r + 1, c - 1);
	}
	if (r < rows - 1 && c < cols - 1 && isdigit(board[r + 1][c + 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r + 1, c + 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r + 1, c + 1 });
		getBorder(board, visitedCells, r + 1, c + 1);
	}
	if (c < cols - 1 && isdigit(board[r][c + 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r, c + 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r , c + 1 });
		getBorder(board, visitedCells, r, c + 1);
	}
	if (c > 0 && isdigit(board[r][c - 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r, c - 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r , c - 1 });
		getBorder(board, visitedCells, r, c - 1);
	}


}

void getBorder(std::vector<std::vector<char>> board, std::vector<std::vector<std::pair<int, int>>>* visitedCells, uint16_t r, uint16_t c) {

	size_t rows = board.size(), cols = board[0].size();



	// finding empty spaces around the cell
	if (r > 0 && board[r - 1][c] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r - 1, c}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({r - 1,c});
		getBorderEmpty(board, visitedCells, r - 1, c);
	}
	if (r > 0 && c > 0 && board[r - 1][c-1] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r - 1, c-1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r - 1,c - 1});
		getBorderEmpty(board, visitedCells, r - 1, c -1);
	}
	if (r > 0 && c < cols - 1 && (board[r - 1][c+1]) && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r - 1, c+1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r - 1, c + 1 });
		getBorderEmpty(board, visitedCells, r - 1, c + 1);
	}
	if (r < rows - 1 && board[r + 1][c] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r + 1, c}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r + 1, c });
		getBorderEmpty(board, visitedCells, r + 1, c);
	}
	if (r < rows - 1 && c > 0 && board[r + 1][c - 1] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r + 1, c - 1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r + 1, c - 1 });
		getBorderEmpty(board, visitedCells, r + 1, c-1);
	}
	if (r < rows - 1 && c < cols - 1 && board[r + 1][c + 1] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r + 1, c + 1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r + 1, c + 1 });
		getBorderEmpty(board, visitedCells, r + 1, c+1);
	}
	if (c < cols - 1 && board[r ][c + 1] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r , c+1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r , c + 1 });
		getBorderEmpty(board, visitedCells, r , c + 1);
	}
	if (c > 0 && board[r][c-1] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r , c-1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r , c - 1 });
		getBorderEmpty(board, visitedCells, r , c - 1);
	}


}

//std::vector<std::vector<int>> fillMatrix(std::vector<std::vector<char>> board, std::vector<std::pair<int, int>> visitedCells ) {
//
//
//
//}

//int main(int argc, char* argv[])
int main()
{

	//std::vector<std::vector<int>> a = { {2, -1, 1, 5},
	//				  {1, -2, 2, 3},
	//				  {1, 1, 1, 6} };

	//gaussElimination(a);




	//.............
	uint16_t rows = 3, columns = 3, minesleft = 3 ;
	std::vector<std::vector<char>> board(rows, std::vector<char>(columns));
	std::vector<int> lastPos(2);


	


	uint8_t ret = 0;

	while (true)
	{

		ret = readBoard(&board, rows, columns);
		std::vector<std::vector<std::pair<int, int>>> visitedCells(2);

		getBorder(board,&visitedCells, 0, 0);


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
