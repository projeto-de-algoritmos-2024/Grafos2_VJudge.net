#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> graph;
        
        for (const auto& ticket : tickets) {
            graph[ticket[0]].push(ticket[1]);
        }
        
        vector<string> result;
        stack<string> stk;
        stk.push("JFK");
        
        while (!stk.empty()) {
            string current = stk.top();
            
            if (graph[current].empty()) {
                result.push_back(current);
                stk.pop();
            } else {
                stk.push(graph[current].top());
                graph[current].pop();
            }
        }
        
        reverse(result.begin(), result.end());
        return result;
    }
};
