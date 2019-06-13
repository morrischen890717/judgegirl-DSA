#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#define max_node_num 100005
#define inf 1e18
using namespace std;
vector<pair<int, long long>> map_[max_node_num];
long long dijkstra(int start, int end, int n);
long long dijkstra(int start, int end, int n){
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    //int dis1[n] = {inf};
    //int dis2[n] = {inf};
    long long dis1[n], dis2[n];
    //memset(dis1, inf, n);
    //memset(dis2, inf, n);
    for(int i = 0; i < n; i++){
        dis1[i] = inf;
        dis2[i] = inf;
    }
    dis1[start] = 0;
    pq.push({dis1[start], start});
    while(!pq.empty()){
        pair<long long, int> now = pq.top();
        pq.pop();
        int now_node = now.second;
        long long now_dis = now.first;
        if(dis2[now_node] < now_dis) continue;
        for(pair<int, long long> go:map_[now_node]){
            int go_node = go.first;
            long long go_dis = go.second;
            if(now_dis + go_dis < dis1[go_node]){
                dis2[go_node] = dis1[go_node];
                dis1[go_node] = now_dis + go_dis;
                pq.push({dis1[go_node], go_node});
                pq.push({dis2[go_node], go_node});
            }
            else if(now_dis + go_dis < dis2[go_node] && now_dis + go_dis > dis1[go_node]){
                dis2[go_node] = now_dis + go_dis;
                pq.push({dis2[go_node], go_node});
            }
        }
    }
    return dis2[end] - dis1[end];
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        int n, m, start, end;
        cin >> n >> m >> start >> end;
        for(int j = 0; j < n; j++){
            map_[j].clear();
        }
        for(int j = 0; j < m; j++){
            int from, to;
            long long dis;
            cin >> from >> to >> dis;
            map_[from].push_back({to, dis});
        }
        cout << dijkstra(start, end, n) << '\n';
    }
    return 0;
}
