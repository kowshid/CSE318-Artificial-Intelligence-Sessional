#include <bits/stdc++.h>

#define pr pair<double,double>
#define INF 999999.9

using namespace std;

int sz;
int bestNNidx, worstNNidx, bestSidx, worstSidx;
double cost, actualCost;
double distNN[4],  distS[4];
vector <pr> cityList;
vector <int> path;
vector <bool> visited;
vector <double> costTableNN;
vector <double> costTableS;
vector <pair<int, int>> vpr;
vector <vector <int>> pathsNN;
vector <vector <int>> pathsS;
ofstream myfile("1505102.txt");

void GetMap()
{
    pr temp;
    double x, y, a;

    for(int i = 0; i < sz; i++)
    {
        cin >> a >> x >> y;
        cityList[i] = make_pair(x, y);
    }

    cin >> actualCost;
    //myfile << "Actual Cost : " << actualCost << endl;
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
        myfile <<pathTemp[i]+1 << "-->";
    }

    myfile << endl;
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

    double dist[5] = {INF, INF, INF, INF, INF}, n, high;
    int result[5], j = 0, idx, random;

    for(int i = 0; i < sz; i++)
    {
        high = 0.0;

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
    int choice = a;
    fill(visited.begin(), visited.end(), false);
    path.clear();

    int t = root;
    int n = 1;

    path.push_back(root);
    visited[root] = true;

    if(choice == 1) //greedy_simple
    {
        while(n < sz)
        {
            t = GetNearestNeighbour(t);
            path.push_back(t);
            visited[t] = true;

            n++;
        }
    }

    if(choice == 2) //greedy_randomized
    {
        //myfile << "Check inside randomized" << endl;
        while(n < sz)
        {
            t = GetNearestNeighbourRandom(t);
            path.push_back(t);
            visited[t] = true;

            n++;
        }
    }

    path.push_back(root);

    if (choice == 1)
    {
        myfile << "NearestNeighbor heuristic Path distance :" << PathDistance(path) << endl;
    //PrintPath(path);
    }

    if(choice == 2)
    {
        //myfile << "Path: ";
        //PrintPath(path);
        myfile << "Path Distance : " << PathDistance(path) << endl;
    }
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

    myfile << "Savings heuristics Path distance :" << PathDistance(path) << endl;
    //PrintPath(path);
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

    //myfile << "Path: ";
    //PrintPath(path);
    myfile << "Path Distance : " << PathDistance(path) << endl;
}

void TwoOptFirst (vector <int> path)
{
    vector <int> pathTemp;
    pathTemp.clear();
    for(int k : path)
    {
        pathTemp.push_back(k);
    }

    double dist = PathDistance(pathTemp);
    double distNew;
    bool flag;

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

    myfile << "After applying Two-Opt First heuristics: " <<  PathDistance(pathTemp) << endl;
    //PrintPath(pathTemp);
}

void TwoOptBest (vector <int> path)
{
    vector <int> pathTemp;
    pathTemp.clear();
    for(int k : path)
    {
        pathTemp.push_back(k);
    }

    double dist = PathDistance(pathTemp);
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

    myfile << "Path distance after applying Two-Opt heuristics: " <<  PathDistance(pathTemp) << endl;
    //PrintPath(pathTemp);
}

