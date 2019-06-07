#include <iostream>
#include <cstdio>
using namespace std;
long long state[1000005];
long long num_list[1000005];
long long max_[1000005];
long long max(long long a, long long b){
    if(a > b) return a;
    return b;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long answer;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> num_list[i];
        if(i == 0) max_[i] = num_list[i];
        else max_[i] = max(max_[i - 1] + num_list[i], max(max_[i - 1], num_list[i]));
    }
    state[2] = num_list[0] + num_list[2];
    answer = state[2];
    for(int i = 3; i < n; i++){
        state[i] = max(state[i - 1], max_[i - 2]) + num_list[i];//要不要放第i - 1個
        answer = max(answer, state[i]);
    }
    cout << answer << '\n';
    return 0;
}
//dp[i] = max(dp[i - 1], dp[i - 2] + num);
//reference:http://www3.tcgs.tc.edu.tw/npsc/index.php?topic=2531.0
/*
用三個陣列來記錄，A[ i ]記錄輸入的數字是多少，
B[ i ]記錄從第一個數到第i個數取某些數字(至少取一個)的最大值是多少，(第i個不一定要取)，
B[1]=A[1]，i=2~N-2時，B[ i ]=max(A[ i ], B[ i-1 ], A[ i ]+B[ i-1 ]),
而 C[ i ]記錄以第i個為最後一個的最大不連續和是多少，(第i個一定要取)
C[3]=A[1]+A[3]，i=4~N時，C[ i ]=max(C[ i-1 ], B[ i-2 ])+A[ i ]，
即可求出答案。
*/
