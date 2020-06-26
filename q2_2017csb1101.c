#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int step_counter = 1;

// tape[] = n%r#r#..r$11..

//Will find the first one in
//the row and make it a
void find1(char tape[], int i)
{
    printf("Find 1\n");
    while (tape[i] != '#')
    {
        if (tape[i] == '$')
        {
            return;
        }
        if (tape[i] == '1')
        {
            printf("%d: %c -> a R\n", step_counter, tape[i]);
            tape[i] = 'a';
            step_counter++;
            return;
        }
        i++;
    }
    return;
}

//Will add 1 at the end
//of the matrix
void add1end(char tape[], int i)
{
    printf("Add 1 at end\n");
    while (tape[i] != '$')
    {
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        i++;
    }
    printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
    step_counter++;
    i++;
    while (tape[i] != '0')
    {
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        i++;
    }
    printf("%d: %c -> 1 L\n", step_counter, tape[i]);
    step_counter++;
    tape[i] = '1';
    i--;
    //return
    printf("Going back\n");
    while (tape[i] != 'x')
    {
        printf("%d: %c -> %c L\n", step_counter, tape[i], tape[i]);
        step_counter++;
        i--;
    }
    printf("%d: %c -> a R\n", step_counter, tape[i]);
    tape[i] = 'a';
    step_counter++;
    i++;
}

//Will fetch the next row
int getnextrow(char tape[], int i)
{
    printf("Get next row\n");
    while (tape[i] != '#')
    {
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        if (tape[i] == '$')
        {
            return -1;
        }
        i++;
    }
    printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
    step_counter++;
    i++;
    return i;
}

//Will reset the tape
//with respective 1s and 0s
void reset(char tape[])
{
    printf("Reset\n");
    int i = 0;
    while (tape[i] != '$')
    {
        if ((tape[i] == 'a') || (tape[i] == 'b') || (tape[i] == 'x'))
        {
            printf("%d: %c -> 1 R\n", step_counter, tape[i]);
            step_counter++;
            tape[i] = '1';
        }
        else
        {
            printf("%d: %c -> %c L\n", step_counter, tape[i], tape[i]);
            step_counter++;
        }
        i++;
    }
}

//Will point at the start
//of the matrix
int atstart(char tape[])
{
    printf("At start\n");
    int i = 0;
    while (tape[i] != '%')
    {
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        i++;
    }
    printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
    step_counter++;
    i++;
    return i;
}

//Will find if the global 1
//exist in the matrix
int globalfind1(char tape[], int i)
{
    printf("Globat find 1\n");
    while (tape[i] != '$')
    {
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        if (tape[i] == '1')
        {
            printf("%d: %c -> %c L\n", step_counter, tape[i + 1], tape[i + 1]);
            step_counter++;
            return i;
        }
        i++;
    }
    return -1;
}

//Will print the result
void complete(char tape[], int flag)
{
    printf("\nComplete string\n");
    int i = 0;
    while (tape[i] != '$')
    {
        printf("%c", tape[i]);
        i++;
    }
    printf("%c", tape[i]);
    i++;
    if (tape[i] != '1')
    {
        printf("0");
    }
    while (tape[i] == '1')
    {
        printf("%c", tape[i]);
        i++;
    }
    if(flag == 1)
    {
        printf("%c", tape[i]);
    }
    printf("\n\n");
}

int unarytobinary(char tape[])
{
    int i = 0;
    while (tape[i] != '$')
    {
        i++;
    }
    i++;
    int index = i;
    int count = 0;
    while (tape[i] == '1')
    {
        tape[i] = '0';
        count++;
        i++;
    }
    int num[32];
    tape[index] = '0';
    int flag = 0;
    if(!(count & 1))
    {
        flag = 1;
    }
    for (i = 0; count > 0; i++)
    {
        num[i] = count % 2;
        count = count / 2;
    }
    for (i = i - 1; i >= 0; i--)
    {
        if (num[i] == 1)
        {
            tape[index] = '1';
        }
        else if (num[i] == 0)
        {
            tape[index] = '0';
        }
        index++;
    }
    if(flag == 1)
    {
        tape[index] = '0';
    }
    return flag;
}

int main()
{
    // char temp[] = "10#10#11";
    char temp[200];
    printf("Please provide input\n");
    scanf("%s", temp);
    
    char tape[200];
    for (int i = 0; i < 200; i++)
    {
        tape[i] = '0';
    }
    int i;
    int size = strlen(temp);
    for (i = 0; i < size; i++)
    {
        tape[i] = temp[i];
    }
    tape[size] = '$'; //ending point
    i = 0;
    while (tape[i] != '#')
    {
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        i++;
    }
    tape[i] = '%'; //starting point
    printf("%d: # -> %c R\n", step_counter, tape[i]);
    step_counter++;
    int point = 1;
    int start;
    int first1;
    int row;
    // complete(tape);
    while (point)
    {
        start = atstart(tape);
        first1 = globalfind1(tape, start);
        if (first1 != -1) //1 found at some row
        {
            printf("%d: %c -> x R\n", step_counter, tape[first1]);
            step_counter++;
            tape[first1] = 'x';
            add1end(tape, first1 + 1);
            row = getnextrow(tape, first1);
            while (row != -1)
            {
                find1(tape, row);
                row = getnextrow(tape, row);
            }
        }
        else
        {
            point = 0;
            reset(tape);
            int flag = unarytobinary(tape);
            complete(tape, flag);
        }
    }
}