void task1()
{
    myfile  << "In task1 " << endl << endl;

    int random;
    double bestNN = INF, worstNN = 0.0, bestS = INF, worstS = 0.0, avgNN = 0, avgS = 0.0;

    for(int i = 0; i < 5; i++)
    {
        random = rand()%sz;

        myfile << "Source is " << random+1 << endl;

        NearestNeighbour(random, 1);
        costTableNN[random] = PathDistance(path);
        avgNN += costTableNN[random];

        if(costTableNN[random] < bestNN)
        {
            bestNN = costTableNN[random];
            bestNNidx = random;
        }

        if(costTableNN[random] > worstNN)
        {
            worstNN = costTableNN[random];
            worstNNidx = random;
        }

        Savings(random);
        costTableS[random] = PathDistance(path);
        avgS += costTableS[random];

        if(costTableS[random] < bestS)
        {
            bestS = costTableS[random];
            bestSidx = random;
        }

        if(costTableS[random] > worstS)
        {
            worstS = costTableS[random];
            worstSidx = random;
        }
    }

    avgNN = avgNN/5.0;
    avgS = avgS/5.0;

    myfile << endl << "Using NearestNeighbor heuristics: " << endl;
    myfile << endl << "Best source node : " << bestNNidx+1 << endl;
    myfile <<  "Best cost : " << costTableNN[bestNNidx] << endl;
    myfile << "Worst cost : " << costTableNN[worstNNidx] << endl;
    myfile << "Average cost : " << avgNN << endl;

    myfile << endl << "Using Savings heuristics: " << endl;
    myfile << endl << "Best source node : " << bestSidx+1 << endl;
    myfile <<  "Best cost : " << costTableS[bestSidx] << endl;
    myfile << "Worst cost : " << costTableS[worstSidx] << endl;
    myfile << "Average cost : " << avgS << endl;
}

void task2()
{
    myfile << endl << "In task2 " << endl << endl;

    int j = 0, idx, iterationNumber = 10;
//    double distNN[3] = {INF, INF, INF},  distS[3] = {INF, INF, INF};
    double high, distCur;
    double bestNN = INF, worstNN = 0.0, bestS = INF, worstS = 0.0, avgNN = 0.0, avgS = 0.0;

    myfile << "Using NearestNeighbor (randomized) heuristics" << endl;

    for(int i = 0; i < iterationNumber; i++)
    {
        high = 0.0;

        NearestNeighbour(bestNNidx, 2);

//        costTableNN[bestNNidx] = PathDistance(path);
        distCur = PathDistance(path);
        avgNN += distCur;

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
            pathsNN[j].clear();

            for(int i : path)
            {
                pathsNN[j].push_back(i);
            }

            if(PathDistance(pathsNN[j]) != worstNN && PathDistance(pathsNN[j]) != bestNN)
            {
                distNN[j] = PathDistance(pathsNN[j]);
                j++;
            }
        }

        else
        {
            //find the index with worst cost
            for(int k = 0; k < 3; k++)
            {
                if(high < distNN[k])
                {
                    idx = k;
                    high = distNN[k];
                }
            }

            if (distCur == distNN[0] || distCur == distNN[1] || distCur == distNN[2])
            {

            }

            else if (distCur < distNN[idx])
            {
                pathsNN[idx].clear();
                for(int i : path)
                {
                    pathsNN[idx].push_back(i);
                }

                distNN[idx] = PathDistance(pathsNN[idx]);
            }
        }
    }

    j = 0;

    myfile << endl << "Using Savings (randomized) heuristics" << endl;

    for(int i = 0; i < iterationNumber; i++)
    {
        high = 0.0;

        SavingsRandom(bestSidx);

        distCur = PathDistance(path);
        avgS += distCur;

        if(distCur < bestS)
        {
            bestS = distCur;
        }

        if(distCur > worstS)
        {
            worstS = distCur;
        }

        if(j < 3)
        {
            pathsS[j].clear();

            for(int i : path)
            {
                pathsS[j].push_back(i);
            }

            distS[j] = PathDistance(pathsS[j]);
            j++;
        }

        else
        {
            //find the index with worst cost
            for(int k = 0; k < 3; k++)
            {
                if(high < distS[k])
                {
                    idx = k;
                    high = distS[k];
                }
            }

            if (distCur == distS[0] || distCur == distS[1] || distCur == distS[2])
            {

            }

            else if(distCur < distS[idx])
            {
                pathsS[idx].clear();

                for(int i : path)
                {
                    pathsS[idx].push_back(i);
                }

                distS[idx] = PathDistance(pathsS[idx]);
            }
        }
    }

    avgNN = avgNN/iterationNumber;
    avgS = avgS/iterationNumber;

    myfile << endl << "NearestNeighbor (randomized) heuristics: " << endl;
    myfile << endl << "Best root node : " << bestNNidx+1 << endl;
    myfile << "Best cost :"  << bestNN << endl;
    myfile << "Worst cost : " << worstNN << endl;
    myfile << "Average cost : " << avgNN << endl << endl;

    for(int i = 0; i < 3; i++)
    {
        //myfile << "pathNN " << i << ": ";
        //PrintPath(pathsNN[i]);
        myfile << "cost " << distNN[i] << endl;
    }

    myfile << endl << "In Savings (randomized) heuristics: " <<endl;
    myfile << endl << "Best source : " << bestSidx+1 << endl;
    myfile << "Best cost : "  << bestS << endl;
    myfile << "Worst cost : " << worstS << endl;
    myfile << "Average cost : " << avgS << endl << endl;

    for(int i = 0; i < 3; i++)
    {
        //myfile << "pathS " << i << ": ";
        //PrintPath(pathsS[i]);
        myfile << "cost " << distS[i] << endl;
    }
}

