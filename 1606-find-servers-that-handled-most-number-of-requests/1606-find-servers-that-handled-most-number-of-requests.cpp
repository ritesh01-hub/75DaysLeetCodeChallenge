
class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        
        // Available servers
        set<int> available;
        for (int i = 0; i < k; i++) {
            available.insert(i);
        }

        // Min heap: {completion time, server index}
        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > busy;

        vector<int> count(k, 0);

        for (int i = 0; i < arrival.size(); i++) {
            
            // Release servers whose requests are completed
            while (!busy.empty() && busy.top().first <= arrival[i]) {
                available.insert(busy.top().second);
                busy.pop();
            }

            // If all servers are busy, drop the request
            if (available.empty()) {
                continue;
            }

            // Preferred server
            int server = i % k;

            // Find the first available server >= preferred server
            auto it = available.lower_bound(server);

            // Wrap around if necessary
            if (it == available.end()) {
                it = available.begin();
            }

            server = *it;

            // Assign request
            available.erase(it);

            count[server]++;

            // Calculate completion time
            busy.push({
                (long long)arrival[i] + load[i],
                server
            });
        }

        // Find maximum number of handled requests
        int maxi = *max_element(count.begin(), count.end());

        vector<int> ans;

        for (int i = 0; i < k; i++) {
            if (count[i] == maxi) {
                ans.push_back(i);
            }
        }

        return ans;
    }
};
