

typedef struct node
{//Use single link list to build the stack to record the data
  int col;  
  int row;  
  struct node*next;
}list;


list *createnode();
list *push(int col,int row,list*first);
list *pop(int *col,int *row,list *first);

list *record(char **path,int col,int row,list* first);
