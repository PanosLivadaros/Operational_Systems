#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

void create_process(int process_num) {
    pid_t pid = fork();
    if (pid == 0) { // Child process
        printf("My Process ID: %d | Parent Process ID: %d | Process Number: %d\n", getpid(), getppid(), process_num);
        fflush(stdout); // Ensure output is printed immediately
    } else if (pid > 0) { // Parent waits for the child
        waitpid(pid, NULL, 0);
    }
}

int main() {
    create_process(1); // p1
    create_process(3); // p3 (child of p1)
    create_process(2); // p2
    create_process(4); // p4 (child of p2)
    create_process(5); // p5 (child of p2)
    create_process(6); // p6 (child of p5)

    printf("My Process ID: %d | Parent Process ID: %d | Process Number: %d\n", getpid(), getppid(), 0);

    return 0;
}
