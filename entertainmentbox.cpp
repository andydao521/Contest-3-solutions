#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    // n = number of TV shows
    // k = number of recording slots (machines that can record simultaneously)

    vector<pair<int,int>> shows(n); // (start, end)
    // shows[i].first  = start time
    // shows[i].second = end time

    for (int i = 0; i < n; i++) {
        cin >> shows[i].first >> shows[i].second;
    }

    // sort shows by END time (earliest finishing first)
    sort(shows.begin(), shows.end(), [](pair<int,int> a, pair<int,int> b) {
        return a.second < b.second;
    });
    // WHY:
    // Classic greedy strategy:
    // Always pick the show that finishes earliest → leaves room for more shows later

    multiset<int> slots; // stores end times of currently used recording slots
    // Each value = when that slot becomes free again
    // multiset is sorted automatically

    int count = 0; // number of shows we successfully record

    for (int i = 0; i < n; i++) {
        int start = shows[i].first;
        int end = shows[i].second;

        // find the first slot that ends AFTER start
        auto it = slots.upper_bound(start);
        // upper_bound(start) → first element > start

        // case 1: we found a slot that can be reused
        if (it != slots.begin()) {
            --it;
            // now it points to the largest end time ≤ start
            // meaning this slot is free right when we need it

            slots.erase(it);   // remove old end time (slot becomes reused)
            slots.insert(end); // update slot with new show's end time
            count++;           // we recorded this show
        }
        // case 2: no reusable slot, but we still have free machines
        else if (slots.size() < k) {
            slots.insert(end); // assign a new slot
            count++;           // we recorded this show
        }
        // else:
        // no slot available → we skip this show
    }

    cout << count << endl;
    return 0;
}