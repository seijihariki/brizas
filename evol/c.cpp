#include <stdio.h>  
#include <stdlib.h>

int main()
{
    int m, n, k, b, d, e, x, e1, e2,o;
    char c, N, S, L, O, B, A, y, z, c1, c2;

    m = 50;
    n = -50;/*(m,n)*/

    scanf("%d", &k);

    for (b = 1; b <= k; b++)
    {
        scanf("%d %c",&d,&c);

        if (c == 'N')
            m = m + d;

        if (c == 'S')
            m = m - d;

        if (c == 'L')
            n = n + d;

        if (c == 'O')
            n = n - d;
    
        if (n > 180)
            n = n - 360;

        if (n < -180)
            n = n + 360;
        
        if (m > 180)
            m = m - 360;

        if (m < -180)
            m = m + 360;
        
        if (m > 90 && n < 0)
        {
            n = n * -1;
            n = 180 - n;
            m = 180 - m;
        }
        
        if(m > 90 && n > 0)
        {
            n = n - 180;
            m = 180 - m;
        }
        
        if(m < -90 && n < 0)
        {
            n = n * -1;
            n = 180 - n;
            m = 180 - m;
        }
        
        if(m < -90 && n > 0)
        {
            n = n - 180;
            m = 180 - m;
        }
        
        if(m > 90){
		
            m = 180 - m;
    }
        //if(n>90){
        //n=180-n;}
        
        if(m < -90){
		
            m = -180 - m;
}
        //if(n<-90){
       // n=-180-n;}
    }
    
    scanf("%d", &e);
    for(o = 1; o <= e; o++)
    {
        scanf("%d %c %d %c", &e1, &c1, &e2, &c2);
     
        if(m > 0 && n > 0)
        {
            y = 'N';
            x = 'L';
        }
        
        if(m < 0 && n < 0)
        {
            y = 'S';
            x = 'O';
            m = m * -1;
            n = n * -1;
        }
        
        if(m < 0 && n > 0)
        {
            y = 'S';
            x = 'L';
            m = m * -1;
        }
        
        if(m > 0 && n < 0)
        {
            y = 'N';
            x = 'O';
            n = n * -1;
        }
       
}
       // printf ("%d %c %d %c", m, y, n, x);
//estrela
       
     
        if(e1 == m && e2 == n + 10 && c1 == y && c2 == x)
        {
			printf ("%d %c %d %c \n", m, y, n, x);
            printf("mapa correto");
        }
		else{
			printf ("%d %c %d %c \n", m, y, n, x);
            printf("mapa incorreto");
}

    system("PAUSE");
    return 0;
}