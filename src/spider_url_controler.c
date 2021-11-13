#include <SPIDER.h>

int spider_url_controler(const char *origin_url)
{
	int webfd;
	url_t tmp;
	url_t node;
	ssl_t *ssl = NULL;
	char request_head[4096];
	data_fd = open("resdate", O_RDWR|O_CREAT, 0664); //创建存储文件
	strcpy(tmp.origin_url, origin_url);

	//容器创建
	container_t *u_ct = spider_container_create(1000);
	container_t *p_ct = spider_container_create(100000);

	//去重校验
	if((spider_remove_duplication(u_ct, p_ct, tmp.origin_url)) != -1)
	{
		spider_container_setnode(u_ct, tmp); //添加
	}

	while(u_ct->cur != 0 && p_ct->max != p_ct->cur)
	{
		//创建一次性链接sockfd
		webfd = spider_net_init();
		//获取一个未处理url
		spider_container_getnode(u_ct, &node);
		//解析url
		spider_analytical_url(&node);
		//链接web服务器
		spider_connect_webserver(webfd, node);
		//创建请求头
		spider_create_request(request_head, node);

		//判断http协议，选择不同的交互方式
		if(node.HTYPE)
		{
			ssl = spider_openssl_create(webfd);  //完成https的安全认证
		}

		if((spider_request_response(webfd, request_head, node, ssl)) == -1)
		{
			continue;   //结束本次循环
		}

		//下载完成放到已处理容器
		spider_container_setnode(p_ct, node);
		//解析网页源码（可能解析出更多链接，所以传递容器，方便放入）
		spider_analytical_html(&node, u_ct, p_ct);
	}
	close(webfd);
	return 0;
}
