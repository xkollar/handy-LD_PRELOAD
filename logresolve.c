#include <stdio.h>
#include <netdb.h>
#include <dlfcn.h>
#include <unistd.h>
#include <stdlib.h>

#undef getaddrinfo

FILE *__my_fopen_log()
{
	static FILE *file = NULL;
        if (!file) {
                char *name = getenv("RESOLVE_LOG_FILE");
		if (!name) {
			file = stderr;
		} else {
			file = fopen(name, "a");
		}
	}
	return file;
}

// Overrides:

__attribute__((visibility("default")))
struct hostent *gethostbyname(const char *name)
{
	static struct hostent *(*lib_gethostbyname)
		(const char *name) = NULL;
	static FILE *file = NULL;
        if (!lib_gethostbyname) {
		char *error;
		lib_gethostbyname = dlsym(RTLD_NEXT, "gethostbyname");
		if ((error = dlerror()) != NULL) {
			fprintf(stderr, "dlsym: %s\n", error);
			exit(EXIT_FAILURE);
		}
	}
        if (!file) {
		file = __my_fopen_log();
	}
	fprintf(file, "Process %d is resolving (gethostbyname): %s\n", getpid(), name);
	fflush(file);
	return lib_gethostbyname(name);
	
}

__attribute__((visibility("default")))
int getaddrinfo(const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res)
{
        static int (*lib_getaddrinfo) (const char *node, const char *service,
                const struct addrinfo *hints,
                struct addrinfo **res) = NULL;
	static FILE *file = NULL;
	if (!lib_getaddrinfo) {
		char *error;
		lib_getaddrinfo = dlsym(RTLD_NEXT, "getaddrinfo");
		if ((error = dlerror()) != NULL) {
			fprintf(stderr, "dlsym: %s\n", error);
			exit(EXIT_FAILURE);
		}
	}
        if (!file) {
		file = __my_fopen_log();
	}
	fprintf(file, "Process %d is resolving (getaddrinfo): %s\n", getpid(), node);
	fflush(file);
	return lib_getaddrinfo(node, service, hints, res);
}

