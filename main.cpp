
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



// referencing function used in function bellow, but declared later
void getBorderEmpty(std::vector<std::vector<char>> board, std::vector<std::vector<std::pair<int, int>>>* visitedCells, uint16_t r, uint16_t c);

// Recursive function to find border. Adds number cells
// visitedCells[0] are empty cells
// visitedCells[1] are number cells
void getBorder(std::vector<std::vector<char>> board, std::vector<std::vector<std::pair<int, int>>>* visitedCells, uint16_t r, uint16_t c) {

	size_t rows = board.size(), cols = board[0].size();


	if (r > 0 && isdigit(board[r - 1][c]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r - 1, c}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r - 1,c });
		getBorderEmpty(board, visitedCells, r - 1, c);
	}
	if (r > 0 && c > 0 && isdigit(board[r - 1][c - 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r - 1, c - 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r - 1,c - 1 });
		getBorderEmpty(board, visitedCells, r - 1, c - 1);
	}
	if (r > 0 && c < cols - 1 && isdigit(board[r - 1][c + 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r - 1, c + 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r - 1, c + 1 });
		getBorderEmpty(board, visitedCells, r - 1, c + 1);
	}
	if (r < rows - 1 && isdigit(board[r + 1][c]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r + 1, c}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r + 1, c });
		getBorderEmpty(board, visitedCells, r + 1, c);
	}
	if (r < rows - 1 && c > 0 && isdigit(board[r + 1][c - 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r + 1, c - 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r + 1, c - 1 });
		getBorderEmpty(board, visitedCells, r + 1, c - 1);
	}
	if (r < rows - 1 && c < cols - 1 && isdigit(board[r + 1][c + 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r + 1, c + 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r + 1, c + 1 });
		getBorderEmpty(board, visitedCells, r + 1, c + 1);
	}
	if (c < cols - 1 && isdigit(board[r][c + 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r, c + 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r , c + 1 });
		getBorderEmpty(board, visitedCells, r, c + 1);
	}
	if (c > 0 && isdigit(board[r][c - 1]) && std::find((*visitedCells)[1].begin(), (*visitedCells)[1].end(), std::pair<int, int>{r, c - 1}) == (*visitedCells)[1].end()) {
		(*visitedCells)[1].push_back({ r , c - 1 });
		getBorderEmpty(board, visitedCells, r, c - 1);
	}
}

// Recursive function to find border. Adds Empty cells
// visitedCells[0] are empty cells
// visitedCells[1] are number cells
void getBorderEmpty(std::vector<std::vector<char>> board, std::vector<std::vector<std::pair<int, int>>>* visitedCells, uint16_t r, uint16_t c) {

	//matrixBinds->push_back({NULL, NULL});

	size_t rows = board.size(), cols = board[0].size();
	
	if (r > 0 && board[r - 1][c] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r - 1, c}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({r - 1,c});
		getBorder(board, visitedCells, r - 1, c);
	}
	if (r > 0 && c > 0 && board[r - 1][c-1] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r - 1, c-1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r - 1,c - 1});
		getBorder(board, visitedCells, r - 1, c -1);
	}
	if (r > 0 && c < cols - 1 && (board[r - 1][c+1]) == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r - 1, c+1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r - 1, c + 1 });
		getBorder(board, visitedCells, r - 1, c + 1);
	}
	if (r < rows - 1 && board[r + 1][c] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r + 1, c}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r + 1, c });
		getBorder(board, visitedCells, r + 1, c);
	}
	if (r < rows - 1 && c > 0 && board[r + 1][c - 1] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r + 1, c - 1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r + 1, c - 1 });
		getBorder(board, visitedCells, r + 1, c-1);
	}
	if (r < rows - 1 && c < cols - 1 && board[r + 1][c + 1] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r + 1, c + 1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r + 1, c + 1 });
		getBorder(board, visitedCells, r + 1, c+1);
	}
	if (c < cols - 1 && board[r ][c + 1] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r , c+1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r , c + 1 });
		getBorder(board, visitedCells, r , c + 1);
	}
	if (c > 0 && board[r][c-1] == EMPTY && std::find((*visitedCells)[0].begin(), (*visitedCells)[0].end(), std::pair<int, int>{r , c-1}) == (*visitedCells)[0].end()) {
		(*visitedCells)[0].push_back({ r , c - 1 });
		getBorder(board, visitedCells, r , c - 1);
	}

}

