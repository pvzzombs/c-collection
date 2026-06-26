#pragma once

#include "bigInteger.h"

#ifdef __cplusplus
extern "C" {
#endif

void BigInt_multiply_toomcook3_impl(BigInt *, BigInt *, BigInt *);
void BigInt_multiply_toomcook3(BigInt *, BigInt *, BigInt *);

#if defined(BIGINT_IMPL) || defined(MPA_IMPL)

void BigInt_multiply_toomcook3_impl(BigInt * multiplicand, BigInt * multiplier, BigInt * product) {
  if (multiplicand->internalSize < BIGINT_TOOMCOOK3_THRESHOLD && multiplier->internalSize < BIGINT_TOOMCOOK3_THRESHOLD) {
    BigInt_multiply_with_sign(product, multiplicand, multiplier);
  } else {
    BigInt x_0, x_1, x_2;
    BigInt y_0, y_1, y_2;
    BigInt x0, x1, xn1, x2, xinf;
    BigInt y0, y1, yn1, y2, yinf;
    BigInt x2_2x_1, x2_4x_2;
    BigInt y2_2y_1, y2_4y_2;
    BigInt two, four, sixteen, six;
    BigInt w0, w1, w2, wn1, winf;
    BigInt c0, c1, c2, c3, c4;
    BigInt s, d, u, temp1, temp2, temp3;
    int l = BigInt_max_int(multiplicand->internalSize, multiplier->internalSize);
    int b = (l + 2) / 3;
    int len1, len2, lenMax;
    
    /* if (l % 3 > 0) {
      b++;
    }*/
    /*lenMax = l;
    if (multiplier->internalSize > lenMax) {
      lenMax = multiplier->internalSize;
    }*/
    
    BigInt_init_none(&x_0);
    BigInt_init_none(&x_1);
    BigInt_init_none(&x_2);
    
    BigInt_init_none(&y_0);
    BigInt_init_none(&y_1);
    BigInt_init_none(&y_2);
    
    BigInt_init_none(&x0);
    BigInt_init(&x1);
    BigInt_init(&xn1);
    BigInt_init(&x2);
    BigInt_init_none(&xinf);
    
    BigInt_init_none(&y0);
    BigInt_init(&y1);
    BigInt_init(&yn1);
    BigInt_init(&y2);
    BigInt_init_none(&yinf);
    
    BigInt_init_none(&w0);
    BigInt_init_none(&w1);
    BigInt_init_none(&wn1);
    BigInt_init_none(&w2);
    BigInt_init_none(&winf);
    
    BigInt_init_none(&c0);
    BigInt_init_none(&c1);
    BigInt_init_none(&c2);
    BigInt_init_none(&c3);
    BigInt_init_none(&c4);
    
    BigInt_init_none(&x2_2x_1);
    BigInt_init_none(&x2_4x_2);
    
    BigInt_init_none(&y2_2y_1);
    BigInt_init_none(&y2_4y_2);
    
    BigInt_init_none(&two);
    BigInt_init_none(&four);
    BigInt_init_none(&sixteen);
    BigInt_init_none(&six);
    
    BigInt_init_none(&s);
    BigInt_init_none(&d);
    BigInt_init_none(&u);
    BigInt_init_none(&temp1);
    BigInt_init_none(&temp2);
    BigInt_init_none(&temp3);
    
    BigInt_set_from_limb(&two, 2, BIGINT_BASE);
    BigInt_set_from_limb(&four, 4, BIGINT_BASE);
    BigInt_set_from_limb(&sixteen, 16, BIGINT_BASE);
    BigInt_set_from_limb(&six, 6, BIGINT_BASE);
    
    BigInt_set_positive_sign(&two);
    BigInt_set_positive_sign(&four);
    BigInt_set_positive_sign(&sixteen);
    BigInt_set_positive_sign(&six);
    
    /*printf("-----------\n");
    printf("b: %d, l: %d\n", b, l);*/
    
    BigInt_set_from_view(&x_0, multiplicand, 0, b - 1);
    BigInt_set_from_view(&x_1, multiplicand, b, 2 * b - 1);
    BigInt_set_from_view(&x_2, multiplicand, 2 * b, l - 1);
    
    BigInt_set_from_view(&y_0, multiplier, 0, b - 1);
    BigInt_set_from_view(&y_1, multiplier, b, 2 * b - 1);
    BigInt_set_from_view(&y_2, multiplier, 2 * b, l - 1);
    
    x_0.sign = multiplicand->sign;
    x_1.sign = multiplicand->sign;
    x_2.sign = multiplicand->sign;
    
    y_0.sign = multiplier->sign;
    y_1.sign = multiplier->sign;
    y_2.sign = multiplier->sign;
    
    /* x(1) = (x_0 + x_1 + x_2)*/
    BigInt_add_ts(&x1, &x1, &x_0);
    BigInt_add_ts(&x1, &x1, &x_1);
    BigInt_add_ts(&x1, &x1, &x_2);
    
    /* y(1) = (y_0 + y_1 + y_2)*/
    BigInt_add_ts(&y1, &y1, &y_0);
    BigInt_add_ts(&y1, &y1, &y_1);
    BigInt_add_ts(&y1, &y1, &y_2);
    
    /* x(-1) = (x_0 - x_1 + x_2) */
    BigInt_add_ts(&xn1, &xn1, &x_0);
    BigInt_subtract_ts(&xn1, &xn1, &x_1);
    BigInt_add_ts(&xn1, &xn1, &x_2);
    
    /* y(-1) = (y_0 - y_1 + y_2) */
    BigInt_add_ts(&yn1, &yn1, &y_0);
    BigInt_subtract_ts(&yn1, &yn1, &y_1);
    BigInt_add_ts(&yn1, &yn1, &y_2);
    
    BigInt_multiply_with_sign(&x2_2x_1, &two, &x_1);
    BigInt_multiply_with_sign(&x2_4x_2, &four, &x_2);
    
    BigInt_multiply_with_sign(&y2_2y_1, &two, &y_1);
    BigInt_multiply_with_sign(&y2_4y_2, &four, &y_2);
    
    /* x(2) = (x_0 + 2 * x_1 + 4 * x_2) */
    BigInt_add_ts(&x2, &x2, &x_0);
    BigInt_add_ts(&x2, &x2, &x2_2x_1);
    BigInt_add_ts(&x2, &x2, &x2_4x_2);
    
    /* y(2) = (y_0 + 2 * y_1 + 4 * y_2) */
    BigInt_add_ts(&y2, &y2, &y_0);
    BigInt_add_ts(&y2, &y2, &y2_2y_1);
    BigInt_add_ts(&y2, &y2, &y2_4y_2);
    
    /* x(0) = x_0, y(0) = y_0 */
    BigInt_copy(&x0, &x_0);
    BigInt_copy(&y0, &y_0);
    
    /*printf("x0 is: ");
    BigInt_print_internal(&x0);
    printf("x_0 is ");
    BigInt_print_internal(&x_0);*/
    
    /* x(inf) = x_2, y(inf) = y_2 */
    BigInt_copy(&xinf, &x_2);
    BigInt_copy(&yinf, &y_2);
    
    /* w(0) = x(0) * y(0) */
    BigInt_multiply_toomcook3_impl(&x0, &y0, &w0);
    /* BigInt_remove_leading_zeroes(&w0); */
    /*BigInt_multiply(&temp1, &x0, &y0);
    if (BigInt_cmp(&temp1, &w0) != 0) {
      printf("Expected: ");
      BigInt_print_internal(&temp1);
      printf("Actual: ");
      BigInt_print_internal(&w0);
      printf("Error! w0 mismatch\n");
      exit(1);
    }*/

    /* w(inf) = x(inf) * y(inf) */
    BigInt_multiply_toomcook3_impl(&xinf, &yinf, &winf);
    /* BigInt_remove_leading_zeroes(&winf); */
    /*BigInt_multiply(&temp1, &xinf, &yinf);
    if (BigInt_cmp(&temp1, &winf) != 0) {
      printf("Error! winf mismatch\n");
      printf("xinf: ");
      BigInt_print_internal(&xinf);

      printf("yinf: ");
      BigInt_print_internal(&yinf);
      exit(1);
    }*/
    
    /* w(1) = x(1) * y(1) */
    BigInt_multiply_toomcook3_impl(&x1, &y1, &w1);
    /* BigInt_remove_leading_zeroes(&w1); */
    /* BigInt_multiply(&temp1, &x1, &y1);
    if (BigInt_cmp(&temp1, &w1) != 0) {
      printf("x1");
      BigInt_print_internal(&x1);
      printf("y1");
      BigInt_print_internal(&x1);
      printf("Error! w1 mismatch\n");
      exit(1);
    }*/
    
    /* w(-1) = x(-1) * y(-1) */
    BigInt_multiply_toomcook3_impl(&xn1, &yn1, &wn1);
    /* BigInt_remove_leading_zeroes(&wn1); */
    /* BigInt_multiply(&temp1, &xn1, &yn1);
    if (BigInt_cmp(&temp1, &wn1) != 0) {
      printf("Error! w0 mismatch\n");
      exit(1);
    } */
    
    /* w(2) = x(2) * y(2) */
    BigInt_multiply_toomcook3_impl(&x2, &y2, &w2);
    /* BigInt_remove_leading_zeroes(&w2); */
    /* BigInt_multiply(&temp1, &x2, &y2);
    if (BigInt_cmp(&temp1, &w2) != 0) {
      printf("Error! w2 mismatch\n");
      exit(1);
    } */
    
    /*printf("w0 BigInt sign is %d\n", w0.sign);
    printf("w1 BigInt sign is %d\n", w1.sign);
    printf("wn1 BigInt sign is %d\n", wn1.sign);
    printf("w2 BigInt sign is %d\n", w2.sign);
    printf("winf BigInt sign is %d\n", winf.sign);*/
    
    /* c0 = w(0) */
    BigInt_copy(&c0, &w0);
    /* BigInt_remove_leading_zeroes(&c0); */
    /* c4 = w(inf) */
    BigInt_copy(&c4, &winf);
    /* BigInt_remove_leading_zeroes(&c4); */
    
    /* s = (w(1) + w(-1)) / 2 */
    BigInt_add_with_sign(&s, &w1, &wn1);
    BigInt_divide_ts(&s, &s, &two);
    
    /* d = (w(1) - w(-1)) / 2 */
    BigInt_subtract_with_sign(&d, &w1, &wn1);
    BigInt_divide_ts(&d, &d, &two);
    
    /* c2 = s - c0 - c4 */
    BigInt_subtract_with_sign(&c2, &s, &c0);
    BigInt_subtract_ts(&c2, &c2, &c4);
    /* BigInt_remove_leading_zeroes(&c2); */
    
    /* u = w(2) - c0 - 4*c2 - 16*c4 */
    BigInt_multiply_with_sign(&temp1, &four, &c2);
    BigInt_multiply_with_sign(&temp2, &sixteen, &c4);
    BigInt_subtract_with_sign(&u, &w2, &c0);
    BigInt_subtract_ts(&u, &u, &temp1);
    BigInt_subtract_ts(&u, &u, &temp2);
    
    /* c3 = (u - 2*d) / 6 */
    BigInt_multiply_with_sign(&temp3, &two, &d);
    BigInt_subtract_with_sign(&c3, &u, &temp3);
    BigInt_divide_ts(&c3, &c3, &six);
    /* BigInt_remove_leading_zeroes(&c3); */
    
    /* c1 = d - 2*c3 */
    BigInt_multiply_with_sign(&temp1, &two, &c3);
    BigInt_subtract_with_sign(&c1, &d, &c3);
    /* BigInt_remove_leading_zeroes(&c1); */
    
    BigInt_shift_left(&c4, b * 4);
    BigInt_shift_left(&c3, b * 3);
    BigInt_shift_left(&c2, b * 2);
    BigInt_shift_left(&c1, b);
    
    BigInt_add_with_sign(&temp2, &c4, &c3);
    BigInt_add_with_sign(&temp3, &c2, &c1);
    BigInt_add_with_sign(&temp1, &temp2, &temp3);
    
    BigInt_add_with_sign(product, &temp1, &c0);
    BigInt_remove_leading_zeroes(product);
    
    BigInt_destroy(&x_0);
    BigInt_destroy(&x_1);
    BigInt_destroy(&x_2);
    
    BigInt_destroy(&y_0);
    BigInt_destroy(&y_1);
    BigInt_destroy(&y_2);
    
    BigInt_destroy(&x0);
    BigInt_destroy(&x1);
    BigInt_destroy(&xn1);
    BigInt_destroy(&x2);
    BigInt_destroy(&xinf);
    
    BigInt_destroy(&y0);
    BigInt_destroy(&y1);
    BigInt_destroy(&yn1);
    BigInt_destroy(&y2);
    BigInt_destroy(&yinf);
    
    BigInt_destroy(&w0);
    BigInt_destroy(&w1);
    BigInt_destroy(&wn1);
    BigInt_destroy(&w2);
    BigInt_destroy(&winf);
    
    BigInt_destroy(&c0);
    BigInt_destroy(&c1);
    BigInt_destroy(&c2);
    BigInt_destroy(&c3);
    BigInt_destroy(&c4);
    
    BigInt_destroy(&x2_2x_1);
    BigInt_destroy(&x2_4x_2);
    
    BigInt_destroy(&y2_2y_1);
    BigInt_destroy(&y2_4y_2);
    
    BigInt_destroy(&two);
    BigInt_destroy(&four);
    BigInt_destroy(&sixteen);
    BigInt_destroy(&six);
    
    BigInt_destroy(&s);
    BigInt_destroy(&d);
    BigInt_destroy(&u);
    BigInt_destroy(&temp1);
    BigInt_destroy(&temp2);
    BigInt_destroy(&temp3);
    
  }
}

void BigInt_multiply_toomcook3(BigInt * product, BigInt * multiplicand, BigInt * multiplier) {
  if (multiplicand->internalSize < BIGINT_TOOMCOOK3_THRESHOLD && multiplier->internalSize < BIGINT_TOOMCOOK3_THRESHOLD) {
    BigInt_multiply_karatsuba_with_sign(product, multiplicand, multiplier);
  } else {
    BigInt_multiply_toomcook3_impl(multiplicand, multiplier, product);
    BigInt_remove_leading_zeroes(product);
  }
}

#endif

#ifdef __cplusplus
}
#endif
