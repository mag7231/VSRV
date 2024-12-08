#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main() {
    printf("Hello, World!\n");
    int fd;
    /* Open a nonexistent file to cause an error */
    fd = open ("nonexist.txt", O_RDONLY);
    if (fd == -1) /* fd == -1 =, an error occurred */
    {
        printf ("errno = %d\n", errno);
        perror ("main");
    }
    fd = open ("/", O_WRONLY); /* Force a different error */
    if (fd == -1)
    {
        printf ("errno = %d\n", errno);
        perror ("main");
    }
    /* Execute a successful system call */
    fd = open ("nonexist.txt", O_RDONLY | O_CREAT, 0644);
    printf ("errno = %d\n", errno); /* Display after successful call */
    perror ("main");
    errno = 0; /* Manually reset error variable */
    perror ("main");
    return 0;
}