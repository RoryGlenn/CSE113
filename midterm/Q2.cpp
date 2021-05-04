void mut_excl(int me /* 0 or 1 */) 
{
    static int loser;
    static int interested[2] = {0, 0};
    int other; /* local variable */
   
    other = 1 - me;
    interested[me] = 1;
    loser = me;
    while (loser == me && interested[other]) { }

    /* critical section */
    interested[me] = 0;
}




void lock()
{
    int i = threadid.get();
    int j = l - i;
    bool flag[i] = true;
    int victim = i;
    
    while ( flag[j] && victim == i ) 
    {

    }

}

void unlock()
{
    int i = threadid.get();
    flag[i] = false;
}





int main()
{

}
