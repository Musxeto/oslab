#include <unistd.h>
#include <sys/wait.h>
#include <iostream>
using namespace std;

int main() {
    pid_t child_pid = fork(); 

    if (child_pid < 0) {  
        cout << "Fork Failed" << endl;
        return 1;
    } else if (child_pid == 0) {  
        execlp("/bin/bash", "bash", "-c", "ls -l | sort -n +4", NULL);  
    } else {  
        wait(NULL);  
    }

    return 0;
}
