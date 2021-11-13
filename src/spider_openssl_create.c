#include <SPIDER.h>

ssl_t *spider_openssl_create(int webfd)
{
	ssl_t *ssl = (ssl_t *)malloc(sizeof(ssl_t));

	//初始化
	SSL_load_error_strings();
	SSL_library_init();
	OpenSSL_add_ssl_algorithms();

	//认证上下文
	ssl->sslctx = SSL_CTX_new(SSLv23_method());
	//安全套接字
	ssl->sslsocket = SSL_new(ssl->sslctx);
	SSL_set_fd(ssl->sslsocket, webfd);

	//安全认证
	SSL_connect(ssl->sslsocket);

	return ssl;
}
