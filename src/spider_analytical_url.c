#include <SPIDER.h>


//http://pic1.win4000.com/wallpaper/2018-05-16/5afb9b5997e48.jpg

int spider_analytical_url(url_t *node)
{
	
	bzero(node->domain, sizeof(node->domain));
	bzero(node->path, sizeof(node->path));
	bzero(node->fileName, sizeof(node->fileName));
	bzero(node->IP, sizeof(node->IP));

	int i = 0;
	int flag = 0;
	int start;
	int fsize = 0;

	char *array[] = {"http://", "https://", NULL};

	//判断http类型,并获取
	if(strncmp(node->origin_url, array[0], strlen(array[0])) == 0)
	{
		node->HTYPE = 0;
		node->PORT = 80;
		start = strlen(array[0]);   //记录协议类型长度，方便跳过
	}
	else
	{
		node->HTYPE = 1;
		node->PORT = 443;
		start = strlen(array[1]);
	}

	//获取网站域名
	for(i = start; node->origin_url[i] != '/' && node->origin_url[i] != '\0'; i++)
	{
		node->domain[flag] = node->origin_url[i];
		flag++;
	}
	flag = 0;

	//获取文件名长度
	for(i = strlen(node->origin_url); node->origin_url[i] != '/'; i--,fsize++);
	//获取文件名
	for(i = strlen(node->origin_url)-fsize+1; node->origin_url[i] != '\0'; i++)
	{
		node->fileName[flag] = node->origin_url[i];
		flag++;
	}
	flag = 0;

	//获取路径
	for(i = start+strlen(node->domain); i < strlen(node->origin_url)-fsize+1; i++)
	{
		node->path[flag] = node->origin_url[i];
		flag++;
	}
	
	//获取公网IP
	struct hostent *ent = NULL;
	if((ent = gethostbyname(node->domain)) != NULL)
	{
		//从结构体中的h_addr_list中获取一个大端ip，转换为字符串存储
		inet_ntop(AF_INET, ent->h_addr_list[0], node->IP, 16);
	}

	//printf如果参数不正确，会产生栈溢出！！！
	printf("[2] 解析URL链接，获取关键信息 [%s]\n", node->IP);
}
