{
        int roll;
        char name[20];
        float mark;
        struct st *next;
};
void print(struct st *);
void add_end(struct st **);
void rev_data(struct st *);
int count(struct st *);
void rem_node(struct st **);
void delete_node(struct st **,int);
int main()
{
        struct st *hptr=0;
        char ch;
        do
        {
                add_end(&hptr);
                printf("do you want one more data\n");
                scanf(" %c",&ch);
        }while((ch=='y')||(ch=='Y'));

        printf("What process i do ----> 1)rev_data 2)delete_particular_recode 3)delete_all 4)count how many record have");
        char op;        
        scanf("%c",&op);

        print(hptr);
        rev_data(hptr);
        print(hptr);

        delete_node(&hptr,30);
        printf("After free the space\n");
        print(hptr);       
}
void add_end(struct st **ptr)
{
        struct st *temp=(struct st*)malloc(sizeof(struct st));
-- INSERT --                                                                                                        31,120         5%
