#include <SPIDER.h>

int spider_remove_duplication(container_t *u_ct, container_t *p_ct, const char *url)
{
	int flag = u_ct->rear;
	while(flag%u_ct->max != u_ct->front)
	{
		if(strncmp(u_ct->queue_node[flag].origin_url, url, strlen(url)) == 0)
		{
			return -1;
		}
		flag++;
	}

	flag = p_ct->rear;
	while(flag%p_ct->max != p_ct->front)
	{
		if(strncmp(p_ct->queue_node[flag].origin_url, url, strlen(url)) == 0)
		{
			return -1;
		}
		flag++;
	}

	return 0;
}
