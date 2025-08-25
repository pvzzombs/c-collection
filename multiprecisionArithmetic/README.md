## Multiprecision Arithmetic

See `test.c`.

## Big Integer
### Initialization
`BigInt_init` - Initialize `BigInt` to zero.  
`BigInt_init_from_string` - Initialize `BigInt` from string.  
`BigInt_to_string` - Convert `BigInt` to string.  
`BigInt_swap` - Swap two `BigInt`.  
`BigInt_destroy` - Destroy `BigInt`.  
`BigInt_cmp` - Compare `BigInt`.  
`BigInt_add` - Add `BigInt`.  
`BigInt_subtract` - Subtract `BigInt`.  
`BigInt_multiply` - Multiply `BigInt`.  
`BigInt_divide` - Divide `BigInt`.  

### Example/s:

```c
char num1[] = "9876543210987654321987654321";
char num2[] = "12345678901234567890";
char * s;

BigInt a, b, c;

BigInt_init_from_string(&a, num1);
BigInt_init_from_string(&b, num2);
BigInt_init(&c);

BigInt_add(&c, &a, &b);
s = BigInt_to_string(&c);
printf("%s\n",s);
free(s);
BigInt_subtract(&c, &a, &b);
s = BigInt_to_string(&c);
printf("%s\n",s);
free(s);
BigInt_multiply(&c, &a, &b);
s = BigInt_to_string(&c);
printf("%s\n",s);
free(s);
BigInt_divide(&c, &a, &b);
s = BigInt_to_string(&c);
printf("%s\n",s);
free(s);

BigInt_destroy(&a);
BigInt_destroy(&b);
BigInt_destroy(&c);

```