    /* (   (
   (    )\ ))
   )\  (()/(   (             )
 (((_)  /(_)) ))\   (     ( /(  (
 )\___ (_))  /((_)  )\ )  )(_)) )\
((/ __||_ _|(_))(  _(_/( ((_)_ ((_)
 | (__  | | | || || ' \))/ _` |(_-<
  \___||___| \_,_||_||_| \__,_|/__/ 05/02/2015*/

#include <iostream>
#include <stdlib.h>
#include<conio.h>
#include<windows.h>
#include "Cellular_Header.h"

using namespace std;


//Main function to implement Cellular Automata
int proceed()
{
    int i;
    int j;
    int k = 7;
    int l = 0;
    char disChar1;
    char disChar2;
    unsigned int decVal = 0;
    const int RULES = 8;
    const int SIZE = 79;
    const int ITTERERATIONS = 33;
    int conditions[RULES];
    int *currentState = (int*) malloc (SIZE* sizeof(int));
    int *nextState = (int*) malloc (SIZE* sizeof(int));

    if(currentState == NULL)
    {
        cout<<"Out of memory";
        exit(1);
    }

    cout<<"\tPress 1 to  start Cellular Automata or another number to exit: ";
    cin>>j;

    if(j == 1)
    {
        cout<<"\t\tPress 1 to enter a RULE or 2 to create a RULE: ";
        cin>>j;
        cout<<"\t\t\tChoose your 2 display Characters"<<endl;
        cout<< "\t\t\t\tCharacter 1: ";
        cin>>disChar1;
        cout<<"\t\t\t\tCharacter 2: ";
        cin>>disChar2;

        while(j == 1)
        {
            initialiseArray(currentState, nextState, SIZE);
            cout<<"\t\t\tChoose your rule from 0 to 255: ";
            cin>>decVal;

            if(decVal <= 255 && decVal >= 0)
            {
                decimal2Binary(conditions, decVal, RULES);
                clearScreen();
                cout<<"\t\t\t\tRule Number: "<<decVal<<endl;
                textColour(k);
                printDesign(currentState, SIZE , disChar1, disChar2);

                for(i=0; i<ITTERERATIONS; i++)                                             //Function calls
                {
                    updateArray(currentState, nextState, conditions, SIZE);
                    k = copyArray(currentState, nextState, SIZE, l);
                    l++;
                    textColour(k);
                    printDesign(currentState, SIZE, disChar1, disChar2);
                }
                textColour(7);
                cout<<endl<<"\t\tPress 1 to re-enter RULE or any other number to exit:";
                cin>>j;
            }
            else
            {
                cout<<"Rule Does Not Exist";
                return 0;
            }

            if(j != 1)
            {
                cout<<"\t\t\t\tExiting";
                return 0;
            }
        }

        while(j == 2)
        {
            initialiseArray(currentState, nextState, SIZE);
            cout<<"\t\t\tEnter your 8 conditions MSB first"<<endl;

            for(i=0; i<RULES; i++)                                                     //Scan in conditions
            {
                cout<<"\t\t\t\tCondition"<<i+1;
                cout <<": ";
                cin>>conditions[i];

                if(conditions[i] != 1  &&  conditions[i] != 0)
                {
                    cout<<"\t\t\tUnreconised condition re-type"<<endl;
                    i--;
                }
            }

            clearScreen();
            cout<<"\t\t\tYour Rules are: ";

            for(i=0; i<RULES; i++)
            {
                cout<<conditions[i];
            }

            cout<<endl;
            textColour(k);
            printDesign(currentState, SIZE, disChar1, disChar2);

            for(i=0; i<ITTERERATIONS; i++)                                             //Function calls
            {
                updateArray(currentState, nextState, conditions, SIZE);
                k = copyArray(currentState, nextState, SIZE, l);
                l++;
                textColour(k);
                printDesign(currentState, SIZE, disChar1, disChar2);
            }

            textColour(7);
            cout<<endl<<"\tPress 2 to re-enter conditions or any other number to exit:";
            cin>>j;

            if(j != 2)
            {
                cout<<"\t\t\t\tExiting";
                return 0;
            }
        }
    }

    else if(j != 1 && j == 2)
    {
        cout<<"\t\t\t\tExiting:"<<endl;
    }
    else
    {
        cout<<"\t\t\tUnrecognised Entry Exiting"<<endl;
    }

    free(currentState);
    free(nextState);

    return 0;
}

//Function  to print an Array
void printDesign(int *currentState, int SIZE, char disChar1, char disChar2)
{
    int i;

    for(i=0; i<SIZE; i++)
    {
        if(currentState[i] == 1)
            cout <<disChar1;

        else
            cout<<disChar2;
    }

    cout<<endl;
}

