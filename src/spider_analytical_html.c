#include <SPIDER.h>

//<h1>大标题</h1>
//<meta name="keywords" content="描述">
//<a href = "/news/2021100428.html"> </a>
//https://ak.hypergryph.com/链接地址

int spider_analytical_html(url_t* node, container_t *u_ct, container_t *p_ct)
{
	int fd = open(node->fileName, O_RDWR);
	int fsize = lseek(fd, 0, SEEK_END);
	char *string = mmap(NULL, fsize, PROT_READ, MAP_PRIVATE, fd, 0);
	close(fd);

	char *jstring = string;
	url_t tmp;
	regex_t hreg, dreg, areg;

	regmatch_t hmatch[2];
	regmatch_t dmatch[2];
	regmatch_t amatch[2];

	char h1[1024];
	char desc[8192];
	char link[4096];
	bzero(h1, sizeof(h1));
	bzero(desc, sizeof(desc));
	bzero(link, sizeof(link));

	regcomp(&hreg, "<h1 >\\([^<]\\+\\?\\)</h1>", 0);
	regcomp(&dreg, "<meta name=\"description\" content=\"\\([^\"]\\+\\?\\)\">", 0);
	regcomp(&areg, "<a[^>]\\+\\?href=\"\\(/item/[^\"]\\+\\?\\)\"[^>]\\+\\?>[^<]\\+\\?</a>", 0);

	if((regexec(&hreg, string, 2, hmatch, 0)) == 0)
	{
		snprintf(h1, hmatch[1].rm_eo-hmatch[1].rm_so+1, "%s", string+hmatch[1].rm_so);
	}
	if((regexec(&dreg, string, 2, dmatch, 0)) == 0)
	{
		snprintf(desc, dmatch[1].rm_eo-dmatch[1].rm_so+1, "%s", string+dmatch[1].rm_so);
	}

	//只有满足特定条件，才进行新url解析
	if(u_ct->cur < 50)
	{
		while((regexec(&areg, string, 2, amatch, 0)) == 0)
		{
			snprintf(link, amatch[1].rm_eo-amatch[1].rm_so+24, "https://baike.baidu.com/%s", string+amatch[1].rm_so);
			if((spider_remove_duplication(u_ct, p_ct, link)) == 0)
			{
				strcpy(tmp.origin_url, link);
				spider_container_setnode(u_ct, tmp);
			}
			bzero(link, sizeof(link));
			string += amatch[0].rm_eo;
			if(p_ct->max == p_ct->cur)
			{
				continue;
			}
		}
	}

	printf("%s\n", h1);
	printf("%s\n", desc);
	printf("%s\n", node->origin_url);

	regfree(&hreg);
	regfree(&dreg);
	regfree(&areg);

	munmap(jstring, fsize);
	unlink(node->fileName);
	return 0;
}
