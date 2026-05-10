class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
         stack<int> st;       // stores indices (monotonically increasing heights)
        int maxArea = 0;
        int n = heights.size();

        for (int i = 0; i <= n; i++) {
            // Use 0 as sentinel at the end to flush remaining stack
            int currHeight = (i == n) ? 0 : heights[i];

            while (!st.empty() && currHeight < heights[st.top()]) {
                int height = heights[st.top()];
                st.pop();

                // Width: from stack's new top (left boundary) to i (right boundary)
                int width = st.empty() ? i : (i - st.top() - 1);

                maxArea = max(maxArea, height * width);
            }

            st.push(i);
        }

        return maxArea;
    }
};