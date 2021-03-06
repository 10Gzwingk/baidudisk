#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "baiduapi.h"
#include "threadpool.h"
#include "net.h"

char confpath[1024];

struct fuse_operations baidu_oper = {
    .init       = baidu_init,
    .destroy    = baidu_destroy,
    .getattr    = baidu_getattr,
    .fgetattr   = baidu_fgetattr,
    .readdir    = baidu_readdir,
    .mkdir      = baidu_mkdir,
    .unlink     = baidu_unlink,
    .rmdir      = baidu_rmdir,
    .rename     = baidu_rename,
    .statfs     = baidu_statfs,
    .open       = baidu_open,
    .read       = baidu_read,
    .create     = baidu_create,
    .write      = baidu_write,
    .release    = baidu_release,
    .ftruncate  = baidu_ftruncate,
    .truncate   = baidu_truncate,
    .fsync      = baidu_fsync,
    .flush      = baidu_flush,
    .access     = baidu_stub,
    .utimens    = baidu_stub,
};


int main(int argc, char *argv[]) {
    netinit();                          //初始化网络
    sprintf(confpath, "%s/.baidudisk", getenv("HOME"));
    while(gettoken());                  //取得access_token
    return fuse_main(argc, argv, &baidu_oper,NULL);
}
