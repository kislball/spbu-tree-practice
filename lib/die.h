#pragma once

// Преждевременно завершает работу программу, если condition == true
#define dieIf(condition, text)                                                 \
  do {                                                                         \
    if (condition) {                                                           \
      fprintf(stderr, "died because %s, %s:%d:\t%s\n", text, __FILE__,         \
              __LINE__, #condition);                                           \
      exit(EXIT_FAILURE);                                                      \
    }                                                                          \
  } while (0)

// Преждевременно завершает работу программу, если condition == false
#define dieIfNot(condition, text) dieIf(!(condition), text)
