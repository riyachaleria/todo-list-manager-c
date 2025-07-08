#include<stdio.h>
#include<stdlib.h>
#include<string.h>
# define password_hash 8246073859955783634
typedef struct {
    int id;
    char description[100];
    int status;
    int priority;
}task;
void addtask();
int loadtasks(task **arr, int *count);
void viewtasks(task *arr, int count);
void updatemenu();
void savechanges(task *arr, int count);
void viewcompletedtasks(task *arr,int count);
void markcomplete(task *arr, int count);
void deletetask(task **arr, int *count);
void reindexAllTasks();
void updatedescription(task *arr,int count);
void updatestatus(task *arr,int count);
void deleteallcompleted(task **arr,int *count);
int getmaxid();
void savetask();
void deletealltask();
void backupfile(task *arr,int count);
void exportcsv(task *arr,int count);
void viewincompletedtasks(task *arr,int count);
void searchtasks(task *arr,int count);
void tolowercase(char *str);
char* getPriorityLabel(int level);
void viewfiltermenu();
void restorebackup();
void updatepriority(task *arr,int count);
void sortpriority(task *arr,int count);
int comparebyasc(const void *a,const void *b);
int comparebydes(const void *a,const void *b);
unsigned long long simplehash(const char *str);
int adminlogin();
int main()
{
    if(adminlogin())
    {
        printf("Access Granted....\n");
    }
    else{
        printf("Access Denied! Exiting.....\n");
        return 0;
    }
    int choice;
    printf("\n=========================================\n");
    printf("  Welcome to Your To-Do List Manager  \n");
    printf("=========================================\n");
    printf("Manage your tasks efficiently and stay productive!\n");
    do {
        printf("\n------------ Main Menu ------------\n\n");
        printf("1 - Add Task.\n");
        printf("2 - View & Filter Tasks by Status.\n");
        printf("3 - Update Task.\n");
        printf("4 - Mark a Task as Completed.\n");
        printf("5 - Search Tasks.\n");
        printf("6 - Sort Task by priority.\n");
        printf("7 - Delete a Task.\n");
        printf("8 - Delete All Tasks.\n");
        printf("9 - Delete All Completed Tasks.\n");
        printf("10 - Backup All Tasks to File.\n");
        printf("11 - Restore Tasks from Backup.\n");
        printf("12 - Export All Tasks to CSV.\n");
        printf("13 - Save Tasks.\n");
        printf("14 - Exit.\n");
        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1 : {
                addtask();
                break;
            }
            case 2 : {
                viewfiltermenu();
                break;
            }
            case 3 : {
                updatemenu();
                break;
            }
            case 4 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break;
                }
                markcomplete(arr,count);
                savechanges(arr,count);
                free(arr);
                break;
            }
            case 5 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break;
                }
                searchtasks(arr,count);
                free(arr);
                break;
            }
            case 6 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break;
                }
                sortpriority(arr,count);
                free(arr);
                break;
            }
            case 7 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break;
                }
                deletetask(&arr,&count);
                savechanges(arr,count);
                reindexAllTasks();
                free(arr);
                break;
            }
            case 8 : {
                deletealltask();
                break;
            }
            case 9 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break;
                }
                deleteallcompleted(&arr,&count);
                savechanges(arr,count);
                reindexAllTasks();
                free(arr);
                break;
            }
            case 10 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break;
                }
                backupfile(arr,count);
                free(arr);
                break;
            }
            case 11 : {
                restorebackup();
                break;
            }
            case 12 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    break;
                }
                exportcsv(arr,count);
                free(arr);
                break;
            }
            case 13 : {
                savetask();
                break;
            }
            case 14 : {
                printf("\nThank you for using the To-Do List Manager. Goodbye!\n");
                break;
            }
            default : {
                printf("Invalid Choice. Choose Again.");
            }
        }
    }while(choice != 14);
    return 0;
}
unsigned long long simplehash(const char *str)
{
    unsigned long long hash = 5381;
    int ch;
    while((ch = *str++))
    {
        hash = ((hash << 5) + hash) + ch;
    }
    return hash;
}
int adminlogin()
{
    char str[50];
    int attempts = 3;
    for(int attempt = 1;attempt<=attempts;attempt++)
    {
        printf("Enter Your Password (Attempt %d of %d) : ",attempt,attempts);
        scanf("%[^\n]",str);
        while ((getchar()) != '\n');
        unsigned long long inputhash = simplehash(str);
        if(inputhash == password_hash)
        {
            printf("\nLogin Successful! Welcome.\n");
            return 1;
        }
        else{
            printf("\nLogin Failed! Incorrect Password.\n");
            if(attempt < attempts)
            {
                printf("Please try again.\n\n");
            }
            else 
            {
                printf("\nMaximum login attempts reached. Access Denied.\n");
                return 0;
            }
        }
    }
    return 0;
}
void addtask()
{
    char mode[3];
    printf("Do you want to:\n");
    printf("1 - Append to existing data\n");
    printf("2 - Overwrite all existing data\n");
    printf("Enter your choice (1 or 2): ");
    int filechoice;
    scanf("%d",&filechoice);
    if(filechoice == 1)
    {
        strcpy(mode,"ab");
    }
    else if(filechoice == 2)
    {
        strcpy(mode,"wb");
    }
    else {
        printf("Invalid choice. Defaulting to append mode.\n");
        strcpy(mode, "ab");
    }
    FILE *fp;
    task *tasks;
    fp = fopen("to-do-list.bin",mode);
    if(fp == NULL)
    {
        printf("Error : Unable To Open The File.");
        return ;
    }
    int n;
    printf("\n------------------------------------------\n");
    printf("Enter how many tasks you want to add : ");
    scanf("%d",&n);
    if (n <= 0) {
        printf("Invalid number of tasks.\n");
        return;
    }
    tasks = (task*)malloc(n*sizeof(task));
    if (!tasks) {
        printf("Memory allocation failed!\n");
        fclose(fp);
        return;
    }
    int lastid = (filechoice == 1) ? getmaxid() : 0;
    printf("\nEnter %d Tasks Details :-\n",n);
    for(int i=0;i<n;i++)
    {
        lastid++;
        tasks[i].id = lastid;
        printf("\nTask %d :-\n",i+1);
        printf("Enter Task Description : ");
        while ((getchar()) != '\n');  
        scanf("%[^\n]",tasks[i].description);
        tasks[i].status = 0;
        printf("Set Task Priority.\n");
        printf("1 - Low.\n");
        printf("2 - Medium.\n");
        printf("3 - High.\n");
        int priorityinput;
        do{
            printf("Enter Priority (1-3): ");
            scanf("%d", &priorityinput);
            if(priorityinput < 1 || priorityinput > 3)
            {
                printf("Invalid input. Please enter 1, 2, or 3.\n");
            }
        }while(priorityinput < 1 || priorityinput > 3);
        tasks[i].priority = priorityinput;
    }
    fwrite(tasks,sizeof(task),n,fp);
    fclose(fp);
    printf("Tasks have been added successfully.\n");
    free(tasks);
    if (filechoice == 2) {
        reindexAllTasks();
    }
}
int getmaxid()
{
    FILE *fp = fopen("to-do-list.bin", "rb");
    if (fp == NULL) return 0;
    task temp;
    int maxid = 0;
    while (fread(&temp, sizeof(task), 1, fp) == 1)
    {
        if(temp.id > maxid)
        {
            maxid = temp.id;
        }
    }
    fclose(fp);
    return maxid;
}
void reindexAllTasks()
{
    task *arr;
    int count;
    if (loadtasks(&arr, &count) != 0) return;
    for(int i=0;i<count;i++)
    {
        arr[i].id = i+1;
    }
    FILE *fp;
    fp = fopen("to-do-list.bin","wb");
    if(fp == NULL)
    {
        printf("Error : Unable To Open The File.");
        return ;
    }
    fwrite(arr,sizeof(task),count,fp);
    fclose(fp);
    free(arr);
}
int loadtasks(task **arr, int *count)
{
    FILE *fp = fopen("to-do-list.bin", "rb");
    if (fp == NULL) {
        printf("Error: Unable To Open The File.\n");
        return 1;
    }
    int countint = 0;
    int capacity = 2;
    *arr = (task*)malloc(capacity*sizeof(task));
    task temp;
    while(fread(&temp,sizeof(task),1,fp) == 1)
    {
        if(countint == capacity)
        {
            capacity *= 2;
            *arr = (task*)realloc(*arr,capacity*sizeof(task));
            if (*arr == NULL) {
                printf("Memory reallocation failed!\n");
                free(*arr);
                fclose(fp);
                return 1;
            }
        }
        (*arr)[countint] = temp;
        countint++;
    }
    *count = countint;
    fclose(fp);
    return 0;
}
char* getPriorityLabel(int level) 
{
    switch(level) {
        case 1: return "Low";
        case 2: return "Medium";
        case 3: return "High";
        default: return "Unknown";
    }
}
void viewtasks(task *arr,int count)
{
    printf("\n------------------------------------------\n");
    printf("\nAll Tasks Records Are There :-\n");
    for(int i =0;i<count;i++)
    {
        printf("\n===============================");
        printf("\n  Tasks %d Details", i + 1);
        printf("\n===============================");
        printf("\nID : %d", arr[i].id);
        printf("\nDescription : %s", arr[i].description);
        printf("\nStatus : %s",arr[i].status == 1 ? "Completed" : "Incomplete");
        printf("\nPriority : %s",getPriorityLabel(arr[i].priority));
        printf("\n");
    }
    printf("\n------------------------------------------\n");
}
void updatemenu()
{
    int choice;
    printf("\n------------------------------------------\n");
    printf("\n---------- Update Menu ----------\n");
    printf("1 - Update Task Description.\n");
    printf("2 - Update task Status.\n");
    printf("3 - Update Priority of a Task.\n");
    printf("0 - Back to Main Menu.\n");
    do {
        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                updatedescription(arr,count);
                savechanges(arr,count);
                free(arr);
                break;
            }
            case 2 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                updatestatus(arr,count);
                savechanges(arr,count);
                free(arr);
                break;
            }
            case 3 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                updatepriority(arr,count);
                savechanges(arr,count);
                free(arr);
                break;
            }
            case 0 : {
                return ;
            }
        }
    }while(choice < 0 || choice > 3);
}
void updatedescription(task *arr,int count)
{
    int search;
    int found = 0;
    printf("\n------------------------------------------\n");
    printf("Enter the Id of task which Description you want to Update.\n");
    scanf("%d",&search);
    for(int i=0;i<count;i++)
    {
        if(arr[i].id == search)
        {
            found = 1;
            printf("\nCurrent Description : %s",arr[i].description);
            printf("\nEnter the New Description of id %d : ",arr[i].id);
            while ((getchar()) != '\n');
            scanf("%[^\n]",arr[i].description);
            printf("\nDescription is Updated Successfuly.\n");
            break;
        }
    }
    if(found == 0)
    {
        printf("\nTask ID Not Found.\n");
    }
}
void updatestatus(task *arr,int count)
{
    int search;
    int found = 0;
    printf("\n------------------------------------------\n");
    printf("Enter the Id of task which Status you want to Update : \n");
    scanf("%d",&search);
    for(int i=0;i<count;i++)
    {
        if(arr[i].id == search)
        {
            found = 1;
            printf("\nDescription : %s",arr[i].description);
            printf("\nCurrent Status : %s",arr[i].status == 1 ? "Completed" : "Incomplete");
            char confirm;
            printf("\nAre You sure you want to change status of this task? [YES - Y / NO - N] : ");
            while ((getchar()) != '\n');
            scanf("%c",&confirm);
            if(confirm != 'Y' && confirm != 'y')
            {
                printf("\nChange in Status cancelled by user.\n");
                return ;
            }
            if(arr[i].status == 0)
            {
                arr[i].status = 1;
                printf("\nStatus is Updated Successfully. New status: Completed\n");
            }
            else{
                arr[i].status = 0;
                printf("\nStatus is Updated Successfully. New status: Incomplete\n");
            }
            break;
        }
    }
    if(found == 0)
    {
        printf("\nTask ID Not Found.\n");
    }
}
void updatepriority(task *arr,int count)
{
    int search;
    int found = 0;
    printf("\n------------------------------------------\n");
    printf("Enter the Id of the ask whose Priority you want to Update : \n");
    scanf("%d",&search);
    for(int i=0;i<count;i++)
    {
        if(arr[i].id == search)
        {
            found = 1;
            printf("\nDescription : %s",arr[i].description);
            printf("\nCurrent Priority : %s",getPriorityLabel(arr[i].priority));
            char confirm;
            printf("\nAre You sure you want to change the Priority of this task? [YES - Y / NO - N] : ");
            while ((getchar()) != '\n');
            scanf("%c",&confirm);
            if(confirm != 'Y' && confirm != 'y')
            {
                printf("\nChange in Priority cancelled by user.\n");
                return ;
            }
            printf("Set Task Priority.\n");
            printf("1 - Low.\n");
            printf("2 - Medium.\n");
            printf("3 - High.\n");
            int priorityinput;
            do{
                printf("Enter Priority (1-3): ");
                scanf("%d", &priorityinput);
                if(priorityinput < 1 || priorityinput > 3)
                {
                    printf("Invalid input. Please enter 1, 2, or 3.\n");
                }
            }while(priorityinput < 1 || priorityinput > 3);
            arr[i].priority = priorityinput;
            printf("\nPriority updated successfully. New Priority : %s\n\n", getPriorityLabel(arr[i].priority));
        }
    }
    if(found == 0)
    {
        printf("\nTask ID Not Found.\n");
    }
}
void markcomplete(task *arr, int count)
{
    int search;
    int found = 0;
    printf("\n------------------------------------------\n");
    printf("Enter the ID of the task you want to mark as complete : \n");
    scanf("%d",&search);
    for(int i=0;i<count;i++)
    {
        if(arr[i].id == search)
        {
            found = 1;
            if(arr[i].status == 1)
            {
                printf("\nThis task is already marked as completed.\n");
            }
            else{
                arr[i].status = 1;
                printf("\nTask Marked as Completed.\n");
            }
            break;
        }
    }
    if(found == 0)
    {
        printf("\nTask ID Not Found.\n");
    }
}
void savechanges(task *arr, int count)
{
    if (count == 0) 
    {
        printf("No tasks to save. Skipping file write.\n");
        return;
    }
    FILE *fp;
    fp = fopen("to-do-list.bin","wb");
    if(fp == NULL)
    {
        printf("Error : Unable To Open The File.");
        return ;
    }
    fwrite(arr,sizeof(task),count,fp);
    fclose(fp);
    printf("Changes saved successfully.\n");
}
void deletetask(task **arr, int *count)
{
    int search;
    int found = 0;
    printf("\n------------------------------------------\n");
    printf("Enter the ID of the task you want to Delete : ");
    scanf("%d",&search);
    for(int i=0;i<*count;i++)
    {
        if((*arr)[i].id == search)
        {
            found = 1;
            char confirm ;
            printf("Are You Sure you want to Delete id %d Task [YES - Y / NO - N] : ",(*arr)[i].id);
            while ((getchar()) != '\n');
            scanf("%c",&confirm);
            if(confirm != 'Y' && confirm != 'y')
            {
                printf("\nDeletion cancelled by user.\n");
                return ;
            }
            for(int j=i;j <(*count)-1;j++)
            {
                (*arr)[j] = (*arr)[j+1];
            }
            *arr = (task*)realloc(*arr,((*count)-1)*sizeof(task));
            (*count)--;
            printf("\nTask Id %d Deleted Successfully.\n",search);
            break;
        }
    }
    if(found == 0)
    {
        printf("\nTask ID Not Found.\n");
    }
}
void savetask()
{
    printf("\n------------------------------------------\n");
    printf("\nSave Option Selected.\n");
    printf("All Tasks saved again successfully.\n");
}
void deletealltask()
{
    printf("\n------------------------------------------\n");
    char confirm ;
    printf("Are You Sure you want to Delete All Tasks [YES - Y / NO - N] : ");
    while ((getchar()) != '\n');
    scanf("%c",&confirm);
    if(confirm != 'Y' && confirm != 'y')
    {
        printf("\nDeletion cancelled by user.\n");
        return ;
    }
    FILE *fp = fopen("to-do-list.bin", "wb");
    if (fp == NULL) {
        printf("Error: Unable To Open The File.\n");
        return ;
    }
    printf("All Tasks are Deleted Successfully.\n");
    fclose(fp);
}
void deleteallcompleted(task **arr,int *count)
{
    printf("\n------------------------------------------\n");
    char confirm ;
    printf("Are You Sure you want to Delete all Completed Tasks [YES - Y / NO - N] : ");
    while ((getchar()) != '\n');
    scanf("%c",&confirm);
    if(confirm != 'Y' && confirm != 'y')
    {
        printf("\nDeletion cancelled by user.\n");
        return ;
    }
    int countint = 0;
    for(int i=0;i<*count;i++)
    {
        if((*arr)[i].status == 1)
        {
            countint++;
            for(int j = i;j<*count-1;j++)
            {
                (*arr)[j] = (*arr)[j+1];
            }
            i--;
        }
    }
    *arr = (task*)realloc(*arr,((*count)-countint)*sizeof(task));
    (*count) = (*count) - countint;
    printf("All completed tasks have been deleted.\n");
}
void backupfile(task *arr,int count)
{
    if (count == 0) 
    {
        printf("No tasks to Backup. Skipping file write.\n");
        return;
    }
    printf("\n------------------------------------------\n");
    FILE *fp = fopen("backup.bin","wb");
    if (fp == NULL) {
        printf("Error: Unable To Open The File.\n");
        return ;
    }
    fwrite(arr,sizeof(task),count,fp);
    fclose(fp);
    printf("\nData has been successfully backed up in 'backup.bin' File.\n");
}
void exportcsv(task *arr,int count)
{
    if (count == 0) 
    {
        printf("No tasks to Export. Skipping file write.\n");
        return;
    }
    printf("\n------------------------------------------\n");
    FILE *fp = fopen("exportcsv.csv","w");
    if (fp == NULL) {
        printf("Error: Unable To Open The File.\n");
        return ;
    }
    fprintf(fp,"Task Id,Description,Status,Priority\n");
    for(int i=0;i<count;i++)
    {
        fprintf(fp,"%d,%s,%s,%s\n",arr[i].id,arr[i].description,arr[i].status ? "Completed" : "Incomplete",getPriorityLabel(arr[i].priority));
    }
    fclose(fp);
    printf("\nData is Successfully Exported to CSV file.\n");
}
void restorebackup()
{
    printf("\n------------------------------------------\n");
    char confirm;
    printf("Are you sure you want to restore the backup? This will overwrite the current to-do list. [YES - Y / NO - N] : ");
    while ((getchar()) != '\n');
    scanf("%c", &confirm);
    if (confirm != 'Y' && confirm != 'y') {
        printf("Restore cancelled by user.\n");
        return;
    }
    FILE *fp1 = fopen("backup.bin","rb");
    if (fp1 == NULL) {
        printf("Error: Unable To Open The File.\n");
        return ;
    }
    FILE *fp2 = fopen("to-do-list.bin","wb");
    if (fp2 == NULL) {
        printf("Error: Unable To Open The File.\n");
        fclose(fp1);
        return ;
    }
    task temp;
    while(fread(&temp, sizeof(task), 1, fp1) == 1)
    {
        fwrite(&temp, sizeof(task), 1, fp2);
    }
    fclose(fp1);
    fclose(fp2);
    printf("\nBackup has been restored successfully to your main To-Do List.\n");
}
void searchtasks(task *arr,int count)
{
    printf("\n------------------------------------------\n");
    int searchfound = 0;
    char keyword[100];
    printf("Enter the task You want to Search : ");
    while ((getchar()) != '\n');
    scanf("%[^\n]",keyword);
    tolowercase(keyword);
    for(int i=0;i<count;i++)
    {
        char tempdesc[100];
        strcpy(tempdesc,arr[i].description);
        tolowercase(tempdesc);
        if(strstr(tempdesc,keyword) != NULL)
        {
            searchfound++;
            printf("\n===============================");
            printf("\n  Tasks %d Details", i + 1);
            printf("\n===============================");
            printf("\nID : %d", arr[i].id);
            printf("\nDescription : %s", arr[i].description);
            printf("\nStatus : %s",arr[i].status == 1 ? "Completed" : "Incomplete");
            printf("\nPriority : %s",getPriorityLabel(arr[i].priority));
            printf("\n");
        }
    }
    if(searchfound > 0)
    {
        printf("\nTotal %d Matches Found.\n",searchfound);
    }
    else{
        printf("\nNo Matches Found.\n");
    }
}
void tolowercase(char *str) 
{
    for (int i = 0; str[i]; i++) {
        if(str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}
void viewfiltermenu()
{
    int choice;
    printf("\n------------------------------------------\n");
    printf("\n--------------View Menu--------------\n");
    printf("1 - View All Tasks.\n");
    printf("2 - View All Completed Tasks.\n");
    printf("3 - View All Incomplete Tasks.\n");
    printf("0 - Back to Main Menu.\n");
    do {
        printf("\nEnter Your Choice : ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                viewtasks(arr,count);
                free(arr);
                break;
            }
            case 2 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                viewcompletedtasks(arr,count);
                free(arr);
                break;
            }
            case 3 : {
                task *arr;
                int count;
                if (loadtasks(&arr, &count) != 0) 
                {
                    printf("Unable to load records. Returning to main menu.\n");
                    return;
                }
                viewincompletedtasks(arr,count);
                free(arr);
                break;
            }
            case 0 : {
                return;
            }
            default : {
                printf("\nInvalid Choice. Choose Again.\n");
            }
        }
    }while(choice < 0 || choice > 3 );
}
void viewcompletedtasks(task *arr,int count) 
{
    printf("\n------------------------------------------\n");
    int searchfound = 0;
    for(int i=0;i<count;i++)
    {
        if(arr[i].status == 1)
        {
            searchfound++;
            printf("\n===============================");
            printf("\n  Tasks %d Details", i + 1);
            printf("\n===============================");
            printf("\nID : %d", arr[i].id);
            printf("\nDescription : %s", arr[i].description);
            printf("\nStatus : %s",arr[i].status == 1 ? "Completed" : "Incomplete");
            printf("\nPriority : %s",getPriorityLabel(arr[i].priority));
            printf("\n");
        }
    }
    printf("\n%.2f%% of all tasks are completed.\n", ((float)searchfound / count) * 100);
    if(searchfound > 0)
    {
        printf("\nTotal Completed Tasks Are : %d\n",searchfound);
    }
    else {
        printf("\nNo Tasks completed Yet.\n");
    }
}
void viewincompletedtasks(task *arr,int count) 
{
    printf("\n------------------------------------------\n");
    int searchfound = 0;
    for(int i=0;i<count;i++)
    {
        if(arr[i].status == 0)
        {
            searchfound++;
            printf("\n===============================");
            printf("\n  Tasks %d Details", i + 1);
            printf("\n===============================");
            printf("\nID : %d", arr[i].id);
            printf("\nDescription : %s", arr[i].description);
            printf("\nStatus : %s",arr[i].status == 0 ? "Incomplete" : "Completed");
            printf("\nPriority : %s",getPriorityLabel(arr[i].priority));
            printf("\n");
        }
    }
    printf("\n%.2f%% of all tasks are incomplete.\n", ((float)searchfound / count) * 100);
    if(searchfound > 0)
    {
        printf("\nTotal Incomplete Tasks Are : %d\n",searchfound);
    }
    else {
        printf("\nAll Tasks are completed.\n");
    }
}
void sortpriority(task *arr,int count)
{
    printf("\n------------------------------------------\n");
    if(count == 0)
    {
        printf("No tasks available to sort.\n");
        return;
    }
    int sortOrder;
    printf("1 - Ascending.\n");
    printf("2 - Descending.\n");
    printf("\nEnter Your Sorting Preference : ");
    scanf("%d",&sortOrder);
    if(sortOrder == 1)
    {
        qsort(arr,count,sizeof(task),comparebyasc);
        printf("Tasks sorted by priority (Low to High) successfully!\n");
        viewtasks(arr,count);
    }
    else{
        qsort(arr,count,sizeof(task),comparebydes);
        printf("Tasks sorted by priority (High to Low) successfully!\n");
        viewtasks(arr,count);
    }
    char confirm;
    printf("Do You want to save the sorted data? [YES - Y / NO - N] : ");
    while ((getchar()) != '\n');
    scanf("%c", &confirm);
    if (confirm == 'Y' || confirm == 'y') {
        savechanges(arr,count);
        printf("\nSorted Data is Successfully Saved.\n");
    }
    else{
        printf("\nSorted Data Did Not save in File.\n");
    }
}
int comparebydes(const void *a,const void *b)
{
    task *taskA = (task*)a;
    task *taskB = (task*)b;
    return taskB->priority - taskA->priority;
}
int comparebyasc(const void *a,const void *b)
{
    task *taskA = (task*)a;
    task *taskB = (task*)b;
    return taskA->priority - taskB->priority;
}