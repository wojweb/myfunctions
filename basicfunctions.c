//Number functions
int mypow(int numb, int n){
    int result = 1;
    for(int i=0; i < n; i++)
        result *= numb;
    return result;
}

//Char functions
int isInNumberSystem(char c, int base){
    if((base <= 10 && (c >= '0' && c < '0' + base))   ||
        (base > 10 && ((c >= '0' && c<= '9') ||(c >= 'A' && c < 'A' + base - 10) )))
        return 1;
    else
        return 0;
}
int isWhite(char c)
{
    if(c == ' ' || c == '\n' || c == '\t')
        return 1;
    else
        return 0;
}

//String functions
int mystrlen(char s[]){
    int i;
    for(i =  0; s[i] != '\0'; i++)
        ;
    return i;
}

int mystrcpy(char s1[], char s2[]){
    int i;
    int s1len = sizeof(s1);
    for(i = 0; s2[i] != '\0'; i++){
        if(i == s1len){
            i = -1;
            break;
        }
        s1[i] = s2[i];
    }
    s1[i] = '\0';
    return i;
}

void myputIn(char * str1, char* str2){
    for(int i = 0; i < mystrlen(str2); i++)
        str1[i] = str2[i];
}


//Model on K&R implementation
void myreverse(char s[])
{
    int i, j;
    char c;

    for(i = 0, j = mystrlen(s) - 1; i < j; i++, j--){
        c = s[j];
        s[j] = s[i];
        s[i] = c;    
    }
}

void myitoa(int n, int base, char s[])
{
    int i, sign, numb;
    if((sign = n) < 0)
        n = -n;
    i = 0;
    do{ //generate digits in reverse order
        numb = (n % base);
        if(numb < 10)
            s[i++] = numb + '0';
        else
            s[i++] = numb -10 + 'A'; 
    } while((n /= base) > 0);
    if(sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    myreverse(s);
}

int myatoi(char s[], int base)
{
    int i, sign, sum;
    i = 0;
    sign = 1;
    if(s[i] =='-'){
        sign = -1;
        i++;
    }
    sum = 0;
    for(i; i < mystrlen(s); i++){
        if(!isInNumberSystem(s[i], base))
            return 0;
        sum*=base;
        if(s[i] <='9')
            sum+= s[i] - '0';
        else
            sum += s[i] - 'A' + 10;
    }
    return sum * sign;
    
    
}

