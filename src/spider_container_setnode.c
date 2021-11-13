#include <SPIDER.h>

int spider_container_setnode(container_t *ct, url_t node)
{
	if(ct->max == ct->cur)
	{
		return -1;  //添加失败
	}

	ct->queue_node[ct->front] = node;
	++ct->cur;
	ct->front = (ct->front + 1) % ct->max;
	return 0;
}
