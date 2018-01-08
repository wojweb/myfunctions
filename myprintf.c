#include<stdarg.h> //va_start. va_argv, va_list, va_end
#include<unistd.h> //write
#include<stdlib.h> //malloc, free etc"

#include"mylib.h"

int myprintf(char str[], ...)
{
    int i, j;
    char temp[100]; // maksymalna dlugosc liczby
    int tempNumb;
    va_list valist;
    // char *p;
    char *strToPrintf =(char*) malloc(mystrlen(str) + 100);

    if(strToPrintf == NULL){
        exit(0);
    }
 
    /* inistalize valist for num number of argument */
    va_start(valist, str);
    // p = (char*) (&str + sizeof str);

    for(i = 0, j = 0; str[i] != '\0'; i++){
        if(str[i] == '%'){
            i++;
            switch((int) str[i]){
                case (int) 'd': 
                    tempNumb = va_arg(valist, int);
                    // tempNumb = *((int *)p);
                    // p += sizeof (int);
                    myitoa(tempNumb, 10, temp);
                    break;
                case (int) 'x':
                    temp[0] = '0';
                    temp[1] = 'x';
                    // tempNumb = va_arg(valist, int);
                    tempNumb = *((int *)p);
                    p += sizeof(int);
                    myitoa(tempNumb, 16, temp + 2);
                    break;
                case (int) 'b': 
                    temp[0] = '0';
                    temp[1] = 'b';
                    tempNumb = va_arg(valist, int);
                    // tempNumb = *((int *)p);
                    // p += sizeof(int);
                    myitoa(tempNumb, 2, temp + 2);
                    break;
                case (int) 's':
                    tempNumb = mystrcpy(temp, va_arg(valist, char*));
                    // tempNumb = mystrcpy(temp, *((int *)p));
                    // p += sizeof temp;
                    if(tempNumb == -1)
                        return -1;
                    break;   
                default :
                    return -1;  
            }
            myputIn(strToPrintf + j, temp);
            j+= mystrlen(temp);
            
        }
        else{
            strToPrintf[j++] = str[i];
        }
    }
    strToPrintf[j] = '\0';

    i = write(STDOUT, strToPrintf,mystrlen(strToPrintf));
    // clean memory reserved for valist
    va_end(valist);
    // p = NULL;
    //clean memory of table
    free(strToPrintf);

    return i;
}