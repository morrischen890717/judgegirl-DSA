#include <iostream>
#define max 12
#define mod 1000000007
using namespace std;
int c[max * max][max * max], solved[max * max][max * max];
char map[max][max];
long long paper_way[max][max][max][max][max * max];
long long dp_solved[max][max][max][max][max * max];
int C(int n, int m){ //C(n取m)
    if(solved[n][m] == true)
        return c[n][m];
    solved[n][m] = true;
    if(n == m || m == 0)
        return c[n][m] = 1;
    else
        return c[n][m] = (C(n - 1, m) + C(n - 1, m - 1)) % mod;
}
int check(int row_or_col, int fixed_index, int range_L, int range_R){ // 0 for row, 1 for col
    if(row_or_col){
        for(int i = range_L; i < range_R; i++){
            if(map[i][fixed_index] == 'X'){
                return 0;
            }
        }
    }
    else{
        for(int i = range_L; i < range_R; i++){
            if(map[fixed_index][i] == 'X'){
                return 0;
            }
        }
    }
    return 1;
}
long long tear(int L1, int R1, int L2, int R2, int K);
long long tear(int L1, int R1, int L2, int R2, int K){
    if(dp_solved[L1][R1][L2][R2][K]){
        return paper_way[L1][R1][L2][R2][K];
    }
    dp_solved[L1][R1][L2][R2][K] = 1;
    if(K == 0){
        paper_way[L1][R1][L2][R2][K] = 1;
        return paper_way[L1][R1][L2][R2][K];
    }
    if(R1 <= L1 || R2 <= L2){
        paper_way[L1][R1][L2][R2][K] = 0;
        return paper_way[L1][R1][L2][R2][K];
    }
    long long sum = 0;
    if(L1 != R1 - 1){//cannot tear it when there is only one column left
        //start tearing column part
        for(int i = L1; i < R1; i++){
            if(check(1, i, L2, R2)){
                for(int K_A = 0; K_A < K; K_A++){
                    sum += ((C(K - 1, K_A) * tear(L1, i, L2, R2, K_A) % mod) * tear(i + 1, R1, L2, R2, K - 1 - K_A) % mod);
                }
            }
        }
    }
    if(L2 != R2 - 1){//cannot tear it when there is only one row left
        //start tearing row part
        for(int i = L2; i < R2; i++){
            if(check(0, i, L1, R1)){
                for(int K_A = 0; K_A < K; K_A++){
                    sum += ((C(K - 1, K_A) * tear(L1, R1, L2, i, K_A) % mod) * tear(L1, R1, i + 1, R2, K - 1 - K_A) % mod);
                }
            }
        }
    }
    paper_way[L1][R1][L2][R2][K] = sum % mod;
    return paper_way[L1][R1][L2][R2][K];
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> map[i][j];
        }
    }
    long long sum = 0;
    //int col_can_tear = 0;
    //int row_can_tear = 0;
    /*for(int i = 0; i < m; i++){
        if(check(1, i, 0, n)){
            col_can_tear = 1;
            break;
        }
    }
    for(int i = 0; i < n; i++){
        if(check(0, i, 0, m)){
            row_can_tear = 0;
            break;
        }
    }*/
    //if(col_can_tear || row_can_tear){
        for(int K = 0; K <= n * m; K++){
            sum += tear(0, m, 0, n, K);
            sum %= mod;
        }
    //}
    cout << sum << '\n';
    return 0;
}
