#include <stdio.h> 
#include <stdlib.h>
#include <conio.h>
#include <windows.h> 
#include <string.h>  
COORD b = {1,0};/// coordinates
void a(int x,int y)
{
    b.X = x;
    b.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),b);
}
int main()   ///main function
{
    FILE *fp, *ft;  /// file open and close
    char another;
	char choice;
  /** structure that represent a employee */
    struct emp
    {
        char name[40];  ///name of employee
        int DOB;       /// date of birth of employee
        int age;     /// age of employee
		char ms[40];   /// marital status of employee
		char qualification[40];  /// qualification of employee
		char employement[40];    /// previous employement of employee
        float bs;        /// basic salary of employee
    };
    struct emp e; 
    char employeename[40]; ///employee name for update or list the deatils
    long int resize; 
    fp = fopen("EMP.DAT","rb+");  /
    if(fp == NULL)  //if file is null
    {
        fp = fopen("EMP.DAT","wb+"); //write
        if(fp == NULL)
        {
            printf("Connot open file"); ///again if file is null
            exit(1);
        }
    }
    resize = sizeof(e);
    while(1)
    {
        system("cls"); 
        a(20,5); 
        printf("1. Add Record"); /// option for add record
        a(20,7);
        printf("2. show Records"); ///option for listing record
        a(20,9);
        printf("3. Modify Records"); /// option for editing record
        a(20,11);
        printf("4. Delete Records"); /// option for deleting record
        a(20,13);
        printf("6. Exit"); /// exit from the program
        a(20,15);
        printf("Your Choice: "); /// choose your choice
        fflush(stdin); 
        choice = getchar(); 
        switch(choice)
        {
        case '1':  
            system("cls");
            fseek(fp,0,SEEK_END); 
            another = 'y';
            while(another == 'y')  
            {
                ///add details of employee
                printf("\nEnter name: ");  // enter name
                scanf("%s",e.name);
                printf("\nEnter date of birth: ");  /// enter date of birth
                scanf("%d", &e.DOB);
                printf("\nEnter age: "); /// enter age
                scanf("%d", &e.age);
                printf("\nEnter marital status: "); /// enter marital status
                scanf("%s",e.ms);
                printf("\nEnter academic qualifications: ");  ///enter qualification
                scanf("%s",e.qualification);
                printf("\nEnter  previous employment details: "); ///enter previous status
                scanf("%s",e.employement);
                printf("\nEnter salary: "); ///enter salary
                scanf("%f", &e.bs);
                fwrite(&e,resize,1,fp); 
                printf("\nAdd another record(y/n) "); /// add another one
                fflush(stdin);
                another = getchar(); // to choose another
            }
            break;
        case '2':
        //list details of employee
            system("cls");
            rewind(fp); 
            while(fread(&e,resize,1,fp)==1)  
            {
                printf("\n%s %d %d %s %s %s %.2f",e.name,e.DOB,e.age,e.ms,e.qualification,e.employement,e.bs); 
            }
            getch();
            break;
        case '3':  
        ///modify details of employee
            system("cls");
            another = 'y';
            while(another == 'y')
            {
                printf("Enter the employee name to modify: ");
                scanf("%s", employeename);  //scan the employee name for midification
                rewind(fp);
                while(fread(&e,resize,1,fp)==1)  
                {
                    if(strcmp(e.name,employeename) == 0) ///string comparison
                    {
                        printf("\nEnter new name,dob, age,ms,qualification,employement and bs: ");
                        scanf("%s %d %d %s %s %s %.2f",e.name,e.DOB,e.age,e.ms,e.qualification,e.employement,e.bs);
                        fseek(fp,-resize,SEEK_CUR); 
                        fwrite(&e,resize,1,fp); 
                        break;
                    }
                }
                printf("\nModify another record(y/n)");//choose to continue or add another one
                fflush(stdin);
                another = getche();
            }
            break;
        case '4':
        ///delete details of employee
            system("cls");
            another = 'y';
            while(another == 'y') /// if yes we can choose another name
            {
                printf("\nEnter employee name to delete: ");
                scanf("%s",employeename); ///scan employee name for deletion
                ft = fopen("Temp.dat","wb");  ///open file
                while(fread(&e,resize,1,fp) == 1)  
                {
                    if(strcmp(e.name,employeename) != 0)   /// if the entered record match
                    {
                        fwrite(&e,resize,1,ft); 
                    }
                }
                fclose(fp);
                fclose(ft);
                remove("EMP.DAT"); /// remove the orginal file
                rename("Temp.dat","EMP.DAT");   ///rename the file
                fp = fopen("EMP.DAT", "rb+");/// open the file and read
                printf("Delete another record(y/n)");  // choose to delete another one
                fflush(stdin);    
            }
            break;
			 case '5':
            fclose(fp); ///close the file
            exit(0); // exit from the program
        }
    }
    return 0;
}