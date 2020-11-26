#include <stdio.h> 
#include <unistd.h> 
#include <fcntl.h> 

#define BUF_SIZE 256

int main(int argc , char* argv[]) {

    pid_t pid;
    int file_desc[2], in_fd, n;
    char buf[BUF_SIZE];
    char fname[32];
    
    if(pipe(file_desc) < 0) {

        fprintf(stderr, "Failed creating pipe\n");
        return 1;
    }

    pid = fork();

    if(pid == 0) {
        //child
        close(file_desc[1]);
        close(0);
        dup(file_desc[0]);
        close(file_desc[0]);


        execlp("display", "display", "-", NULL);
    }
    else {
        //parent
        close(file_desc[0]);


        if((in_fd = open(argv[1], O_RDONLY)) < 0) {
            
            fprintf(stderr, "Failed opening file\n");
            return 2;
        }
        
        while((n = read(in_fd, &buf, BUF_SIZE)) > 0) {
    
            if(write(file_desc[1], &buf, n) < 0) {
                fprintf(stderr, "Failed writing to pipe\n");
                return 3;
            }  
        }
        close(in_fd);
    } 
}