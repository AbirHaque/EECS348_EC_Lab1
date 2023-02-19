/*
Author: Abir Haque
Last modified: 18 February 2023
Purpose:
    My own implementation of a node-based linked list using knowledge gained from EECS 268 and EECS 330.
*/

class LinkedList{
    private:
        struct Node{
            int entry=0;
            Node* next=nullptr;
        };

        
        Node* head=nullptr;
        int length=0;

    public:
        int get_length(){
            return length;
        }

        void append(int x){
            Node* tmp=new Node();
            tmp->entry=x;
            tmp->next=head;
            head=tmp;
            length+=1;
        }

        void insert( int index, int x){
            Node* tmp=new Node();
            tmp->entry=x;
            if (index==0){
                tmp->next=head;
                head=tmp;
            }
            else if (index == length-1){
                Node* jumper=head;
                for(int i = 0; i < index-1; i++){
                    jumper=jumper->next;
                }
                Node* jumper_next_next=jumper->next->next;
                jumper->next=tmp;
                tmp->next=jumper_next_next;
            }
            else{
                append(x);
            }
            length+=1;
        }


        int get( int index){
            Node* jumper=head;
            for(int i = 0; i < index; i++){
                jumper=jumper->next;
            }
            return jumper->entry;
        }

        bool is_in( int x){
            Node* jumper=head;
            for(int i = 0; i < length; i++){
                if (jumper->entry==x){
                    return true;
                }
                jumper=jumper->next;
            }
            return false;
        }

        void remove( int index){
            if (index==0){
                head=head->next;
            }
            else if (index == length-1){
                Node* jumper=head;
                for(int i = 0; i < index-1; i++){
                    jumper=jumper->next;
                }
                jumper->next=nullptr;
            }
            else{
                Node* jumper=head;
                for(int i = 0; i < index-1; i++){
                    jumper=jumper->next;
                }
                jumper->next=jumper->next->next;
            }
            length-=1;

        }

        int index_of(int val){
            Node* jumper=head;
            for(int i = 0; i < length; i++){
                if (jumper->entry==val){
                    return i;
                }
                jumper=jumper->next;
            }
            return -1;
        }


        void empty_list(){
            head=nullptr;
            length=0;
        }

        ~LinkedList(){
            delete head;
        }
};