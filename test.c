
int test(int n,...)
{
    int result;
    int * p = (int *) (&n);
    int number;

    for(int i =0; i < n; i++){
        number = *((int*) p);
        p += sizeof (int);
    }
    result = *((int *) p);
    // p = NULL;
    return result;
    
}