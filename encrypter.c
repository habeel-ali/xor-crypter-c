#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage: encrypter.exe <file_path>");
    return 1;
  }

  FILE *fptr = fopen(argv[1], "r");
  size_t path_length = strlen(argv[1]);
  size_t suffix_length = strlen("-encrypted");
  size_t outname_length = path_length + suffix_length + 1;

  char *outname = malloc(outname_length);
  snprintf(outname, outname_length, "%s-encrypted", argv[1]);

  FILE *out = fopen(outname, "w");

  if (!fptr)
  {
    printf("Error: failed to open file.");
    return 2;
  }

  char encryptionKey;
  printf("Enter XOR encryption key: ");
  getchar();
  if (scanf("%c", &encryptionKey) != 1)
  {
    fprintf(stderr, "Error reading encryption key.\n");
    fclose(fptr);
    return 3;
  }

  char *line = NULL;
  size_t length = 0;
  ssize_t nread;

  while ((nread = getline(&line, &length, fptr)) != -1)
  {
    for(ssize_t i = 0; i < nread; i++) {
      line[i] = line[i] ^ encryptionKey;
      fputc(line[i], out);
      putchar(line[i]);
    }
  }

  if (ferror(fptr))
  {
    perror("Error: failed to read file.");
    return 4;
  }

  free(line);
  free(outname);
  fclose(fptr);
  putchar('\n');
  return 0;
}
