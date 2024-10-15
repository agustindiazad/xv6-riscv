#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h"



int main(void) {
    int n;
    int pid;

    for(n = 0; n < 10; n++) {
        pid = fork();
        if(pid < 0) {
            printf("Error al hacer fork\n");
            exit(1);
        }
        if(pid == 0) {
	    sleep(10*(n+1));
            // Establecer prioridad y boost para cada proceso hijo
            setpriority(getpid(), 10 - n);  // Prioridades decrecientes
            setboost(getpid(), n % 2 == 0 ? 1 : -1);  // Boost alternante

            printf("El proceso %d se esta ejecutando con PID %d, una prioridad %d y boost %d\n",
                   n, getpid(), 10 - n, n % 2 == 0 ? 1 : -1);
            exit(0);
        }
    }

    for(n = 0; n < 20; n++) {
        wait(0);
    }

    exit(0);
}
