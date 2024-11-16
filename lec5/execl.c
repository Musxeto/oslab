#include <stdio.h>
#include <unistd.h>

int main(){
    printf("This Process will use ls command \n");
    execl("/bin/ls","ls",NULL);
    printf("This Componenet did not work");
    return 0; 
}
