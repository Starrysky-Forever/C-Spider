#include <SPIDER.h>

container_t *spider_container_create(int size)
{
	container_t *ct = NULL;
	ct = (container_t *)malloc(sizeof(container_t));

	ct->queue_node = (url_t *)malloc(size * sizeof(url_t));

	ct->front = 0;
	ct->rear = 0;
	ct->max = size;
	ct->cur = 0;

	return ct;
}
