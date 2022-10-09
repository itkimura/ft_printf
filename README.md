# ft_printf
This is a implementation of printf function that formats and prints data.

![Screenshot 2022-10-09 at 18 59 12](https://user-images.githubusercontent.com/61685238/194766999-336efedb-30f3-499f-891c-b3d75687d7bd.png)



## Function prototype
```
int   ft_printf(const char *format, ...);
````
## Format specifiers
A format specifier follows this prototype:
```
%[flags][width][.precision][length][type]
```
The following format specifiers are supported:

### Supported Flags
| Flag | Description |
|---|---|
| "#" | A "#" character specifying that the value should be printed in an "alternate form".  For b, c, d, s and u formats, this option has no effect.  For the o formats the precision of the number is increased to force the first character of the output string to a zero.  For the x (X) format, a non-zero result has the string 0x (0X) prepended to it.  For a, A, e, E, f, F, g and G formats, the result will always contain a decimal point, even if no digits follow the point (normally, a decimal point only appears in the results of those formats if a digit follows the decimal point).  For g and G formats, trailing zeros are not removed from the result as they would otherwise be;
| "-" | A minus sign `-' which specifies left adjustment of the output in the indicated field; |
| "+" | A "+" character specifying that there should always be a sign placed before the number when using signed formats.|
| " " | A space specifying that a blank should be left before a positive number for a signed format. A `+' overrides a space if both are used; |

### Supported Width
**(number) or (\*).**

An optional digit string specifying a field width; if the output string has fewer bytes than the field width it will be blank-padded on the left (or right, if the left-adjustment indicator has been given) to make up the field width (note that a leading zero is a flag, but an embedded zero is part of a field width);

### Supported precision
**.(number) or .(\*).**

An optional period, ‘.’, followed by an optional digit string giving a precision which specifies the number of digits to appear after the decimal point, for e and f formats, or the maximum number of bytes to be printed from a string; if the digit string is missing, the precision is treated as zero;

### Supported type
| Type | Description |
|---|---|
| diouXx | The argument is printed as a signed decimal (d or i), unsigned octal, unsigned decimal, or unsigned hexadecimal (X or x), respectively. |
| fF | The argument is printed in the style `[-]ddd.ddd' where the number of d's after the decimal point is equal to the precision specification for the argument.  If the precision is missing, 6 digits are given; if the precision is explicitly 0, no digits and no decimal point are printed.  The values infinity and NaN are printed as ‘inf’ and ‘nan’, respectively. |
| c | The first byte of argument is printed. |
| s | Bytes from the string argument are printed until the end is reached or until the number of bytes indicated by the precision specification is reached; however if the precision is 0 or missing, the string is printed entirely. |
| % | Print a `%'; no argument is used. |

## Highlights
### diouXx, s, and c
The function prints each char one by one. So programme doesn't malloc for above types.
For the numbers, the reqursive function print each digit one by one.

![Screenshot 2022-10-09 at 18 54 12](https://user-images.githubusercontent.com/61685238/194766835-cf06423b-1451-4e0b-bf9f-6c6750b8e9a5.png)

### float
The IEEE 754 standard specifies a binary32 as having:
- Sign bit: 1 bit
- Exponent width: 8 bits
- Significand precision: 24 bits (23 explicitly stored)
This gives from 6 to 9 significant decimal digits precision. My ft_printf converts from the IEEE 754 single-precision format to char to output.
![My first board - Single-precision floating-point format](https://user-images.githubusercontent.com/61685238/194764718-e4bdc041-fb16-4a12-a6a5-caf62720becd.jpg)
