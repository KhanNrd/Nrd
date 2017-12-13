#include <functional>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <numeric>
#include <string>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>



using namespace std;


int n, m;
vector <bool> used;
map <pair <int, int>, bool> was;

struct node{
    int cnt;
    vector <int> g;
};

vector <node> a;
vector <pair <int, int> > edge, ed;

void read_Instructions(){
    cin >> n >> m;
    a.resize(n);
    used.resize(n);
    for(int i = 0, u, v; i < m; ++i){
        cin >> u >> v;
        u--, v--;
        edge.push_back(make_pair(u, v));
        a[u].g.push_back(v);
    }
}

void read_StartState(){
    for(int i = 0; i < n; ++i){
        cin >> a[i].cnt;
    }
}

vector <pair <int, int> > get_RandomEdges(){
    vector <pair <int, int> > res;
    int e = 1;
    while(e != 0){
        e = rand() % m + 1;
        res.clear();
        random_shuffle(edge.begin(), edge.end());
        for(int i = 0; i < m && e; ++i){
            int u = edge[i].first;
            int v = edge[i].second;
            if(a[u].cnt > 0 && !used[v]){
                res.push_back(edge[i]);
                used[v] = 1;
                e--;
            }
        }
        for(int i = 0; i < n; ++i){
            used[i] = 0;
        }
    }
    return res;
}

void update(){
    for(int i = 0; i < (int)ed.size(); ++i){
        int u = ed[i].first;
        int v = ed[i].second;
        a[u].cnt--;
        a[v].cnt++;
    }
}

void transition(){
    ed = get_RandomEdges();
    for(int i = 0; i < n; ++i){
        used[i] = 0;
    }
    for(int i = 0; i < (int)ed.size(); ++i){
        int u = ed[i].first;
        int v = ed[i].second;
        used[u] = 1;
        was[make_pair(u, v)] = 1;
    }
    update();
}

void print(){
    for(int i = 0; i < n; ++i){
        if(used[i]){
            cout << "from " << i + 1 << " to ->\n";
            for(int j = 0; j < (int)a[i].g.size(); ++j){
                int u = i;
                int v = a[i].g[j];
                if(was[make_pair(u, v)]){
                    cout << v + 1 << "\n";
                }
            }
        }
    }
    for(int i = 0; i < n; ++i){
        cout << a[i].cnt << " ";
    }
    cout << "\n";
    for(int i = 0; i < n; ++i){
        used[i] = 0;
    }
    for(int i = 0; i < m; ++i){
        was[make_pair(edge[i].first, edge[i].second)] = 0;
    }
}

int main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    srand(time(NULL));
    read_Instructions();
    read_StartState();
    while(true){
        transition();
        print();
        char c = getchar();
    }
}
