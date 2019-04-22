#include <bits/stdc++.h>
using namespace std;
int b[301]{0,}, n, m;

bool is_possible(int max_val)
{
    if(max_val < b[0]) return false;
    int sum = b[0], g = 1;

    for(int i=1; i<n; ++i){
        if(b[i] > max_val) return false;
        if(sum + b[i] > max_val){
            sum = b[i];
            g++;
        } else {
            sum += b[i];
        }
    }

    return g <= m;
}

int solve() {
    int lo = 0, hi = 30000, mid;

    while(lo + 1 < hi){
        mid = (lo + hi) / 2;
        if(is_possible(mid)){
            hi = mid;
        } else {
            lo = mid;
        }
    }
    
    return is_possible(lo) ? lo : hi;
}

void print_sets(int max_val)
{
    vector<int> subsum{0, b[0]};
    for(int i=1; i<n; ++i){
        subsum.push_back(subsum[i]+b[i]);
    }

    vector<int> answer(m, 1);
    answer[0] = n - m + 1;
    int start = 0;
    for(int i = 0; i < m - 1; ++i){
        while (1){
            int idx = 0;
            for(int j=0; j<=i; ++j) idx += answer[j];
            int cur_sum = subsum[idx] - subsum[start];
            if(cur_sum <= max_val) break;
            answer[i+1]++;
            answer[i]--;
        }
        start += answer[i];
    }

    for(auto a : answer) cout << a << " ";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < n; ++i) cin >> b[i];

    int ans = solve();
    cout << ans << "\n";
    print_sets(ans);

    return 0;
}
