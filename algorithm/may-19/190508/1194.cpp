#include <bits/stdc++.h>
using namespace std;
char board[51][51];
int n, m, s_y, s_x;
struct node{
    int y, x, move;
    string keys;
    node(int y_, int x_, int move_):y(y_),x(x_),move(move_),keys(""){}
    node(int y_, int x_, int move_, string keys_):y(y_),x(x_),move(move_),keys(keys_){}
    bool operator == (const node &n) const {
        return y == n.y && x == n.x && keys == n.keys;
    }
    bool operator < (const node& n) const {
        if(y != n.y) return y < n.y;
        if(x != n.x) return x < n.x;
        return keys < n.keys;
    }
};
set<node> visited;

int valid_position(int y, int x)
{
    return (y >=0 && y < n) && (x >= 0 && x < m);
}

int dydx[4][2] = {
        0,1,
        1,0,
        0,-1,
        -1,0
};

bool have_key(const string& keys, char lock)
{
    for(char k : keys){
        if(k == lock + ('a' - 'A')){
            return true;
        }
    }
    return false;
}

bool is_lock(char c)
{
    return c >= 'A' && c <= 'F';
}

bool is_key(char c)
{
    return c >= 'a' && c <= 'f';
}

void add_key(string& s, char c)
{
    for(char k : s){
        if(k == c) return;
    }
    s += c;
    sort(s.begin(), s.end());
}

int bfs()
{
    queue<node> q;
    q.push(node{s_y, s_x, 0});

    while(q.size()){
        auto n = q.front();
        q.pop();

        if(visited.find(n) != visited.end()) continue;
        visited.insert(n);

        for(int i=0; i<4; ++i){
            int next_y = n.y + dydx[i][0], next_x = n.x + dydx[i][1];
            if(valid_position(next_y, next_x)){
                if(board[next_y][next_x] == '1'){
                    return n.move + 1;
                }
                if(board[next_y][next_x] == '#'){
                    continue;
                }
                node new_node{next_y, next_x, n.move + 1, n.keys};
                if(is_key(board[next_y][next_x])){
                    add_key(new_node.keys, board[next_y][next_x]);
                }

                if(visited.find(new_node) != visited.end()) continue;
                if(is_lock(board[next_y][next_x])){
                    if(have_key(n.keys, board[next_y][next_x])) {
                        q.push(new_node);
                    }
                    continue;
                }
                q.push(new_node);
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for(int i=0; i<n; ++i){
        for(int j=0; j<m; ++j){
            cin >> board[i][j];
            if(board[i][j] == '0') s_y = i, s_x = j;
        }
    }

    cout << bfs();

    return 0;
}
