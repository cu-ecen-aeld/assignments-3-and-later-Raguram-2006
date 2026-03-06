#include "systemcalls.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdarg.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 * successfully using the system() call, false if an error occurred.
*/
bool do_system(const char *cmd)
{
    int result = system(cmd);
    if (result == -1) {
        return false;
    }
    return (result == 0);
}

/**
* @param count -The numbers of variables passed to the function.
* @param ... - A list of 1 or more arguments after the @param count argument.
* @return true if the command was executed successfully using execv, false otherwise.
*/
bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    fflush(stdout);
    pid_t pid = fork();

    if (pid == -1) {
        va_end(args);
        return false;
    } 
    else if (pid == 0) {
        execv(command[0], command);
        exit(EXIT_FAILURE); 
    } 
    else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            va_end(args);
            return false;
        }
        va_end(args);
        return (WIFEXITED(status) && (WEXITSTATUS(status) == 0));
    }
}

/**
* @param outputfile - The full path to the file to write with command output.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    int fd = open(outputfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        va_end(args);
        return false;
    }

    fflush(stdout);
    pid_t pid = fork();

    if (pid == -1) {
        close(fd);
        va_end(args);
        return false;
    } 
    else if (pid == 0) {
        if (dup2(fd, 1) < 0) {
            exit(EXIT_FAILURE);
        }
        close(fd);
        execv(command[0], command);
        exit(EXIT_FAILURE);
    } 
    else {
        close(fd);
        int status;
        // This is where your error was: the waitpid call was incomplete!
        if (waitpid(pid, &status, 0) == -1) {
            va_end(args);
            return false;
        }
        va_end(args);
        return (WIFEXITED(status) && (WEXITSTATUS(status) == 0));
    }
}
