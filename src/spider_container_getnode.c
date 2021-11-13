#include <SPIDER.h>

int spider_container_getnode(container_t *ct, url_t *node)
{
	if(ct->cur == 0)
	{
		return -1;
	}
	
	*node = ct->queue_node[ct->rear];
	--ct->cur;
	ct->rear = (ct->rear + 1) % ct->max;

	return 0;
}
