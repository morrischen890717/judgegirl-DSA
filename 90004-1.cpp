#include <iostream>
#include <unordered_map>
using namespace std;
char Alice[17][2], Bob[17][2];
unordered_map<unsigned long long, int> map_;
int max(int a, int b){
    if(a >= b){
        return a;
    }
    else{
        return b;
    }
}
int min(int a, int b){
    if(a <= b){
        return a;
    }
    else{
        return b;
    }
}
unsigned long long pre_trans(unsigned long long zzz, char now_pre_color, char now_pre_num){
    switch (now_pre_color){
        case 'C':
            zzz &= ~((unsigned long long)3 << 22);
            break;
        case 'D':
            zzz &= ~((unsigned long long)1 << 23);
            zzz |= ((unsigned long long)1 << 22);
            break;
        case 'H':
            zzz &= ~((unsigned long long)1 << 22);
            zzz |= ((unsigned long long)1 << 23);
            break;
        case 'S':
            zzz |= ((unsigned long long)3 << 22);
            break;
    }
    switch (now_pre_num){
        case 'A':
            zzz &= ~((unsigned long long)7 << 19);
            zzz |= ((unsigned long long)1 << 18);
            break;
        case '2':
            zzz &= ~((unsigned long long)3 << 20);
            zzz |= ((unsigned long long)1 << 19);
            zzz &= ~((unsigned long long)1 << 18);
            break;
        case '3':
            zzz &= ~((unsigned long long)3 << 20);
            zzz |= ((unsigned long long)3 << 18);
            break;
        case '4':
            zzz &= ~((unsigned long long)1 << 21);
            zzz |= ((unsigned long long)1 << 20);
            zzz &= ~((unsigned long long)3 << 18);
            break;
        case '5':
            zzz &= ~((unsigned long long)1 << 21);
            zzz |= ((unsigned long long)1 << 20);
            zzz &= ~((unsigned long long)1 << 19);
            zzz |= ((unsigned long long)1 << 18);
            break;
        case '6':
            zzz &= ~((unsigned long long)1 << 21);
            zzz |= ((unsigned long long)3 << 19);
            zzz &= ~((unsigned long long)1 << 18);
            break;
        case '7':
            zzz &= ~((unsigned long long)1 << 21);
            zzz |= ((unsigned long long)7 << 18);
            break;
        case '8':
            zzz |= ((unsigned long long)1 << 21);
            zzz &= ~((unsigned long long)7 << 18);
            break;
        case '9':
            zzz |= ((unsigned long long)1 << 21);
            zzz &= ~((unsigned long long)3 << 19);
            zzz |= ((unsigned long long)1 << 18);
            break;
        case 'T':
            zzz |= ((unsigned long long)1 << 21);
            zzz &= ~((unsigned long long)1 << 20);
            zzz |= ((unsigned long long)1 << 19);
            zzz &= ~((unsigned long long)1 << 18);
            break;
        case 'J':
            zzz |= ((unsigned long long)1 << 21);
            zzz &= ~((unsigned long long)1 << 20);
            zzz |= ((unsigned long long)3 << 18);
            break;
        case 'Q':
            zzz |= ((unsigned long long)3 << 20);
            zzz &= ~((unsigned long long)3 << 18);
            break;
        case 'K':
            zzz |= ((unsigned long long)3 << 20);
            zzz &= ~((unsigned long long)1 << 19);
            zzz |= ((unsigned long long)1 << 18);
            break;
    }
    return zzz;
}
int alphabeta(unsigned long long now, int alpha, int beta, int now_player, char pre_color, char pre_num){
    int if_A_win = 1;
    int if_B_win = 1;
    for(int i = 0; i < 17; i++){
        if((now >> (42 + i)) & 1){
            if_A_win = 0;
        }
        if((now >> (25 + i)) & 1){
            if_B_win = 0;
        }
    }
    if(if_A_win == 1 && if_B_win == 0){
        int point = 0;
        for(int i = 0; i < 17; i++){
            if((now >> (25 + i)) & 1){
                //cout << "A_WIN_i = " << i << '\n';
                //cout << Bob[i][1] << '\n';
                switch(Bob[i][1]){
                    case 'A':
                        point += 1;
                        break;
                    case 'T':
                        point += 10;
                        break;
                    case 'J':
                        point += 11;
                        break;
                    case 'Q':
                        point += 12;
                        break;
                    case 'K':
                        point += 13;
                        break;
                    default:
                        point += Bob[i][1] - '0';
                }
            }
        }
        return point;
    }
    if(if_A_win == 0 && if_B_win == 1){
        int point = 0;
        for(int i = 0; i < 17; i++){
            if((now >> (42 + i)) & 1){
                switch(Alice[i][1]){
                    case 'A':
                        point += 1;
                        break;
                    case 'T':
                        point += 10;
                        break;
                    case 'J':
                        point += 11;
                        break;
                    case 'Q':
                        point += 12;
                        break;
                    case 'K':
                        point += 13;
                        break;
                    default:
                        point += Alice[i][1] - '0';
                }
            }
        }
        return -point;
    }
    unordered_map<unsigned long long, int>::iterator it;
    if((it = map_.find(now)) != map_.end()){
        return it->second;
    }
    if(now_player == 0){
        int v = -200;
        int pass_A = 1;
        int k = alpha + 200;
        for(int j = 0; j < 9; j++){
            if((k >> j) & 1){
                now |= ((unsigned long long)1 << (j + 9));
            }
            else{
                now &= ~((unsigned long long)1 << (j + 9));
            }
        }
        for(int i = 0; i < 17; i++){
            if(((now >> (42 + i)) & 1) && ((((now >> 18) & 15) == 0) || Alice[i][1] == pre_num || Alice[i][0] == pre_color)){
                pass_A = 0;
                unsigned long long zzz = now;
                zzz &= ~((unsigned long long)1 << (42 + i));
                zzz |= ((unsigned long long)1 << 24);
                zzz = pre_trans(zzz, Alice[i][0], Alice[i][1]);
                v = max(v, alphabeta(zzz, alpha, beta, 1, Alice[i][0], Alice[i][1]));
                alpha = max(v, alpha);
                if(beta <= alpha){
                    break;
                }
            }
        }
        if(pass_A){
            unsigned long long zzz = now;
            zzz |= ((unsigned long long)1 << 24);
            zzz &= ~((unsigned long long)15 << 18);
            v = max(v, alphabeta(zzz, alpha, beta, 1, 'B', 'm'));
            alpha = max(v, alpha);
        }
        map_.insert(make_pair(now, v));
        return v;
    }
    else{
        int v = 200;
        int pass_B = 1;
        int k = beta + 200;
        for(int j = 0; j < 9; j++){
            if((k >> j) & 1){
                now |= ((unsigned long long)1 << j);
            }
            else{
                now &= ~((unsigned long long)1 << j);
            }
        }
        for(int i = 0; i < 17; i++){
            if(((now >> (25 + i)) & 1) && ((((now >> 18) & 15) == 0) || Bob[i][1] == pre_num || Bob[i][0] == pre_color)){
                pass_B = 0;
                unsigned long long zzz = now;
                zzz &= ~((unsigned long long)1 << (25 + i));
                zzz &= ~((unsigned long long)1 << 24);
                zzz = pre_trans(zzz, Bob[i][0], Bob[i][1]);
                v = min(v, alphabeta(zzz, alpha, beta, 0, Bob[i][0], Bob[i][1]));
                beta = min(v, beta);
                if(beta <= alpha){
                    break;
                }
            }
        }
        if(pass_B){
            unsigned long long zzz = now;
            zzz &= ~((unsigned long long)1 << 24);
            zzz &= ~((unsigned long long)15 << 18);
            v = min(v, alphabeta(zzz, alpha, beta, 0, 'B', 'm'));
            beta = min(v, beta);
        }
        map_.insert(make_pair(now, v));
        return v;
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int now_player = 0;
    for(int i = 0; i < n; i++){
        cin >> Alice[i];
    }
    for(int i = 0; i < n; i++){
        cin >> Bob[i];
    }
    unsigned long long start = 0;
    int k = 0;
    for(int i = 0; i < n; i++){
        k <<= 1;
        k |= 1;
    }
    start |= k;
    start <<= 17;
    start |= k;
    start <<= 25;
    start |= (unsigned long long)400;
    int h;
    h = alphabeta(start, -200, 200, 0, -1, -1);
    if(h < 0){
        cout << "Bob" << '\n';
        cout << -h << '\n';
    }
    else{
        cout << "Alice" << '\n';
        cout << h << '\n';
    }
    return 0;
}
