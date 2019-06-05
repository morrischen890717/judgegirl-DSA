#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
long long state_yield[4][4][4][4];
long long tmp_state[4][4][4][4];
int trans(char a){
    switch(a){
        case 'M':
            return 1;
        case 'F':
            return 2;
        case 'B':
            return 3;
        default:
            return 0;
    }
}
int compute(int a, int b, int c){
    int yield = 0;
    if(a == 1 || b == 1 || c == 1) yield++;
    if(a == 2 || b == 2 || c == 2) yield++;
    if(a == 3 || b == 3 || c == 3) yield++;
    return yield;
}
int dp(int n){
    char input;
    for(int i = 0; i < n; i++){
        int now = trans(getchar());
        for(int b = 0; b < 4; b++){
            for(int d = 0; d < 4; d++){
                for(int a = 0; a < 4; a++){
                    int mxA = -1, mxB = -1;
                    for(int c = 0; c < 4; c++){
                        if(state_yield[a][b][c][d] != -1){
                            if(state_yield[a][b][c][d] + compute(c, d, now) > mxB){
                                mxB = state_yield[a][b][c][d] + compute(c, d, now);
                            }
                        }
                        if(state_yield[c][b][a][d] != -1){
                            if(state_yield[c][b][a][d] + compute(c, b, now) > mxA){
                                mxA = state_yield[c][b][a][d] + compute(c, b, now);
                            }
                        }
                    }
                    if(mxB > tmp_state[a][b][d][now]){
                        tmp_state[a][b][d][now] = mxB;
                    }
                    if(mxA > tmp_state[b][now][a][d]){
                        tmp_state[b][now][a][d] = mxA;
                    }
                        //cout << "aaa " << tmp_state[a][b][d][now] << ' ' << mxB << '\n';
                        //cout << "bbb " << tmp_state[b][now][a][d] << ' ' << mxA << '\n';
                }
            }
        }
        memcpy(state_yield, tmp_state, sizeof(tmp_state));
    }
    int answer = -2;
    for(int a = 0; a < 4; a++){
        for(int b = 0; b < 4; b++){
            for(int c = 0; c < 4; c++){
                for(int d = 0; d < 4; d++){
                    if(state_yield[a][b][c][d] > answer){
                        answer = state_yield[a][b][c][d];
                    }
                }
            }
        }
    }
    return answer;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    //cin >> n;
    scanf("%d", &n);
    getchar();
    memset(state_yield, -1, sizeof(state_yield));
    memset(tmp_state, -1, sizeof(state_yield));
    state_yield[0][0][0][0] = 0;
    tmp_state[0][0][0][0] = 0;
    cout << dp(n) << '\n';
    return 0;
}
//dp(b, id, c, d) = dp(a, b, c, d) + val(a, b, id);
//dp(a, b, d, id) = dp(a, b, c, d) + val(c, d, id);
