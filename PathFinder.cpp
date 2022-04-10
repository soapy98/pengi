#include "PathFinder.h"
#include <algorithm>

CustomLevel* PathFinder::mCustomLevel;

struct Node {
	int row, col;
	int parent_row, parent_col;
	int f, g, h;

	Node(int r, int c) {
		f = 0;
		g = 0;
		h = 0;
		parent_row = -1;
		parent_col = -1;
		row = r;
		col = c;
	}

	bool operator<(const Node& rhs) const { return f < rhs.f; }
	bool operator==(const Node& rhs) const { return row == rhs.row && col == rhs.col; }
};


void PathFinder::SetLevel(CustomLevel* levelIn)
{
	mCustomLevel = levelIn;
}


std::vector<std::pair<int, int>> PathFinder::PathAStar(int sourceRow, int sourceCol, int destRow, int destCol)
{
	std::vector<std::pair<int, int>> path;
	if (sourceRow == destRow && sourceCol == destCol) {
		return path;
	}
	//bool isNodeClosed[RowCount][ColCount] = { false };
	std::pair<int, int> parent[RowCount][ColCount]{ std::make_pair(-1,-1) };
	std::vector<Node> openList;
	std::vector<Node> closedList;

	Node sourceNode(sourceRow, sourceCol);
	sourceNode.h = abs(sourceRow - destRow) + abs(sourceCol - destCol);
	sourceNode.f = sourceNode.h;
	openList.push_back(sourceNode);

	while (openList.size() > 0) {

		std::sort(openList.begin(), openList.end());

		Node currentNode = openList.front();
		int currentRow = openList.front().row;
		int currentCol = openList.front().col;

		closedList.push_back(currentNode);
		openList.erase(openList.begin());

		std::vector<std::pair<int, int>> neighbours;
		neighbours.push_back({ currentRow + 1, currentCol });
		neighbours.push_back({ currentRow - 1, currentCol });
		neighbours.push_back({ currentRow, currentCol + 1 });
		neighbours.push_back({ currentRow, currentCol - 1 });

		for (auto it = neighbours.begin(); it != neighbours.end();) {
			bool isClosed = false;

			for (auto itC = closedList.begin(); itC != closedList.end(); ++itC) {
				if (itC->row == it->first && itC->col == it->second) {
					isClosed = true;
					break;
				}
			}

			if (it->first == destRow && it->second == destCol) {
				path.push_back({ destRow, destCol });
				path.push_back({ currentNode.row,currentNode.col });
				int currentRow = currentNode.row;
				int currentCol = currentNode.col;

				while (currentRow != -1 && currentCol != -1) {
					path.push_back({ currentRow,currentCol });
					for (auto itC = closedList.begin(); itC != closedList.end(); ++itC) {
						if (itC->row == currentRow && itC->col == currentCol) {
							int parentRow = itC->parent_row;
							int parentCol = itC->parent_col;
							currentRow = parentRow;
							currentCol = parentCol;
						}
					}
				}
				path.pop_back();
				std::reverse(path.begin(), path.end());

				return path;
			}

			if (
				mCustomLevel->LevelDesign[it->first][it->second] != FREE ||
				it->first < 0 ||
				it->first >= RowCount ||
				it->second < 0 ||
				it->second >= ColCount ||
				isClosed)
			{
				it = neighbours.erase(it);
			}
			else {
				++it;
			}
		}

		for (auto it = neighbours.begin(); it != neighbours.end(); ++it) {
			bool isInOpenList = false;
			Node* neighbourNode = nullptr;
			for (auto it2 = openList.begin(); it2 != openList.end(); ++it2) {
				if (it->first == it2->row && it->second == it2->col) {
					isInOpenList = true;
					neighbourNode = &(*it2);
					break;
				}
			}
			if (isInOpenList) {
				int newG = currentNode.g + 1;
				if (newG < neighbourNode->g) {
					neighbourNode->g = newG;
					neighbourNode->f = neighbourNode->g + neighbourNode->h;
					neighbourNode->parent_col = currentNode.col;
					neighbourNode->parent_row = currentNode.row;
				}
			}
			else {
				Node newNode(it->first, it->second);
				newNode.g = abs(newNode.row - sourceRow) + abs(newNode.col - sourceCol);
				newNode.h = abs(newNode.row - destRow) + abs(newNode.col - destCol);
				newNode.f = newNode.g + newNode.h;
				newNode.parent_col = currentNode.col;
				newNode.parent_row = currentNode.row;
				openList.push_back(newNode);
			}
		}
	}
	return path;
}