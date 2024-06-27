#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // 调用fork之前, 代码都在父进程中进行
    printf("海哥教老学员%d春暖花开\n", getpid());
    // 使用fork创建进程
    /* __pid_t fork (void) __THROWNL;
    ** return int 进程号
    **      1. -1出错
    **      2. 父进程中表示子进程的PID
    **      3. 子进程中显示为0
    */
    pid_t pid = fork();
    // 从fork之后, 所有的代码都是在父子进程中各执行一次
    // printf("%d\n", pid);
    if (pid < 0)
    {
        printf("新学员加入失败\n");
        return 1;
    }
    else if (pid == 0)
    {
        // 执行单独子进程代码
        printf("新学员%d加入成功, 他是老学员%d推荐的\n", getpid(), getppid());
    }
    else
    {
        // 执行单独父进程代码
        printf("老学员%d加入成功, 他推荐了%d\n", getpid(), pid);
    }
    return 0;
}