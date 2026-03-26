#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "kernel/riscv.h"

void *memmem(const void *s1, int n1, const void *s2, int n2)
{
  if (n1 < n2)
    return (void *)0;
  const char *p1 = s1, *p2 = s2;
  for (int i = 0; i <= n1 - n2; i++)
    if (p1[i] == p2[0] && memcmp(&p1[i], p2, n2) == 0)
      return (void *)&p1[i];
  return (void *)0;
}

int main(int argc, char *argv[])
{
  char *str = "This may help.";
  void *start = sbrk(0);
  sbrk(4096);
  void *end = sbrk(0);
  char *ptr = memmem(start, end - start, str, strlen(str));
  if (ptr != (void *)0)
  {
    fprintf(1, "%s\n", ptr + 16);
  }
  exit(0);
}
