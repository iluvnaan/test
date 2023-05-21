#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void bubblesort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if(arr[i]>arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        
    }
    
}
void printArray(int arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
void menu()
{
    printf("\n1. ORPHAN EXECUTION\n2. ZOMBIE EXECUTION\n\nENTER CHOICE : ");
}
int main(void)
{

    int n;
    printf("ENTER NUMBER OF ELEMENTS: ");
    scanf("%d", &n);
    int a[n];
    printf("ENTER ELEMENTS: ");
    for (int i = 0; i < n; ++i)
    {
        scanf("%d", &a[i]);
    }
    menu();
    int choice;
    scanf("%d", &choice);
    pid_t p = fork();
 
    switch (choice)
    {
        
    case 1:
        printf("\nINITIATING ORPHAN EXECUTION...!!\n\n");

        if (p == 0)
        {
            sleep(30);
            printf("\nCHILD PROCESS WITH PID : %d AND PARENT ID : %d\n", getpid(), getppid());
            bubblesort(a, n);

            printf("SORTED ARRAY: ");
            printArray(a, n);
            system("ps -elf | grep %d");
            printf("\n");
        }

        else
        {
            //wait(NULL);
            printf("\nPARENT PROCESS WITH PID : %d AND CHILD ID : %d\n", getpid(), p);
            bubblesort(a,  n );

            printf("SORTED ARRAY: ");
            printArray(a, n);
            //snprintf(buffer, 25, );
            system("ps -elf | grep %d");
            printf("\n");
        }
        break;
    case 2:
        printf("\nINITIATING ZOMBIE EXECUTION...!!\n\n");

        if (p == 0)
        {
            printf("\nCHILD PROCESS WITH PID : %d AND PARENT ID : %d\n", getpid(), getppid());

            bubblesort(a, n);

            printf("SORTED ARRAY: ");
            printArray(a, n);
            system("ps -aux | grep %d");

            printf("\n");
        }

        else
        {
            sleep(5);
            printf("\nPARENT PROCESS WITH PID : %d AND CHILD ID : %d\n", getpid(), p);
            bubblesort(a, n);

            printf("SORTED ARRAY: ");
            printArray(a, n);
            system("ps -elf | grep '<defunct>'");
            printf("\n");
        }
        break;
    default:
        printf("WRONG CHOICE...!!");
        printf("\n");
        menu();
        break;
    }
}
