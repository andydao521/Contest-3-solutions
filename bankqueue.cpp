#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int n, T;
    cin >> n >> T;
    // n = number of people in line
    // T = number of minutes until the bank closes
    // Only 1 person can be served per minute → total of T slots

    vector<pair<int,int>> people(n); // (money, deadline)
    // people[i].first  = how much money this person deposits
    // people[i].second = last minute they are willing to wait (deadline)

    for (int i = 0; i < n; i++) {
        cin >> people[i].first >> people[i].second;
    }

    // Sort people by deadline in DESCENDING order
    sort(people.begin(), people.end(), [](pair<int,int> a, pair<int,int> b) {
        return a.second > b.second;
    });
    // WHY:
    // We will process time from T-1 → 0 (backwards),
    // so we want to quickly access all people whose deadline >= current time

    priority_queue<int> pq; // max heap storing money values
    // This lets us always pick the person with the MOST money available

    int i = 0;     // pointer to iterate through sorted people
    int total = 0; // total money collected

    // Loop through time slots from last minute to first
    for (int t = T - 1; t >= 0; t--) {
        // t represents the current minute we are trying to fill

        // Add all people who can still be served at time t
        // (i.e., their deadline >= t → they haven't left yet)
        while (i < n && people[i].second >= t) {
            pq.push(people[i].first); // add their money into heap
            i++;
        }

        // At this point:
        // pq contains ALL people who are still available at time t

        // Greedy choice: serve the richest person available
        if (!pq.empty()) {
            total += pq.top(); // take the maximum money
            pq.pop();          // remove that person (they are served)
        }

        // KEY IDEA:
        // Each minute, we choose the person with the highest money
        // among all people who haven't left yet
        // → This maximizes total money collected
    }

    cout << total << endl;
    // Final answer: maximum money Oliver can collect before closing
}