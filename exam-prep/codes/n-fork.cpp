#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <number_of_processes>" << endl;
        return 1;
    }

    int n = stoi(argv[1]);

    for (int i = 1; i <= n; i++) {
        pid_t pid = fork(); 
        if (pid == 0) {
            cout << "Process " << i << " (PID: " << getpid() << ") created." << endl;
            sleep(1); 
            cout << "Process " << i << " (PID: " << getpid() << ") finished." << endl;
            return 0;
        } else {
            wait(NULL);
        }
    }

    cout << "All processes finished!" << endl;
    return 0;
}
