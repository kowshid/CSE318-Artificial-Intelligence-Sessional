#include<bits/stdc++.h>

#define pr pair<int,int>
#define INF 999999
using namespace std;

int sz, cost;
vector <pr> cityList;
vector <int> path;
vector <bool> visited;

void GetMap()
{
    pr temp;
    int x, y;

    for(int i = 0; i < sz; i++)
    {
        scanf("%d %d", &x, &y);
        cityList[i] = make_pair(x, y);
    }
}

int GetDistance(pr a, pr b)
{
     int dist, xDist, yDist;
     xDist = (a.first-b.first);
     yDist = (a.second-b.second);

     dist = xDist*xDist + yDist*yDist;

     return dist;
}

int GetNearestNeighbour(int root)
{
    int dist = INF, result = INF, n;

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

float PathDistance()
{
    float result = 0;

    for(int i = 0; i < path.size()-1; i++)
    {
        result += sqrt(1.0 * GetDistance(cityList[path[i]], cityList[path[i+1]]));
    }

    return result;
}

void PrintPath()
{
    for(int i = 0; i < path.size(); i++)
    {
        cout<<path[i]+1<<"-->";
    }

    //cout<<path[path.size()-1]+1<<endl;
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

    cout << PathDistance() << endl;
    PrintPath();
}

int NextNodeNI()
{
    int dist = INF, result, temp;

    for(int i = 0; i < sz; i++)
    {
        if(visited[i])
        {
            temp = GetNearestNeighbour(i);

            if(cost < dist)
            {
                dist = cost;
                result = temp;
            }
        }
    }

    return result;
}

void NearestInsertion(int root)
{
    int n = 3, next, dist = INF, distNew, idx;

    fill(visited.begin(),visited.end(),false);
    path.clear();

    path.push_back(root);
    visited[root] = true;

    next = GetNearestNeighbour(root);
    path.push_back(next);
    visited[next] = true;

    path.push_back(root);

    cout << PathDistance() << endl;
    PrintPath();
    cout << endl;

    while(path.size() <= sz)
    {
        next = NextNodeNI();
        visited[next] = true;
        dist = INF;

        cout << next + 1<< endl;

        for(int i = 0; i < (path.size() - 1); i++)
        {
            distNew = GetDistance(cityList[path[i]], cityList[next]) + GetDistance(cityList[path[i+1]], cityList[next]) - GetDistance(cityList[path[i]], cityList[path[i+1]]);

            if(distNew < dist)
            {
                dist = distNew;
                idx = i + 1;
            }
        }

        //right shift
        path.push_back(INF);

        for(int i = path.size() - 1; i > idx; i--)
        {
            path[i] = path[i - 1];
        }

        path[idx] = next;
    }

    cout << PathDistance() << endl;
    PrintPath();
}

int NextNodeCI()
{
    int dist = INF, result, distNew;

    for(int j = 0; j < sz; j++)
    {
        if(!visited[j])
        {
            for(int i = 0; i < path.size() - 1; i++)
            {
                distNew = GetDistance(cityList[path[i]], cityList[j]) + GetDistance(cityList[path[i+1]], cityList[j]) - GetDistance(cityList[path[i]], cityList[path[i+1]]);
                if(distNew < dist)
                {
                    dist = distNew;
                    result = j;
                }
            }
        }
    }

    return result;
}

void CheapestInsertion(int root)
{
    int n = 3, next, dist = INF, distNew, idx;

    fill(visited.begin(),visited.end(),false);
    path.clear();

    path.push_back(root);
    visited[root] = true;

    next = GetNearestNeighbour(root);
    path.push_back(next);
    visited[next] = true;

    path.push_back(root);

    cout << PathDistance() << endl;
    PrintPath();
    cout << endl;

    while(path.size() <= sz)
    {
        next = NextNodeCI();
        visited[next] = true;
        dist = INF;

        cout << next + 1 << endl;

        for(int i = 0; i < (path.size() - 1); i++)
        {
            distNew = GetDistance(cityList[path[i]], cityList[next]) + GetDistance(cityList[path[i+1]], cityList[next]) - GetDistance(cityList[path[i]], cityList[path[i+1]]);

            if(distNew < dist)
            {
                dist = distNew;
                idx = i + 1;
            }
        }

        //right shift
        path.push_back(INF);

        for(int i = path.size() - 1; i > idx; i--)
        {
            path[i] =path[i - 1];
        }

        path[idx] = next;

        n++;
    }

    cout << PathDistance() << endl;
    PrintPath();
}

void PrintMap()
{
    for(int i = 0; i < sz; i++)
    {
        printf("\n%d %d", cityList[i].first, cityList[i].second);
    }
}

int main()
{
    int n, m;

    freopen("in.txt","r",stdin);

    scanf("%d", &sz);

    visited.resize(sz);
    cityList.resize(sz);

    GetMap();
    //PrintMap();
    //NearestNeighbour(0);
    NearestInsertion(0);
    CheapestInsertion(0);

    return 0;
}
