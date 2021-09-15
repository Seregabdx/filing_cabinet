#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define OS_TYPE linux
#ifdef OS_TYPE
#define CLS system("clear")
#else
#define CLS system("cls")
#endif // OS_TYPE

struct LHead {
    int cnt;
    struct LNode *first;
    struct LNode *last;
};
typedef struct LHead Head;

struct LHead1 {
    int cnt;
    struct films *first;
    struct films *last;
};
typedef struct LHead1 Head1;


struct LNode {
    char* name;
    struct LNode *next;
};
typedef struct LNode Node;

struct films{
        char *name; // название фильма
        Node *age; // возрастной рейтинг
        Node *country; //страна
        int budget; // бюджет
        int gross;   // сборы
        float rating_kino; // оценки на кинопоиске
        float rating_IM;    // оценки на IMDb
        float rat[3]; // оценки критиков
        struct films *next;
};
typedef struct films film;


void main_menu(Head1 *MyHead, Head* HeaAge, Head* HeaCou);
Head *MakeHead();
Head1 *MakeHead1();
void new_gets(char *s, int lim);
char **simple_split(char *str, int length, char sep);
void struct_fill(char **str, Head1 *MyHead, Head* HeaAge, Head* HeaCou);
Head *InsertListAge(Head* HeaAge, char *str, film *MyNode);
Head *InsertListCo(Head* HeaCou, char *str, film *MyNode);
void InsertAfter_2(Head *Hea, Node *Nod, Node *last);
void AddFirst(Head1 *MyHead, film *NewNode);
void InsertAfter(Head1 *MyHead, film *NewNode, film *CurrentNode);
void input_data(Head1 *MyHead, Head *HeaAge, Head *HeaCou);
void output(Head1 *MyHead);
void ClearStringArray(char **str, int n);
void struct_out(film *str0);
Node *CreateAge(char *NewWord, int slen);
void Edit(Head1 *MyHead, Head *HeaAge, Head *HeaCou);
void Exclude(Head1 *MyHead, Head *HeaAge, Head *HeaCou);
void DelAfter(Head1* MyHead, int n);
void DelTop(Head1* MyHead);
void DelLast(Head1* MyHead);
void make_change(Head1 *MyHead, Head *HeaAge, Head *HeaCou);
void Add(Head1 *MyHead, Head *HeaAge, Head *HeaCou);
void search(Head1 *MyHead, Head *HeaAge, Head *HeaCou);
void sort(Head1 *MyHead, Head *HeaAge, Head *HeaCou);
film *sort_country(film *ph);
film *sort_name(film *ph);
film *sort_age(film *ph);
film *sort_buget(film *ph);
film *sort_gross(film *ph);
film *sort_ratingI(film *ph);
film *sort_ratingK(film *ph);
void print_header();
void Delete(Head1 *MyHead, film *prev, film *New);
void mem_clear(Head1 *MyHead, Head *HeaAge, Head *HeaCou);
void output_file(Head1 *MyHead);


int main()
{
    Head *HeaAge=NULL, *HeaCou=NULL;
    Head1 *Hea=NULL;
    Hea=MakeHead1();
    HeaAge=MakeHead();
    HeaCou=MakeHead();
    main_menu(Hea, HeaAge, HeaCou);
    return 0;
}

