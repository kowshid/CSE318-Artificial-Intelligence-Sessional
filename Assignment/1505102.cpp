#include <iostream>
#include<queue>
#include<vector>
#include<stdio.h>
#include <time.h>
#include <ctime>

using namespace std;

int maxCapacity;
time_t start;
time_t finish;
double elapsed_secs;

class Node
{
public:
    int mis1, mis2;
    int can1, can2;
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
        if ((can1 > mis1  &&  mis1 != 0) || (can2 > mis2  &&  mis2 != 0) || can1 < 0 || can2 < 0 || mis1 < 0 || mis2 < 0)
            return false;
        else
            return true;
    }

    void printNode()
    {
        printf("Side1 has %d missionaries and %d cannibals\n", mis1, can1);
        printf("Side2 has %d missionaries and %d cannibals\n", mis2, can2);
        if(dir)
            printf("Boat is in side 1 and will go to side 2 next\n");
        else
            printf("Boat is in side 2 and will go to side 1 next\n");
    }
};

vector <Node*> expanded;
Node *answer;

bool check(Node *node)
{
    if(node == 0) return false;

    for(int i = 0; i < expanded.size(); i++)
    {
        if(expanded[i]->can1 == node->can1 && expanded[i]->can2 == node->can2 && expanded[i]->mis1 == node->mis1 && expanded[i]->mis2 == node->mis2 && expanded[i]->dir == node->dir)
        {
            return false;
        }
    }

    return true;
}

void print()
{
    vector <Node*> path;
    Node *temp = answer;
    if (answer == 0)
    {
        printf("No Solution\n");
        return;
    }

    while(temp != NULL)
    {
        path.push_back(temp);
        temp = temp->parent;
    }

    int iterations = path.size();
    int expantion = expanded.size();

    //printf("Total iterations: %d\n", iterations);
    //printf("Total expantion: %d\n", expantion);

    for(int i = iterations-1; i >= 0; i--)
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

    printf("Total iterations: %d\n", iterations);
    printf("Total expantion: %d\n", expantion);

    elapsed_secs = double(finish - start) / CLOCKS_PER_SEC;
    printf("Total time: %f\n seconds", elapsed_secs);

    path.clear();
}

void BFS(Node *root)
{
    printf("IN BFS\n");

    queue <Node*> Q;

    //vector<Node*> path;

    Node *node;
    Node *temp;
    //double elapsed_secs;
    //Node *answer;

    node = temp = 0;

    Q.push(root);

    //bool direction = root->dir;
    bool validity;
    bool br = false;

    while(!Q.empty())
    {
        finish = clock();
        elapsed_secs = double(finish - start) / CLOCKS_PER_SEC;
        if(elapsed_secs > 30.0)
        {
            printf("Time limit exceeded\n");
            br = true;
        }

        node = Q.front();
        Q.pop();

        //possible moves
        for(int i = 1; i <= maxCapacity; i++)
        {
            for(int j = 0; j <= i; j++) //number of missionaries
            {
                if(i != 0 && (i-j) > i) continue;

                if(node->dir) //from side1 to side2
                {
                    temp = new Node(node->mis1-j, node->mis2+j, node->can1-(i-j), node->can2+(i-j), false, node);
                    validity = temp->valid()  && check(temp);

                    if(validity)
                    {
                        Q.push(temp);
                        expanded.push_back(temp);
                        if(expanded.size() > 99999)
                        {
                            printf("State expansion limit exceeded\n");
                            br = true;
                        }

                        if(temp->can1 == 0 && temp->mis1 == 0)
                        {
                            answer = temp;
                            br = true;
                            break;
                        }
                    }

                    else
                    {
                        delete temp;
                        temp = 0;
                    }
                }

                else //from side 2 to side 1
                {
                    temp = new Node(node->mis1+j, node->mis2-j, node->can1+(i-j), node->can2-(i-j), true, node);
                    validity = temp->valid() && check(temp);

                    if(validity)
                    {
                        Q.push(temp);
                        expanded.push_back(temp);
                        if(expanded.size() > 99999)
                        {
                            printf("State expansion limit exceeded\n");
                            br = true;
                        }

                        if(temp->can1 == 0 && temp->mis1 == 0)
                        {
                            answer = temp;
                            br = true;
                            break;
                        }
                    }

                    else
                    {
                        delete temp;
                        temp = 0;
                    }
                }
            }

            if(br)
                break;
        }

        if(br)
            break;
    }
}

void DFS(Node *node)
{
    Node *temp = 0;
    bool validity = check(node);

    if(!validity) return;

    if(node->can1 == 0 && node->mis1 == 0)
    {
        answer = node;
        return;
    }

    if(answer != 0) return;

    if(expanded.size() > 99999)
    {
        printf("State expansion limit exceeded\n");
        exit(0);
    }

    finish = clock();
    elapsed_secs = double(finish - start) / CLOCKS_PER_SEC;
    if(elapsed_secs > 30.0)
    {
        printf("Time limit exceeded\n");
        //br = true;
        exit(0);
    }

    expanded.push_back(node);

    for(int i = 1; i <= maxCapacity; i++)
    {
        for(int j = 0; j <= i; j++)
        {
            if(i != 0 && (i-j) > i) continue;

            if(node->dir) //from side1 to side2
            {
                temp = new Node(node->mis1-j, node->mis2+j, node->can1-(i-j), node->can2+(i-j), false, node);

                if(temp->valid()) DFS(temp);

                else
                {
                    delete temp;
                    temp = 0;
                }
            }

            else //from side 2 to side 1
            {
                temp = new Node(node->mis1+j, node->mis2-j, node->can1+(i-j), node->can2-(i-j), true, node);

                if(temp->valid()) DFS(temp);

                else
                {
                    delete temp;
                    temp = 0;
                }
            }
        }
    }
}

int main ()
{
    //freopen("in.txt","r",stdin);

    while (1)
    {
        int mis, can, cap, choice;
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
        answer = 0;

        Node *root = new Node(mis, 0, can, 0, true, NULL);

        printf("Enter 1 for BFS, 2 for DFS\n");
        scanf("%d", &choice);

        if (choice == 1)
        {
            start = clock();
            BFS(root);
            print();
           // cout << start << " " << finish << endl;
        }

        else if(choice == 2)
        {
            start = clock();
            printf("In DFS\n");
            DFS(root);
            print();
        }

        expanded.clear();
    }

    return 0;
}
