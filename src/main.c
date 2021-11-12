#include <SPIDER.h>


int main(void)
{
	int webfd;
	char request_head[4096];
	url_t node;
	webfd = spider_net_init();
	const char *str = "http://pic1.win4000.com/wallpaper/2018-05-16/5afb9b5997e48.jpg";

	strcpy(node.origin_url, str);
	spider_analytical_url(&node);
	spider_connect_webserver(webfd, node);
	spider_create_request(request_head, node);
	spider_request_response(webfd, request_head, node);

	return 0;
}
