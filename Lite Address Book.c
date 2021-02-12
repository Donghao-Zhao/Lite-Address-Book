#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DATAPATH "data.dat"
#define N 20

//struct define
struct student
{
    char name[N];
    char sex[N];
    char birthday[N];
    char telephone[N];
};

//function define(hide)
int scan();
int load();
int writeback();

//function define
int add();
int delete();
int change();
int list();
int search();
int quit();


//variables define
int i = 0,max = 0;
char mode;
struct student stu_scan[N];
char scan_name[N];
FILE *fp;

//main function
int main()
{
    printf("\nWelcome to the student contact system!\n\n");
    while(1)
    {
        max = load();
        printf("\nInput character in the left to move into mode in the right\n");
        printf("|*a*| |*Add one*|\n\
        |*d*| |*Delete one*|\n\
        |*c*| |*Change one*|\n\
        |*s*| |*Search one*|\n\
        |*l*| |*List all*|\n\
        |*q*| |*Quit system*|\n");
        printf("Switch mode:");
        scanf("%c",&mode);
        switch(mode)
        {
            case 'a':add();break;
            case 'd':delete();break;
            case 'c':getchar();change();break;
            case 'l':getchar();list();break;
            case 's':search();break;
            case 'q':getchar();quit();break;
            default:getchar();printf("\nInput error!\nPlease input again.\n");
        }
}
return 0;
}

int load()
{
    max = 0;
    if((fp = fopen(DATAPATH,"r")) == NULL)
    {
        printf("Open database error,Maybe there's no data had been written!\n");
        return 0;
    }
    while(fread(&stu_scan[max++],sizeof(struct student),1,fp));
    fclose(fp);
    printf("\nSuccessfully read %d student's information from database\n",--max);
    return max;
}

int scan()
{
    printf("\n(Input 'q' to quit)\nInput scanned name:");
    scanf("%s",scan_name);
    if((strcmp(scan_name,"q")) == 0){getchar();return -1;}
    i = 0;
    for(i = 0 ; i < max ; i++)
    if((strcmp(stu_scan[i].name,scan_name)) == 0)break;
    return i;
}

int writeback()
{
    int cur = 0,real = 0;
    if((fp = fopen(DATAPATH,"w")) == NULL)
    printf("Open database error!\n");
    for(cur = 0 ; cur < max ; cur++ )
    if(*stu_scan[cur].name != '\0')
    {
        fwrite(&stu_scan[cur],sizeof(struct student),1,fp);
        real++;
    }
    fclose(fp);
    printf("\nSuccessfully write %d student's information to database\n",real);
}

int add()
{
    struct student stu_create;
    FILE *fp;
    printf("\nName:");
    scanf("%s",stu_create.name);
    printf("Sex:");
    scanf("%s",stu_create.sex);
    printf("Birthday:");
    scanf("%s",stu_create.birthday);
    printf("Telephone:");
    scanf("%s",stu_create.telephone);
    getchar();
    if((fp = fopen(DATAPATH,"a")) == NULL)
    printf("Open database error!\n");
    if((fwrite(&stu_create,sizeof(struct student),1,fp)) == 0)
    printf("Writing data error!\n");
    else printf("Create successfully!\n");
    fclose(fp);
}

int list()
{
    for(i=0;i<max;i++)
    printf("\nname : %s\nsex : %s\nbirthday : %s\ntelephone : %s\n",stu_scan[i].name,stu_scan[i].sex,stu_scan[i].birthday,stu_scan[i].telephone);
}

int delete()
{
    while(1)
    {
        int flag = scan();
        if(flag == -1)return 0;
        else if(flag == max)printf("There's no data about this student!\n");
        else 
        {
            printf("\nName : %s\nSex : %s\nBirthday : %s\nTelephone : %s\n",stu_scan[flag].name,stu_scan[flag].sex,stu_scan[flag].birthday,stu_scan[flag].telephone);
            printf("\nDo you really want to delete data of this student?\n(Data deleted can't be recovered!)\n");
            while(1)
            {
                char decision = getchar();
                if(decision == 'y')
                {
                    getchar();
                    *stu_scan[flag].name = '\0';
                    *stu_scan[flag].sex = '\0';
                    *stu_scan[flag].birthday = '\0';
                    *stu_scan[flag].telephone = '\0';
                    printf("Delete successfully!\n");
                    writeback();
                    break;
                }
                else if(decision == 'n'){getchar();break;}
                else printf("\nPlease input 'y' or 'n'");
            }
        }
    }
}

int search()
{
    while(1)
    {
        int flag = scan(fp);
        if(flag == -1)return 0;
        else if(flag == max)printf("There's no data about this student!\n");
        else printf("\nname : %s\nsex : %s\nbirthday : %s\ntelephone : %s\n",stu_scan[flag].name,stu_scan[flag].sex,stu_scan[flag].birthday,stu_scan[flag].telephone);
    }
}

int change()
{
    int flag;
    char decision;
    int flag_change;

    while(1)
    {
        flag = scan();
        getchar();
        if(flag == -1)return 0;
        else if(flag == max)printf("There's no data about this student!\n");
        else 
        {
            printf("\nname : %s\nsex : %s\nbirthday : %s\ntelephone : %s\n",stu_scan[flag].name,stu_scan[flag].sex,stu_scan[flag].birthday,stu_scan[flag].telephone);
            printf("\nDo you really want to change data of this student?('y' or 'n')\n(Data changed can't be recovered!):");
            while(1)
            {
                decision = getchar();
                if(decision == 'y')
                {
                    while(1)
                    {
                        char item[N] = {0};
                        char content[N] = {0};
                        flag_change = 0;
                        printf("\nInput item you want to change('q' to quit):");
                        scanf("%s",item);
                        if(strcmp(item,"q") == 0){getchar();break;}
                        printf("\nInput new content you want to replace:");
                        scanf("%s",content);
                        printf("content = %s\n",content);
                        if((strcmp(item,"name")) == 0)
                        {
                            strcpy(stu_scan[flag].name,content);
                            flag_change = 1;
                        }
                        else if((strcmp(item,"sex")) == 0)
                        {
                            strcpy(stu_scan[flag].sex,content);
                            flag_change = 1;
                        }
                        else if((strcmp(item,"birthday")) == 0)
                        {
                            strcpy(stu_scan[flag].birthday,content);
                            flag_change = 1;
                        }
                        else if((strcmp(item,"telephone")) == 0)
                        {
                            strcpy(stu_scan[flag].telephone,content);
                            flag_change = 1;
                        }
                        else printf("Input item error,check your input!\n");
                        if(flag_change == 1)printf("\nname : %s\nsex : %s\nbirthday : %s\ntelephone : %s\n",stu_scan[flag].name,stu_scan[flag].sex,stu_scan[flag].birthday,stu_scan[flag].telephone);
                        writeback();
                    }
                    break;
                }
                else if(decision == 'n'){getchar();break;}
                else printf("Please input 'y' or 'n':");
            }
        }
    }
}

int quit()
{
    printf("\nDo you really want to quit?('y' or 'n')\n(Waring : Any information not being saved will be missing!):");
    while(1)
    {
        char decision = getchar();
        if(decision == 'y')exit(7);
        else if(decision == 'n'){getchar();break;}
        else printf("Please input 'y' or 'n'");
    }
}
