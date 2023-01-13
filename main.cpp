
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

int countSomethingAround(const std::vector<std::vector<char>>& board, const unsigned int r, const unsigned int c, const char someChar) {

	unsigned int rmin = (r == 0 ? 0 : r - 1), rmax = (r == board.size() - 1 ? static_cast<unsigned int>(board.size()) - 1 : r + 1);
	unsigned int cmin = (c == 0 ? 0 : c - 1), cmax = (c == board[0].size() - 1 ? static_cast<unsigned int>(board[0].size()) - 1 : c + 1);
	int charsCount = 0;
	for (auto ri = rmin; ri <= rmax; ri++) {
		for (auto ci = cmin; ci <= cmax; ci++) {
			if (board[ri][ci] == someChar)
				charsCount++;
		}
	}
	return charsCount;
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

	for (unsigned int n = 0; n < rows; n++) {

		matrix[n][cols - 1] = board[visitedCells[1][n].first][visitedCells[1][n].second] - '0' - countSomethingAround(board, visitedCells[1][n].first, visitedCells[1][n].second, MINE);

		for (unsigned int  e = 0; e < cols-1;e++) {;
			if (visitedCells[1][n].first-1 <= visitedCells[0][e].first && visitedCells[0][e].first <= visitedCells[1][n].first + 1 
				&& visitedCells[1][n].second - 1 <= visitedCells[0][e].second && visitedCells[0][e].second <= visitedCells[1][n].second + 1) {
				matrix[n][e] = 1;
;			}
		}
	}

	return matrix;
}



//TODO del
void print_matrix(const std::vector<std::vector<double>>& matrix) {
	for (const auto& row : matrix) {
		for (const auto& column : row)
			std::cout << column << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
}


// rewriten pseudocode from https://rosettacode.org/wiki/Reduced_row_echelon_form with some modifications
std::vector<std::vector<double>> gaus(std::vector<std::vector<double>> matrix) {
	

	//std::vector<std::vector<double>> matrix{
	//		{1, 1, 0, 0, 0, 0, 0, 0, 1},
	//		{1, 1, 1, 0, 0, 0, 0, 0, 2},
	//		{0, 1, 1, 1, 0, 0, 0, 0, 3},
	//		{0, 0, 1, 1, 1, 1, 1, 0, 2},
	//		{0, 0, 0, 0, 0, 1, 1, 1, 1},
	//		{0, 0, 0, 0, 0, 0, 1, 1, 1},
	//	//{1,2,-1,-4},{2,3,-1,-11},{-2,0,-3,22}
	//};

	//print_matrix(matrix);

	size_t rowCount = matrix.size(), columnCount = matrix[0].size(), i = 0, lead = 0;
	double lv = 0;
	
	for (size_t r = 0; r < rowCount; r++) {

		if (lead >= columnCount)
			break;
		i = r;
		while (matrix[i][lead] == 0) {
			i += 1;

			if (i == rowCount) {
				i = r;
				lead ++;
				if (columnCount == lead) {
					//print_matrix(matrix);
					return matrix;
				}
			}
		}

		std::swap(matrix[i], matrix[r]);
		
		lv = matrix[r][lead];

		if (lv != 0) {

			for (size_t mrx = 0; mrx < columnCount; mrx++) {
				matrix[r][mrx] /= lv;
			}
		}

		for (i = 0; i < rowCount; i++) {

			if (i != r) {

				lv = matrix[i][lead];
				for (size_t j = 0; j < columnCount; j++) {

					matrix[i][j] -= matrix[r][j] * lv;
				}
			}
		}
		lead++;
	}

	//print_matrix(matrix);
	return matrix;
}


// return: #1 == rownum, #2 == colnum, #3 flag {0 : step, 1: mark}
std::vector<int> getStepWithBounds(std::vector<std::vector<double>> matrix) {
	double maxBound = 0, minBound = 0;

	uint16_t rows = static_cast<uint16_t>(matrix.size()), cols = static_cast<uint16_t>(matrix[0].size());

	for (uint16_t r = 0; r < rows; r++) {
		maxBound = 0, minBound = 0;
		for (uint16_t c = 0; c < cols - 1; c++) {
			if (matrix[r][c] > 0)
				maxBound += matrix[r][c];
			else if (matrix[r][c] < 0)
				minBound += matrix[r][c];
		}
		if (matrix[r][cols - 1] == minBound) {
			for (uint16_t c = 0; c < cols - 1; c++) {
				if (matrix[r][c] < 0) {
					//std::cout << "mark " << r << " " << c << "\n";
					return {r, c, 1};
				}
				if (matrix[r][c] > 0) {
					//std::cout << "step " << r << " " << c << "\n";
					return  {r, c, 0};
				}
			}
		}
		else if (matrix[r][cols - 1] == maxBound) {
			for (uint16_t c = 0; c < cols - 1; c++) {
				if (matrix[r][c] > 0) {
					//std::cout << "mark " << r << " " << c << "\n";
					return  {r, c, 1};
				}
				if (matrix[r][c] < 0) {
					//std::cout << "step " << r << " " << c << "\n";
					return  {r, c, 0};
				}
			}
		}
	}
	
	return { -1,-1, -1 };
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
	

	//solving with matrix
	std::vector<std::vector<std::pair<int, int>>> visitedCells(2);
	std::vector<int> matrixPos = { 0,0,0 };

	for (uint16_t c = 0, r = 0; r < rows; r++) {
		for (c = 0; c < cols; c++) {
			if (isdigit(board[r][c]) && countSomethingAround(board, r, c, EMPTY) > 0) {


				getBorderEmpty(board, &visitedCells, r, c);
				matrixPos = getStepWithBounds(gaus(fillmatrix(board, visitedCells)));

				if (matrixPos[0] == -1)
					continue;

				if (matrixPos[2] == 0)
					std::cout << "step " << visitedCells[0][matrixPos[1]].first << " " << visitedCells[0][matrixPos[1]].second << "\n";
				else
					std::cout << "mark " << visitedCells[0][matrixPos[1]].first << " " << visitedCells[0][matrixPos[1]].second << "\n";
				
				return { visitedCells[0][matrixPos[1]].first , visitedCells[0][matrixPos[1]].second};

			}
		}
	}


	return emptyPos;
}



//int main(int argc, char* argv[])
int main()
{

	//.............
	uint16_t rows = 5, columns = 7, minesleft = 5 ;
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
