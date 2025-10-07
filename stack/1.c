#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  size_t capacity;
  size_t size;
  char* items;
} Stack＜char＞;

typedef struct {
  bool is_some;
  char value;  // this is pain
} Option＜char＞;

Stack＜char＞ new(size_t initial_capacity) {
  Stack＜char＞ stack = {
    .capacity = 128,
    .size = 0,
    .items = malloc(sizeof(char) * 128)
  };
  return stack;
}

void push(Stack＜char＞* stack, char c) {
  if (stack->capacity == stack->size) {
    stack->capacity *= 2;
    realloc(stack->items, stack->capacity);
  }
  stack->items[stack->size] = c;
  stack->size += 1;
}

Option＜char＞ pop(Stack＜char＞* stack) {
  Option＜char＞ o = {0};
  if (stack->size != 0) {
    stack->size -= 1;
    o.value = stack->items[stack->size];
    o.is_some = true;
  }
  return o;
}

int main() {
  char input[] =
    "let mut b = 8; for a in 1..10 { println!(\"Hello {a} {b}\"); b += a; }";

  char* cursor = input;
}