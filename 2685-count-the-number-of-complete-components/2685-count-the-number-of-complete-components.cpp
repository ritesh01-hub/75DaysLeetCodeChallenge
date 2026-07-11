class Solution {
public:

    void dfs(int node,
             vector<vector<int>> &adj,
             vector<bool> &visited,
             int &vertices,
             int &degreeSum) {

        visited[node] = true;
        vertices++;

        degreeSum += adj[node].size();

        for (int neighbour : adj[node]) {
            if (!visited[neighbour]) {
                dfs(neighbour, adj, visited, vertices, degreeSum);
            }
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {

        // Step 1: Build Graph
        vector<vector<int>> adj(n);

        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];

            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<bool> visited(n, false);

        int completeComponents = 0;

        // Step 2: Traverse every component
        for (int i = 0; i < n; i++) {

            if (!visited[i]) {

                int vertices = 0;
                int degreeSum = 0;

                dfs(i, adj, visited, vertices, degreeSum);

                // Every edge counted twice
                int edgesCount = degreeSum / 2;

                // Expected edges in complete graph
                int expectedEdges = vertices * (vertices - 1) / 2;

                if (edgesCount == expectedEdges)
                    completeComponents++;
            }
        }

        return completeComponents;
    }
};