class Solution {
public:
    bool isValid(string s) {

        stack<char> st;

        for(int i = 0; i < s.length(); i++) {

            // Opening brackets
            if(s[i] == '(' || s[i] == '{' || s[i] == '[') {
                st.push(s[i]);
            }

            // Closing brackets
            else {

                if(st.empty()) {
                    return false;
                }

                if(s[i] == ')' && st.top() != '(') {
                    return false;
                }

                if(s[i] == '}' && st.top() != '{') {
                    return false;
                }

                if(s[i] == ']' && st.top() != '[') {
                    return false;
                }

                st.pop();
            }
        }

        return st.empty();
    }
};