void main_menu(Head1* MyHead, Head* HeaAge, Head* HeaCou)
{
    char sw;

    printf("Select an action\n");
    printf("1. Data entry in the electronic filing cabinet\n");
    printf("2. Making changes (deletion, adjustment, addition)\n");
    printf("3. Search for data on various grounds\n");
    printf("4. Sorting by various signs\n");
    printf("5. Output data\n");
    printf("6. EXIT\n");
    scanf("%c", &sw);
    getchar();
    switch(sw)
    {
    case '1':
        system("cls");
        input_data(MyHead, HeaAge, HeaCou);
        system("cls");
        main_menu(MyHead,HeaAge, HeaCou);
        break;
    case '2':
        system("cls");
        make_change(MyHead,HeaAge, HeaCou);
        break;
    case '3':
        system("cls");
        search(MyHead, HeaAge, HeaCou);
        break;
    case '4':
        system("cls");
        sort(MyHead, HeaAge, HeaCou);
        break;
    case '5':
        system("cls");
        output(MyHead);
        output_file(MyHead);
        main_menu(MyHead,HeaAge, HeaCou);
        break;
    case '6':
        system("cls");
        printf("The program has completed\n");
        mem_clear(MyHead,HeaAge, HeaCou);
        break;
    default:
        printf("Wrong input\n");
    }
}

void mem_clear(Head1 *MyHead, Head *HeaAge, Head *HeaCou)
{
    film *Nod, *prev;
    Nod=MyHead->first;
    prev=MyHead->first;
    while(Nod!=NULL)
    {
        if(Nod->age!=NULL)
        {
            free(Nod->age);
            Nod->age=NULL;
        }
        if(Nod->country!=NULL)
        {
            free(Nod->country);
            Nod->country=NULL;
        }
        free(Nod->name);
        prev=Nod;
        Nod=Nod->next;
        free(prev);
    }
}

Head *MakeHead()
{
    Head *ph=NULL;

    ph=(Head*)malloc(sizeof(Head));
    if(ph)
    {
        ph->cnt=0;
        ph->first=NULL;
        ph->last=NULL;
    }
    return ph;
}

Head1 *MakeHead1()
{
    Head1 *ph=NULL;

    ph=(Head1*)malloc(sizeof(Head1));
    if(ph)
    {
        ph->cnt=0;
        ph->first=NULL;
        ph->last=NULL;
    }
    return ph;
}

void print_header()
{
    printf("|%15s|%5s | %6s  | %6s | %6s | %2s |%2s| %2s | %2s | %2s |\n","film name","age","country","budget","gross","KP","IMDb","1","2","3");
    printf("+---------------+------+----------+--------+--------+----+----+----+----+----+\n");
}


void output(Head1 *MyHead)
{
    film *MyNode=NULL;

    MyNode = MyHead->first;
    print_header();
    while(MyNode!=NULL)
    {
        struct_out(MyNode);
        MyNode=MyNode->next;
    }
    output_file(MyHead);
}

void output_file(Head1 *MyHead)
{
    FILE *file=NULL;
    film *str0, *Nod;

    file = fopen("output.txt", "w");
    if(file!=NULL)
    {
        fprintf(file, "|%15s|%5s | %6s  | %6s | %6s | %2s |%2s| %2s | %2s | %2s |\n","film name","age","country","budget","gross","KP","IMDb","1","2","3");
        fprintf(file, "+---------------+------+----------+--------+--------+----+----+----+----+----+\n");
        Nod=MyHead->first;
        while(Nod!=NULL)
        {
            str0=Nod;
            fprintf(file, "|%15s| %5s| %9s| %7.0i| %7.0i| %3.1f| %3.1f| %3.1f| %3.1f| %3.1f|\n",
                            str0->name,str0->age->name,str0->country->name,str0->budget,str0->gross,str0->rating_kino,str0->rating_IM,str0->rat[0],str0->rat[1],str0->rat[2]);
            Nod=Nod->next;
        }
    }
    fclose(file);
}

void struct_out(film *str0)
{
    printf("|%15s| %5s| %9s| %7.0i| %7.0i| %3.1f| %3.1f| %3.1f| %3.1f| %3.1f|\n",
        str0->name,str0->age->name,str0->country->name,str0->budget,str0->gross,str0->rating_kino,str0->rating_IM,str0->rat[0],str0->rat[1],str0->rat[2]);
}

void new_gets(char *s, int lim)
{
    char c;
    int i;

    for(i=0;((c=getchar())!='\n')&&(i<lim-1);i++,s++)
        *s=c;
    *s='\0';
}

