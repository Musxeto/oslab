#include <iostream>
#include <unistd.h> 
using namespace std;

int main() {
    cout << "Original process with pid " << getpid() << " ppid " << getppid() << endl;

    pid_t pid = fork(); 

    if (pid != 0) { 
        cout << "Parent process with pid " << getpid() << " ppid " << getppid() << endl;
    }
    else { 
        sleep(5); 
        cout << "Child process with pid " << getpid() << " ppid " << getppid() << endl;
    }

    cout << "pid " << getpid() << " terminates\n";
    return 0;
}
