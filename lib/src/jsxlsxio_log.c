#include <stdio.h>
#include <stdlib.h>

FILE *log_stdout = NULL;
FILE *log_stdinf = NULL;
FILE *log_stddbg = NULL;
FILE *log_stdwrn = NULL;
FILE *log_stderr = NULL;

const char *assert_header = "[Assert Failure]";
const char *expect_header = "[Expect Failure]";

void flush_logs(void) {
  fflush(log_stdout);
  fflush(log_stderr);
}