char **simple_split(char *str, int length, char sep)
{
    char **str_array=NULL;
    int i,j,k,m;
    int key,count;
    for(j=0,m=0;j<length;j++)
    {
        if(str[j]==sep) m++;
    }
    if(m!=0)
    {
    key=0;
    str_array=(char**)malloc((m+1)*sizeof(char*));
    if(str_array!=NULL)
    {
        for(i=0,count=0;i<=m;i++,count++)
        {
            str_array[i]=(char*)malloc(length*sizeof(char));
            if(str_array[i]!=NULL) key=1;
            else
            {
                key=0;
                i=m;
            }
        }
        if(key)
        {
            k=0;
            m=0;
            for(j=0;j<length;j++)
            {
                if(str[j]!=sep) str_array[m][j-k]=str[j];
                else
                {
                    str_array[m][j-k]='\0';
                    k=j+1;
                    m++;
                }
            }
        }
        else
        {
            ClearStringArray(str_array,count);
        }
     }
    }
    else str_array=NULL;
     return str_array;
}

void ClearStringArray(char **str, int n)
{
    int i;

    for(i=0;i<n;i++)
    {
        free(str[i]);
        str[i]=NULL;
    }
    free(str);
    str=NULL;

}

void struct_fill(char **str, Head1 *MyHead, Head* HeaAge, Head* HeaCou)
{
    film *MyNode=NULL, *a=NULL;

    MyNode = (film*)malloc(sizeof(film));
    if(MyNode!=NULL)
    {
        MyNode->name=str[0];
        InsertListAge(HeaAge, str[1], MyNode);
        InsertListCo(HeaCou, str[2], MyNode);
        MyNode->budget=atoi(str[3]);
        MyNode->gross=atoi(str[4]);
        MyNode->rating_kino=atof(str[5]);
        MyNode->rating_IM=atof(str[6]);
        MyNode->rat[0]=atof(str[7]);
        MyNode->rat[1]=atof(str[8]);
        MyNode->rat[2]=atof(str[9]);
        MyNode->next=NULL;
        if(MyHead->first==NULL)
        {
            AddFirst(MyHead, MyNode);
        }
        else
        {
            a=MyHead->last;
            InsertAfter(MyHead, MyNode, a);
        }
    }
}

Node *CreateAge(char *NewWord, int slen)
{
   Node *NewNode=NULL;
   char *someword=NULL;

    NewNode = (Node*)malloc(sizeof(Node));
    someword=(char*)malloc((slen+1)*sizeof(char));
    if(NewNode&&someword)
    {
        someword=NewWord;
        NewNode->name=someword;
        NewNode->next = NULL;
    }
    return NewNode;
}

Head *InsertListAge(Head* HeaAge, char *str, film *MyNode)
{
    Node *Nod=NULL, *b=NULL;
    int flag;
    flag=0;
    Nod=CreateAge(str, strlen(str)+1);
    if(HeaAge->first==NULL)
    {
        HeaAge->first=Nod;
        HeaAge->last=Nod;
        HeaAge->cnt++;
        MyNode->age=Nod;
    }
    else
    {
        b=HeaAge->first;
        while(b!=NULL && flag!=1)
        {
            if(strcmp(b->name,str)==0)
            {
                MyNode->age=b;
                flag=1;
            }
            b=b->next;
        }
        if(flag!=1)
        {
            b=HeaAge->last;
            InsertAfter_2(HeaAge, Nod, b);
            MyNode->age=Nod;
        }
    }
    return HeaAge;
}
Head *InsertListCo(Head* HeaCou, char *str, film *MyNode)
{
    Node *Nod=NULL, *b=NULL;
    int flag;
    flag=0;
    Nod=CreateAge(str, strlen(str)+1);
    if(HeaCou->first==NULL)
    {
        HeaCou->first=Nod;
        HeaCou->last=Nod;
        HeaCou->cnt++;
        MyNode->country=Nod;
    }
    else
    {
        b=HeaCou->first;
        while(b!=NULL && flag!=1)
        {
            if(strcmp(b->name,str)==0)
            {
                MyNode->country=b;
                flag=1;
            }
            b=b->next;
        }
        if(flag!=1)
        {
            b=HeaCou->last;
            InsertAfter_2(HeaCou, Nod, b);
            MyNode->country=Nod;
        }
    }
    return HeaCou;
}

