## Multiprecision Arithmetic

See `test.c`.

## Big Integer
### Common functions
`BigInt_init` - Initialize `BigInt` to zero.  
`BigInt_init_from_string` - Initialize `BigInt` from string.  
`BigInt_set_from_string` - Set already initialized `BigInt` from string.  
`BigInt_to_string` - Convert `BigInt` to string.  
`BigInt_swap` - Swap two `BigInt`.  
`BigInt_destroy` - Destroy `BigInt`.  
`BigInt_cmp` - Compare `BigInt`.  
`BigInt_add` - Add `BigInt`.  
`BigInt_subtract` - Subtract `BigInt`.  
`BigInt_multiply` - Multiply `BigInt`.  
`BigInt_divide` - Divide `BigInt`.  

### Example/s:

**NOTE**: Please ensure that the **minuend is bigger** than or **equal** to the **subtrahend** and that the **dividend is bigger** than or **equal** to the **divisor**. If not correctly done, might lead to unintended results.

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
Use a number from user input: 
```c
char num1[1024];
char num2[1024];
char * s;

BigInt a, b, c;
int index;
char * end;

BigInt_init(&a);
BigInt_init(&b);
BigInt_init(&c);

printf("Enter first number: ");
fgets(num1, 1024, stdin);
printf("Enter second number: ");
fgets(num2, 1024, stdin);

end = strstr(num1, "\n");
num1[end - num1] = 0;
end = strstr(num2, "\n");
num2[end - num2] = 0;

BigInt_set_from_string(&a, num1);
BigInt_set_from_string(&b, num2);

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

## Performance Results:
### Windows 10 benchmark results:
```
Processor	AMD A6-7480 Radeon R5, 8 Compute Cores 2C+6G      3.50 GHz
System Type	64-bit operating system, x64-based processor
```
```
Addition performance test...
Average: 4907433 per second.
Multiplication performance test...
Average: 145545 per second.
Subtraction performance test...
Average: 4529856 per second.
Division performance test...
Average: 258892 per second.
```
### Porteus 5.01 (Linux) benchmark results:
```
OS: Porteus 5.01 x86_64
Host: Hewlett-Packard 172A
Kernel: 6.12.5-porteus
CPU: Intel i7 M 620 (2) @ 2.667GHz
```
```
Addition performance test...
Average: 4341531 per second.
Multiplication performance test...
Average: 122977 per second.
Subtraction performance test...
Average: 4413290 per second.
Division performance test...
Average: 555831 per second.

```
### How to perform benchmarking?
Please kindly run `performance` or `performance.exe`.