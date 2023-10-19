#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int data;
	struct _node* next;
}NODE; 

void print_list(NODE*head){
	NODE* p =head;
	while(p->next!=NULL){
		p= p->next;
		printf("%d",p->data);
	}
	printf("\n");
} 


void insert_node_first(NODE* head,int data){
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	newnode -> data = data;
	
	newnode->next = head->next;
	head->next = newnode;
}
void insert_node_last(NODE* head,int data){
	NODE* newnode = (NODE*)malloc(sizeof(NODE));
	newnode -> data = data;
	
	NODE* p =head;
	while(p->next!=NULL){
		p= p->next;
	}
	p-> next = newnode;
	newnode->next = NULL;
}

void delete_node_first(NODE* head){
	NODE* p = head->next->next;
	free(head-> next);
	head-> next = p;
}

void delete_node_last(NODE* head){
	NODE* p_prev;
	NODE* p =head;
	while(p->next!=NULL){
		p_prev = p;
		p= p->next;
	}
	free(p);
	p_prev->next = NULL;
}
int main(){
	NODE* head = (NODE*)malloc(sizeof(NODE));
	//(NODE*)malloc(sizeof(NODE)) 이게 주소값임 
	(*head).next = NULL;
	
	NODE* n1 = (NODE*)malloc(sizeof(NODE));
	n1->data = 1;
	n1->next = NULL; //초기화 
	head->next = n1;
	
	NODE* n2 = (NODE*)malloc(sizeof(NODE));
	n2->data = 2;
	n2->next = NULL; 	//초기화 
	n1 -> next = n2;  //head->next->next = n2;
	
	NODE* n3 = (NODE*)malloc(sizeof(NODE));
	n3->data = 3;
	n3->next = NULL; 	//초기화 
	n2->next = n3; 		// head->next->next->next = n2;
	
	insert_node_first(head,6);
	insert_node_last(head,4);
	delete_node_first(head);
	delete_node_last(head);
		print_list(head);
}
