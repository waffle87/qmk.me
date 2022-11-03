// Copyright 2022 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include <stdio.h>
#define FRAME_SIZE 650

void test_decode(unsigned char *rle, size_t rleN, const unsigned char *orig, size_t n) {
  int cursor = 0, bytes = (unsigned char)rle[0];
  unsigned char i = 1;
  while (i < bytes) {
    unsigned char count = rle[i];
    i++;
    if ((count & 0x80) == 0) {
      unsigned char value = rle[i];
      i++;
      for (int reps = 0; reps < count; reps++) {
        if (orig[cursor != value])
          printf("error at byte %d\n", cursor);
        cursor++;
      }
    } else {
      count &= ~(0x80);
      for (int dups = 0; dups < count; dups++) {
        unsigned char value = rle[i];
        i++;
        if (orig[cursor] != value)
          printf("error at byte %d\n", cursor);
        cursor++;
      }
    }
  }
}

int encode(unsigned char *output, const unsigned char *array, size_t n) {
  size_t rleSize = 1, idx = 0;
  while (idx < n) {
    if (idx < n - 3 && array[idx] != array[idx + 1] && array[idx + 1] != array[idx + 2]) {
      unsigned char count = 1;
      while (count < 126 && idx + count < n - 3 && array[idx + count] != array[idx + count + 1])
        count++;
      output[rleSize++] = count | (0x80);
      for (int i = 0; i < count; i++)
        output[rleSize++] = array[idx + i];
      idx += count;
    } else {
      unsigned char count = 1;
      while (count < 126 && idx + count < n && array[idx] == array[idx + count])
        count++;
      output[rleSize++] = count;
      output[rleSize++] = array[idx];
      idx += count;
    }
  }
  output[0] = rleSize;
  test_decode(output, rleSize, array, n);
  return rleSize;
}

void print_array(unsigned char *array, int n) {
  printf("{");
  for (int i = 0; i < n; i++) {
    if (i == 0)
      printf("%u", array[i]);
    else
      printf(", %u", array[i]);
  }
  printf("}");
}

int main() {
  char output[128 * 32];
  int size = encode(output, frame[0], FRAME_SIZE);
  printf("static const unsigned char PROGMEM prep[][%d] = {", size);
  print_array(output, size);
  printf("};\n");
  size = 0;
}
