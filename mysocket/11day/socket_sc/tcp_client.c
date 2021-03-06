#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <arpa/inet.h>
#include <fcntl.h>

// tcp client
int main(int argc, const char* argv[])
{
    // 创建套接字
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1)
    {
        perror("socket error");
        exit(1);
    }

    // 连接服务器
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);
    int ret = connect(fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret == -1)
    {
        perror("connect error");
        exit(1);
    }

    // 通信
    while(1)
    {
        // 写数据
        // 接收键盘输入
        char buf[512];
        fgets(buf, sizeof(buf), stdin);
        // 发送给服务器
        write(fd, buf, strlen(buf)+1);

        // 接收服务器端的数据
#if 0
        int flag = fcntl(fd, F_GETFL);
        flag |= O_NONBLOCK;
        fcntl(fd, F_SETFL, flag);
        while()
        {
            read();
        }
#endif
        int len = read(fd, buf, sizeof(buf));
        printf("read buf = %s, len = %d\n", buf, len);
    }
    return 0;
}
