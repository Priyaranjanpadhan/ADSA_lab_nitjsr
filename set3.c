#include<stdio.h>
#include<stdlib.h>

// 1. b>Implement a circular queue using a linked list.
struct node{
  int data;
  struct node* next;  
};

struct node* head = NULL;
struct node* rear = NULL;  // keep rear pointer for O(1) operations

struct node* create_node(int data){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode -> data = data;
    newNode -> next = NULL;
    return newNode;
}

void enqueue_ll(int data){
    struct node* newNode = create_node(data);

    if(head == NULL){
      head = rear = newNode;
      newNode -> next = head;
      return;
    }

    rear -> next = newNode;
    newNode -> next = head;
    rear = newNode;
}

void dequeue_ll(){
  if(head == NULL){
    printf("Queue is empty!\n");
    return;
  }

  if(head == rear){ // only one element
    printf("Deleted element = %d\n", head->data);
    free(head);
    head = rear = NULL;
    return;
  }

  struct node* temp = head;
  printf("Deleted element = %d\n", temp->data);
  head = head -> next;
  rear -> next = head;
  free(temp);
}

void display_ll(){
  if(head == NULL){
    printf("Queue is empty\n");
    return;
  }
  struct node* temp = head;
  do{
    printf("%d ", temp -> data);
    temp = temp -> next;
  }while(temp != head);
  printf("\n");
}

// 1. a>Implement a circular queue using an array
void enqueue_arr(int arr[], int data,int *front, int *rear,int n){
  if((*rear + 1) % n == *front){
    printf("The queue is full\n");
    return;
  }

  if(*front == -1 && *rear == -1){
    *front = *rear = 0;
    arr[*rear] = data;
    return;
  }

  *rear = (*rear + 1) % n;
  arr[*rear] = data;
}

void dequeue_arr(int arr[], int *front, int *rear, int n){
  if(*front == -1){
    printf("The queue is underflow\n");
    return;
  }

  printf("Deleted element = %d\n", arr[*front]);

  if(*front == *rear){ // only one element
    *front = *rear = -1;
  }
  else{
    *front = (*front + 1) % n;
  }
}

void display_arr(int arr[], int front, int rear, int n){
  if(front == -1){
    printf("Queue is empty\n");
    return;
  }
  int i = front;
  while(1){
    printf("%d ", arr[i]);
    if(i == rear) break;
    i = (i + 1) % n;
  }
  printf("\n");
}


//2.Implement a queue using two stacks
#define SIZE 5

int stacks1[SIZE];
int top1 = -1;
int stacks2[SIZE];
int top2 = -1;

void push(int stack[], int *top, int data){
  if(*top == SIZE - 1){
    printf("The queue is full");
    return;
  }

  stack[++(*top)] = data;
}

int pop(int stack[], int *top){
  if(*top == -1){
    printf("The queue is empty");
    return -1;
  }

  return stack[(*top)--];
}

void enqeue_stack(int data, int stacks1[], int stacks2[], int *top1, int *top2){
  if(*top1 == SIZE - 1){
    printf("The queue is full\n");
    return;
  }

  if(*top1 == -1){
    push(stacks1, top1, data);
    return;
  }

  else{
    while(*top1 != -1){
      int a = pop(stacks1, top1);
      push(stacks2, top2, a);
    }
    push(stacks1, top1, data);

    while(*top2 != -1){
      int a = pop(stacks2, top2);
      push(stacks1, top1, a);
    }
    return;
  }
}

int dequeue_stack(int stacks1[], int *top1){
  if(*top1 == -1){
    printf("The queue is empty\n");
    return -1;
  }
  int val = pop(stacks1, top1);
  printf("Dequeued element: %d\n", val);
  return val;
}

void display_queue_stack(int stacks1[], int top1){//here we take the value and not pointer because we dont want to change the top value
    if(top1 == -1){
        printf("The queue is empty\n");
        return;
    }
    for(int i = top1; i >= 0; i--){
        printf("%d ", stacks1[i]);
    }
    printf("\n");
}

//Implement a stack using 2queue

int queue1[SIZE];
int queue2[SIZE];
int front1 = -1, rear1 = -1;
int front2 = -1, rear2 = -1;

void enqueue(int queue[], int data, int *front, int *rear){
  if(*rear == SIZE - 1){
    printf("The queue is overflow\n");
    return;
  }

  if(*front == -1 && *rear == -1){
    *front = 0;
    *rear = 0;
    queue[*rear] = data;
  }
  else{
    queue[++(*rear)] = data;
  }
  
}

int dequeue(int queue[], int *front, int *rear){
  if(*front == -1 || *front > *rear){
    printf("The queue is empty\n");
    return -1;
  }
  int val = queue[*front];
  (*front)++;                 
  if(*front > *rear){         // reset when empty
    *front = *rear = -1;
  }
  return val;
}

void push_queue(int data){
  while(front1 != -1){
    int a = dequeue(queue1, &front1, &rear1);
    enqueue(queue2, a, &front2, &rear2);
  }

  enqueue(queue1, data, &front1, &rear1);

  while(front2 != -1){
    int a = dequeue(queue2, &front2, &rear2);
     enqueue(queue1, a, &front1, &rear1);
  }
}

int pop_queue(){
  if(front1 == -1){
    printf("The Stack is underflow.\n");
    return -1;
  }

  int val = dequeue(queue1, &front1, &rear1);
  printf("The deleted value is : %d", val);
  return val;
}

void display_Stack_queue(){
  if(front1 == -1){
    printf("The Stack is empty.\n");
    return;
  }
  printf("The given Stack is : ");
  for(int i = front1; i <= rear1; i++){
    printf("%d ", queue1[i]);
  }
  printf("\n");
}

int main(){
  // Linked list circular queue
  enqueue_ll(10);
  enqueue_ll(20);
  enqueue_ll(30);
  display_ll();

  dequeue_ll();
  display_ll();

  // Array circular queue
  int arr[SIZE];
  int front = -1, rear = -1;

  enqueue_arr(arr,10,&front,&rear,SIZE);
  enqueue_arr(arr,20,&front,&rear,SIZE);
  enqueue_arr(arr,30,&front,&rear,SIZE);
  enqueue_arr(arr,40,&front,&rear,SIZE);
  enqueue_arr(arr,50,&front,&rear,SIZE);

  display_arr(arr,front,rear,SIZE);

  dequeue_arr(arr,&front,&rear,SIZE);
  dequeue_arr(arr,&front,&rear,SIZE);

  display_arr(arr,front,rear,SIZE);

  //queue using 2stacks
  enqeue_stack(10, stacks1, stacks2, &top1, &top2);
  enqeue_stack(20, stacks1, stacks2, &top1, &top2);
  enqeue_stack(30, stacks1, stacks2, &top1, &top2);
  enqeue_stack(40, stacks1, stacks2, &top1, &top2);

  printf("Queue after enqueues: ");
  display_queue_stack(stacks1, top1);

  dequeue_stack(stacks1, &top1);
  dequeue_stack(stacks1, &top1);

  printf("Queue after two dequeues: ");
   display_queue_stack(stacks1, top1);

  enqeue_stack(50, stacks1, stacks2, &top1, &top2);
  enqeue_stack(60, stacks1, stacks2, &top1, &top2);

  printf("Final queue: ");
  display_queue_stack(stacks1, top1);

   //Stack using 2 queues
  push_queue(10);
  push_queue(20);
  push_queue(30);
  display_Stack_queue();

  pop_queue();
  display_Stack_queue();

  push_queue(40);
  display_Stack_queue();

  return 0;
}
