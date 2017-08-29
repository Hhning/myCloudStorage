#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include "make_log.h"
#include "redis_op.h"

#define LOG_MODULE "test"
#define LOG_PROC "redis_op"

int main()
{
    redisContext *conn = NULL;  //redis连接句柄
    int ret = 0;
    char value[VALUES_ID_SIZE] = {0};

    conn = rop_connectdb_nopwd("127.0.0.1", "6379");
    if(conn == NULL)
    {
        LOG(LOG_MODULE, LOG_PROC, "connect error");
        return 1;
    }

    ret = rop_set_string(conn, "FOO", "nihaomeinv");
    if(ret != 0)
    {
        LOG(LOG_MODULE, LOG_PROC, "set error");
        return 1;
    }

    ret = rop_get_string(conn, "FOOL", value);
    if(ret != 0)
    {
        LOG(LOG_MODULE, LOG_PROC, "get error");
        return 1;
    }

    printf("value = %s\n", value);
    
    //创建一个链表 添加元素
    ret = rop_list_push(conn, "my_list_key", "zhangsan");
    if(ret != 0)
    {
        LOG(LOG_MODULE, LOG_PROC, "list push error");
        return 1;
    }
    
    ret = rop_list_push(conn, "my_list_key", "lisi");
    if(ret != 0)
    {
        LOG(LOG_MODULE, LOG_PROC, "list push error");
        return 1;
    }
    ret = rop_list_push(conn, "my_list_key", "wangwu");
    if(ret != 0)
    {
        LOG(LOG_MODULE, LOG_PROC, "list push error");
        return 1;
    }
    //断开连接
    rop_disconnect(conn);

    return 0;
}

