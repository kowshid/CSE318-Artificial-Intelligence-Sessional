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

                if(arr[i][j] != 0)
                {
                    if(arr[i][j] != count)
                        return false;
                }
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

        for(int i = 0; i < n; i++)
        {
            //printf("%d ", ar[i]);
        }

        printf("\n");

        for(int i = 0; i < n-1; i++)
        {
            for(int j = i+1; j < n; j++)
            {
                if(ar[i] > ar[j] && (ar[j] != 0))
                    inversion++;
            }
        }

        printf("Inversion count: %d\n", inversion);

        if(boardSize%2 == 1)
        {
            printf("Boardsize odd\n");
            if(inversion%2 == 1)
            {
                printf("\nNO RESULT\n");
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
                printf("\nNO RESULT\n");
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

int linearConflict(Node node, int a)
{
    int row1, row2, col1, col2;
    int bSize = node.boardSize;
    int result = 0;

    for (int i = 0; i < bSize; i++)
    {
        for (int j = 0; j < bSize - 1; j++)
        {
            row1 = (node.arr[i][j] - 1)/a;
            col1 = (node.arr[i][j] - 1)%a;

            if(node.arr[i][j] != 0 && row1 == i)
            {
                for(int k = (j+1); k < bSize; k++)
                {
                    row2 = (node.arr[i][k] - 1)/a;
                    col2 = (node.arr[i][k] - 1)%a;

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
            row1 = (node.arr[j][i] - 1)/a;
            col1 = (node.arr[j][i] - 1)%a;

            if(node.arr[j][i] != 0 && col1 == i)
            {
                for(int k = (j+1); k < bSize; k++)
                {
                    row2 = (node.arr[k][i] - 1)/a;
                    col2 = (node.arr[k][i] - 1)%a;

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

int main()
{
    freopen("in.txt", "r", stdin);

    int bSize;
    scanf("%d", &bSize);
    sz = bSize;

    Node *initial = new Node(sz);
    initial->getNode();
    initial->printNode();

    printf("%d\n", linearConflict(*initial, sz));
}
