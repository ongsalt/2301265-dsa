#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// translated from rust impl by claude

bool check(unsigned int* seq, size_t n) {
  // all length 3 subsequences
  for (size_t i = 0; i < n; i++) {
    for (size_t j = i + 1; j < n; j++) {
      for (size_t k = j + 1; k < n; k++) {
        if (seq[i] + seq[k] == seq[j] * 2) {
          printf("%u %u %u at %zu %zu %zu\n", seq[i], seq[j], seq[k], i, j, k);
          return false;
        }
      }
    }
  }
  return true;
}

unsigned int* solve_optimized(unsigned int n, size_t* result_size) {
  unsigned int p = 3;
  while (p < n) {
    p *= 2;
  }

  unsigned int* seq = (unsigned int*)malloc(p * sizeof(unsigned int));
  if (seq == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  size_t size = 3;
  seq[0] = 0;
  seq[1] = 2;
  seq[2] = 1;

  while (size < n) {
    for (size_t i = 0; i < size; i++) {
      seq[i] *= 2;
      seq[i + size] = seq[i] + 1;
    }
    size *= 2;
  }

  // Filter elements >= n and count valid elements
  size_t count = 0;
  for (size_t i = 0; i < p; i++) {
    if (seq[i] < n) {
      count++;
    }
  }

  // Create result array with only valid elements
  unsigned int* result = (unsigned int*)malloc(count * sizeof(unsigned int));
  if (result == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    free(seq);
    exit(1);
  }

  // show result
  size_t idx = 0;
  for (size_t i = 0; i < p; i++) {
    if (seq[i] < n) {
      result[idx++] = seq[i];
    }
  }

  free(seq);
  *result_size = count;
  return result;
}

int main() {
  unsigned int n;
  if (scanf("%u", &n) != 1) {
    fprintf(stderr, "Failed to read input\n");
    return 1;
  }
  n++;  // Add 1 like in the Rust version

  size_t size;
  unsigned int* seq = solve_optimized(n, &size);

  // Print the sequence
  for (size_t i = 0; i < size; i++) {
    if (i > 0)
      printf(" ");
    printf("%u", seq[i]);
  }
  printf("\n");

  // Check the solution
  if (!check(seq, size)) {
    printf("failed\n");
  }

  free(seq);
  return 0;
}
