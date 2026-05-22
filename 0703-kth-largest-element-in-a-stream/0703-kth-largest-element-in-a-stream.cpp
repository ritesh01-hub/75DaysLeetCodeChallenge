class KthLargest {
private:
    priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap
    int k;

public:
    KthLargest(int k, vector<int>& nums) {
        this->k = k;
        for (int num : nums) {
            minHeap.push(num);
            if (minHeap.size() > k)
                minHeap.pop(); // remove smallest, keep top-k
        }
    }
    
    int add(int val) {
        minHeap.push(val);
        if (minHeap.size() > k)
            minHeap.pop(); // evict if heap exceeds size k
        return minHeap.top(); // top of min-heap = kth largest
    }
};