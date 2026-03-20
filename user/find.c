#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

void find(char *path, char *file, char *name, int out)
{
  int fd = open(path, O_RDONLY);
  struct stat st;
  fstat(fd, &st);
  switch (st.type)
  {
  case T_DEVICE:
  case T_FILE:
    if (strcmp(file, name) == 0)
    {
      fprintf(out, "%s\n", path);
    }
    break;
  case T_DIR:
  {
    struct dirent de;
    while (read(fd, &de, sizeof(de)) > 0)
    {
      if (de.inum == 0)
      {
        continue;
      }
      if (strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0)
      {
        char buf[512];
        strcpy(buf, path);
        char *ptr = buf + strlen(buf);
        *ptr++ = '/';
        strcpy(ptr, de.name);
        find(buf, de.name, name, out);
      }
    }
    break;
  }
  default:
    break;
  }
  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc == 3)
  {
    find(argv[1], argv[1], argv[2], 1);
    exit(0);
  }
  else if (argc > 3 && strcmp(argv[3], "-exec") == 0)
  {
    int fds[2];
    pipe(fds);
    if (fork() > 0)
    {
      close(fds[1]);
      char buf[512];
      int n = 0, m;
      while ((m = read(fds[0], buf + n, sizeof(buf) - n)) > 0)
      {
        n += m;
      }
      buf[n] = '\0';
      close(fds[0]);
      char *args[32];
      int num = 0;
      for (int i = 0; i < argc - 4; i++)
      {
        args[num++] = argv[4 + i];
      }
      char *start = buf, *end;
      while ((end = strchr(start, '\n')) != (char *)0)
      {
        args[num++] = start;
        *end = '\0';
        start = end + 1;
      }
      args[num] = (char *)0;
      exec(argv[4], args);
    }
    else
    {
      close(fds[0]);
      find(argv[1], argv[1], argv[2], fds[1]);
      close(fds[1]);
      exit(0);
    }
  }
  else
  {
    fprintf(2, "Usage: find path name [-exec script]\n");
    exit(1);
  }
}
