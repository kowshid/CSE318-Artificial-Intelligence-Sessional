#include<bits/stdc++.h>

#define pr pair<double,double>
#define INF 999999
using namespace std;

int sz;
double cost;
vector <pr> cityList;
vector <int> path;
vector <bool> visited;

void GetMap()
{
    pr temp;
    double x, y, a;

    for(int i = 0; i < sz; i++)
    {
        cin >> a >> x >> y;
        cityList[i] = make_pair(x, y);
    }

//    printf("Got Map\n");
}

void PrintMap()
{
    for(int i = 0; i < sz; i++)
    {
        printf("\n%d %d", cityList[i].first, cityList[i].second);
    }
}

double GetDistance(pr a, pr b)
{
     double dist, xDist, yDist;
     xDist = (a.first-b.first);
     yDist = (a.second-b.second);

     dist = sqrt(1.0 * (xDist*xDist + yDist*yDist));

     return dist;
}

int GetNearestNeighbour(int root)
{
    double dist = INF, result = INF, n;

    for(int i = 0; i < sz; i++)
    {
        if(visited[i]) continue;

        n = GetDistance(cityList[root], cityList[i]);
        //printf("\n%d", n);

        if(n < dist && n != 0)
        {
            dist = n;
            result = i;
        }
    }

    cost = dist;
    return result;
}

double PathDistance()
{
    double result = 0.0;

    for(int i = 0; i < path.size()-1; i++)
    {
        result += GetDistance(cityList[path[i]], cityList[path[i+1]]);
    }

    return result;
}

void PrintPath()
{
    for(int i = 0; i < path.size(); i++)
    {
        cout<<path[i]+1<<"-->";
    }

    cout << endl;
}

void NearestNeighbour(int root)
{
    fill(visited.begin(),visited.end(),false);
    path.clear();

    int t = root;
    int n = 1;

    path.push_back(root);
    visited[root] = true;

    while(n < sz)
    {
        t = GetNearestNeighbour(t);
        path.push_back(t);
        visited[t] = true;

        n++;
    }

    path.push_back(root);

    cout << "Path distance for NearestNeighbour heuristics: " <<  PathDistance() << endl << "Path: " << endl;
    PrintPath();
}

void Savings(int root)
{
    fill(visited.begin(),visited.end(),false);
    path.clear();

//    path.push_back(root);
    visited[root] = true;

    deque <int> pathInitial;
    double savingTable[sz][sz];
    int head, tail, matha, lej;
    double highest = 0.0, highest1 = 0.0, highest2 = 0.0;

    for(int i = 0; i < sz; i++)
    {
        for(int j = i+1; j < sz; j++)
        {
            if(i == root || j == root || i == j)
            {
                savingTable[i][j] = INF;
            }

            else
            {
                savingTable[i][j] = GetDistance(cityList[root], cityList[i]) + GetDistance(cityList[root], cityList[j]) - GetDistance(cityList[i], cityList[j]);
                savingTable[j][i] = savingTable[i][j];

                if (savingTable[i][j] > highest)
                {
                    highest = savingTable[i][j];
                    head = i;
                    tail = j;
                }
            }
        }
    }

    pathInitial.push_front(head);
    pathInitial.push_back(tail);
    visited[head] = true;
    visited[tail] = true;

    while(pathInitial.size() < sz-1)
    {
        head = pathInitial.front();
        tail = pathInitial.back();

        for(int i = 0; i < sz; i++)
        {
            if(!visited[i])
            {
                if(highest1 < savingTable[head][i])
                {
                    highest1 = savingTable[head][i];
                    matha = i;
                }
            }
        }

         for(int i = 0; i < sz; i++)
        {
            if(!visited[i])
            {
                if(highest2 < savingTable[tail][i])
                {
                    highest2 = savingTable[tail][i];
                    lej = i;
                }
            }
        }

        if(matha != lej)
        {
            pathInitial.push_front(matha);
            pathInitial.push_back(lej);
            visited[matha] = true;
            visited[lej] = true;
        }

        if(matha == lej)
        {
            if(highest1 > highest2)
            {
                pathInitial.push_front(matha);
                visited[matha] = true;
            }

            else
            {
                pathInitial.push_back(lej);
                visited[lej] = true;
            }
        }

        highest1 = 0.0;
        highest2 = 0.0;
    }

    pathInitial.push_back(root);
    pathInitial.push_front(root);

    for(int i : pathInitial)
    {
        path.push_back(i);
    }

    cout << "Path distance for Savings heuristics: " << PathDistance() << endl << "Path: " << endl;
    PrintPath();
}

void Opt2 (int root)
{
    NearestNeighbour(root);
    //NearestInsertion(root);

    float dist = PathDistance();
    float distNew;
    bool flag;
    int i = 1;

    while(true)
    {
        flag = false;

        for(int i = 1; i < path.size()-2; i++)
        {
            for(int j = i+1; j < path.size()-1; j++)
            {
                reverse(path.begin()+i, path.begin()+j);
                distNew = PathDistance();

                if(distNew < dist)
                {
                    dist = distNew;
                    flag = true;
                    break;
                }

                else
                {
                    reverse(path.begin()+i, path.begin()+j);
                }
            }

            if(flag) break;
        }

        if(!flag) break;
    }

    cout << "Path distance for Two-Opt heuristics: " <<  PathDistance() << endl << "Path: " << endl;
    PrintPath();
}

int main()
{
    int n, m;

    freopen("burma14.tsp","r",stdin);

    scanf("%d", &sz);

    visited.resize(sz);
    cityList.resize(sz);

    GetMap();

    Savings(0);
    NearestNeighbour(0);

    return 0;
}
