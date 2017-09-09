

typedef struct node
{//Use single link list to build the stack to record the data
  int j;  //record j
  int i;  //record i
  struct node*next;
}list;


list *createnode();
list *push(int j,int i,list*first);
list *pop(int *j,int *i,list *first);

list *record(int **path,int j,int i,list* first);
