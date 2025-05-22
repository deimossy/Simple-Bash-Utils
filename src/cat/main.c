#include "./cat_functions.h"

int main(int argc, char **argv) {
  Flags flags = {0};
  if (argc > 1) {
    work_with_arguments(argc, argv, &flags);
  } else {
    printf("Usage: cat [OPTION]... [FILE]...");
  }

  return 0;
}
