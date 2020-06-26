#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tape[] = x#y$(y')^

int step_counter = 1;

//  This function will find the first 1
//  now present in x
int find1(char tape[], int n)
{
    printf("Finding first 1\n");
    int i = 0;
    while (tape[i] != '#')
    {
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        if (tape[i] == '0')
        {
            i++;
        }
        else if (tape[i] == '1')
        {
            return i;
        }
    }
    return -1;
}

//  This function will show remainder
void showoutput(char tape[])
{
    int i = 0;
    while (tape[i] != '#')
    {
        printf("%c", tape[i]);
        i++;
    }
    printf("\n");
}

//  This function will check if enough bits
//  are present for the long division
int checkbits(char tape[], int first1, int n)
{
    printf("Checking for %d bits\n", n);
    int i = first1;
    int count = 1;
    while (tape[i] != '#' && count < n + 1)
    {
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        count++;
        i++;
    }

    if (count == n + 1)
    {
        return 1;
    }
    return -1;
}

//return the position of first 1/0 in y
//if not present will return -1
int moveright(char tape[], int i)
{
    printf("Moving Right\n");
    while (tape[i] != '#')
    {
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        i++;
    }
    printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
    step_counter++;
    i++;
    while (tape[i] != '$')
    {
        if (tape[i] == '0')
        {
            printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
            step_counter++;
            printf("%d: %c -> %c L\n", step_counter, tape[i + 1], tape[i + 1]);
            step_counter++;
            return i;
        }
        else if (tape[i] == '1')
        {
            printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
            step_counter++;
            printf("%d: %c -> %c L\n", step_counter, tape[i + 1], tape[i + 1]);
            step_counter++;
            return i;
        }
        else
        {
            printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
            step_counter++;
            i++;
        }
    }
    return -1;
}

//return the position of first 1/0 in x
//if not present will return -1
int moveleft(char tape[], int i)
{
    printf("Moving Left\n");
    while (tape[i] != '#')
    {
        printf("%d: %c -> %c L\n", step_counter, tape[i], tape[i]);
        step_counter++;
        i--;
    }
    printf("%d: %c -> %c L\n", step_counter, tape[i], tape[i]);
    step_counter++;
    i--;
    while (i >= 0)
    {
        if (tape[i] == 'a')
        {
            printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
            step_counter++;
            return i + 1;
        }
        else if (tape[i] == 'b')
        {
            printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
            step_counter++;
            return i + 1;
        }
        else
        {
            printf("%d: %c -> %c L\n", step_counter, tape[i], tape[i]);
            step_counter++;
            i--;
        }
    }
    return -1;
}

//resets whole tape
void resetvalue(char tape[], int i)
{
    printf("Resetting Values\n");
    while (i >= 0)
    {
        if (tape[i] == 'a')
        {
            printf("%d: %c -> 1 L\n", step_counter, tape[i]);
            step_counter++;
            tape[i] = '1';
        }
        else if (tape[i] == 'b')
        {
            printf("%d: %c -> 0 L\n", step_counter, tape[i]);
            step_counter++;
            tape[i] = '0';
        }
        else
        {
            printf("%d: %c -> %c L\n", step_counter, tape[i], tape[i]);
            step_counter++;
        }
        i--;
    }
}

//compare x[i] with y[i]
int compareval(char tape[], int n, int first1)
{
    int flag = 0;
    int count = 0;
    int value = 0;
    while (flag == 0 && count < n)
    {
        count++;
        if (tape[first1] != '#')
        {
            flag = 0;
            printf("Checking inital x[i]\n");
            if (tape[first1] == '1')
            {
                printf("%d: %c -> a R\n", step_counter, tape[first1]);
                step_counter++;
                tape[first1] = 'a';
            }
            else if (tape[first1] == '0')
            {
                printf("%d: %c -> b R\n", step_counter, tape[first1]);
                step_counter++;
                tape[first1] = 'b';
            }

            value = moveright(tape, first1 + 1);
            printf("Comparing Values\n");
            if (tape[value] == '0')
            {
                printf("%d: %c -> b L\n", step_counter, tape[value]);
                step_counter++;
                tape[value] = 'b';
                if (tape[first1] == 'a') //x > y
                {
                    printf("x > y\n");
                    flag = 1;
                }
                else if (tape[first1] == 'b') //x[i] == y[i]
                {
                    flag = 0;
                }
            }
            else if (tape[value] == '1')
            {
                printf("%d: %c -> a L\n", step_counter, tape[value]);
                step_counter++;
                tape[value] = 'a';
                if (tape[first1] == 'a') //x[i] == y[i]
                {
                    flag = 0;
                }
                else if (tape[first1] == 'b') //x < y
                {
                    printf("x < y\n");
                    flag = 2;
                }
            }
            if (flag == 0)
            {
                first1 = moveleft(tape, value - 1);
            }
            else
            {
                resetvalue(tape, value);
                return flag;
            }
        }
        else
        {
            resetvalue(tape, value);
            break;
        }
    }
    printf("x = y\n");
    resetvalue(tape, value);
    return 0;
}

