#include<bits/stdc++.h>

using namespace std;

int sz, choice, explore, expansion;

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

        if(arr[boardSize-1][boardSize-1] != 0)
            return false;

        for(int i = 0; i < boardSize; i++)
        {
            for(int j = 0; j < boardSize; j++)
            {
                count++;
                if(arr[i][j] != 0 && arr[i][j] != count)
                    return false;
            }
        }

        return true;
    }

    bool isSolvable()
    {
        int n = boardSize*boardSize;
        int count = 0, inversion = 0;
        int ar[n];

        for(int i = 0; i < boardSize; i++)
        {
            for(int j = 0; j < boardSize; j++)
            {
                ar[count++] = arr[i][j];
            }
        }

//        for(int i = 0; i < n; i++)
//        {
//            printf("%d ", ar[i]);
//        }
//
//        printf("\n");

        for(int i = 0; i < n-1; i++)
        {
            for(int j = i+1; j < n; j++)
            {
                if(ar[i] > ar[j] && (ar[j] != 0))
                    inversion++;
            }
        }

        printf("\nInversion count: %d\n", inversion);

        if(boardSize%2 == 1)
        {
            printf("Boardsize odd\n");

            if(inversion%2 == 1)
            {
                printf("\nNOT SOLVABLE\n");
                return false;
            }
            else
            {
                printf("\nResult Available\n");
                return true;
            }
        }

        if(boardSize%2 == 0)
        {
            printf("Boardsize even\n");
            int zX;

            for(int i = 0; i < boardSize; i++)
            {
                for(int j = 0; j < boardSize; j++)
                {
                    if(arr[i][j] == 0)
                    {
                        zX = i;
                    }
                }
            }

            printf("Zero is in %dth row\n", zX);

            if((inversion+zX)%2 == 0)
            {
                printf("\nNOT SOLVABLE\n");
                return false;
            }
            else
            {
                printf("\nResult Available\n");
                return true;
            }
        }
    }
};

vector <Node *> closedList;
vector <Node *> explored;

Node *answer;

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

bool nodeCheck(Node *a, Node *b)
{
    for(int i = 0; i < sz; i++)
    {
        for(int j = 0; j < sz; j++)
        {
            if(a->arr[i][j] != b->arr[i][j])
                return false;
        }
    }

    return true;
}

bool check(Node *node) //false for unequal, true for equal
{
    //if(node == 0) return false;

    for(int i = 0; i < closedList.size(); i++)
    {
        //printf("\nmatch found\n");
        if(nodeCheck(node, closedList[i]))
            return true; //node already exists
    }

    return false; //no match found; doesn't exist
}

bool checkExplore(Node *node) //false for unequal, true for equal
{
    //if(node == 0) return false;

    for(int i = 0; i < explored.size(); i++)
    {
        if(nodeCheck(node, explored[i]))
            return true; //node already exists
    }

    return false; //no match found; doesn't exist
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
            if(node.arr[i][j] != count  && node.arr[i][j] != 0)
                result++;
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
                row = (node.arr[i][j] - 1)/sz;
                col = (node.arr[i][j] - 1)%sz;

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
    //int a = sz;

    for (int i = 0; i < bSize; i++)
    {
        for (int j = 0; j < bSize - 1; j++)
        {
            row1 = (node.arr[i][j] - 1)/sz;
            col1 = (node.arr[i][j] - 1)%sz;

            if(node.arr[i][j] != 0 && row1 == i)
            {
                for(int k = (j+1); k < bSize; k++)
                {
                    row2 = (node.arr[i][k] - 1)/sz;
                    col2 = (node.arr[i][k] - 1)%sz;

                    if(row1 == row2 && col1 > col2)
                    {
                        result++;
                        //printf("%d %d\n", node.arr[i][j], node.arr[i][k]);
                    }
                }
            }
        }
    }


    for(int i = 0; i < bSize; i++)
    {
        for (int j = 0; j < bSize - 1; j++)
        {
            row1 = (node.arr[j][i] - 1)/sz;
            col1 = (node.arr[j][i] - 1)%sz;

            if(node.arr[j][i] != 0 && col1 == i)
            {
                for(int k = (j+1); k < bSize; k++)
                {
                    row2 = (node.arr[k][i] - 1)/sz;
                    col2 = (node.arr[k][i] - 1)%sz;

                    if(row1 > row2 && col1 == col2)
                    {
                        result++;
                        //printf("%d %d\n", node.arr[j][i], node.arr[k][i]);
                    }
                }
            }
        }
    }

    return result;
}

int heuristic(Node node, int a)
{
    if(a == 1)
        return hammingDistance(node);
    else if(a == 2)
        return manhattanDistance(node);
    else if(a == 3)
        return (manhattanDistance(node) + 2*linearConflict(node));
}

