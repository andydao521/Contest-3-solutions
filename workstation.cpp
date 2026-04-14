#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    // n = number of researchers
    // m = number of minutes before an unused workstation locks itself

    vector<pair<int,int>> people(n); // (arrival, duration)
    // people[i].first  = arrival time
    // people[i].second = how long they stay

    for (int i = 0; i < n; i++) {
        cin >> people[i].first >> people[i].second;
    }

    // sort researchers by arrival time (earliest first)
    sort(people.begin(), people.end());
    // WHY:
    // We process events in time order, so we always handle the next arriving researcher

    priority_queue<int, vector<int>, greater<int>> pq;
    // min heap storing "end times" of workstations
    // pq.top() = the workstation that becomes free the earliest

    int saved = 0; // number of unlocks we save

    for (int i = 0; i < n; i++) {
        int arrival = people[i].first;
        int end = arrival + people[i].second;
        // end = time when this researcher leaves the workstation

        // remove workstations that have already LOCKED
        while (!pq.empty() && pq.top() + m < arrival) {
            pq.pop();
        }
        // CONCEPT:
        // pq.top() = when a workstation became free
        // pq.top() + m = time it locks
        // if that < arrival → it's already locked → cannot reuse → remove it

        // try to reuse a workstation
        if (!pq.empty() && pq.top() <= arrival) {
            // pq.top() <= arrival → workstation is free AND still unlocked
            saved++;   // we saved an unlock by reusing it
            pq.pop();  // assign this workstation to current researcher
        }

        // assign current researcher to a workstation (new or reused)
        pq.push(end);
        // this workstation will now be free again at time = end
    }

    cout << saved << endl;
    // output how many unlock operations we avoided
    return 0;
}