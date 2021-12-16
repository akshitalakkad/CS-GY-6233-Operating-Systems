#include "types.h"

#include "stat.h"

#include "user.h"


char bf[100000];

char * args;

char * String_Lower(char string[]) {
  int i = 0;
  while (string[i] != '\0') {
    if (string[i] >= 'A' && string[i] <= 'Z') {
      string[i] = string[i] + 32;
    }
    i++;
  }
  return string;
}

int uniq(int fd, int cflag, int dflag, int iflag) {

  char * op[10000];

  char cp[10000];

  int count[10000] = {
    1
  };
  int linecount = 0, index = 0, c1 = 0, c2 = 0, fin = 0, m = 0;
  int n, i, x, k, y;

  while ((n = read(fd, bf, sizeof(bf))) > 0) {

    for (i = 0; i < n; i++) {

      if (bf[i] == '\n') {

        linecount++;

      }

    }

    for (i = 0; bf[i] != '\n'; i++) {

      cp[i] = bf[i];
      c1 = c1 + 1;

    }

    cp[i] = '\0';

    op[0] = (char * ) malloc((c1 + 1) * sizeof(char * ));

    for (i = 0; i < c1 + 1; i++) {

      op[index][i] = cp[i];

    }

    op[index][i] = '\0';

    k = i;

    while (fin < linecount - 1) {

      fin++;

      c2 = 0;

      for (i = k; bf[i] != '\n'; i++) {

        c2++;

        cp[m++] = bf[i];

      }

      cp[m] = '\0';

      k = k + c2 + 1;

      m = 0;
      if (iflag == 0) {
        if (strcmp(op[index], cp) != 0) {

          index = index + 1;

          op[index] = (char * ) malloc((c2 + 1) * sizeof(char * ));

          for (y = 0; y < c2; y++) {

            op[index][y] = cp[y];

          }

          op[index][y] = '\0';

          count[index] = 1;

        } else {

          count[index] = count[index] + 1;

        }
      } else {
        if (strcmp(String_Lower(op[index]), String_Lower(cp)) != 0) {

          index = index + 1;

          op[index] = (char * ) malloc((c2 + 1) * sizeof(char * ));

          for (y = 0; y < c2; y++) {

            op[index][y] = cp[y];

          }

          op[index][y] = '\0';

          count[index] = 1;

        } else {

          count[index] = count[index] + 1;

        }
      }

    }

  }

  if (cflag == 1) {

    for (x = 0; x < index + 1; x++) {
      if (op[x] != '\0') {

        printf(1, "%d %s \n", count[x], op[x]);

      }
    }

  } else if (dflag == 1) {

    for (x = 0; x < index + 1; x++) {

      if (count[x] > 1) {

        printf(1, "%s \n", op[x]);

      }

    }

  } else if (iflag == 1) {

    for (x = 0; x < index + 1; x++) {

      printf(1, "%s \n", op[x]);

    }

  } else {
    for (x = 0; x < index + 1; x++) {

      printf(1, "%s \n", op[x]);

    }

  }

  free(op);

  return 0;

}

int main(int argc, char * argv[]) {

  int fd, i;
  int cflag = 0, dflag = 0, iflag = 0;

  if (argc <= 1) {

    uniq(0, 0, 0, 0);

    exit();

  } else {

    for (i = 0; i < argc; i++) {
      char * arg = argv[i];
      if (strcmp(arg, "-c") == 0 || strcmp(arg, "-C") == 0) {
        cflag = 1;
      } else if (strcmp(arg, "-d") == 0 || strcmp(arg, "-D") == 0) {
        dflag = 1;
      } else if (strcmp(arg, "-i") == 0 || strcmp(arg, "-I") == 0) {
        iflag = 1;
      }
    }

  }

  if ((fd = open(argv[argc - 1], 0)) < 0) {

    printf(1, "Cannot open\n");
    exit();

  } else {

    //args=argv[1];

    uniq(fd, cflag, dflag, iflag);
  }
  close(fd);

  /*else {

  for(i=0; i<argc; i++) {

  if((fd = open(argv[argc-1],0))<0) {  

  printf(1, "Cannot open\n");

  } else {

  args=argv[1];

  uniq(fd,argv[i]);


  }

  close(fd);

  }

  }*/

  exit();

}