//fetch the value of respective complement point
int complementright(char tape[], int i)
{
    printf("Complement Right\n");
    while (tape[i] != '$')
    {
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        i++;
    }
    printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
    step_counter++;
    i++;
    while (tape[i] != '^')
    {
        if (tape[i] == 'z')
        {
            printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
            step_counter++;
            printf("%d: %c -> %c L\n", step_counter, tape[i + 1], tape[i + 1]);
            step_counter++;
            return i;
        }
        else
        {
            printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
            step_counter++;
            i++;
        }
    }
    return -1;
}

//fetch the value of next complement point
int complementleft(char tape[], int i)
{
    printf("Complement Left\n");
    while (tape[i] != '$')
    {
        printf("%d: %c -> %c L\n", step_counter, tape[i], tape[i]);
        step_counter++;
        i--;
    }
    printf("%d: %c -> %c L\n", step_counter, tape[i], tape[i]);
    step_counter++;
    i--;
    while (tape[i] != '#')
    {
        if (tape[i] == 'a')
        {
            printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
            step_counter++;
            return i + 1;
        }
        else if (tape[i] == 'b')
        {
            printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
            step_counter++;
            return i + 1;
        }
        else
        {
            printf("%d: %c -> %c L\n", step_counter, tape[i], tape[i]);
            step_counter++;
            i--;
        }
    }
    return -1;
}

//computes and add value at the end
//2s complement of y
void computecomplement(char tape[])
{
    printf("Computing complement\n");
    int i = 0;
    while (tape[i] != '#')
    {
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        i++;
    }
    printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
    step_counter++;
    i++;
    int index;
    while (tape[i] != '$')
    {
        if (tape[i] == '1')
        {
            printf("%d: %c -> a R\n", step_counter, tape[i]);
            step_counter++;
            tape[i] = 'a';
        }
        else if (tape[i] == '0')
        {
            printf("%d: %c -> b R\n", step_counter, tape[i]);
            step_counter++;
            tape[i] = 'b';
        }
        index = complementright(tape, i + 1);
        if (tape[i] == 'a')
        {
            printf("%d: %c -> 1 R\n", step_counter, tape[index]);
            step_counter++;
            tape[index] = '1';
        }
        else if (tape[i] == 'b')
        {
            printf("%d: %c -> 0 R\n", step_counter, tape[index]);
            step_counter++;
            tape[index] = '0';
        }
        i++;
    }
    printf("%d: %c -> %c L\n", step_counter, tape[index + 1], tape[index + 1]);
    step_counter++;
    resetvalue(tape, i);
}

//highlight the area where operations
//are to be performed
void highlightarea(char tape[], int first1, int n)
{
    printf("Highlighting area\n");
    for (int i = first1; i < first1 + n; i++)
    {
        if (tape[i] == '1')
        {
            printf("%d: %c -> a R\n", step_counter, tape[i]);
            step_counter++;
            tape[i] = 'a';
        }
        else if (tape[i] == '0')
        {
            printf("%d: %c -> b R\n", step_counter, tape[i]);
            step_counter++;
            tape[i] = 'b';
        }
    }
}

//make all 0s 1 until a 1 is found
//which is converted to 0
void until1(char tape[], int i)
{
    printf("Until 1\n");
    while (tape[i] != 'a' && i >= 0)
    {
        printf("%d: %c -> a L\n", step_counter, tape[i]);
        step_counter++;
        tape[i] = 'a';
        i--;
    }
    if (i >= -1)
    {
        printf("%d: %c -> b R\n", step_counter, tape[i]);
        tape[i] = 'b';
    }
    i++;
    step_counter++;
    while (tape[i] == 'a')
    {
        printf("%d: %c -> b R\n", step_counter, tape[i]);
        step_counter++;
        i++;
    }
}