//Function to alter value of Array depending on condition set
void updateArray(int *currentstate, int *nextState, int *conditions, int SIZE)
{
    int i = 0;
    int j;
    j = SIZE-1;

    if(currentstate[j] == 1 && currentstate[i] == 1 && currentstate[i+1] == 1)
    {
        nextState[i] = conditions[0];
    }
    else if(currentstate[j] == 1 && currentstate[i] == 1 && currentstate[i+1] == 0)
    {
        nextState[i] = conditions[1];
    }
    else if(currentstate[j] == 1 && currentstate[i] == 0 && currentstate[i+1] == 1)
    {
        nextState[i] = conditions[2];
    }
    else if(currentstate[j] == 1 && currentstate[i] == 0 && currentstate[i+1] == 0)
    {
        nextState[i] = conditions[3];
    }
    else if(currentstate[j] == 0 && currentstate[i] == 1 && currentstate[i+1] == 1)
    {
        nextState[i] = conditions[4];
    }
    else if(currentstate[j] == 0 && currentstate[i] == 1 && currentstate[i+1] == 0)
    {
        nextState[i] = conditions[5];
    }
    else if(currentstate[j] == 0 && currentstate[i] == 0 && currentstate[i+1] == 1)
    {
        nextState[i] = conditions[6];
    }
    else if(currentstate[j] == 0 && currentstate[i] == 0 && currentstate[i+1] == 0)
    {
        nextState[i] = conditions[7];
    }

    if(currentstate[j-1] == 1 && currentstate[j] == 1 && currentstate[i] == 1)
    {
        nextState[i] = conditions[0];
    }
    else if(currentstate[j-1] == 1 && currentstate[j] == 1 && currentstate[i] == 0)
    {
        nextState[j] = conditions[1];
    }
    else if(currentstate[j-1] == 1 && currentstate[j] == 0 && currentstate[i] == 1)
    {
        nextState[j] = conditions[2];
    }
    else if(currentstate[j-1] == 1 && currentstate[j] == 0 && currentstate[i] == 0)
    {
        nextState[j] = conditions[3];
    }
    else if(currentstate[j-1] == 0 && currentstate[j] == 1 && currentstate[i] == 1)
    {
        nextState[j] = conditions[4];
    }
    else if(currentstate[j-1] == 0 && currentstate[j] == 1 && currentstate[i] == 0)
    {
        nextState[j] = conditions[5];
    }
    else if(currentstate[j-1] == 0 && currentstate[j] == 0 && currentstate[i] == 1)
    {
        nextState[j] = conditions[6];
    }
    else if(currentstate[j-1] == 0 && currentstate[j] == 0 && currentstate[i] == 0)
    {
        nextState[j] = conditions[7];
    }

    for(i=1; i<SIZE-1; i++)
    {
        if(currentstate[i-1] == 1 && currentstate[i] == 1 && currentstate[i+1] == 1)
        {
            nextState[i] = conditions[0];
        }
        else if(currentstate[i-1] == 1 && currentstate[i] == 1 && currentstate[i+1] == 0)
        {
            nextState[i] = conditions[1];
        }
        else if(currentstate[i-1] == 1 && currentstate[i] == 0 && currentstate[i+1] == 1)
        {
            nextState[i] = conditions[2];
        }
        else if(currentstate[i-1] == 1 && currentstate[i] == 0 && currentstate[i+1] == 0)
        {
            nextState[i] = conditions[3];
        }
        else if(currentstate[i-1] == 0 && currentstate[i] == 1 && currentstate[i+1] == 1)
        {
            nextState[i] = conditions[4];
        }
        else if(currentstate[i-1] == 0 && currentstate[i] == 1 && currentstate[i+1] == 0)
        {
            nextState[i] = conditions[5];
        }
        else if(currentstate[i-1] == 0 && currentstate[i] == 0 && currentstate[i+1] == 1)
        {
            nextState[i] = conditions[6];
        }
        else if(currentstate[i-1] == 0 && currentstate[i] == 0 && currentstate[i+1] == 0)
        {
            nextState[i] = conditions[7];
        }
    }
}

//Function to copy one Array into another Array
int copyArray(int *currentSate, int *nextState, int SIZE, int l)
{
    int i;
    int k = 0;
    int j = 0;

    for(i=0; i<SIZE; i++)
    {
        currentSate[i] = nextState[i];
        if(currentSate[i] == 0)
            k++;
        else
            j++;
    }

    if(l%2 == 0)
    {
        k = ((k%15)+1);
    }
    else
    {
        j = ((j%15)+1);
        k = j;
    }

    return k;
}

//Function to Initialise all elements of Array  to 0, except central element which is 1
void initialiseArray(int *currentState, int *nextState, int SIZE)
{
    int i,j;

    for(i=0; i<SIZE; i++)
    {
        currentState[i] = 0;
        nextState[i] = 0;
    }

    j = int (SIZE/2);
    currentState[j] = 1;
}

//Function to convert Decimal to Binary
void decimal2Binary(int *conditions ,int decVal, int RULES)
{
    int i;

    for(i=RULES-1; i>=0; i--)
    {
        conditions[i] = decVal%2;
        decVal = decVal/2;
    }
}

//Function to change the colour of terminal output
void textColour(int colour)
{
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hCon, colour);
}

//Function to clear screen on Windows console
void clearScreen()
{
  DWORD n;
  DWORD size;
  COORD coord = {0};
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  HANDLE h = GetStdHandle (STD_OUTPUT_HANDLE);
  GetConsoleScreenBufferInfo (h, &csbi);
  size = csbi.dwSize.X * csbi.dwSize.Y;
  FillConsoleOutputCharacter (h, TEXT ( ' ' ), size, coord, &n);
  GetConsoleScreenBufferInfo (h, &csbi);
  FillConsoleOutputAttribute (h, csbi.wAttributes, size, coord, &n);
  SetConsoleCursorPosition (h, coord);
}
