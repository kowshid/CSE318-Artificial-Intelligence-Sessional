#include <bits/stdc++.h>

#define pr pair<double,double>
#define INF 999999.9

using namespace std;

int sz;
int bestNNidx, worstNNidx, bestSidx, worstSidx;
double bestNN, worstNN, bestS, worstS;
double cost;
vector <pr> cityList;
vector <int> path;
vector <bool> visited;
vector <double> costTableNN;
vector <double> costTableS;
vector <pair<int, int>> vpr;
vector <vector <int>> paths;

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

double PathDistance(vector <int> pathTemp)
{
    double result = 0.0;

    for(int i = 0; i < pathTemp.size()-1; i++)
    {
        result += GetDistance(cityList[pathTemp[i]], cityList[pathTemp[i+1]]);
    }

    return result;
}

void PrintPath(vector <int> pathTemp)
{
    for(int i = 0; i < pathTemp.size(); i++)
    {
        cout<<pathTemp[i]+1<<"-->";
    }

    cout << endl;
}

int GetNearestNeighbour(int root)
{
    double dist = INF, n;
    int result = INF;

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

int GetNearestNeighbourRandom(int root)
{
    vpr.clear();
    vpr.resize(5);

    double dist[5] = {INF, INF, INF, INF, INF}, n, high = 0.0;
    int result[5], j = 0, idx, random;

    for(int i = 0; i < sz; i++)
    {
        if(visited[i]) continue;

        n = GetDistance(cityList[root], cityList[i]);
        //printf("\n%d", n);
        if(j < 5)
        {
            result[j] = i;
            dist[j] = n;
            vpr[j] = make_pair(root, i);
            j++;
        }

        else
        {
            for(int k = 0; k < 5; k++)
            {
                if(high < dist[k])
                {
                    idx = k;
                    high = dist[k];
                }
            }

            if(n < dist[idx] && n != 0)
            {
                result[idx] = i;
                dist[idx] = n;
                vpr[idx] = make_pair(root, i);
            }
        }
    }

    random = rand()%j;
    cost = dist[random];
    return result[random];
}

void NearestNeighbour(int root, int a)
{
    fill(visited.begin(), visited.end(), false);
    path.clear();

    int t = root;
    int n = 1;

    path.push_back(root);
    visited[root] = true;

    if(a == 1) //greedy_simple
    {
        while(n < sz)
        {
            t = GetNearestNeighbour(t);
            path.push_back(t);
            visited[t] = true;

            n++;
        }
    }

    if(a == 2) //greedy_randomized
    {
        //cout << "Check inside randomized" << endl;
        while(n < sz)
        {
            t = GetNearestNeighbourRandom(t);
            path.push_back(t);
            visited[t] = true;

            n++;
        }
    }

    path.push_back(root);

    cout << "Path distance for NearestNeighbour heuristics: " <<  PathDistance(path) << endl << "Path: ";
    PrintPath(path);
}

void Savings(int root)
{
    fill(visited.begin(), visited.end(), false);
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

//    cout << "Path distance for Savings heuristics: " << PathDistance(path) << endl << "Path: ";
//    PrintPath(path);
}

void SavingsRandom(int root)
{
    fill(visited.begin(), visited.end(), false);
    path.clear();
    vpr.clear();
    vpr.resize(5);

//    path.push_back(root);
    visited[root] = true;

    deque <int> pathInitial;
    double savingTable[sz][sz], low = INF;
    int head, tail, matha, lej, a = 0, idx, random;
    double highest[5] = {INF, INF, INF, INF, INF}, highest1 = 0.0, highest2 = 0.0;

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

                if(a < 5)
                {
                    highest[a] = savingTable[i][j];
                    vpr[a] = make_pair(i, j);
                    a++;
                }

                else
                {
                    for(int k = 0; k < 5; k++)
                    {
                        if(low > highest[k])
                        {
                            idx = k;
                            low = highest[k];
                        }
                    }

                    if (savingTable[i][j] > highest[idx])
                    {
                        highest[idx] = savingTable[i][j];
                        vpr[idx] = make_pair(i,j);
                    }
                }
            }
        }
    }

    random = rand()%a;
    head = vpr[random].first;
    tail = vpr[random].second;

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

//    cout << "Path distance for Savings heuristics: " << PathDistance(path) << endl << "Path: ";
//    PrintPath(path);
}

void TwoOptFirst (int root, vector <int> pathTemp)
{
    double dist = PathDistance(path);
    double distNew;
    bool flag;
    int i = 1;

    while(true)
    {
        flag = false;

        for(int i = 1; i < pathTemp.size()-2; i++)
        {
            for(int j = i+1; j < pathTemp.size()-1; j++)
            {
                reverse(pathTemp.begin()+i, pathTemp.begin()+j+1);
                distNew = PathDistance(pathTemp);

                if(distNew < dist)
                {
                    dist = distNew;
                    flag = true;
                    break;
                }

                else
                {
                    reverse(pathTemp.begin()+i, pathTemp.begin()+j+1);
                }
            }

            if(flag) break;
        }

        if(!flag) break;
    }

    cout << "Path distance after applying Two-Opt heuristics: " <<  PathDistance(pathTemp) << endl << "Path: ";
    PrintPath(pathTemp);
}