void InsertAfter_2(Head *MyHead, Node *NewNode, Node *CurrentNode)
{
    int n;
    if(MyHead&&NewNode&&CurrentNode)
    {
        n=MyHead->cnt+1;
        if(CurrentNode->next==NULL)
        {
            CurrentNode->next=NewNode;
            MyHead->last=NewNode;
        }
        else
        {
            NewNode->next = CurrentNode->next;
            CurrentNode->next=NewNode;
        }
        MyHead->cnt=n;
        CurrentNode->next->next=NULL;
    }
}

void AddFirst(Head1 *MyHead, film *NewNode)
{
    if(MyHead&&NewNode)
    {
        MyHead->first = NewNode;
        MyHead->last = NewNode;
        MyHead->cnt++;
    }
}

void InsertAfter(Head1 *MyHead, film *NewNode, film *CurrentNode)
{
    int n;
    if(MyHead&&NewNode&&CurrentNode)
    {
        n=MyHead->cnt+1;
        if(CurrentNode->next==NULL)
        {
            CurrentNode->next=NewNode;
            MyHead->last=NewNode;
        }
        else
        {
            NewNode->next = CurrentNode->next;
            CurrentNode->next=NewNode;
        }
        MyHead->cnt=n;
        CurrentNode->next->next=NULL;
    }
}

void input_data(Head1 *MyHead, Head *HeaAge, Head *HeaCou)
{
    enum {maxlen=128};
    int it;
    FILE *df;
    char s1[maxlen];
    int n, i, count=0, slen;
    char **s2=NULL;
    char **st1;
    char sep=';';
    film *Nod;

    printf("How many items will be added?\n");
    scanf("%i", &it);
    getchar();
    df=fopen("input.txt","r");
    if(df!=NULL)
    {
        n=0;
        while((fgets(s1,maxlen,df))!=NULL) n++;
        rewind(df);
        puts("Initial array:");
        for(i=0,count=0;i<n;i++,count++)
        {
            fgets(s1,maxlen,df);
            slen=strlen(s1);
            s1[slen-1]='\0';
            slen=strlen(s1);

            s2=simple_split(s1,slen,sep);
            if(s2!=NULL)
            {
                struct_fill(s2, MyHead, HeaAge, HeaCou);
            }
            else puts("Error at data reading!");
        }
        for(i=0;i<it;i++)
        {
            st1=(char**)malloc(3*sizeof(char*));
            Nod = (film*)malloc(sizeof(film));
            if(st1!=NULL && Nod!=NULL)
            {
                st1[0]=(char*)malloc(maxlen*sizeof(char));
                st1[1]=(char*)malloc(maxlen*sizeof(char));
                st1[2]=(char*)malloc(maxlen*sizeof(char));
                if(st1[0]!=NULL && st1[1]!=NULL && st1[2]!=NULL)
                {
                    printf("\nInput name: ");
                    new_gets(st1[0], 50);
                    Nod->name=st1[0];
                    printf("\nInput age rating: ");
                    new_gets(st1[1], 50);
                    printf("\nInput country: ");
                    new_gets(st1[2], 50);
                    HeaAge=InsertListAge(HeaAge, st1[1], Nod);
                    HeaCou=InsertListCo(HeaCou, st1[2], Nod);
                    printf("\nInput budget: ");
                    scanf("%i", &Nod->budget);
                    getchar();
                    printf("\nInput gross: ");
                    scanf("%i", &Nod->gross);
                    getchar();
                    printf("\nInput rating kinopoisk: ");
                    scanf("%f", &Nod->rating_kino);
                    getchar();
                    printf("\nInput rating IMdB: ");
                    scanf("%f", &Nod->rating_IM);
                    getchar();
                    printf("\nInput rating: ");
                    scanf("%f", &Nod->rat[0]);
                    getchar();
                    printf("\nInput rating: ");
                    scanf("%f", &Nod->rat[1]);
                    getchar();
                    printf("\nInput rating: ");
                    scanf("%f", &Nod->rat[2]);
                    getchar();
                    InsertAfter(MyHead, Nod, MyHead->last);
                }
            } else printf("Memory error!\n");
        }
    }
    fclose(df);
    output(MyHead);
    getchar();
}

