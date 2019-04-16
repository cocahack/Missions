#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <unordered_map>
using namespace std;

struct building
{
    int h, idx;
    building(int h_ = 0, int idx_ = 0) { h = h_, idx = idx_; }
    bool operator == (const building& rhs) const { return h == rhs.h && idx == rhs.idx; }
    bool operator < (const building& rhs) const {
        if(h == rhs.h){
            return idx < rhs.idx;
        }
        return h < rhs.h;
    }
};

struct event
{
    int p, h, idx;
    bool end;
    event(int h_ = 0, int p_ = 0, int idx_ = 0, bool end_ = false){ h = h_, p = p_, idx = idx_, end = end_; }
    bool operator == (const event& rhs) const { return h == rhs.h && end == rhs.end && p == rhs.p; }
    bool operator < (const event& rhs) const {
        if(p == rhs.p){
            if(h == rhs.h){
                return end < rhs.end;
            }
            return h < rhs.h;
        }
        return p < rhs.p;
    }
};

vector<event> events;
set<building> buildings;

unordered_map<int, int> answer;
vector<pair<int, int>> reorder_answer;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t, l, h, r;
    cin >> t;

    for(int i=0; i<t; ++i){
        cin >> l >> h >> r;
        events.push_back(event(h, l, i, false));
        events.push_back(event(h, r, i, true));
    }

    sort(events.begin(), events.end());

    for(auto e : events){
        if(e.end){
            if(buildings.size() == 1){
                answer[e.p] = 0;
                buildings.erase(building(e.h, e.idx));
            } else {
                buildings.erase(building(e.h, e.idx));
                if((*buildings.rbegin()).h < e.h)
                    answer[e.p] = (*buildings.rbegin()).h;
            }
        } else {
            if(buildings.empty()){
                answer[e.p] = e.h;
            } else {
                if((*buildings.rbegin()).h < e.h){
                    answer[e.p] = e.h;
                }
            }
            buildings.insert(building(e.h, e.idx));
        }
    }

    for(auto iter : answer){
        reorder_answer.push_back(make_pair(iter.first, iter.second));
    }

    sort(reorder_answer.begin(), reorder_answer.end());

    for(auto a : reorder_answer){
        cout << a.first << " " << a.second << " ";
    }



    return 0;
}
