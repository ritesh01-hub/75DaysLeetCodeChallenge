class Solution {
public:
    bool checkString(string s) {
        int n = s.length();
        bool foundB = false;

        for(int i =0;i<n;i++){
            if(s[i] == 'b'){
                foundB= true;
            }
            else if(s[i]== 'a' && foundB){
                return false;
            }
                
        
        }

        return true;
    }
};