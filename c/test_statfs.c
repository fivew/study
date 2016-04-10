#include <stdio.h>
#include <sys/statfs.h>
#include <errno.h>

int main()
{
    char path[] = "/";

    struct statfs buf;
    
    int result = statfs(path, &buf);
  
    if(0 != result )
    {
         perror(strerror(errno));
         return -1;
    }

    printf("f_type = %x\n", buf.f_type);
    printf("f_bsize = %d\n", buf.f_bsize);
    printf("f_blocks = %d\n", buf.f_blocks);
    printf("f_bfree = %d\n", buf.f_bfree);
    printf("f_bavail = %d\n", buf.f_bavail);
    printf("f_files = %d\n", buf.f_files);
    printf("f_ffree = %d\n", buf.f_ffree);
    printf("f_fsid = %d\n", buf.f_fsid);
    printf("f_namelen = %d\n", buf.f_namelen);
    printf("f_frsize = %d\n", buf.f_frsize);


    printf("文件系统 \t1K-块 \t已用 \t可用 \t已用% \t挂载点\n");

    printf("/dev/sda9 \t%ld \t%ld \t%ld \t%d \t/\n",
          4*buf.f_blocks,
          4*(buf.f_blocks - buf.f_bfree),
          4*buf.f_bavail,
          (100 - buf.f_bfree*100/buf.f_blocks)
          );

   
    return 0;
}
