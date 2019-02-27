//
//  main.c
//  mix
//
//  Created by Hileo on 17/11/20.
//  Copyright (c) 2017年 Coco. All rights reserved.
//


#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int countOpenParentheses(FILE *fp);
int countCloseParentheses(FILE *fp);
int countOpenSquareBrackets(FILE *fp);
int countCloseSquareBrackets(FILE *fp);
int countOpenBraces(FILE *fp);
int countCloseBraces(FILE *fp);
void SyntaxChecking(FILE *fp);
void SyntaxValidation(FILE *fp);
void Formatted(FILE *fp);

int main()
{
    FILE *myFile;
    myFile=fopen("test.txt","r");
    if(myFile==NULL)
    {
        printf("File open unsuccessfully\n");
        exit(1);
    }
    else
    {
        printf("File open successfully\n");
    }
    
    /*Need function fo fill in*/
    SyntaxChecking(myFile);//Question 2.1 Part A Syntax Checking
    Formatted(myFile);//Question 2.2 Part B Formatted Output
    SyntaxValidation(myFile);//Question 2.3 Part C Syntax Validation
    
    fclose(myFile);//Close the file
}

/*Count Parentheses*/
int countOpenParentheses(FILE *fp)
{
    char ch;
    int count=0;
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='(')
        {
            count=count+1;
        }
    }
    fseek(fp,0,SEEK_SET);
    return count;
}

int countCloseParentheses(FILE *fp)
{
    char ch;
    int count=0;
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch==')')
        {
            count=count+1;
        }
    }
    fseek(fp,0,SEEK_SET);
    return count;
}

/*Count square brackets*/
int countOpenSquareBrackets(FILE *fp)
{
    char ch;
    int count=0;
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='[')
        {
            count=count+1;
        }
    }
    fseek(fp,0,SEEK_SET);
    return count;
}

int countCloseSquareBrackets(FILE *fp)
{
    char ch;
    int count=0;
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch==']')
        {
            count=count+1;
        }
    }
    fseek(fp,0,SEEK_SET);
    return count;
}

/*Count braces*/
int countOpenBraces(FILE *fp)
{
    char ch;
    int count=0;
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='{')
        {
            count=count+1;
        }
    }
    fseek(fp,0,SEEK_SET);
    return count;
}

int countCloseBraces(FILE *fp)
{
    char ch;
    int count=0;
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='}')
        {
            count=count+1;
        }
    }
    fseek(fp,0,SEEK_SET);
    return count;
}

/*Syntax Checking*/
void SyntaxChecking(FILE *fp)
{
    int count1o=countOpenParentheses(fp);
    int count1c=countCloseParentheses(fp);
    int count2o=countOpenSquareBrackets(fp);
    int count2c=countCloseSquareBrackets(fp);
    int count3o=countOpenBraces(fp);
    int count3c=countCloseBraces(fp);
    
    /*Bracket Counting*/
    printf("The number of open parentheses is %d\n",count1o);
    printf("The number of close parentheses is %d\n",count1c);
    printf("The number of open square brackets is %d\n",count2o);
    printf("The number of close square brackets is %d\n",count2c);
    printf("The number of open braces is %d\n",count3o);
    printf("The number of close braces is %d\n",count3c);
    
    /*Bracket Validation*/
    if(count1o==count1c&&count2o==count2c&&count3o==count3c)
        printf("The expression is balanced\n");
    else
        printf("The expression is unbalanced\n");
    
    /*Detail Unbalanced Check*/
    if(count1o!=count1c)
        printf("Detail: The parentheses is unbalanced\n");
    if(count2o!=count2c)
        printf("Detail: The square brackets is unbalanced\n");
    if(count3o!=count3c)
        printf("Detail: The braces is unbalanced\n");
    
}

/*Syntax Validation*/
void SyntaxValidation(FILE *fp)
{
    char ch;
    char signList[10000];
    int length=0;
    char orderSignList[10000];
    
    /*Store the sign in the array list*/
    while((ch=fgetc(fp))!=EOF)
    {
        if(ch=='('||ch==')'||ch=='['||ch==']'||ch=='{'||ch=='}')
        {
            signList[length++]=ch;
        }
    }
    
    if(length%2!=0||signList[0]==')'||signList[0]==']'||signList[0]=='}')
    {
        printf("Incorrectly nested.");
        exit(1);
    }
    
    
    /*(Test)Display the detail content of sign list without text*/
    /*printf("The length of sign list(Exclude text) is:%d\n",length);
     printf("The content of sign list is :");
     for(int i=0;i<length;i++)
     {
     printf("%c",signList[i]);
     }
     printf("\n");*/
    
    
    /*Start to check syntax validation*/
    int countOrder=0;
    char temp;
    int judgement=0;//judgement=0 means not match, judgement=1 means match
    
    for(int j=0;j<length;j++)
    {
        /*Store the open bracket in new erray OrderSignList*/
        if(signList[j]=='('||signList[j]=='['||signList[j]=='{')
        {
            orderSignList[countOrder]=signList[j];
            countOrder++;//If have other nest, the orderSignList element will be replaced, and the first element of new nest will be put firstly.
        }
        /*Compare the close bracket with open brackets in OrderSignList*/
        if(signList[j]==')'||signList[j]==']'||signList[j]=='}')
        {
            /*Brackets choosing*/
            /*For ")" */
            if(signList[j]==')')
            {
                temp=orderSignList[countOrder-1];
                if(temp=='(')
                {
                    judgement=1;
                    countOrder--;//Shift to previous open bracket. And check the next close bracket.
                    continue;
                }
                else
                {
                    judgement=0;//Not match. Incorrectly nested
                    break;
                }
            }
            /*For "]" */
            if(signList[j]==']')
            {
                temp=orderSignList[countOrder-1];
                if(temp=='[')
                {
                    judgement=1;
                    countOrder--;
                    continue;
                }
                else
                {
                    judgement=0;
                    break;
                }
            }
            /*For "}" */
            if(signList[j]=='}')
            {
                temp=orderSignList[countOrder-1];
                if(temp=='{')
                {
                    judgement=1;
                    countOrder--;
                    continue;
                }
                else
                {
                    judgement=0;
                    break;
                }
            }
            
        }
    }
    //*Display the validation ouput*/
    if(judgement==1)
        printf("Correctly nested.\n");
    else
        printf("Incorrectly nested.\n");
    /*Set pointer to the start position*/
    fseek(fp,0,SEEK_SET);
    
    /*(Test)Display the orderSignList(Open brackets) and countOrder*/
    /*printf("The order sign list is");
     for(int i=0;i<length;i++)
     {
     printf("%c",orderSignList[i]);
     
     }
     printf("\n");
     printf("%d",countOrder);*/
    
}

