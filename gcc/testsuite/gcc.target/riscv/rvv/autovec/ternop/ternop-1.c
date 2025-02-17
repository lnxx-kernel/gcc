/* { dg-do compile } */
/* { dg-additional-options "-march=rv32gcv -mabi=ilp32d --param=riscv-autovec-preference=scalable" } */

#include <stdint-gcc.h>

#define TEST_TYPE(TYPE)                                                        \
  __attribute__ ((noipa)) void ternop_##TYPE (TYPE *__restrict dst,            \
					      TYPE *__restrict a,              \
					      TYPE *__restrict b, int n)       \
  {                                                                            \
    for (int i = 0; i < n; i++)                                                \
      dst[i] += a[i] * b[i];                                                   \
  }

#define TEST_ALL()                                                             \
  TEST_TYPE (int8_t)                                                           \
  TEST_TYPE (uint8_t)                                                          \
  TEST_TYPE (int16_t)                                                          \
  TEST_TYPE (uint16_t)                                                         \
  TEST_TYPE (int32_t)                                                          \
  TEST_TYPE (uint32_t)                                                         \
  TEST_TYPE (int64_t)                                                          \
  TEST_TYPE (uint64_t)

TEST_ALL ()

/* { dg-final { scan-assembler-times {\tvmadd\.vv} 8 } } */
/* { dg-final { scan-assembler-not {\tvmv} } } */
