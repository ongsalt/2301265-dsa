#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  long *data;
  long size;
  long capacity;
} IntArray;

typedef unsigned long long int u64;

// Global sieve cache
static bool *cached_sieve = NULL;
static u64 cached_size = 0;

void ensure_sieve(u64 n) {
  if (cached_sieve == NULL || cached_size < n) {
    if (cached_sieve) free(cached_sieve);
    
    cached_size = n;
    cached_sieve = calloc(n + 1, sizeof(bool));
    
    for (u64 i = 2; i <= n; i++)
      cached_sieve[i] = true;
    
    for (u64 i = 2; i * i <= n; i++) {
      if (cached_sieve[i]) {
        for (u64 j = i * i; j <= n; j += i) {
          cached_sieve[j] = false;
        }
      }
    }
  }
}

IntArray createArray(u64 capacity) {
  IntArray arr;
  arr.data = malloc(capacity * sizeof(u64));
  arr.size = 0;
  arr.capacity = capacity;
  return arr;
}

void pushArray(IntArray *arr, u64 value) {
  if (arr->size >= arr->capacity) {
    arr->capacity *= 2;
    arr->data = realloc(arr->data, arr->capacity * sizeof(u64));
  }
  arr->data[arr->size++] = value;
}

IntArray getPrimeFactors(u64 n) {
  IntArray result = createArray(32);

  if (n <= 1)
    return result;

  ensure_sieve(n);

  u64 num = n;
  for (u64 i = 2; i <= num; i++) {
    if (cached_sieve[i]) {
      while (num % i == 0) {
        pushArray(&result, i);
        num /= i;
      }
    }
  }

  return result;
}

IntArray findCommon(IntArray a, IntArray b) {
  IntArray result = createArray(32);

  // Simple approach: for each element in a, find it in b and remove it
  bool *used = calloc(b.size, sizeof(bool));

  for (u64 i = 0; i < a.size; i++) {
    for (u64 j = 0; j < b.size; j++) {
      if (!used[j] && a.data[i] == b.data[j]) {
        pushArray(&result, a.data[i]);
        used[j] = true;
        break;
      }
    }
  }

  free(used);
  return result;
}

u64 gcd(u64 m, u64 n) {
  IntArray mFactors = getPrimeFactors(m);
  IntArray nFactors = getPrimeFactors(n);
  IntArray common = findCommon(mFactors, nFactors);

  u64 result = 1;
  for (u64 i = 0; i < common.size; i++) {
    result *= common.data[i];
  }

  free(mFactors.data);
  free(nFactors.data);
  free(common.data);

  return result;
}

int main() {
  printf("gcd(81786288,61052652) = %llu\n", gcd(81786288, 61052652));
  printf("gcd(3234496,7268362) = %llu\n", gcd(3234496, 7268362));
  printf("gcd(8356954,3705742) = %llu\n", gcd(8356954, 3705742));
  printf("gcd(81786288,61052652) = %llu\n", gcd(81786288, 61052652));
  printf("gcd(21535993,91675657) = %llu\n", gcd(21535993, 91675657));
  printf("gcd(26586591,78851391) = %llu\n", gcd(26586591, 78851391));
  printf("gcd(68575643,45017255) = %llu\n", gcd(68575643, 45017255));
  printf("gcd(45991767,77583796) = %llu\n", gcd(45991767, 77583796));
  printf("gcd(459917672,775837965) = %llu\n", gcd(459917672, 775837965));
  printf("gcd(265865917,788513914) = %llu\n", gcd(265865917, 788513914));
  printf("gcd(685756433,450172557) = %llu\n", gcd(685756433, 450172557));
  printf("gcd(785756437,102475659) = %llu\n", gcd(785756437, 102475659));
  printf("gcd(504857673,354879547) = %llu\n", gcd(504857673, 354879547));
  printf("gcd(4737418245,9465215337) = %llu\n", gcd(4737418245, 9465215337));
  printf("gcd(7384184877,6565315335) = %llu\n", gcd(7384184877, 6565315335));
  printf("gcd(6531741823,8795491761) = %llu\n", gcd(6531741823, 8795491761));
  printf("gcd(5865583711,9535851393) = %llu\n", gcd(5865583711, 9535851393));
  printf("gcd(6954464645,8017257569) = %llu\n", gcd(6954464645, 8017257569));
  printf("gcd(84184418245,65310172575) = %llu\n",
         gcd(84184418245, 65310172575));
  printf("gcd(58659151391,85756451391) = %llu\n",
         gcd(58659151391, 85756451391));
  printf("gcd(57564301725,74851857673) = %llu\n",
         gcd(57564301725, 74851857673));
  printf("gcd(59917672487,88512663377) = %llu\n",
         gcd(59917672487, 88512663377));
  printf("gcd(65315344641,98418485851) = %llu\n",
         gcd(65315344641, 98418485851));
  printf("gcd(789176724879,659151396733) = %llu\n",
         gcd(789176724879, 659151396733));
  printf("gcd(659117416437,946585181391) = %llu\n",
         gcd(659117416437, 946585181391));
  printf("gcd(653184188245,758331017965) = %llu\n",
         gcd(653184188245, 758331017965));
  printf("gcd(841818235337,767318488245) = %llu\n",
         gcd(841818235337, 767318488245));
  printf("gcd(953525754641,658518571823) = %llu\n",
         gcd(953525754641, 658518571823));
  
  if (cached_sieve) free(cached_sieve);
  return 0;
}