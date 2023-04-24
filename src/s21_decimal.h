typedef struct {
  unsigned int bits[4];
} s21_decimal;

// s21_arithmetic
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// s21_comparison
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

// s21_converter
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// s21_over
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

// s21_common
void s21_clear_decimal(s21_decimal *number);
int s21_is_empty(s21_decimal number);

unsigned int s21_get_fraction(s21_decimal number);
void s21_set_fraction(s21_decimal *number, unsigned int fraction);
unsigned int s21_get_sign(s21_decimal number);
void s21_offset_right(s21_decimal *number, int offset);
void s21_offset_left(s21_decimal *number, int offset);

int s21_set_max_fraction(s21_decimal *v1, s21_decimal *v2);

int s21_add_bits(s21_decimal v1, s21_decimal v2, s21_decimal *r);
void s21_sub_bits(s21_decimal v1, s21_decimal v2, s21_decimal *r);
int s21_mul_bits(s21_decimal v1, s21_decimal v2, s21_decimal *r);
s21_decimal s21_div_bits(s21_decimal v1, s21_decimal v2, s21_decimal *r);

int s21_div_ten(s21_decimal *value, int times);
int s21_mul_ten(s21_decimal *value);

// void bits(unsigned int a);
// void b(s21_decimal d);

// HUGE_decimal
#define BITS 8
#define OPTS BITS - 1
#define NUMS BITS - 2
typedef struct {
  unsigned int bits[BITS];
} big_decimal;

void s21_make_bigger(s21_decimal src, big_decimal *dst);
int s21_make_smaller(big_decimal src, s21_decimal *dst);
int s21_is_big_empty(big_decimal number);

unsigned int s21_get_big_fraction(big_decimal number);
void s21_set_big_fraction(big_decimal *number, unsigned int fraction);

int s21_add_big_bits(big_decimal v1, big_decimal v2, big_decimal *r);
big_decimal s21_div_big_bits(big_decimal v1, big_decimal v2, big_decimal *r);
int s21_mul_big_bits(big_decimal v1, big_decimal v2, big_decimal *r);

int s21_mul_ten_big(big_decimal *value);
int s21_div_ten_big(big_decimal *value, int times);
int s21_div_ten_nr_big(big_decimal *value, int times);

// void b_big(big_decimal d);