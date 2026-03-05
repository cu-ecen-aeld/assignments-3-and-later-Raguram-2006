#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
   
    if (argc != 3) {
        fprintf(stderr, "Error: Two arguments required: <file> <string>\n");
        openlog("writer", 0, LOG_USER);
        syslog(LOG_ERR, "Invalid number of arguments: %d", argc);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

   
    openlog("writer", 0, LOG_USER);


    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        syslog(LOG_ERR, "Error opening file %s: %s", writefile, strerror(errno));
        closelog();
        return 1;
    }
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);
    ssize_t nr = write(fd, writestr, strlen(writestr));
    if (nr == -1) {
        syslog(LOG_ERR, "Error writing to file: %s", strerror(errno));
        close(fd);
        closelog();
        return 1;
    }

    close(fd);
    closelog();

    return 0;
}
