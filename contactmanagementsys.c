
#include <stdio.h>
#include <malloc.h>
#include <string.h>

//-------------- Structure ---------------------------
typedef struct contact {
    int acno;
    char name[20];
    char phone[15];
    char email[20];
    struct contact *next;
    struct contact *prev;
    } Contact;
Contact *first,*crcontact,*newc;
//----------------------------------------------------
int count = 0;
//------------------FUNCTIONS-------------------------
//------------------Add Contact-----------------------
void add(void)
{
    newc = (struct contact *)malloc(sizeof(struct contact));

    if(first==NULL)
        first = crcontact = newc;
    else
    {
        crcontact = first;
        while(crcontact->next != NULL)
            crcontact = crcontact->next;

        crcontact->next = newc;
        newc->prev = crcontact;
        crcontact = newc;
    }

    count++;
    printf("Contact Number : %i",count);
    crcontact->acno = count;

    printf("\nEnter contact name : ");
    gets(crcontact->name);

    printf("Enter contact Phone number : ");
    gets(crcontact->phone);

    printf("Enter contact email : ");
    gets(crcontact->email);
    printf("\ncontact added!\nPress any key for Main Menu.. ");

    crcontact->next = NULL;
    getch();
}
//------------------list-------------------------
void displaylist(void)
{
    if(first==NULL)
        printf("\nThere are no contacts to display!");

    else
    {
	    printf("Ac No.  Name                 Phone          Email\n");
        printf("------ -------------------- ------------- -------------------\n");

        crcontact=first;

        do
        {

                printf("%6d: %-20s %-15s %-20s\n",crcontact->acno,crcontact->name,crcontact->phone,crcontact->email);
        }

        while((crcontact=crcontact->next) != NULL);
    }
    //getch();
}
//-----------------Delete---------------------------
void deletec(void)
{
    int n;
    if(first==NULL)
    {
        printf("There are no contacts to delete!\nPress any key for Main Menu.. ");
        getch();
	    return;
    }

    displaylist();
    printf("\nEnter contact account number to delete: ");
    scanf("%d",&n);

    crcontact = first;

    while(crcontact != NULL)
    {
        if(crcontact->acno == n)
            {
                if(crcontact == first)  //if it is first n
                {
                   first=crcontact->next;
                   first->prev = NULL;
                }
                else if(crcontact->next == NULL) //if it is last n
                {
                    crcontact->prev->next = NULL;
                }
                else
                {
                    crcontact->prev->next = crcontact->next;
                }
                free(crcontact);
                printf("\ncontact %d deleted!\n\nPress Any Key For Main Menu.. ",n);
                getch();
                return;
            }
        crcontact= crcontact->next;
    }
    printf("contact %d not found!\n",n);
    getch();
 }