void make_change(Head1 *MyHead, Head *HeaAge, Head *HeaCou)
{
    char ch='0';

    printf("What change do you want to make?\n");
    printf("1. Exclude item\n");
    printf("2. Edit item\n");
    printf("3. Add item\n");
    printf("4. Back\n");
    scanf("%c", &ch);
    getchar();

    switch(ch)
    {
    case '1':
        Exclude(MyHead, HeaAge, HeaCou);
        system("cls");
        make_change(MyHead, HeaAge, HeaCou);
        break;
    case '2':
        Edit(MyHead, HeaAge, HeaCou);
        system("cls");
        make_change(MyHead, HeaAge, HeaCou);
        break;
    case '3':
        Add(MyHead, HeaAge, HeaCou);
        system("cls");
        make_change(MyHead, HeaAge, HeaCou);
        break;
    case '4':
        system("cls");
        main_menu(MyHead, HeaAge, HeaCou);
        getchar();
        break;
    default:
        printf("Incorrect value!\n");
        make_change(MyHead, HeaAge, HeaCou);
        system("cls");
        break;
    }
}

void Exclude(Head1 *MyHead, Head *HeaAge, Head *HeaCou)
{
    int k;
    output(MyHead);
    printf("Enter the number of item you want to exclude\n");
    scanf("%i", &k);
    getchar();
    DelAfter(MyHead, k);
    output(MyHead);
    system("cls");
    getchar();
}

void DelAfter(Head1* MyHead, int n)
{
    film *pser1;
    film *pser;
    int i;
    pser=MyHead->first;
    if(n==MyHead->cnt)
        DelLast(MyHead);
    else
        if(n>1 && n<MyHead->cnt)
        {
            for(i=1;i<n-1;i++)
                pser=pser->next;
            pser1=pser->next->next;
            pser->next->next=NULL;
            free(pser->next);
            pser->next=pser1;
            if(pser->next==NULL)
                MyHead->last=pser;
        }
        else
        {
            if(n==1) DelTop(MyHead);
            else printf("Incorrect value!\n");
        }
}

void DelTop(Head1* MyHead)
{
    film *pser;

    pser=MyHead->first->next;
    free(MyHead->first);
    MyHead->first=pser;
    if(MyHead->first == NULL)
        MyHead->last=NULL;
}

void DelLast(Head1* MyHead)
{
    film *pser;
    pser=MyHead->first;
    if(pser->next!=NULL)
        {
            while(pser->next->next)
                    pser=pser->next;
            free(pser->next);
            pser->next=NULL;
            MyHead->last=pser;
        }
    else
        {
            free(pser);
            pser=NULL;
            MyHead->first=NULL;
            MyHead->last=NULL;
        }
}

