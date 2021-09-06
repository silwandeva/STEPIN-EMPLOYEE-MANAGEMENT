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
        printf("4. Delete Records"); /// option for deleting record
        a(20,13);
        printf("Your Choice: "); /// choose your choice
        fflush(stdin); 
        choice = getchar(); 
        switch(choice)
        {
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
        }
    }
    return 0;
}