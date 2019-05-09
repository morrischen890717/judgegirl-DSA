#include <iostream>
#include <unordered_map>
#include <string>
#define x 101
using namespace std;
unordered_map<long long, int> count;
unordered_map<long long, int>::iterator it;
long long power[200000];
void prefix_(string input, long long all_prefix[], int length){
    for(int i = 0; i < length; i++){
        all_prefix[i + 1] = all_prefix[i] * x + input[i];
        if(i != 0){
            power[i] = power[i - 1] * x;
        }
        else{
            power[i] = 1;
        }
    }
    return;
}
int if_have(int now_length, int m, int ori_len, long long all_prefix[]){
    int times = 0;
    int right = -1;
    count.clear();
    for(int i = now_length; i <= ori_len; i++){
        long long now_prefix = all_prefix[i];
        long long delete_prefix = all_prefix[i - now_length];
        now_prefix -= delete_prefix * power[now_length];
        if((it = count.find(now_prefix)) == count.end()){
            count.insert(make_pair(now_prefix, 1));
            times = 1;
        }
        else{
            it = count.find(now_prefix);
            it->second++;
            times = it->second;
        }
        if(times >= m){
            right =  i - now_length;
        }
    }
    return right;
}
void binary_search(int left, int right, int ori_len, int m, long long all_prefix[]){
    int binary_length = 0;
    int right_index = -1;
    int pre_len = -1;
    int pre_right = -1;
    while(left < right){
        binary_length = (left + right) / 2 + 1;
        right_index = if_have(binary_length, m, ori_len, all_prefix);
        if(right_index == -1){
            right = binary_length - 1;
        }
        else{
            left = binary_length;
            pre_len = binary_length;
            pre_right = right_index;
        }
    }
    if(pre_len == -1){
        cout << "none" << '\n';
    }
    else{
        cout << pre_len << " " << pre_right << '\n';
    }
    return;
}
void problem_two(string input, int length, long long all_prefix[]){
    for(int i = length - 2; i > 0; i--){
        long long problem_two_fir;
        long long problem_two_sec;
        problem_two_fir = all_prefix[i];
        problem_two_sec = all_prefix[length] - all_prefix[length - i] * power[i];
        if(problem_two_fir == problem_two_sec){
            for(int j = 1; j < length - i; j++){
                long long mid;
                mid = all_prefix[j + i] - all_prefix[j] * power[i];
                if(mid == problem_two_fir){
                    string aaa;
                    aaa.assign(input, 0, i);
                    cout << aaa << '\n';
                    return;
                }
            }
        }
    }
    cout << "Just a legend\n";
    return;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m;
    string input;
    while(cin >> m){
        if(m == 0){
            break;
        }
        cin >> input;
        int length = input.length();
        long long all_prefix[length + 1];
        all_prefix[0] = 0;
        prefix_(input, all_prefix, length);
        binary_search(0, length + 1, length, m, all_prefix);
        problem_two(input, length, all_prefix);
    }
    return 0;
}