void Edit(Head1 *MyHead, Head *HeaAge, Head *HeaCou)
{
    film *Node;
    int i, k=0, value;
    float value_fl;
    int num;
    char *st;

    st=(char*)malloc(80*sizeof(char));
    if(st!=NULL)
    {
        output(MyHead);
        printf("Enter the number of item you want to edit\n");
        scanf("%i", &k);
        getchar();
        Node=MyHead->first;
        for(i=1;i<k;i++)
        {
            Node=Node->next;
        }
        struct_out(Node);
        printf("Select field\n");
        printf("1-NAME\n");
        printf("2-AGE RATING\n");
        printf("3-COUNTRY\n");
        printf("4-BUDGET\n");
        printf("5-GROSS\n");
        printf("6-RATING KINOPOISK\n");
        printf("7-RATING IMdB\n");
        printf("8-OTHER RATINGS 1\n");
        printf("9-OTHER RATINGS 2\n");
        printf("10-OTHER RATINGS 3\n");
        scanf("%i", &num);
        getchar();
        switch(num)
        {
        case 1:
            new_gets(st, 200);
            Node->name=st;
            break;
        case 2:
            new_gets(st, 200);
            InsertListAge(HeaAge, st, Node);
            break;
        case 3:
            new_gets(st, 200);
            InsertListCo(HeaCou, st, Node);
            break;
        case 4:
            scanf("%i", &value);
            getchar();
            Node->budget=value;
            break;
        case 5:
            scanf("%i", &value);
            getchar();
            Node->gross=value;
            break;
        case 6:
            scanf("%f", &value_fl);
            getchar();
            Node->rating_kino=value_fl;
            break;
        case 7:
            scanf("%f", &value_fl);
            getchar();
            Node->rating_IM=value_fl;
            break;
        case 8:
            scanf("%f", &value_fl);
            getchar();
            Node->rat[0]=value_fl;
            break;
        case 9:
            scanf("%f", &value_fl);
            getchar();
            Node->rat[1]=value_fl;
            break;
        case 10:
            scanf("%f", &value_fl);
            getchar();
            Node->rat[2]=value_fl;
            break;
        default:
            printf("Incorrect value!\n");
            break;
        }
        struct_out(Node);
    }
}

void Add(Head1 *MyHead, Head *HeaAge, Head *HeaCou)
{
    char **st1;
    film *Nod;

    st1=(char**)malloc(3*sizeof(char*));
    Nod = (film*)malloc(sizeof(film));
    if(st1!=NULL && Nod!=NULL)
    {
        st1[0]=(char*)malloc(80*sizeof(char));
        st1[1]=(char*)malloc(80*sizeof(char));
        st1[2]=(char*)malloc(80*sizeof(char));
        if(st1[0]!=NULL && st1[1]!=NULL && st1[2]!=NULL)
        {
            printf("\nInput name: ");
            new_gets(st1[0], 50);
            Nod->name=st1[0];
            printf("\nInput age rating: ");
            new_gets(st1[1], 50);
            printf("\nInput country: ");
            new_gets(st1[2], 50);
            InsertListAge(HeaAge, st1[1], Nod);
            InsertListCo(HeaCou, st1[2], Nod);
            printf("\nInput budget: ");
            scanf("%i", &Nod->budget);
            getchar();
            printf("\nInput gross: ");
            scanf("%i", &Nod->gross);
            getchar();
            printf("\nInput rating kinopoisk: ");
            scanf("%f", &Nod->rating_kino);
            getchar();
            printf("\nInput rating IMdB: ");
            scanf("%f", &Nod->rating_IM);
            getchar();
            printf("\nInput rating: ");
            scanf("%f", &Nod->rat[0]);
            getchar();
            printf("\nInput rating: ");
            scanf("%f", &Nod->rat[1]);
            getchar();
            printf("\nInput rating: ");
            scanf("%f", &Nod->rat[2]);
            getchar();
            InsertAfter(MyHead, Nod, MyHead->last);
        }
    } else printf("Memory error!\n");
}

void Delete(Head1 *MyHead, film *prev, film *New)
{
    if(MyHead->first==New) MyHead->first=New->next;
    else prev->next=New->next;
}


