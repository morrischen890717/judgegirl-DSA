#include <iostream>
#include <cstdio>
using namespace std;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    long long n;
    scanf("%lld", &n);
    long long seesaw[n];
    long long sum = 0;
    long long weight = 0;
    for(int i = 0; i < n; i++){
        scanf("%lld", &seesaw[i]);
        sum += seesaw[i];
        weight += seesaw[i] * (i + 1);
    }
    for(long long x = 0; x <= n / 2; x++){
        if(x){
            weight = weight + (n + 1 - 2 * x) * (seesaw[x - 1] - seesaw[n - x]);
        }
        if(!(weight % sum)){
            cout << x << ' ' << weight / sum - 1 << '\n';
            break;
        }
    }
    return 0;
}
