#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#include "fdfs_api.h"

#include "make_log.h"

#define LOG_MOUDLE "api"
#define LOG_PROC "fdfs"
#include "fdfs_client.h"


int fdfs_upload_by_filename(char *filename, char * fileid)
{
    int ret = 0;
    int pfd[2];
    pid_t pid;

    ret = pipe(pfd);
    if (ret != 0) {
        printf("pipe error");
        return -1;
    }


    pid = fork();
    if (pid < 0) {
        printf("fork error");
        return -1;
    }
    else if (pid == 0){
        //child

        //close pfd[0]
        close(pfd[0]);

        //dup2 stdout->pfd[1]
        dup2(pfd[1], STDOUT_FILENO);

        //exec 
        execlp("fdfs_upload_file", "fdfs_upload_file", "/etc/fdfs/client.conf", filename, NULL);
        printf("exec fdfs_upload_file error\n");
        return -1;
    }
    else {
        //parent

        //close pfd[1]
        close(pfd[1]);

        //wait
        wait(NULL);

        //read pfd[0] --> fileid
        read(pfd[0], fileid, FILE_ID_LEN);

        int len = strlen(fileid);

        fileid[len-1] = '\0';

        close(pfd[0]);
    }
    

    return 0;
}
