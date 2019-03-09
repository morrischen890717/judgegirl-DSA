#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cctype>
using namespace std;
inline void read(int &p){
    p = 0;
    char c = getchar();
    while(!isdigit(c)){
        c = getchar();
    }
    while(isdigit(c)){
        p = p * 10 + c - '0';
        c = getchar();
    }
}
int main(){
    int n, m, k;
    read(n);
    read(m);
    read(k);
    int int_list[n];
    for(int i = 0; i < n; i++){
        read(int_list[i]);
    }
    vector <int> window(int_list, int_list + m);
    sort(window.begin(), window.end());
    for(int i = 0; i < n - m + 1; i++){
        printf("%d\n", window[k - 1]);
        if(i == n - m){
            break;
        }
        window.erase(lower_bound(window.begin(), window.end(), int_list[i]));
        window.insert(lower_bound(window.begin(), window.end(), int_list[i + m]), int_list[i + m]);
    }
    return 0;
}
