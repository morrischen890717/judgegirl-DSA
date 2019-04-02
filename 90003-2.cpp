#include <iostream>
using namespace std;
int number = 0;
int n, q;
int ancestor[200100][20] = {0};//recording the node_num of ancestors
typedef struct Trie{
    int node_num;
    struct Trie *child[26];
}trie;
int node_depth[200100];
trie *getnode(){
    trie *new_node = new trie;
    for(int i = 0; i < 26; i++){
        new_node->child[i] = NULL;
    }
    number++;
    new_node->node_num = number;
    //number++;
    return new_node;
}
trie *ptr[200100];
int query(int fir, int sec);
int query(int fir, int sec){
    if(node_depth[ptr[fir]->node_num] < node_depth[ptr[sec]->node_num]){
        int temp = fir;
        fir = sec;
        sec = temp;
    }
    //jump to the same depth
    int fir_node_num = ptr[fir]->node_num;
    int sec_node_num = ptr[sec]->node_num;
    int higher = node_depth[sec_node_num];
    for(int i = 18; i >= 0; i--){
        if(node_depth[ancestor[fir_node_num][i]] >= higher){
            fir_node_num = ancestor[fir_node_num][i];
        }
    }
    if(fir_node_num == sec_node_num){
        return node_depth[fir_node_num];
    }//return if the two are at the same node after jumping to the same depth
    for(int i = 18; i >= 0; i--){
        if(ancestor[fir_node_num][i] != ancestor[sec_node_num][i]){
            fir_node_num = ancestor[fir_node_num][i];
            sec_node_num = ancestor[sec_node_num][i];
        }
    }
    return node_depth[ancestor[fir_node_num][0]];
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    trie *root = getnode();
    ptr[0] = root;
    root->node_num = 0;
    for(int i = 0; i < 26; i++){
        root->child[i] = NULL;
    }
    node_depth[0] = 0;
    number--;
    //cout << "now_number = " << number << '\n';
    int add_index;
    char add_value;
    for(int i = 1; i <= n; i++){
        cin >> add_index >> add_value;
        add_value -= 'a';
        if(ptr[add_index]->child[add_value] == NULL){
            ptr[add_index]->child[add_value] = getnode();
            //cout << "number123 = " << number << '\n';
            node_depth[number] = node_depth[ptr[add_index]->node_num] + 1;
            ancestor[number][0] = ptr[add_index]->node_num;
            //cout << "number = " << number << "add_index = " << add_index << '\n';
            for(int j = 1; j < node_depth[number]; j++){
                if(ancestor[number][j - 1] != 0){
                    ancestor[number][j] = ancestor[ancestor[number][j - 1]][j - 1];
                }
            }
        }
        ptr[i] = ptr[add_index]->child[add_value];
    }
    int x, y;
    cin >> q;
    for(int i = 0; i < q; i++){
        cin >> x >> y;
        cout << query(x, y) << '\n';
    }
    return 0;
}
