class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int totGas = 0, totCost =0;

        for(int x: gas){
            totGas += x;
        }
        for(int x : cost){
            totCost += x;
        }


        if(totGas< totCost){
            return -1;
        }

        int start = 0; int currGas =0;

        for(int i =0;i<gas.size();i++){
            currGas += (gas[i] - cost[i]);

            if(currGas <0){
                start = i+1;
                currGas = 0;
            }

        }
        return start;
    }
};