/*Formatted Output*/
void Formatted(FILE *fp)
{
    int time=0;
    char ch;
    char temp=0;//previous byte
    int count=0;//count brackets
    int letter=0;//count letter
    while((ch=fgetc(fp))!=EOF)
    {
        /*Evaluate the open bracket*/
        if(ch=='('||ch=='['||ch=='{')
        {
            if(count!=0)
            {
                printf("\n");//Create a new line
            }
            for(int i=0;i<time;i++)
            {
                printf("  ");//Input double space(*time) to indent
            }
            time++;//time plus 1
            count++;
            printf("%c",ch);//print the bracket
            
        }
        
        /*Evaluate the letter*/
        if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||ch==' '||ch==34||ch=='.')
        {
            if(letter<3&&count==0)
            {
                printf("%c",ch);
                //If the firstly byte is not bracket, directly ouput the letter byte
            }
            else
            {
                fseek(fp,-2,SEEK_CUR);
                temp=fgetc(fp);//Check the previous byte
                if((temp>='a'&&temp<='z')||(temp>='A'&&temp<='Z')||temp==' '||temp==34||temp=='.'||temp==';')
                {
                    printf("%c",ch);
                    fseek(fp,1,SEEK_CUR);
                    //If the previous byte is letter(not \n or bracket), directly ouput this letter byte
                }
                else
                {
                    printf("\n");
                    for(int i=0;i<time;i++)
                    {
                        printf("  ");
                    }
                    //If the previous byte is \n or bracket, start a new line and indent by spaces
                    printf("%c",ch);
                    //Then output the letter byte
                    fseek(fp,1,SEEK_CUR);
                    //Set the pointer to location of ch
                }
            }
            count++;
            letter++;
        }
        
        /*Evaluate the ';' */
        if(ch==';')
        {
            if(letter<3&&count==0)
            {
                printf(";");
            }
            else
            {
                fseek(fp,-2,SEEK_CUR);
                temp=fgetc(fp);//Check the previous byte
                if(temp==')'||temp==']'||temp=='}')
                {
                    printf("\n");
                    for(int i=0;i<time;i++)
                    {
                        printf("  ");
                    }
                    printf("%c",ch);
                    fseek(fp,1,SEEK_CUR);
                    //If the previous byte is close bracket, create a new line, then ouput ';' and indent it
                }
                else
                {
                    printf("%c",ch);
                    //If the previous byte is not close bracket, ';' is equal to a letter byte, then directly output it
                    fseek(fp,1,SEEK_CUR);
                    //Set the pointer to location of ch
                }
 
            }
        }
        
        /*(Delete)Evaluate the space(Deleted because it is useless)*/
        /*(Delete)
        if(ch==' ')
        {
            printf(" ");
            count++;
            letter++;
        }(Delete)*/
        
        /*Evaluate \n operation*/
        if(ch=='\n')
        {
            if(letter<3&&count==0)
            {
                printf("\n");
                //If the firstly byte is not bracket, directly ouput the letter byte
            }
            else
            {
                fseek(fp,-2,SEEK_CUR);
                temp=fgetc(fp);//Check the previous byte
                if((temp>='a'&&temp<='z')||(temp>='A'&&temp<='Z')||temp==' '||temp==34||temp=='.')
                {
                    
                    fseek(fp,1,SEEK_CUR);//If previous byte is letter, do not start a new line(\n)
                }
                else
                {
                    printf("\n");
                    fseek(fp,1,SEEK_CUR);//If not, start a new line
                }
            }
            count++;
            letter++;
        }
        
        /*Evaluate the close bracket*/
        if(ch==')'||ch==']'||ch=='}')
        {
            if(count!=0)
            {
                printf("\n");//Create a new line
            }
            time--;
            for(int i=0;i<time;i++)
            {
                printf("  ");//Indent by times
            }
            printf("%c",ch);
            count++;
            
            
        }
        //This byte has been formatted,now start to formatt the next byte*/
    }
    /*Formatted finished, change a new line and set pointer to start position*/
    printf("\n");//Finished. Create a new line
    fseek(fp,0,SEEK_SET);//Set the pointer to start position
}
