#include <SPIDER.h>

int spider_get_statuscode(const char *response_head)
{
	// HTTP/1.1 200 OK

	int statuscode;
	char status[100];
	bzero(status, sizeof(status));

	regex_t reg;
	regmatch_t match[2];
	regcomp(&reg, "HTTP/1.1 \\([^\r\n]\\+\\?\\)\r\n", 0);
	if((regexec(&reg, response_head, 2, match, 0)) == 0)
	{
		snprintf(status, match[1].rm_eo-match[1].rm_so+1, "%s", response_head+match[1].rm_so);
	}
	sscanf(status, "%d", &statuscode);
	regfree(&reg);
	return statuscode;
}
