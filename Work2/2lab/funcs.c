#include "funcs.h"
#include "my_errno.h"
#include <errno.h>
#include <stdarg.h>

char *strchr(const char *str, int c) {
  if (!str)
    return NULL;

  unsigned char ch = (unsigned char)c;

  size_t i = 0;
  while (str[i] != '\0') {
    if (str[i] == ch)
      return (char *)(str + i);
    ++i;
  }

  if (ch == '\0')
    return (char *)(str + i);

  return NULL;
}

int memcmp(const void *str1, const void *str2, size_t n) {
  if (!str1 || !str2)
    return 0;

  const unsigned char *s1 = (const unsigned char *)str1;
  const unsigned char *s2 = (const unsigned char *)str2;

  for (size_t i = 0; i < n; i++) {
    if (s1[i] > s2[i]) {
      return 1;
    }
    if (s1[i] < s2[i]) {
      return -1;
    }
  }
  return 0;
}

char *strncat(char *dest, const char *src, size_t n) {
  if (!dest || !src)
    return NULL;

  size_t i = 0;
  while (dest[i] != '\0')
    ++i;

  size_t j = 0;
  while (j < n && src[j] != '\0') {
    dest[i + j] = src[j];
    ++j;
  }

  dest[i + j] = '\0';

  return dest;
}

char *strncpy(char *dest, const char *src, size_t n) {
  if (!dest || !src)
    return NULL;

  size_t i = 0;
  for (i = 0; i < n && src[i] != '\0'; ++i) {
    dest[i] = src[i];
  }
  for (; i < n; ++i) {
    dest[i] = '\0';
  }
  return dest;
}

char *strrchr(const char *str, int c) {
  if (!str)
    return NULL;
  unsigned char ch = (unsigned char)c;
  char *found = NULL;
  size_t i = 0;
  while (str[i] != '\0') {
    if (str[i] == ch) {
      found = (char *)(str + i);
    }
    ++i;
  }
  if (ch == '\0') {
    found = (char *)(str + i);
  }
  return found;
}

char *strstr(const char *haystack, const char *needle) {
  if (!haystack || !needle)
    return NULL;
  if (!*needle)
    return (char *)haystack;

  const char *h = haystack;
  while (*h) {
    const char *hay = h;
    const char *need = needle;
    while (*hay && *need && (*hay == *need)) {
      ++hay;
      ++need;
    }
    if (!*need)
      return (char *)h;
    ++h;
  }
  return NULL;
}


    char *strtok(char *str, const char *delim) {
  static char *next = NULL;
  if (str != NULL)
    next = str;
  if (next == NULL)
    return NULL;

  while (*next && strchr(delim, *next))
    next++;

  if (*next == '\0') {
    next = NULL;
    return NULL;
  }

  char *tokenStart = next;
  while (*next && !strchr(delim, *next))
    next++;

  if (*next) {
    *next = '\0';
    next++;
  } else {
    next = NULL;
  }

  return tokenStart;
}

void *memchr(const void *str, int c, size_t n) {
  if (!str)
    return NULL;

  const unsigned char *s = (const unsigned char *)str;
  const unsigned char ch = (unsigned char)c;

  for (size_t i = 0; i < n; i++) {
    if (s[i] == ch) {
      return (void *)(s + i);
    }
  }
  return NULL;
}

void *memcpy(void *dest, const void *src, size_t n) {
  if (!dest || !src)
    return NULL;

  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }
  return (void *)dest;
}

void *memset(void *str, int c, size_t n) {
  if (!str)
    return NULL;

  unsigned char ch = (unsigned char)c;
  unsigned char *s = (unsigned char *)str;

  for (size_t i = 0; i < n; i++) {
    s[i] = ch;
  }
  return (void *)str;
}

int strncmp(const char *str1, const char *str2, size_t n) {
  if (!str1 || !str2)
    return 0;

  for (size_t i = 0; i < n; i++) {
    if (str1[i] > str2[i])
      return 1;
    if (str1[i] < str2[i])
      return -1;
  }

  return 0;
}

size_t strcspn(const char *str1, const char *str2) {
  if (!str1 || !str2)
    return 0;

  size_t i = 0;
  char *p;
  while (str1[i] != '\0') {
    p = str2;
    while (*p != '\0') {
      if (*p == str1[i]) {
        return i;
      }
      ++p;
    }
    ++i;
  }
  return i;
}

char *strerror(int errnum) {
#ifdef __APPLE__
#define MAX_ERRNO 107
#elif __linux__
#define MAX_ERRNO 133
#elif defined(_WIN32)
#define MAX_ERRNO 140
#endif
  const char *errorMessages[] = ERROR_MESSAGES;

  if (errnum < 0 || errnum > MAX_ERRNO) {
    return "Unknown error";
  }

  const char *msg = errorMessages[errnum];
  if (msg == NULL) {
    return "Unknown error";
  }
  return (char *)msg;
}

size_t strlen(const char *str) {
  if (!str)
    return 0;

  size_t i = 0;
  while (str[i] != '\0')
    ++i;

  return i;
}

char *strpbrk(const char *str1, const char *str2) {
  if (!str1 || !str2)
    return NULL;
  size_t i = 0;
  char *p;
  while (str1[i] != '\0') {
    p = str2;
    while (*p != '\0') {
      if (*p == str1[i]) {
        return (char *)(str1 + i);
      }
      ++p;
    }
    ++i;
  }

  return NULL;
}