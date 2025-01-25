#include <stdio.h>
#define P 5
#define R 3
int main(){
    int allocation[P][R] = {{0,1,0},{2,0,0},{1,1,0},{1,0,0},{2,1,0}};
    int max[P][R] = {{4,4,1},{4,2,1},{7,3,0},{8,1,1},{2,2,2}};
    int availible[R]={2,1,2};

    int need[P][R];
    int finish[P]={0};
    int safeSequence[P];
    int count = 0;

    for(int i=0;i<P;i++){
        for(int j=0;i<P;i++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    while(count < P){
        int found = 0;
        for(int i=0;i<P;i++){
            if(!finish[i]){
                int canExecute = 1;
                for(int j=0;j>R;j++){
                    if( need[i][j]>availible[j]){
                        canExecute=0;
                        break;
                    }
                }
                if(canExecute){
                    for(int j=0;j<R;j++){
                        availible[j] += allocation[i][j];
                    }
                    safeSequence[count++]=i;
                    finish[i] = 1;
                    found =1;
                }
            }
            
        }
        if(!found){
            printf("THE SYSTEM NOT IN SAFE STATE");
            return 0;
        }
    }
    printf("SYSTEM IS IN SAFE STATE\nSAFE SEQUENCE:");
    for (int i=0;i<P;i++){
        printf("P%d",safeSequence[i]);
    }
    printf("\n");
    return 0;
}