#include "funcs.h"
#include "my_errno.h"
#include <stdio.h>
#include <string.h>

int main() {
  printf("Testim lab2\n");
  printf("============\n\n");

  // a
  char arr1[] = "abcdef";
  printf("memchr: def | d | %s\n", (char *)memchr(arr1, 'd', 6));

  // b
  char a1[] = "abc";
  char a2[] = "abd";
  printf("memcmp: abc abd | %d\n", memcmp(a1, a2, 3));

  // c
  char src1[] = "Hello";
  char dest1[10];
  memcpy(dest1, src1, 6);
  printf("memcpy: Hello | %s\n", dest1);

  // d
  char buf[6];
  memset(buf, 'O', 5);
  buf[5] = '\0';
  printf("memset: O | %s\n", buf);

  // e
  char dcat[4] = "foo";
  strncat(dcat, "barbaz", 36);
  printf("strncat: foo <- barbaz | %s\n", dcat);

  // f
  char s1[] = "abcdef";
  printf("strchr: abcdef | find d |%s\n", strchr(s1, 'd'));

  // g
  printf("strncmp (ab c, abd, 2): %d\n", strncmp("abc", "abd", 2));
  printf("strncmp (abc, abd, 3): %d\n", strncmp("abc", "abd", 3));

  // h
  char src2[] = "12345";
  char dest2[10];
  strncpy(dest2, src2, 3);
  dest2[3] = '\0';
  printf("strncpy: 12345 bytes:3 | %s\n", dest2);

  // i
  printf("strcspn: abcdef | de | %zu\n", strcspn("abcdef", "de"));

  // j
  printf("strerror(2): %s\n", strerror(2));

  // k
  printf("strlen('hello'): %zu\n", strlen("hello"));

  // l
  printf("strpbrk: abcdef xycd | %s\n", strpbrk("abcdef", "xycd"));

  // m
  printf("strrchr: abcabc a | %s\n", strrchr("abcabc", 'a'));

  // n
  printf("strstr: This is a test| is |%s\n", strstr("This is a test", "is"));

  // o
  char text[] = ",,one,1,,two,three";
  char *token = strtok(text, ",");
  while (token) {
    printf("strtok: ,,one,1,,two,three | , | %s\n", token);
    token = strtok(NULL, ",");
  }

  printf("\n============\n");

  char err1[2] = "a";
  char err3[2] = "x";
  char err4[2] = "x";
  char err5[] = {'x'};
  char err2[20] = "BBBBBBBBBBBBBBBBBBBB";
  printf("%s\n", strcat(err1, err2));
  return 0;
}
