#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#define SIZE 20

int stack[SIZE];
int top = -1;
int dummy = 1001;
/*----------------------------------------------------------------------------------------------------------------------*/
int isempty()
{
    if(top == -1)
        return 1;
    else return 0;
}
/*----------------------------------------------------------------------------------------------------------------------*/
int isfull()
{
    if(top == SIZE - 1)
        return 1;
    else return 0;
}
/*----------------------------------------------------------------------------------------------------------------------*/
void push(int id)
{
    top++;
    stack[top] = id;
}
/*----------------------------------------------------------------------------------------------------------------------*/
int pop()
{
    return stack[top--];
}
/*----------------------------------------------------------------------------------------------------------------------*/
struct node
{
    char contact_name[20];
    char contact_number[10];
    int contact_id;
    struct node*dlink;
    struct node*ulink;
}*head;
/*----------------------------------------------------------------------------------------------------------------------*/
void create()
{
    struct node *nn,*temp;
    nn = (struct node*)malloc(sizeof(struct node));
    nn->dlink = NULL;
    nn->ulink = NULL;
    fflush(stdin);
    printf("ENTER THE NAME OF THE CONTACT : ");
    scanf("%s",nn->contact_name);
    fflush(stdin);
    printf("ENTER THE CORRESPONDING CONTACT NUMBER : ");
    scanf("%s",nn->contact_number);
   
    nn->contact_id = dummy++;
    if(head == NULL)
    {
        head = nn;
    }
    // else{
    //     temp->dlink = nn;
    //     nn->ulink =temp;
    //     temp = temp->dlink;
    // }
    else{
        struct node*temp = head;
        while(temp->dlink)
        {
            temp = temp ->dlink;
        }
        temp->dlink = nn;
        nn->ulink = temp;
    }
    FILE * fp;
    fp = fopen("contact_backend.txt","a");
    fprintf(fp,"%s\n%s\n",nn->contact_name,nn->contact_number);
    fprintf(fp,"\n");
    fclose(fp);
}
/*-----------------------------------------------------------------------------------------------------------------------*/
void print_contact_id()
{
    struct node*temp = head;
    while(temp!=NULL)
    {
        printf("%d\n",temp->contact_id);
        temp = temp->dlink;
    }
}
/*-----------------------------------------------------------------------------------------------------------------------*/
void backup_file()
{
    FILE *fp;
    char ch;
    fp = fopen("contact_backend.txt","r");
do{
ch=fgetc(fp);
printf("%c",ch);
}
while(ch!=EOF);
fclose(fp);
    printf("END OF LIST OF CONTACTS");
}
/*------------------------------------------------------------------------------------------------------------------*/
void call_history_display()
{
    int i,x;
    struct node*temp;
    for(i=top;i>=0;i--)
    {
        temp = head;
        x = stack[i];
        while(temp!=NULL)
        {
            if(temp->contact_id==x){
                printf("called : %s\n",temp->contact_name);
                temp = head;
                break;
            }
            else{
                temp = temp->dlink;
            }       
        }
    }
}
/*---------------------------------------------------------------------------------------------------------------------*/
void call_contact()
{
    char str[20];
    printf("enter the contact name to call : ");
    scanf("%s",str);
    int flag  =0;
    //int n = strlen(str);
    struct node*temp = head;
    while(temp!=NULL)
    {
        if(strcmp((temp->contact_name),str)==0)
        {
            flag = 1;
            int num = temp->contact_id;
            //printf("%d\n",num);
            push(num);
            break;
        }
        else{
            temp = temp->dlink;
        }
    }
    if(flag == 0)
            printf("NO MATCHING CONTACTS FOUND\n");
}
/*----------------------------------------------------------------------------------------------------------------------*/
void delete_contact()
{
    struct node* temp= head;
    char name[20];
    printf("enter the contact you want to delete : ");
    scanf("%s",name);
    int count  =0;
    int position_to_delete;
    while(temp!=NULL)
    {
        if(strcmp(temp->contact_name,name))
        {
            position_to_delete = count;
        }
        count++;
    }
}
/*----------------------------------------------------------------------------------------------------------------------*/
void printdata()
{
    struct node*temp;
    temp = head;
    while(temp!=NULL)
    {
        printf("\n%s\n",temp->contact_name);
        printf("%s\n",temp->contact_number);
        temp = temp->dlink;
    }
}
/*----------------------------------------------------------------------------------------------------------------------*/
void search_contact()
{
    char key[20];
    printf("ENTER THE KEY TO SEARCH FOR CONTACTS : ");
    scanf("%s",key);
    struct node*temp = head;
    int i,flag = 0;
    printf("CONTACT MATCHING WITH KEY ARE : \n");
    while(temp!=NULL)
    {
        for(i=0;i<strlen(key);i++)
        {
            if(key[i] == temp->contact_name[i])
                flag = 1;
            else
            {
                 flag = 0;
                 break;
            }  
        }
        if(flag)
        {
            printf("%s\n%s\n",temp->contact_name,temp->contact_number);
        }
        //else continue;
        temp = temp->dlink;
    }
    if(flag = 0)
        printf("\nNO CONTACTS EXISTS WITH THE ENTERED SEARCH KEY!!");
}
/*---------------------------------------------------------------------------------------------------------------------*/
int main()
{
    int opt;
    printf("PLESAE SELECT FROM THE BELOW MENU DRIVE SELECTION\n");
    printf("1. CREATE NEW CONTACT\n2. SEACRH FOR A CONTACT\n3. VIEW ALL THE LIST OF CONTACTS\n4. VIEW THE CALL HISTORY\n5. DELETE A CONTACT \n6. CALL A NUMBER/CONTACT\n");
    printf("7. DELETE LATEST CALL FROM CALL HISTORY\n8.Backup file\n");
    printf("9. EXITING CONTACTS\n");
   
    do
    {
        printf("OPTION : ");
        scanf("%d",&opt);
        switch(opt){
            case 1: create();
                    break;
            case 2: search_contact();
                    break;
            case 3: printdata();
                    break;
            case 4: call_history_display();
                    break;
            case 5: delete_contact();
                    break;
            case 6: call_contact();
                    break;
            case 7: pop();
                    printf("LATEST CALL FROM HISTORY DELETED\n");
                    break;
            case 8:backup_file();
                    break;
            case 9:print_contact_id();
                    break;
           
        }    
        if(opt==10){

            printf("YOU HAVE EXITED THE PROGRAM..!");
            break;
        }
        if(opt>9&&opt<0){

            printf("WRONG OPTION");
            break;
        }
    }while(1);
    return 0;
}
/*-------------------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------END OF CODE-------------------------------------*/