class CMP
{
public:
    bool operator()(const Node *a, const Node *b)
    {
        return a->fn > b->fn;
    }
};

void print()
{
    vector <Node*> path;
    Node *temp = answer;

    if (answer == 0)
    {
        printf("No Solution\n");
        return;
    }

    while(temp != 0)
    {
        path.push_back(temp);
        temp = temp->parent;
    }

    int iterations = path.size();
    expansion = closedList.size();
    explore = explored.size();

//    for(int i = iterations-1; i >= 0; i--)
//    {
//        path[i]->printNode();
//        printf("\n");
//    }

    printf("\nTotal iterations: %d\n", iterations);
    printf("Total explored: %d\n", explore);
    printf("Total expansion: %d\n", expansion);

    if(choice == 1)
        printf("\nUsed Hamming Distance\n");
    else if(choice == 2)
        printf("\nUsed Manhattan Distance\n");
    else if(choice == 3)
        printf("\nUsed Manhattan Distance + 2*linearConflict\n");

    path.clear();
}

void AStarSearch(Node *node, int a)
{
    priority_queue <Node *, vector<Node *>, CMP> openList;

    node->gn = 0;
    node->parent = 0;
    node->fn = node->gn + heuristic(*node, a);
    openList.push(node);

    //closedList.push_back(node);
    //int sz = node->boardSize;

    while(!openList.empty())
    {
        //expansion++;
        Node *temp = openList.top();
        openList.pop();
        closedList.push_back(temp);
        explored.push_back(temp);
        //if(temp->isGoal()) break;

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
            child->fn = child->gn + heuristic(*child, a);

            if(!check(child))
            {
                if(child->isGoal())
                {
                    answer = child;
                    break;
                }

                else
                {
                    openList.push(child);
                   	if(!checkExplore(child)) explored.push_back(temp);
                }

                //child->printNode();
            }
        }

        if(zX < (sz - 1)) //down move possible
        {
            Node *child = new Node(sz);
            makeChild(temp, child);

            swap(child->arr[zX][zY], child->arr[zX+1][zY]);
            //child->printNode();

            child->gn = temp->gn + 1;
            child->fn = child->gn + heuristic(*child, a);

            if(!check(child))
            {
                if(child->isGoal())
                {
                    answer = child;
                    break;
                }

                else
                {
                    openList.push(child);
                    if(!checkExplore(child)) explored.push_back(temp);
                }
            }
        }

        if(zY < (sz - 1)) //right move possible
        {
            Node *child = new Node(sz);
            makeChild(temp, child);

            swap(child->arr[zX][zY], child->arr[zX][zY+1]);
            //child->printNode();

            child->gn = temp->gn + 1;
            child->fn = child->gn + heuristic(*child, a);

            if(!check(child))
            {
                if(child->isGoal())
                {
                    answer = child;
                    break;
                }

                else
                {
                    openList.push(child);
                    if(!checkExplore(child)) explored.push_back(temp);
                }
            }
        }

        if(zY > 0) //left move possible
        {
            Node *child = new Node(sz);
            makeChild(temp, child);

            swap(child->arr[zX][zY], child->arr[zX][zY-1]);
            //child->printNode();

            child->gn = temp->gn + 1;
            child->fn = child->gn + heuristic(*child, a);

            if(!check(child))
            {
                if(child->isGoal())
                {
                    answer = child;
                    break;
                }

                else
                {
                    openList.push(child);
                    if(!checkExplore(child)) explored.push_back(temp);
                }
            }
        }
    }

    print();
}

int main()
{
    expansion = 0;
    explore = 0;
    answer = 0;

    int bSize, n;

    freopen("in.txt","r",stdin);

    //printf("\nInput board square size\n");
    scanf("%d", &bSize);

    sz = bSize;

    Node *initial = new Node(sz);

    //printf("\nEnter State\n");
    initial->getNode();
    initial->printNode();

    printf("\nHammingDistance of initial = %d\n", hammingDistance(*initial));
    printf("ManhattanDistance of initial = %d\n", manhattanDistance(*initial));
    printf("LinearConflict of initial = %d\n", linearConflict(*initial));

    if(initial->isGoal())
    {
        answer = initial;
        //answer->printNode();
        printf("This is goal\n");
        return 0;
    }

//    printf("\nEnter\n1 for hammingDistance\n2 for manhattanDistance\n3 for linearConflict and manhattan\n");
//    scanf("%d", &n);
//    choice = n;

    if(initial->isSolvable())
    {
        printf("\nEntering AStar\n");

//        AStarSearch(initial, choice);
        for(int i = 1; i < 4; i++)
        {
            choice = i;
            printf("\nSolve %d\n", i);
            AStarSearch(initial, choice);
            closedList.clear();
            explored.clear();
        }
    }

    //closedList.clear();
    //explored.clear();
    return 0;
}
