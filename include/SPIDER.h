#include <SOCKET.h>

/*
https://img2.baidu.com/it/u=4246794212,2658652294&fm=26&fmt=auto
https://img1.baidu.com/it/u=1641325154,949363497&fm=26&fmt=auto
https://img2.baidu.com/it/u=2232459289,542605765&fm=26&fmt=auto
https://desk-fd.zol-img.com.cn/t_s144x90c5/g6/M00/02/0A/ChMkKWGAmuqIRyQ8ADQDcB93xVgAAVLRwOOfkkANAOI798.jpg
https://img-pre.ivsky.com/img/bizhi/pre/201910/10/gonglu-010.jpg
http://pic1.win4000.com/wallpaper/2018-05-16/5afb9b5997e48.jpg
*/
int data_fd;

typedef struct
{
	char origin_url[4096]; //存储原始url链接
	char domain[1024];
	char path[1024];
	char fileName[1024];
	char IP[16];
	int PORT;
	int HTYPE;  //0 HTTP，1 HTTPS
}url_t;

typedef struct
{
	SSL *sslsocket;
	SSL_CTX *sslctx;
}ssl_t;

typedef struct
{
	url_t *queue_node;
	int front;
	int rear;
	int max;
	int cur;
}container_t;

int spider_net_init();  //网络初始化，返回sockfd
int spider_analytical_url();  //传入只附带原始地址的url_t，传出解析后的
int spider_connect_webserver(int, url_t); //完成tcp链接
int spider_create_request(char *, url_t);
int spider_request_response(int, char *, url_t, ssl_t *);
int spider_get_statuscode(const char *);
ssl_t *spider_openssl_create(int);
container_t *spider_container_create(int);
int spider_remove_duplication(container_t *, container_t *, const char *);
int spider_container_setnode(container_t *, url_t);
int spider_container_getnode(container_t *, url_t *);
int spider_analytical_html(url_t *, container_t *, container_t *);
int spider_save_data(const char *name, const char *desc, const char* url);
int spider_url_controler(const char *alpha_url);