void search(Head1 *MyHead, Head *HeaAge, Head *HeaCou)
{
    film *NewNode=NULL;
    film *prev=NULL;
    Node *g;
    int k, num, counter, flag=0;
    char *st;

    k=0;
    counter=0;
    printf("Select search field\n");
    printf("1-NAME\n");
    printf("2-AGE RATING\n");
    printf("3-COUNTRY\n");
    scanf("%i", &num);
    getchar();
    NewNode=MyHead->first;
    prev=MyHead->first;
    st=(char*)malloc(100*sizeof(char));
    if(st!=NULL)
    {
        while(NewNode != NULL && flag == 0)
        {
            switch(num)
            {
            case 1:
                if(k==0)
                {
                    printf("\nINPUT NAME: ");
                    new_gets(st,50);
                    k++;
                }
                if(strcmp(NewNode->name,st)==0)
                {
                    Delete(MyHead, prev, NewNode);
                    NewNode=prev;
                    counter++;
                }
                break;
            case 2:
                if(k==0)
                {
                    printf("Search variant (enter as written):");
                    g=HeaAge->first;
                    while(g!=NULL)
                    {
                        printf("\n%s ",g->name);
                        g=g->next;
                    }
                    printf("\nINPUT AGE RATING: ");
                    new_gets(st,50);
                    k++;
                }
                if(strcmp(NewNode->age->name, st)!=0)
                {
                    Delete(MyHead, prev, NewNode);
                    NewNode=prev;
                    counter++;
                }
                break;
            case 3:
                if(k==0)
                {
                    printf("Search variant (enter as written):");
                    g=HeaCou->first;
                    while(g!=NULL)
                    {
                        printf("\n%s ",g->name);
                        g=g->next;
                    }

                    printf("\nINPUT COUNTRY: ");
                    new_gets(st,50);
                    k++;
                }
                if(strcmp(NewNode->country->name, st)!=0)
                {
                    Delete(MyHead, prev, NewNode);
                    NewNode=prev;
                    counter++;
                }
                break;
            default:
                printf("Incorrect value!");
                flag=1;
                break;
            }
            prev=NewNode;
            NewNode=NewNode->next;
        }
        NewNode=MyHead->first;
        if(MyHead->first!=NULL && flag!=1)
        {
            if(counter!=0)
            {
                print_header();
                while(NewNode != NULL)
                {
                    struct_out(NewNode);
                    NewNode=NewNode->next;
                }
            }
            else printf("\nThere are no items with specified content.\n");
        }
    }
    main_menu(MyHead, HeaAge, HeaCou);
}

void sort(Head1 *MyHead, Head *HeaAge, Head *HeaCou)
{

    int num;
    film *(*SortKind)(film*) = NULL;
    film *Nod=NULL;

    printf("Select search field\n");
    printf("1-NAME\n");
    printf("2-AGE RATING\n");
    printf("3-COUNTRY\n");
    printf("4-BUDGET\n");
    printf("5-GROSS\n");
    printf("6-RATING KINOPOISK\n");
    printf("7-RATING IMdB\n");
    scanf("%i", &num);
    getchar();
    Nod=MyHead->first;
    switch(num)
    {
    case 1:
        SortKind=sort_name;
        break;
    case 2:
        SortKind=sort_age;
        break;
    case 3:
        SortKind=sort_country;
        break;
    case 4:
        SortKind=sort_buget;
        break;
    case 5:
        SortKind=sort_gross;
        break;
    case 6:
        SortKind=sort_ratingK;
        break;
    case 7:
        SortKind=sort_ratingI;
    }
    Nod=MyHead->first;
    MyHead->first=SortKind(Nod);
    output(MyHead);
    main_menu(MyHead, HeaAge, HeaCou);
}

film *sort_name(film *ph)			// функция возвращает заголовок нового списка
{
    film *q, *out, *p , *pr;
    out=NULL;                    // выходной список пуст
    while (ph!=NULL)              // пока не пуст входной список
    {
        q=ph; ph=ph->next;  // исключить очередной
        for ( p=out,pr=NULL; p!=NULL && strcmp(q->name,p->name)>0; pr=p,p=p->next);
        if (pr==NULL)             // включение перед первым
        {
            q->next=out; out=q;
        }
        else                      // иначе после предыдущего
        {
            q->next=p; pr->next=q;
        }
    }
 return out;
}