//--------------------------modify--------------------
void edit(void)
{
    int n, t;

    if(first==NULL)
    {
        printf("There are no contacts to modify!");
        getch();
	return;
    }

    displaylist();
    printf("\nEnter contact account number to modify or change: ");
    scanf("%d",&n);

    t = findac(n);

    if( t >0 )
    {
	    printf("Contact %d:\n",crcontact->acno);
	    printf("Name: %s\n",crcontact->name);
	    if(display())
		    gets(crcontact->name);
	    printf("\nPhone: %s\n",crcontact->phone);
	    if(display())
		    gets(crcontact->phone);
	    printf("\nEmail: %s\n",crcontact->email);
	    if(display())
		    gets(crcontact->email);
        printf("\nContact Updated!\nPress Any Key For Main Menu.. ");
        getch();
	    return;
	}
    printf("\ncontact %d was not found!\nPress any key for Main Menu.. ",n);
    getch();
}
//-----------------------------------------------------------
int findac (int ac)
{
    int n;
    n = ac;
    crcontact = first;
    while(crcontact != NULL)
    {

        if(crcontact->acno == n)
	     {
           return 1;
         }

	else
	{
	    crcontact = crcontact->next;
	}
    }
    return -1;
}
//------------------------find----------------------------
int search(void)
{
     char buff[20];

     if(first==NULL)
	{
        printf("There are no contacts to find!");
        getch();
	    return 1;
    }

    printf("Enter contact name: ");
    fflush(stdin);
    gets(buff);

    crcontact = first;
    while(crcontact != NULL)
    {
        if( strcmp(crcontact->name, buff) == 0 )
	    {
			printf("Ac No.  Name                 Phone          Email\n");
			printf("------ -------------------- ------------- -------------------\n");
            printf("%6d: %-20s %-15s %-20s\n",\
            crcontact->acno,\
            crcontact->name,\
            crcontact->phone,\
            crcontact->email);
            getch();
			return 0;
	    }
		else
		{
			crcontact = crcontact->next;
		}
    }
    printf("\ncontact %s was not found!\n",buff);
    getch();
          return 1;
}
//------------------------------------------------------------------
int display(void)
{
	char ch;

    fflush(stdin);
	printf("Update? (Y to update any other key to not)");
	ch = getchar();
	ch = toupper(ch);
	fflush(stdin);
	if(ch == 'Y')
	{
		printf("Enter new value: ");
		return(1);
	}
	else
		return(0);
}
//-------------------Main Function---------------------------------

int main()
{
    FILE *fp;
    char ch;
    first = NULL;

    fp = fopen("contacts.dat","r");

    if(fp)
    {
	    first = (struct contact *)malloc(sizeof(struct contact));
	    first->prev = NULL;
	    crcontact = first;
	    while(1)
     	    {
		    newc = (struct contact *)malloc(sizeof(struct contact));
		    fread(crcontact,sizeof(struct contact),1,fp); //copy 1 data from file and put it into doubly linked list
		    newc->prev = crcontact;
		    if(crcontact->next == NULL)
			    break;
		    crcontact->next = newc;
		    crcontact = newc;
	    }
	    fclose(fp);
	    count = crcontact->acno;

    }

    do
    {
	fflush(stdin);   //clearing terminal buffer
	system("cls");
	    printf("Devloped By : Nizam Ansari");
        printf("\n\n\t______________________________________________");
        printf("\n\t**** WELCOME TO CONTACT MANAGEMENT SYSTEM ****");
        printf("\n\t----------------------------------------------");
        printf("\n\n\t\tMenu:");
        printf("\n\t\t`````");
        printf("\n\t\t1. Add Contact");
        printf("\n\t\t2. Delete Contact");
        printf("\n\t\t3. List All Contact");
        printf("\n\t\t4. Modify Contact");
        printf("\n\t\t5. Find Contact (by Name)");
        printf("\n\t\t6. Exit\n");
        printf("\n\tEnter Your Choice : ");
        ch = getchar();
	    ch = toupper(ch);
        switch(ch)
        {
            case '1':
                system("cls");
                printf("Add a new contact\n-----------------\n\n");
	        fflush(stdin);
                add();
                break;
	    case '2':
	        system("cls");
		printf("Delete a Contact\n----------------\n\n");
		deletec();
		break;
	    case '3':
	        system("cls");
		printf("List All Contacts\n------------------\n\n");
		displaylist();
		getch();
		break;
	    case '4':
	        system("cls");
		printf("Modify a contact\n-----------------\n\n");
		edit();
		break;
	    case '5':
	        system("cls");
		printf("Find a contact by name\n---------------------\n\n");
		search();
		break;
            case '6':
                printf("\n\nSave and quit\n");
                default:
                break;
        }
    }
    while(ch != '6');
    crcontact = first;

    if(crcontact == NULL)
	    return(0);

    fp = fopen("contacts.dat","w");

    if(fp == NULL)
    {
	    printf("Error writing to %s\n","contacts.dat");
	    return(1);
    }

    while(crcontact != NULL)
    {
	    fwrite(crcontact,sizeof(struct contact),1,fp);
	    crcontact = crcontact->next;
    }
    fclose(fp);
    return(0);
}
