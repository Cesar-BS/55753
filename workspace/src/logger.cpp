
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#define FIFO_PATH "/tmp/loggerfifo"

int main(int argc, char **argv) {
    int fd;
    int n;
    char buffer[1024];

    // borrar FIFO por si existiera previamente, este paso es bastante importante
    unlink(FIFO_PATH);

    /* crear el FIFO */
    if (mkfifo(FIFO_PATH, 0600) < 0) {
        perror("No puede crearse el FIFO");
        return(1);
    }
    /* Abrir el FIFO */
    if ((fd = open(FIFO_PATH, O_RDONLY)) < 0) {
        perror("No puede abrirse el FIFO");
        return(1);
    }
    /* Leer de la FIFO */
    while ((n = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[n] = '\0';
        printf("%s", buffer);
        fflush(stdout);
    }
    close(fd);
    unlink(FIFO_PATH);//HACE DESAPARECER LA FIFO
    return(0);
}
