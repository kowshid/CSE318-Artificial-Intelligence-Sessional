#include<bits/stdc++.h>

using namespace std;

int sz;

class Node
{
public:
    int fn, gn;
	int boardSize;
	int arr[5][5];
	Node *parent;

	Node()
	{

	}

	Node(int n)
	{
		boardSize = n;
        parent = 0;

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

	bool isGoal()
	{
		int count = 0;

		for(int i = 0; i < boardSize; i++)
		{
			for(int j = 0; j < boardSize; j++)
			{
				count++;

				if(arr[i][j] != 0)
				{
					if(arr[i][j] != count) return false;
				}
			}
		}

		return true;
	}
};

void makeChild(Node *parent, Node *child)
{
    child->parent = parent;
    child->boardSize = parent->boardSize;
    for(int i = 0; i < child->boardSize; i++)
    {
        //printf("check\n");
        for(int j = 0; j < child->boardSize; j++)
        {
            child->arr[i][j] = parent->arr[i][j];
        }
    }
}

vector <Node *> closedList;

bool check(Node *node)
{
    bool result = true;

    if(node == 0) return false;

    for(int i = 0; i < closedList.size(); i++)
    {
        for (int j = 0; j < sz; j++)
        {
            for(int k = 0; k < sz; k++)
            {
                if(closedList[i]->arr[j][k] != node->arr[j][k]) result = false;
            }
        }
    }

    return result;
}

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

					if(row1 == row2 && col1 > col2)
					{
                        result++;
                        printf("%d %d\n", node.arr[i][j], node.arr[i][k]);
                    }
				}
			}
		}
	}


	for(int i = 0; i < bSize; i++)
	{
		for (int j = 0; j < bSize - 1; j++)
		{
			row1 = (node.arr[j][i] - 1)/3;
			col1 = (node.arr[j][i] - 1)%3;

			if(node.arr[j][i] != 0 && col1 == i)
			{
				for(int k = (j+1); k < bSize; k++)
				{
					row2 = (node.arr[k][i] - 1)/3;
					col2 = (node.arr[k][i] - 1)%3;

					if(row1 > row2 && col1 == col2)
					{
                        result++;
                        printf("%d %d\n", node.arr[j][i], node.arr[k][i]);
                    }
				}
			}
		}
	}

	return result;
}

int heuristic(Node node, int a)
{
	if(a == 1) return hammingDistance(node);
	if(a == 2) return manhattanDistance(node);
	if(a == 3) return manhattanDistance(node) + 2*linearConflict(node);
}

class CMP
{
public:
	bool operator()(const Node *a, const Node *b)
	{
		return a->fn > b->fn;
	}
};

void AStarSearch(Node *node)
{
	priority_queue <Node *, vector<Node *>, CMP> openList;

    node->gn = 0;

	openList.push(node);

	//int sz = node->boardSize;

	while(!openList.empty())
	{
        Node *temp = openList.top();
        openList.pop();

        closedList.push_back(temp);

        if(temp->isGoal()) break;

        int zX, zY;

        for(int i = 0; i < sz; i++)
        {
            for(int j = 0; j < sz; j++)
            {
                if(temp->arr[i][j] == 0)
                {
                    zX = i;
                    zY = j;
                }
            }
        }

        if(zX > 0) //up move possible
        {
            Node *child = new Node(sz);
            makeChild(temp, child);
            swap(child->arr[zX][zY], child->arr[zX-1][zY]);
            //child->printNode();
            child->gn = temp->gn + 1;
            child->fn = temp->gn + heuristic(*child,1);

            if(!check(child))
            {
                closedList.push_back(child);
                openList.push(child);
            }
        }

        if(zX < (sz - 1)) //down move possible
        {
            Node *child = new Node(sz);
            makeChild(temp, child);
            swap(child->arr[zX][zY], child->arr[zX+1][zY]);
            //child->printNode();
            child->gn = temp->gn + 1;
            child->fn = temp->gn + heuristic(*child,1);

            if(!check(child))
            {
                closedList.push_back(child);
                openList.push(child);
            }
        }

        if(zY < (sz - 1)) //right move possible
        {
            Node *child = new Node(sz);
            makeChild(temp, child);
            swap(child->arr[zX][zY], child->arr[zX][zY+1]);
            //child->printNode();
            child->gn = temp->gn + 1;
            child->fn = temp->gn + heuristic(*child,1);

            if(!check(child))
            {
                closedList.push_back(child);
                openList.push(child);
            }
        }

        if(zY > 0) //left move possible
        {
            Node *child = new Node(sz);
            makeChild(temp, child);
            swap(child->arr[zX][zY], child->arr[zX][zY-1]);
            //child->printNode();
            child->gn = temp->gn + 1;
            child->fn = temp->gn + heuristic(*child,1);

            if(!check(child))
            {
                closedList.push_back(child);
                openList.push(child);
            }
        }
	}
}

int main()
{
	freopen("in.txt","r",stdin);

	int bSize, n;

	//printf("\nInput board size\n");
	scanf("%d", &bSize);

	sz = bSize;

	int arr[bSize][bSize];

	Node *initial = new Node(bSize);

	//printf("\nEnter State\n");
	initial->getNode();

	initial->printNode();

	printf("hammingDistance = %d\n", hammingDistance(*initial));
	printf("manhattanDistance = %d\n", manhattanDistance(*initial));
	printf("linearConflict = %d\n", linearConflict(*initial));

    AStarSearch(initial);

	return 0;
}

