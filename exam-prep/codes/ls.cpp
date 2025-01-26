#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

int main() {
    pid_t child_pid = fork();  

    if (child_pid < 0) {  
        cout << "Fork Failed" << endl;
        return 1;
    } else if (child_pid == 0) {
        execl("/bin/ls", "ls", "-l", NULL); 
        sleep(5); 
        return 1;
    } else {  
        wait(NULL);  
    }

    return 0;
}
