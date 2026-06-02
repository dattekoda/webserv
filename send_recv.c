#include <sys/types.h>
#include <sys/socket.h>

#include <stdio.h>
#include <string.h>

size_t	my_strlcat(char *dst, const char *src, size_t size) {
	const size_t	dst_space = strnlen(dst, size);

	size -= dst_space;
	dst += dst_space;
	while (*src && 1 < size) {
		*(dst++) = *(src++);
		--size;
	}
	while (size) {
		*(dst++) = '\0';
		--size;
	}
	return dst_space + strlen(src);
}

int	send_recv(int acc, int child_no) {
	char	buf[512], *ptr;
	ssize_t	len;

	if ((len = recv(acc, buf, sizeof(buf), 0)) == -1) {
		perror("recv");
		return -1;
	}
	if (len == 0) {
		(void) fprintf(stderr, "[child%d]recv:EOF\n", child_no);
		return -1;
	}
	buf[len] = '\0';
	if ((ptr = strpbrk(buf, "\r\n")) != NULL) {
		*ptr = '\0';
	}
	(void) fprintf(stderr, "[child%d]%s\n", child_no, buf);
	(void) my_strlcat(buf, ":OK\r\n", sizeof(buf));
	len = strlen(buf);
	if ((len = send(acc, buf, len, 0)) == -1) {
		perror("send");
		return -1;
	}
	return 0;
}

