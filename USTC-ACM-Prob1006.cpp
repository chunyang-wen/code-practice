#include <stdio.h>
#include <string.h>
int main() {
    char v[10036] = {0};
    char j1, j2, j3, j4;
    char s2, s3, s4;
    short n = 0;
    // memset(v, 0, sizeof(v));
         
    for (j4=0; j4<10; j4++) {             
        s4 = j4;             
        for (j3=0; j3<10; j3++) {                
            s3 = s4 + j3;                
            for (j2=0; j2<10; j2++) {
                s2 = s3 + j2;                   
                for (j1=0; j1<10; j1++) {                      
                    v[s2 + j1 + n++] = 1; 
                    if (!v[n]) printf("%d\n", n);  
                }                
            }           
        }      
    }     
    // for (n=1; n<10000; n++) {
        // if (!v[n]) printf("%d\n", n);  
    // } 
    return 0;

} 