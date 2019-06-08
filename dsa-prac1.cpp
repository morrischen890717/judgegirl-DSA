#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#define inf 1000000
using namespace std;
int dis[10005];
int visited[10005];
vector<pair<int, int>> map_[10000 + 5];
int mst(int n);
int mst(int n){
    int cost = 0;
    int count = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    int start_node = 1;
    dis[start_node] = 0;
    pq.push(make_pair(dis[start_node], start_node));
    while(!pq.empty()){
        pair<int, int> now = pq.top();
        pq.pop();
        if(!visited[now.second]){
            visited[now.second] = 1;
            count++;
            cost += dis[now.second];
            for(pair<int, int> k:map_[now.second]){
                if(k.first < dis[k.second]){
                    dis[k.second] = k.first;
                    pq.push(make_pair(dis[k.second], k.second));
                }
            }
        }
    }
    if(count == n) return cost;
    else return -1;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    while(cin >> n >> m){
        if(n == 0 && m == 0) break;
        for(int i = 1; i <= n; i++){
            map_[i].clear();
        }
        memset(visited, 0, sizeof(visited));
        memset(dis, inf, sizeof(dis));
        for(int i = 0 ; i < m; i++){
            int node1, node2, weight;
            cin >> node1 >> node2 >> weight;
            map_[node1].push_back(make_pair(weight, node2));
            map_[node2].push_back(make_pair(weight, node1));
        }
        cout << mst(n) << '\n';
    }
    return 0;
}
