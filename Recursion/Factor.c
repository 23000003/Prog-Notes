//Linklist

Node *removefactor(Node *head, int factor){   //returns and removes
    
   if(head == NULL){
        return NULL;
    }
    head->next = removefactor(head->next, factor);

    if(head->val % factor == 0 && head != NULL){
      head->val = head->next->val;
      struct ListNode *temp = head->next;
      head->next = head->next->next;
      free(temp);
    }
    return head;
}
