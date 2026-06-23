# Documentation and Notes
## BigInt
`BigInt` functions are easy to use, you can check the README for an example and read the function declarations list from the main `bigInteger.h` file, but here are some functions of interest:

### Initialization:
`BigInt_init` - Initialize `BigInt` to zero  
`BigInt_init_*` - Initialize `BigInt` to whatever `*` means  
`BigInt_init_*_limb` - Initialize `BigInt` to whatever `*` means, but you must specify the number of limbs to use and allocate...  
`BigInt_init_from_string`, `BigInt_init_from_string_with_sign` - Initlalize `BigInt` from C string  

### Destruction
`BigInt_destroy` - Release `BigInt` memory allocations

### Utilities
`BigInt_copy` - Copies `BigInt`  
`BigInt_copy_to_no_init` - Copies `BigInt`, but the destination does not need to be initialized first  
`BigInt_swap` - Swap two `BigInt`s  
`BigInt_cmp`, `BigInt_cmp_with_sign` - Compare two `BigInt`s, latter having a sign  
`BigInt_remove_leading_zeroes` - Remove leading zeroes  
`BigInt_add_leading_zero` - Add one leading zero  
`BigInt_add_leading_zeroes` - Add multiple leading zeroes  
`BigInt_print`, `BigInt_print_s` - Print `BigInt`, latter having a sign  
`BigInt_set_from_string`, `BigInt_set_from_string_with_sign` - Set already initialized `BigInt` from C string  
`BigInt_count_digits_base_10` - Count decimal digits of `BigInt`  
`BigInt_print_internal` - Print internal representation of `BigInt`  

### Arithmetic
`BigInt_add`, `BigInt_subtract`, `BigInt_multiply`, `BigInt_divide` - Core arithmetic functions  
`BigInt_add_wtih_sign`, `BigInt_subtract_wtih_sign`, `BigInt_multiply_wtih_sign`, `BigInt_divide_wtih_sign` - Core arithmetic functions, but deals with sign  
`BigInt_add_small`, `BigInt_multiply_small` - `BigInt` and `BigInt_limb_t` operands  
`BigInt_add_t`, `BigInt_subtract_t`, `BigInt_multiply_t`, `BigInt_divide_t` - Core arithmetic functions, but stores the answer to temporary before copying to destination  
`BigInt_add_ts`, `BigInt_subtract_ts`, `BigInt_multiply_ts`, `BigInt_divide_ts` - Core arithmetic functions, but stores the answer to temporary before copying to destination, and deals with sign  
`BigInt_shift_left`, `BigInt_shift_right` - Shift `BigInt` by a specific amount to the preferred direction  
`BigInt_multiply_karatsuba`, `BigInt_multiply_karatsuba_with_sign` - Karatusba algorithm implementation for fast multiplication  
`BigInt_multiply_karatsuba_t`, `BigInt_multiply_karatsuba_ts` - Same as above but stores in temporary before copying  
`BigInt_multiply_auto`, `BigInt_multiply_auto_with_sign`, `BigInt_multiply_auto_t`, `BigInt_multiply_auto_ts` - Automatically chooses best multiplication algorithm for the current size of `BigInt` operands  