#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <hiredis.h>

int main(int argc, char **argv) {
    //unsigned int j;
    redisContext *c;
    redisReply *reply;

    //struct timeval timeout = { 1, 500000 }; // 1.5 seconds
   // c = redisConnectWithTimeout(hostname, port, timeout);
    c = redisConnect("127.0.0.1", 6379);
    if (c == NULL || c->err) {
        if (c) {
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } else {
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }


    /* Set a key */
    reply = redisCommand(c,"SET %s %s", "foo", "hello world");
    if(reply == NULL)
    {
        printf("set error\n");
    }
    printf("SET: %s\n", reply->str);
    freeReplyObject(reply);
    
    reply = redisCommand(c, "GET %s", "foo");
    if(reply == NULL)
    {
        printf("set error\n");

    }

    //reply->type  应该是一个字符串类型
    printf("value = %s, len = %lu\n", reply->str, reply->len);
    freeReplyObject(reply);


    /* Disconnects and frees the context */
    redisFree(c);

    return 0;
}
