#include <SPIDER.h>

int spider_request_response(int webfd, char *request_head, url_t node, ssl_t *ssl)
{
	//向外部服务器发送http请求
	//第一次接收响应（获取响应头和部分响应体）
	//提取响应头`
	//获取，判断响应码 如果为200 则接收，否则此次下载失败

	//如果为200
	/*
	   创建资源文件，将第一次读取的响应内容中部分响应体保存
	   循环接收并内容并保存（下载完毕）
	   下载成功返回0
	 */

	char recv_buffer[8192];
	char response_buffer[4096];
	char *pos;  //记录返回数据中的空行
	int rsize;
	int statuscode;
	int fd;

	bzero(recv_buffer, sizeof(recv_buffer));
	bzero(response_buffer, sizeof(response_buffer));

	if(ssl == NULL)
	{
		//向web服务器发送http请求
		send(webfd, request_head, strlen(request_head), 0);
		printf("[5] 发送请求成功、\n");

		rsize = recv(webfd, recv_buffer, sizeof(recv_buffer), 0);

		if((pos = strstr(recv_buffer, "\r\n\r\n")) == NULL)  //在一个字符串里找子串
		{
			printf("spider_request_response recv response_head error, strstr call failed\n");
			close(webfd);
			return -1;
		}

		//将recv_buffer按照%s格式化成字符串，并将字符串复制到str中，大小为pos-recv_buffer+4(写入字符的最大数目，超过会被截断)
		snprintf(response_buffer, pos-recv_buffer+4, "%s", recv_buffer);
		printf("[6] 获取响应头成功 respone_head:\n%s", response_buffer);

		if((statuscode = spider_get_statuscode(response_buffer)) == 200)
		{
			printf("[] 服务器的响应码 %d\n", statuscode);
			fd = open(node.fileName, O_RDWR|O_CREAT, 0775);
			write(fd, pos+4, rsize-(pos-recv_buffer+4)); //写入部分响应体
			while((rsize = recv(webfd, recv_buffer, sizeof(recv_buffer), 0)) > 0)
			{
				write(fd, recv_buffer, rsize);
			}
			printf("[7] 下载成功，本次交互完毕\n");
		}
		else
		{
			printf("[] 服务器的响应码 %d\n", statuscode);
			close(webfd);
			return -1;
		}
	}
	else
	{	
		SSL_write(ssl->sslsocket, request_head, strlen(request_head));
		printf("[5] HTTPS发送请求成功、\n");

		rsize = SSL_read(ssl->sslsocket, recv_buffer, sizeof(recv_buffer));

		if((pos = strstr(recv_buffer, "\r\n\r\n")) == NULL)  //在一个字符串里找子串
		{
			printf("spider_request_response recv response_head error, strstr call failed\n");
			close(webfd);
			return -1;
		}

		//将recv_buffer按照%s格式化成字符串，并将字符串复制到str中，大小为pos-recv_buffer+4(写入字符的最大数目，超过会被截断)
		snprintf(response_buffer, pos-recv_buffer+4, "%s", recv_buffer);
		printf("[6] 获取响应头成功 respone_head:\n%s", response_buffer);

		if((statuscode = spider_get_statuscode(response_buffer)) == 200)
		{
			printf("[] HTTPS服务器的响应码 %d\n", statuscode);
			fd = open(node.fileName, O_RDWR|O_CREAT, 0775);
			write(fd, pos+4, rsize-(pos-recv_buffer+4)); //写入部分响应体
			while((rsize = SSL_read(ssl->sslsocket, recv_buffer, sizeof(recv_buffer))) > 0)
			{
				write(fd, recv_buffer, rsize);
			}
			printf("[7] HTTPS下载成功，本次交互完毕..\n");
			close(fd);
			free(ssl);
			ssl = NULL;
		}
		else
		{
			printf("[] HTTPS服务器的响应码 %d\n", statuscode);
			free(ssl);
			ssl = NULL;
			close(webfd);
			return -1;
		}
	}
	close(webfd);
	//下载成功返回0
	return 0;
}
