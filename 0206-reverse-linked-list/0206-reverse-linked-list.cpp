/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // using three pointers:
        ListNode* perv = NULL;
        ListNode* curr = head;
        ListNode* Next = head;
         
          while(curr){
            Next= curr->next;
            curr->next = perv;
            perv = curr;
            curr = Next;
          }
          return perv;
    }
};