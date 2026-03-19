#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define isdigit(c) ((c) >= '0' && (c) <= '9')

int sixfive(int ans[], int fd)
{
  int n = 0;
  char c;
  while (read(fd, &c, 1) > 0)
  {
    if (!isdigit(c))
    {
      continue;
    }
    char buf[16];
    char *ptr = buf;
    while (isdigit(c))
    {
      *ptr++ = c;
      if (!(read(fd, &c, 1) > 0))
      {
        break;
      }
    }
    *ptr = '\0';
    int x = atoi(buf);
    if (x % 5 == 0 || x % 6 == 0)
    {
      ans[n++] = x;
    }
  }
  return n;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(2, "Usage: sixfive files...\n");
    exit(1);
  }

  for (int j = 1; j < argc; j++)
  {
    int fd = open(argv[j], O_RDONLY);

    int ans[1024];
    int n = sixfive(ans, fd);
    for (int i = 0; i < n; i++)
    {
      fprintf(1, "%d\n", ans[i]);
    }

    close(fd);
  }

  exit(0);
}
