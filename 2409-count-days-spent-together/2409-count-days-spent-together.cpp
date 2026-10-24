class Solution {
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, 
                          string arriveBob, string leaveBob) {
        
        vector<int> days = {31, 28, 31, 30, 31, 30, 
                            31, 31, 30, 31, 30, 31};

        auto getDay = [&](string date) {
            int month = stoi(date.substr(0, 2));
            int day = stoi(date.substr(3, 2));

            int total = 0;

            for (int i = 0; i < month - 1; i++) {
                total += days[i];
            }

            return total + day;
        };

        int aliceStart = getDay(arriveAlice);
        int aliceEnd   = getDay(leaveAlice);

        int bobStart = getDay(arriveBob);
        int bobEnd   = getDay(leaveBob);

        int start = max(aliceStart, bobStart);
        int end   = min(aliceEnd, bobEnd);

        if (start > end)
            return 0;

        return end - start + 1;
    }
};