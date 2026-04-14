#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>
using namespace std;

int main() {
    priority_queue<int> left; 
    // max heap → stores the smaller half of numbers
    // top() = largest value in the smaller half

    priority_queue<int, vector<int>, greater<int>> right; 
    // min heap → stores the larger half of numbers
    // top() = smallest value in the larger half → THIS is our median

    string s;

    while (cin >> s) {
        // input is either:
        // a number (new cookie arrives)
        // or "#" (request to output median)

        if (s == "#") {
            // output the median
            cout << right.top() << "\n";
            // problem requires:
            // - odd count → middle value
            // - even count → upper median
            // → always right.top()

            right.pop();
            // remove that cookie since it gets sent away
        } 
        else {
            int x = stoi(s);
            // convert string to integer (cookie diameter)

            // decide which heap to insert into
            if (!right.empty() && x > right.top())
                right.push(x);  // goes into larger half
            else
                left.push(x);   // goes into smaller half

            // IDEA:
            // - left holds smaller values
            // - right holds larger values
        }


        if (left.size() > right.size()) {
            // left has too many → move largest from left to right
            right.push(left.top());
            left.pop();
        }
        else if (right.size() > left.size() + 1) {
            // right has too many → move smallest from right to left
            left.push(right.top());
            right.pop();
        }

    }
}