#ifndef UTIL_H
#define UTIL_H

void util_memcpy(void* src, int a, void* dest, int b, int len) {
	while (b < len) {
		dest[b++] = src[a++];
  }
}

#endif//UTIL_H