film *sort_age(film *ph)			// функция возвращает заголовок нового списка
{
    film *q, *out, *p , *pr;
    out = NULL;                    // выходной список пуст
    while (ph !=NULL)              // пока не пуст входной список
    {
        q = ph; ph = ph->next;  // исключить очередной
        for ( p=out,pr=NULL; p!=NULL && strcmp(q->age->name,p->age->name)>0; pr=p,p=p->next);
        if (pr==NULL)             // включение перед первым
        {
            q->next=out; out=q;
        }
        else                      // иначе после предыдущего
        {
            q->next=p; pr->next=q;
        }
    }
 return out;
}

film *sort_country(film *ph)			// функция возвращает заголовок нового списка
{
    film *q, *out, *p , *pr;
    out = NULL;                    // выходной список пуст
    while (ph !=NULL)              // пока не пуст входной список
    {
        q = ph; ph = ph->next;  // исключить очередной
        for ( p=out,pr=NULL; p!=NULL && strcmp(q->country->name,p->country->name)>0; pr=p,p=p->next);
        if (pr==NULL)             // включение перед первым
        {
            q->next=out; out=q;
        }
        else                      // иначе после предыдущего
        {
            q->next=p; pr->next=q;
        }
    }
 return out;
}

film *sort_buget(film *ph)			// функция возвращает заголовок нового списка
{
    film *q, *out, *p , *pr;
    out = NULL;                    // выходной список пуст
    while (ph !=NULL)              // пока не пуст входной список
    {
        q = ph; ph = ph->next;  // исключить очередной
        for ( p=out,pr=NULL; p!=NULL && q->budget>p->budget; pr=p,p=p->next);
        if (pr==NULL)             // включение перед первым
        {
            q->next=out; out=q;
        }
        else                      // иначе после предыдущего
        {
            q->next=p; pr->next=q;
        }
    }
 return out;
}

film *sort_gross(film *ph)			// функция возвращает заголовок нового списка
{
    film *q, *out, *p , *pr;
    out = NULL;                    // выходной список пуст
    while (ph !=NULL)              // пока не пуст входной список
    {
        q = ph; ph = ph->next;  // исключить очередной
        for ( p=out,pr=NULL; p!=NULL && q->gross>p->gross; pr=p,p=p->next);
        if (pr==NULL)             // включение перед первым
        {
            q->next=out; out=q;
        }
        else                      // иначе после предыдущего
        {
            q->next=p; pr->next=q;
        }
    }
 return out;
}

film *sort_ratingK(film *ph)			// функция возвращает заголовок нового списка
{
    film *q, *out, *p , *pr;
    out = NULL;                    // выходной список пуст
    while (ph !=NULL)              // пока не пуст входной список
    {
        q = ph; ph = ph->next;  // исключить очередной
        for ( p=out,pr=NULL; p!=NULL && q->rating_kino>p->rating_kino; pr=p,p=p->next);
        if (pr==NULL)             // включение перед первым
        {
            q->next=out; out=q;
        }
        else                      // иначе после предыдущего
        {
            q->next=p; pr->next=q;
        }
    }
 return out;
}

film *sort_ratingI(film *ph)			// функция возвращает заголовок нового списка
{
    film *q, *out, *p , *pr;
    out = NULL;                    // выходной список пуст
    while (ph !=NULL)              // пока не пуст входной список
    {
        q = ph; ph = ph->next;  // исключить очередной
        for ( p=out,pr=NULL; p!=NULL && q->rating_IM>p->rating_IM; pr=p,p=p->next);
        if (pr==NULL)             // включение перед первым
        {
            q->next=out; out=q;
        }
        else                      // иначе после предыдущего
        {
            q->next=p; pr->next=q;
        }
    }
 return out;
}


