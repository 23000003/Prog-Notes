// Removes nodes that is greater than in the right side
// 5,2,13,3,8  returns 13, 8

struct ListNode* removeNodes(struct ListNode* head) {
    if (!head){
      return NULL;
    }
    
  head->next = removeNodes(head->next);

  if(head->next != NULL && head->val < head->next->val){
      head->val = head->next->val;
      struct ListNode *temp = head->next;
      head->next = head->next->next;
      free(temp);
  }
  return head;
}
