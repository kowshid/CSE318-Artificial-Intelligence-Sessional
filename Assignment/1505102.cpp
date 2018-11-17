#include <iostream>
#include<queue>
#include<vector>
#include<stdio.h>

int maxCapacity;

using namespace std;

class Node
{
    public:
    int mis1;
    int mis2;
    int can1;
    int can2;
    bool dir; //true for side 1 to 2, false for side 2 to 1
    Node *parent;

    Node(int a, int b, int c, int d, bool e, Node *p)
    {
        mis1 = a;
        mis2 = b;
        can1 = c;
        can2 = d;
        dir = e;
        parent = p;
    };

    bool valid()
    {
        if ((can1 > mis1  &&  mis1 != 0) || (can2 > mis2  &&  mis2 != 0) || can1 < 0 || can2 < 0 || mis1 < 0 || mis2 < 0) return false;
        else return true;
    }

    void print()
    {
        printf("Side1 has %d missionaries and %d cannibals\n", mis1, can1);
        printf("Side2 has %d missionaries and %d cannibals\n", mis2, can2);
        if(dir) printf("Boat is in side 1 and will go to side 2 next\n");
        else printf("Boat is in side 2 and will go to side 1 next\n");
    }
};

bool check(vector <Node *> vect, Node *node)
{
    //int sz = vect.size();

    for(int i = 0; i < vect.size(); i++)\
    {
        if(vect[i]->can1 == node->can1 && vect[i]->can2 == node->can2 && vect[i]->mis1 == node->mis1 && vect[i]->mis2 == node->mis2 && vect[i]->dir == node->dir)
        {
            return false;
        }
    }

    return true;
}

void BFS(Node *root, int capacity)
{
    printf("IN BFS");

    queue <Node*> Q;

    vector<Node*> vect;
    vector<Node*> path;

    Node *node;
    Node *temp;
    Node *answer;

    Q.push(root);

    bool direction = root->dir;
    bool validity;
    bool br = false;

    while(!Q.empty())
    {
        node = Q.front();
        Q.pop();

        for(int i = 1; i <= maxCapacity; i++)
        {
            for(int j = 0; j <= i; j++)
            {
                if(direction) //from side1 to side2
                {
                    temp = new Node(node->mis1-j, node->mis2+j, node->can1-(i-j), node->can2+(i-j), false, node);

                    validity = temp->valid();
                    if(validity && check(vect, temp))
                    {
                        Q.push(temp);
                        vect.push_back(temp);
                        printf("pushed\n");
                        if(temp->can1 == 0 && temp->mis1 == 0)
                        {
                            answer = temp;
                            br = true;
                            break;
                        }
                    }
                }

                else //from side 2 to side 1
                {
                    temp = new Node(node->mis1+j, node->mis2-j, node->can1+(i-j), node->can2-(i-j), true, node);
                    validity = temp->valid();
                    if(validity && check(vect, temp))
                    {
                        Q.push(temp);
                        vect.push_back(temp);
                        printf("pushed");
                        if(temp->can1 == 0 && temp->mis1 == 0)
                        {
                            answer = temp;
                            br = true;
                            break;
                        }
                    }
                }
            }

            if(br) break;
        }
        if(br) break;
    }

    temp = answer;

    while(temp != NULL)
    {
        path.push_back(temp);
        temp = temp->parent;
    }

    int iterations = path.size();

    for(int i = iterations; i > 0; i--)
    {
        if(path[i]->dir) //dir is true, that means boat is in side 1
        {
            printf("(%d, %d) >> (%d, %d)\n", path[i]->mis1, path[i]->can1, path[i]->mis2, path[i]->can2);
        }
        else //dir is true, that means boat is in side 2
        {
            printf("(%d, %d) << (%d, %d)\n", path[i]->mis1, path[i]->can1, path[i]->mis2, path[i]->can2);
        }
    }
}

int main ()
{
    while (1)
    {
        int mis, can, cap;
        printf("Enter the number of  missionaries, cannibal and boat capacity respectively\n");
        scanf("%d%d%d", &mis, &can, &cap);
        if (mis <= 0 || can <= 0 || cap <= 0)
        {
            printf("Input error\n");
            return 0;
        }

        if(can > mis)
        {
            printf("No result\n");
            return 0;
        }

        maxCapacity = cap;

        Node *root = new Node(mis, 0, can, 0, true, NULL);

        BFS(root, maxCapacity);
    }

    return 0;
}
