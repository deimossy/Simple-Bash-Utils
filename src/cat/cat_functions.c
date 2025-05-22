#include "./cat_functions.h"

void print_data_from_file(int argc, char **argv, int index, Flags *flags) {
  int flag_status = Flag_No_Error;

  for (; index < argc && flag_status == Flag_No_Error; index++) {
    FILE *file = fopen(argv[index], "r");

    if (file == NULL) {
      flag_status = File_Error;
      fprintf(stderr, "cat: %s: No such file or directory\n", argv[index]);
    } else {
      apply_flags(flags, file);
      fclose(file);
    }
  }
}

void work_with_arguments(int argc, char **argv, Flags *flags) {
  int error_flag = parsing_flags(flags, argc, argv);
  int file_index = -1;

  if (error_flag == Flag_No_Error) {
    int file_status = get_file_index(argc, argv, &file_index);
    if (file_status == Flag_No_Error) {
      print_data_from_file(argc, argv, file_index, flags);
    }
  }
}

int parsing_flags(Flags *options, int argc, char **argv) {
  int flag_status = Flag_No_Error;

  char *flags_short = "benstvET";
  struct option flags_long[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                {"number", no_argument, NULL, 'n'},
                                {"squeeze-blank", no_argument, NULL, 's'},
                                {NULL, 0, NULL, 0}};

  int rez;
  while (flag_status == Flag_No_Error &&
         (rez = getopt_long(argc, argv, flags_short, flags_long, NULL)) != -1) {
    if (rez == '?') {
      fprintf(stderr, "cat: invalid option -- '%c'\n", optopt);
      fprintf(stderr, "Try 'cat --help' for more information.\n");
      flag_status = Invalid_Error;
    } else {
      flag_status = set_flag(options, rez);
    }
  }

  return flag_status;
}

int set_flag(Flags *options, int rez) {
  int flag_status = Flag_No_Error;

  switch (rez) {
    case 'b':
      options->flag_b = 1;
      break;
    case 'e':
      options->flag_e = 1;
      options->flag_v = 1;
      break;
    case 'n':
      options->flag_n = 1;
      break;
    case 's':
      options->flag_s = 1;
      break;
    case 't':
      options->flag_t = 1;
      options->flag_v = 1;
      break;
    case 'v':
      options->flag_v = 1;
      break;
    case 'E':
      options->flag_e = 1;
      break;
    case 'T':
      options->flag_t = 1;
      break;
    case '?':
    default:
      flag_status = Invalid_Error;
      break;
  }

  return flag_status;
}

int get_file_index(int argc, char **argv, int *index) {
  int flag_status = File_Error;

  for (int i = optind; i < argc && flag_status == File_Error; i++) {
    if (argv[i][0] != '-') {
      flag_status = Flag_No_Error;
      *index = i;
    }
  }

  return flag_status;
}

void apply_flags(Flags *flags, FILE *file) {
  int cur_ch = 10, past_ch = 10;
  static int lines_counter = 1;
  int squeeze_counter = 0;
  int line_status = 1;

  while ((cur_ch = fgetc(file)) != EOF) {
    if (flags->flag_s) {
      if (check_squeeze_lines(cur_ch, past_ch, &squeeze_counter)) {
        continue;
      }
    }

    if (flags->flag_b || flags->flag_n) {
      print_line_count(cur_ch, &lines_counter, line_status, flags);
    }

    if (flags->flag_t) {
      processing_opt_t(&cur_ch);
    }

    if (flags->flag_e) {
      processing_opt_e(cur_ch);
    }

    if (flags->flag_v) {
      processing_opt_v(&cur_ch);
    }

    printf("%c", cur_ch);
    past_ch = cur_ch;
    line_status = (cur_ch == '\n' ? 1 : 0);
  }
}

int check_squeeze_lines(int cur, int prev, int *counter) {
  if (cur == '\n' && prev == '\n') {
    *counter += 1;
  } else {
    *counter = 0;
  }

  return (*counter > 1 ? 1 : 0);
}

void print_line_count(int cur_ch, int *lines_counter, int line_status,
                      Flags *flags) {
  if (flags->flag_b) {
    if (line_status && cur_ch != '\n') {
      printf("%6d\t", (*lines_counter)++);
    }
  } else {
    if (line_status) {
      printf("%6d\t", (*lines_counter)++);
    }
  }
}

void processing_opt_t(int *cur_ch) {
  if (*cur_ch == '\t') {
    printf("^");
    *cur_ch = 'I';
  }
}

void processing_opt_e(int cur_ch) {
  if (cur_ch == '\n') {
    printf("$");
  }
}

void processing_opt_v(int *cur_ch) {
  if ((*cur_ch >= 0 && *cur_ch < 9) || (*cur_ch > 10 && *cur_ch < 32)) {
    *cur_ch += 64;
    printf("^");
  } else if (*cur_ch == 127) {
    *cur_ch = 63;
    printf("^");
  }
}