void TwoOptBest (int root, vector <int> pathTemp)
{
    double dist = PathDistance(path);
    double distNew;
    bool flag;
    int i = 1;

    while(true)
    {
        flag = false;

        for(int i = 1; i < pathTemp.size()-2; i++)
        {
            for(int j = i+1; j < pathTemp.size()-1; j++)
            {
                reverse(pathTemp.begin()+i, pathTemp.begin()+j+1);
                distNew = PathDistance(pathTemp);

                if(distNew < dist)
                {
                    dist = distNew;
                    flag = true;
                }

                else
                {
                    reverse(pathTemp.begin()+i, pathTemp.begin()+j+1);
                }
            }

            if(flag) break;
        }

        if(!flag) break;
    }

    cout << "Path distance after applying Two-Opt heuristics: " <<  PathDistance(pathTemp) << endl << "Path: ";
    PrintPath(pathTemp);
}

void task1()
{
    int random;

    for(int i = 0; i < 5; i++)
    {
        random = rand()%sz;

        NearestNeighbour(random, 1);
        costTableNN[random] = PathDistance(path);

        if(PathDistance(path) < bestNN)
        {
            bestNN = PathDistance(path);
            bestNNidx = random;
        }

        if(PathDistance(path) > worstNN)
        {
            worstNN = PathDistance(path);
            worstNNidx = random;
        }

        Savings(random);
        costTableS[random] = PathDistance(path);

        if(PathDistance(path) < bestS)
        {
            bestS = PathDistance(path);
            bestSidx = random;
        }
        if(PathDistance(path) > worstS)
        {
            worstS = PathDistance(path);
            worstSidx = random;
        }
    }

    cout << endl << "Best root node for NearestNeighbour heuristics: " << bestNNidx+1 << endl;
    cout << endl << "Best cost using NearestNeighbour heuristics: " << costTableNN[bestNNidx] << endl;
    cout << "Worst cost using NearestNeighbour heuristics: " << costTableNN[worstNNidx] << endl;

    cout << endl << "Best root node for Saving heuristics: " << bestSidx+1 << endl;
    cout << endl << "Best cost using Savings heuristics: " << costTableS[bestSidx] << endl;
    cout << "Worst cost using Savings heuristics: " << costTableS[worstSidx] << endl << endl;
}

void task2()
{
    int j = 0, idx;
    double dist[3] = {INF, INF, INF}, distCur;

    for(int i = 0; i < 6; i++)
    {
        double high = 0.0;

        NearestNeighbour(bestNNidx, 2);

//        costTableNN[bestNNidx] = PathDistance(path);
        distCur = PathDistance(path);

        if(distCur < bestNN)
        {
            bestNN = distCur;
        }

        if(distCur > worstNN)
        {
            worstNN = distCur;
        }

        if(j < 3)
        {
            for(int i : path)
            {
                paths[j].push_back(i);
            }

            dist[j] = PathDistance(paths[j]);
            j++;
        }

        else
        {
            //find the index with worst cost
            for(int k = 0; k < 3; k++)
            {
                if(high < dist[k])
                {
                    idx = k;
                    high = dist[k];
                }
            }

            if(distCur < dist[idx])
            {
                paths[idx].clear();
                for(int i : path)
                {
                    paths[idx].push_back(i);
                }

                dist[idx] = PathDistance(paths[idx]);
            }
        }
    }

//    for(int i = 0; i < 5; i++)
//    {
//        SavingsRandom(bestSidx);
////        costTableS[bestSidx] = PathDistance(path);
//
//        if(PathDistance(path) < bestS)
//        {
//            bestS = PathDistance(path);
//            //bestSidx = random;
//        }
//        if(PathDistance(path) > worstS)
//        {
//            worstS = PathDistance(path);
//            //worstSidx = random;
//        }
//    }

    cout << endl << "Best root node for NearestNeighbour heuristics: " << bestNNidx+1 << endl;
    cout << endl << "Best cost using NearestNeighbour (randomized) heuristics: " << bestNN << endl;
    cout << "Worst cost using NearestNeighbour (randomized) heuristics: " << worstNN << endl;

//    cout << endl << "Best root node for Saving heuristics: " << bestSidx+1 << endl;
//    cout << endl << "Best cost using Savings (randomized) heuristics: " << bestS << endl;
//    cout << "Worst cost using Savings (randomized) heuristics: " << worstS << endl << endl;

    for(int i = 0; i < 3; i++)
        {
            cout << "path " << i << ": ";
            PrintPath(paths[i]);
        }
}

void task3()
{
    NearestNeighbour(bestNNidx, 1);
    TwoOptBest(bestNNidx, path);

    cout << endl << endl;

    //Savings(bestSidx);
    //Opt2(bestSidx);
}

int main()
{
    srand(time(NULL));
    bestS = INF, bestNN = INF, worstS = 0, worstNN = 0;

    freopen("burma14.tsp","r",stdin);

    scanf("%d", &sz);

    visited.resize(sz);
    cityList.resize(sz);
    costTableNN.resize(sz);
    costTableS.resize(sz);
    paths.resize(3);

    GetMap();

    task1();
    task2();
   // task3();

    return 0;
}
