#ifndef CAT_FUNCTIONS_H_
#define CAT_FUNCTIONS_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

enum Error_Flag { Flag_No_Error, Invalid_Error, File_Error };

typedef struct {
  int flag_b;
  int flag_e;
  int flag_n;
  int flag_s;
  int flag_t;
  int flag_v;
} Flags;

void print_data_from_file(int argc, char **argv, int index, Flags *flags);
void work_with_arguments(int argc, char **argv, Flags *flags);
int parsing_flags(Flags *options, int argc, char **argv);
int set_flag(Flags *options, int rez);
int get_file_index(int argc, char **argv, int *index);
void apply_flags(Flags *flags, FILE *file);
int check_squeeze_lines(int cur, int prev, int *counter);
void print_line_count(int cur_ch, int *lines_counter, int line_status,
                      Flags *flags);
void processing_opt_t(int *cur_ch);
void processing_opt_e(int cur_ch);
void processing_opt_v(int *cur_ch);

#endif  // CAT_FUNCTIONS_H_