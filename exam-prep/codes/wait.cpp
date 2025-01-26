#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main(){
    pid_t pid = fork();  // Create a new process

    if(pid < 0){  // Check for fork failure
        cout << "Fork Failed" << endl;
        exit(1);
    }
    
    if (pid == 0){  // This block is executed by the child process
        cout << "Child Here!" << endl;
        sleep(10);  // Simulate some work in the child process
    } 
    else {  // This block is executed by the parent process
        wait(NULL);  // Wait for the child to finish
        cout << "Well done kid" << endl;
    }
    return 0;
}