void task3()
{
    double bestNN = INF, worstNN = 0.0, bestS = INF, worstS = 0.0, tempDist;
    NearestNeighbour(bestNNidx, 1);

    for(int i : path)
    {
        pathsNN[3].push_back(i);
    }

    distNN[3] = PathDistance(pathsNN[3]);

    Savings(bestSidx);

    for(int i : path)
    {
        pathsS[3].push_back(i);
    }

    distS[3] = PathDistance(pathsS[3]);

    vector <int> tempPath;

    myfile << endl << "Applying Two-Opt First Improvement: " << endl;
    myfile << endl << "On NearestNeighbor Randomized" << endl;

    for(int i = 0; i < 4; i++)
    {
        //myfile << "path " << i+1 << " : "; PrintPath(pathsNN[i]);
        myfile << "Initial Path Distance " << i+1 << " : " << distNN[i] << endl;
        TwoOptFirst(pathsNN[i]);
    }

    myfile << endl << "On Savings Randomized" << endl;

    for(int i = 0; i < 4; i++)
    {
        //myfile << "path " << i+1 << " : "; PrintPath(pathsS[i]);
        myfile << "Initial Path Distance " << i+1 << " : " << distS[i] << endl;
        TwoOptFirst(pathsS[i]);
    }

    myfile << endl << "Applying Two-Opt Best Improvement: " << endl;
    myfile << endl << "On NearestNeighbor Randomized" << endl;

    for(int i = 0; i < 4; i++)
    {
        //myfile << "path " << i+1 << " : "; PrintPath(pathsNN[i]);
        myfile << "Initial Path Distance " << i+1 << " : " << distNN[i] << endl;
        TwoOptBest(pathsNN[i]);
    }

    myfile << endl << "On Savings Randomized" << endl;

    for(int i = 0; i < 4; i++)
    {
        //myfile << "path " << i+1 << " : "; PrintPath(pathsS[i]);
        myfile << "Initial Path Distance " << i+1 << " : " << distS[i] << endl;
        TwoOptBest(pathsS[i]);
    }
}

int main()
{
    srand(time(NULL));

    freopen("berlin52.tsp", "r", stdin);
    //freopen("1505102.txt", "w", stdin);

    scanf("%d", &sz);

    visited.clear();
    cityList.clear();
    costTableNN.clear();
    costTableS.clear();
    pathsNN.clear();
    pathsS.clear();

    visited.resize(sz);
    cityList.resize(sz);
    costTableNN.resize(sz);
    costTableS.resize(sz);
    pathsNN.resize(4);
    pathsS.resize(4);

    GetMap();

    task1();
    task2();
    task3();

    myfile.close();
    return 0;
}
