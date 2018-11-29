#include<bits/stdc++.h>

using namespace std;

class Node
{
public:
	int boardSize;
	int arr[5][5];

	Node()
	{

	}

	Node(int n)
	{
		boardSize = n;

		for(int i = 0; i < boardSize; i++)
		{
			for(int j = 0; j < boardSize; j++)
			{
				arr[i][j] = 0;
			}
		}
	}

	void getNode()
	{
		for(int i = 0; i < boardSize; i++)
		{
			for(int j = 0; j < boardSize; j++)
			{
				scanf("%d", &arr[i][j]);
			}
		}
	}

	void printNode()
	{
		for(int i = 0; i < boardSize; i++)
		{
			for(int j = 0; j < boardSize; j++)
			{
				printf("%d ", arr[i][j]);
			}

			printf("\n");
		}
	}
};

int hammingDistance(Node node)
{
	int bSize = node.boardSize;
	int count = 0;
	int result = 0;

	for (int i = 0; i < bSize; i++)
	{
		for (int j = 0; j < bSize; j++)
		{
			count++;

			if(node.arr[i][j] != count  && node.arr[i][j] != 0) result++;
		}
	}

	return result;
}

int manhattanDistance(Node node)
{
	int row, col;
	int bSize = node.boardSize;
	int count = 0;
	int result = 0;

	for (int i = 0; i < bSize; i++)
	{
		for (int j = 0; j < bSize; j++)
		{
			count++;

			if(node.arr[i][j] != 0 && node.arr[i][j] != count)
			{
				row = (node.arr[i][j] - 1)/3;
				col = (node.arr[i][j] - 1)%3;

				result = result + abs(i - row) + abs(j - col);
			}
		}
	}

	return result;
}

int linearConflict(Node node)
{
	int row1, row2, col1, col2;
	int bSize = node.boardSize;
	int result = 0;

	for (int i = 0; i < bSize; i++)
	{
		for (int j = 0; j < bSize - 1; j++)
		{
			row1 = (node.arr[i][j] - 1)/3;
			col1 = (node.arr[i][j] - 1)%3;

			if(node.arr[i][j] != 0 && row1 == i)
			{
				for(int k = (j+1); k < bSize; k++)
				{
					row2 = (node.arr[i][k] - 1)/3;
					col2 = (node.arr[i][k] - 1)%3;

					if(row1 == row2 && col1 > col2) result++;
				}
			}
		}
	}


	for (int i = 0; i < bSize; i++)
	{
		for (int j = 0; j < bSize; j++)
		{
			row1 = (node.arr[j][i] - 1)/3;
			col1 = (node.arr[j][i] - 1)%3;

			if(node.arr[i][j] != 0 && col1 == i)
			{
				for(int k = (j+1); k < bSize; k++)
				{
					row2 = (node.arr[k][i] - 1)/3;
					col2 = (node.arr[k][i] - 1)%3;

					if(row1 > row2 && col1 == col2) result++;
				}
			}
		}
	}

	return result;
}

void AStarSearch()
{
	
}

int main()
{
	freopen("in.txt","r",stdin);

	int bSize, n;

	//printf("\nInput board size\n");
	scanf("%d", &bSize);

	int arr[bSize][bSize];

	Node initial(bSize);

	//printf("\nEnter State\n");
	initial.getNode();

	initial.printNode();

	printf("hammingDistance = %d\n", hammingDistance(initial));
	printf("manhattanDistance = %d\n", manhattanDistance(initial));
	printf("linearConflict = %d\n", linearConflict(initial));

	return 0;
}
