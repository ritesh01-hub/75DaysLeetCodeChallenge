class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        unordered_map<Node*, Node*> cloned;
        queue<Node*> q;

        // Clone the starting node and push to queue
        cloned[node] = new Node(node->val);
        q.push(node);

        while (!q.empty()) {
            Node* curr = q.front(); q.pop();

            for (Node* neighbor : curr->neighbors) {
                // If neighbor not cloned yet, clone it and enqueue
                if (cloned.find(neighbor) == cloned.end()) {
                    cloned[neighbor] = new Node(neighbor->val);
                    q.push(neighbor);
                }
                // Link cloned curr → cloned neighbor
                cloned[curr]->neighbors.push_back(cloned[neighbor]);
            }
        }

        return cloned[node];
    }
};