//find respective point for subtraction
//in y'
int subright(char tape[])
{
    printf("Finding right point\n");
    int i = 0;
    while (tape[i] != 'z')
    {
        if (tape[i] == '^')
        {
            printf("%d: %c -> %c L\n", step_counter, tape[i], tape[i]);
            step_counter++;
            i--;
            printf("Found at %d\n", i);
            return i;
        }
        printf("%d: %c -> %c R\n", step_counter, tape[i], tape[i]);
        step_counter++;
        i++;
    }
    printf("%d: %c -> %c L\n", step_counter, tape[i], tape[i]);
    step_counter++;
    i--;
    printf("Found at %d\n", i);
    return i;
}

//subtract y' from x
void subtract(char tape[], int index, int n, int d)
{
    printf("Subtraction\n");
    int i = index + n + d - 1;
    printf("Tape %c,  %d\n", tape[i], i);
    int point;
    while (i >= index + d)
    {
        point = subright(tape);
        if (tape[point] == '1')
        {
            printf("Point 1, tape %c\n", tape[i]);
            if (tape[i] == 'a')
            {
                printf("1 a\n");
                tape[point] = 'z';
                printf("%d: %c -> 0 L\n", step_counter, tape[i]);
                tape[i] = '0';
                step_counter++;
            }
            else if (tape[i] == 'b')
            {
                printf("1 b\n");
                tape[point] = 'z';
                printf("%d: %c -> 1 L\n", step_counter, tape[i]);
                tape[i] = '1';
                step_counter++;
                until1(tape, i - 1);
            }
        }
        else if (tape[point] == '0')
        {
            printf("Point 0, tape %c\n", tape[i]);
            if (tape[i] == 'a')
            {
                printf("0 a\n");
                tape[point] = 'z';
                printf("%d: %c -> 1 L\n", step_counter, tape[i]);
                tape[i] = '1';
                step_counter++;
            }
            else if (tape[i] == 'b')
            {
                printf("0 b\n");
                tape[point] = 'z';
                printf("%d: %c -> 0 L\n", step_counter, tape[i]);
                tape[i] = '0';
                step_counter++;
            }
        }
        i--;
    }
    resetvalue(tape, index + n + d - 1);
}

//check complete area
void complete(char tape[])
{
    int i = 0;
    printf("\nCheck\n");
    while (tape[i] != '^')
    {
        printf("%c", tape[i]);
        i++;
    }
    printf("^\n\n");
}

int main()
{
    // char temp[] = "11#10";
    char temp[200];
    printf("Please provide input\n");
    scanf("%s", temp);

    char tape[500];
    for (int i = 0; i < 500; i++)
    {
        tape[i] = 'z';
    }
    int i;
    int size = strlen(temp);
    for (i = 0; i < size; i++)
    {
        tape[i] = temp[i];
    }
    tape[size] = '$';
    int n = 0;
    int start = 0, end = 0;
    for (i = 0; i < 500; i++)
    {
        if (tape[i] == '#')
        {
            start = i;
        }
        if (tape[i] == '$')
        {
            end = i;
            break;
        }
    }
    n = end - start - 1;
    tape[size + n + 1] = '^';
    int first1 = 0;
    int point = 1;
    while (point)
    {
        first1 = find1(tape, n);
        if (first1 == -1)
        {
            point = 0;
            printf("Remainder!!\n");
            showoutput(tape);
        }
        else
        {
            int bits = checkbits(tape, first1, n);
            if (bits == 1) //enough bits are present
            {
                int compare = 1;
                compare = compareval(tape, n, first1);
                //compare == 0 take equal value
                if (compare == 0)
                {
                    printf("Subtracting value x = y\n");
                    for (i = first1; i < first1 + n; i++)
                    {
                        printf("%d: %c -> 0 R\n", step_counter, tape[i]);
                        tape[i] = '0';
                        step_counter++;
                    }
                    // complete(tape);
                }
                //compate == 1 x > y
                if (compare == 1)
                {
                    computecomplement(tape);
                    printf("Subtracting value x > y\n");
                    highlightarea(tape, first1, n);
                    subtract(tape, first1, n, 0);
                    // complete(tape);
                }
                //compare == 2 x < y
                if (compare == 2)
                {
                    int n1bits = checkbits(tape, first1, n + 1);
                    if (n1bits == -1)   //n+1 bits not present
                    {
                        point = 0;
                        printf("Remainder!!\n");
                        showoutput(tape);
                    }
                    else                //n+1 bits present
                    {
                        computecomplement(tape);
                        printf("Subtracting value x > y\n");
                        highlightarea(tape, first1, n + 1);
                        subtract(tape, first1, n, 1);
                        // complete(tape);
                    }
                }
            }
            else //remainder
            {
                point = 0;
                printf("Remainder!!\n");
                showoutput(tape);
            }
        }
    }
}