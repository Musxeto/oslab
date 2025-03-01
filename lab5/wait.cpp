#include <iostream>
#include <unistd.h>
#include <sys/wait.h> // for wait()
#include <cstdlib>
using namespace std;

int main() {
    pid_t pid = fork();

    if (pid == -1) { 
        cerr << "Fork failed" << endl;
        exit(1);
    }

    if (pid == 0) { 
        cout << "Child here!" << endl;
    } else { 
        int status;
        wait(&status);
        cout << "Well done, kid!" << endl;
    }
    return 0;
}