// visitedCells[0] are empty cells
// visitedCells[1] are number cells
std::vector<std::vector<double>> fillmatrix(std::vector<std::vector<char>> board, std::vector<std::vector<std::pair<int, int>>>  visitedCells ) {

	size_t rows = visitedCells[1].size(), cols = visitedCells[0].size() + 1;

	std::vector<std::vector<double>> matrix(rows, std::vector<double>(cols));

	for (auto n = 0; n < rows; n++) {

		matrix[n][cols - 1] = board[visitedCells[1][n].first][visitedCells[1][n].second] - '0'; //TODO minus miny
		for (auto e = 0; e < cols-1;e++) {;
			if (visitedCells[1][n].first-1 <= visitedCells[0][e].first && visitedCells[0][e].first <= visitedCells[1][n].first + 1 
				&& visitedCells[1][n].second - 1 <= visitedCells[0][e].second && visitedCells[0][e].second <= visitedCells[1][n].second + 1) {
				matrix[n][e] = 1;
;			}
		}
	}

	return matrix;
}

void print_matrix(const std::vector<std::vector<double>>& matrix) {
	for (const auto& row : matrix) {
		for (const auto& column : row)
			std::cout << column << " ";
		std::cout << "\n";
	}
}


// rewriten pseudocode from https://en.wikipedia.org/wiki/Gaussian_elimination with some modifications
void gaus(std::vector<std::vector<double>> matrix) {
	int h = 0; /* Initialization of the pivot row */
	int k = 0; /* Initialization of the pivot column */

	print_matrix(matrix);
	std::cout << "\n";

	//std::vector<std::vector<double>> matrix{
	//		{1, 1, 0, 0, 0, 0, 0, 0, 1},
	//		{1, 1, 1, 0, 0, 0, 0, 0, 2},
	//		{0, 1, 1, 1, 0, 0, 0, 0, 3},
	//		{0, 0, 1, 1, 1, 1, 1, 0, 2},
	//		{0, 0, 0, 0, 0, 1, 1, 1, 1},
	//		{0, 0, 0, 0, 0, 0, 1, 1, 1},
	//};

	int m = matrix.size(), n = matrix[0].size();

	while (h < m and k < n) {

				/* Find the k-th pivot: */
		int i_max = 0;
		for (int i = h; i < m; i++) {
			if (abs(matrix[i][k]) >= i_max)
				i_max = abs(matrix[i][k]);
		}
		
		if (matrix[i_max][k] == 0) {

			/* No pivot in this column, pass to next column */
			k = k + 1;
		}
		else {

			std::swap(matrix[h], matrix[i_max]);
			/* Do for all rows below pivot: */
			for (int i = h + 1; i < m; i++) {

				double f = matrix[i][k] / matrix[h][k];
				/* Fill with zeros the lower part of pivot column: */
				matrix[i][k] = 0;
				/* Do for all remaining elements in current row: */
				for (int j = k + 1; j < n; j++)
					matrix[i][j] = matrix[i][j] - matrix[h][j] * f;
				/* Increase pivot row and column */
			}
			h = h + 1;
			k = k + 1;
		}
	}


	print_matrix(matrix);

}

//int main(int argc, char* argv[])
int main()
{

	//std::vector<std::vector<int>> a = { {2, -1, 1, 5},
	//				  {1, -2, 2, 3},
	//				  {1, 1, 1, 6} };

	//gaussElimination(a);




	//.............
	uint16_t rows = 5, columns = 5, minesleft = 5 ;
	std::vector<std::vector<char>> board(rows, std::vector<char>(columns));
	std::vector<int> lastPos(2);


	


	uint8_t ret = 0;

	while (true)
	{

		ret = readBoard(&board, rows, columns);

		//tmp
		std::vector<std::vector<std::pair<int, int>>> visitedCells(2);

		getBorderEmpty(board,&visitedCells, 3, 0);

		gaus(fillmatrix(board, visitedCells));
		//---

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
