#include <stdio.h>
#include <gmp.h>

#define FIB_INDEX 1000000

int main(void)
{
    mpz_t a, b, temp;

    mpz_init(a);
    mpz_init(b);
    mpz_init(temp);

    // F(0) = 0, F(1) = 1
    mpz_set_ui(a, 1);
    mpz_set_ui(b, 1);

    for (int i = 0; i < FIB_INDEX; i++)
    {
        mpz_add(temp, a, b);
        mpz_set(a, b);
        mpz_set(b, temp);
    }

    // a = F(1,000,000)

    FILE *file = fopen("genfib.bin", "w");
    if (!file)
    {
        perror("fopen");
        return 1;
    }

    // Write decimal representation
    mpz_out_str(file, 10, a);
    // fputc('\n', file);

    fclose(file);

    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(temp);

    printf("Fibonacci number %d saved to genfib.bin\n", FIB_INDEX);

    return 0;
}
