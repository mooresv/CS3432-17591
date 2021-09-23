int main() 
{
    unsigned int i, j; 
    int a[100], b[50];
    unsinged int n = 100, m = 50;

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) 
            if (a[i] == b[j])
                goto found;
    return(-1);

found: return(0);
}
        
    
