#include <iostream>
#include <set>
using namespace std;
int main(){
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    int array[n];

    multiset<int>::iterator it;
    for(int i = 0; i < m; i++){
        scanf("%d", &array[i]);
    }
    multiset<int> window(array, array + m);
    it = window.begin();
    for(int i = m; i < n; i++){
        scanf("%d", &array[i]);
    }
    for(int i = 0; i < k - 1; i++){
        it++;
    }
    printf("%d\n", *(it));
    for(int i = 0; i < n - m; i++){
        window.insert(array[i + m]);
        multiset<int>::iterator erase_point;
        erase_point = window.lower_bound(array[i]);
        if(array[i + m] < *(it)){//insert
            it--;
        }
        //printf("now_it = %d\n", *(it));
        if(array[i] != *(it)){
            window.erase(erase_point);
            if(array[i] < *(it)){
                it++;
            }
        }
        else{
            if(erase_point == window.end()--){
                it--;
                window.erase(erase_point);
            }
            else{
                //printf("i = %d\n", i);
                it++;
                window.erase(erase_point);
            }
        }
        printf("%d\n", *(it));
    }
    return 0;
}
