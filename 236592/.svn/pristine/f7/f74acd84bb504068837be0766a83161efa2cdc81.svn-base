#include<stdarg.h>
#include<unistd.h>
#include<stdlib.h>
#include"mylib.h"

int myscanf(char str[], ...)
{
    int i, j, result = 0;
    va_list valist;
    char temp[200];
    char buff[1];
    int tempInt;

    va_start(valist, str);
    for(i = 0; str[i] != '\0'; i++){
        if(str[i] == '%'){
            i++;
            for(j=0; !isWhite(buff[0]); j++){
                if(read(STDIN, buff, 1) < 0){
                    va_end(valist);
                    return -1;
                }
                temp[j] = buff[0];
            }
            j--;
            temp[j] = '\0';
            result += j;
            switch(str[i]){
                case (int) 's' :
                    mystrcpy(va_arg(valist, char*), temp);
                    break;
                case (int) 'd' :
                    (*va_arg(valist, int *)) =  myatoi(temp, 10);
                    break;
                case (int) 'x' :
                    if(temp[0] == '0' && temp[1] =='x')
                        (*va_arg(valist, int *)) =  myatoi(temp + 2, 16);
                    else                
                        (*va_arg(valist, int *)) =  myatoi(temp, 16);
                    break;
                case (int) 'b' :
                    if(temp[0] == '0' && temp[1] =='b')
                        (*va_arg(valist, int *)) =  myatoi(temp + 2, 2);
                    else
                        (*va_arg(valist, int *)) =  myatoi(temp, 2);
                    break;              
                default:
                    return -1;
            }
        }
    }

    while(buff[0] != '\n')
        read(STDIN, buff, 1);
    

    va_end(valist);
    return result;

    

}