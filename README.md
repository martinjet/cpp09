*This project has been created as part of the 42 curriculum by mmarek.*

# CPP Module 09 – STL containers and the Ford-Johnson sort

## Description

The last module of the 42 C++ piscine: three small programs in **C++98**, each
built around a different standard container. A container used in one exercise
may not be reused in the next, so each choice has to be deliberate.

| Exercise | Program | Container(s) | What it does |
|---|---|---|---|
| `ex00` | `btc` | `std::map` | Values a bitcoin amount on a given date using a CSV price history |
| `ex01` | `RPN` | `std::stack` | Evaluates an expression in Reverse Polish Notation |
| `ex02` | `PmergeMe` | `std::vector`, `std::deque` | Sorts integers with the **Ford-Johnson (merge-insertion)** algorithm |

The highlight is `ex02`. Ford-Johnson is designed to sort with as few
comparisons as possible, so the implementation counts every comparison and
checks the result against the algorithm's theoretical worst case.

### ex00 – Bitcoin Exchange

- Loads the price history into a `std::map<std::string, double>`. Dates in
  `YYYY-MM-DD` format sort correctly as strings.
- For each `date | value` line of the input file, it finds the rate for that
  date. If the date is missing, it uses the closest **earlier** date via
  `map::lower_bound`.
- Validates input: real calendar dates (leap years included), a value between
  0 and 1000, the `|` separator, and malformed rows in the database itself.

```
$ ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
Error: too large a number.
```

### ex01 – Reverse Polish Notation

- A classic stack evaluator: operands are pushed, and each operator pops two
  of them and pushes the result.
- Input tokens are single digits (`0–9`) and `+ - * /`, separated by spaces.
- Errors are reported for invalid tokens, multi-digit numbers, division by
  zero and unbalanced expressions.

```
$ ./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"
42
$ ./RPN "(1 + 1)"
Error
```

### ex02 – PmergeMe (Ford-Johnson merge-insertion sort)

Ford-Johnson (Lester Ford Jr. & Selmer Johnson, 1959) comes very close to the
information-theoretic minimum number of comparisons for small inputs:

1. **Pair and compare.** Elements are paired and each pair is ordered, so
   every pair has a larger element *a* and a smaller element *b*.
2. **Recurse.** The larger elements are sorted recursively and form the
   *main chain*. Here this is done level by level over groups of rows.
3. **Insert in Jacobsthal order.** The smaller elements are binary-inserted
   into the main chain in an order derived from the Jacobsthal numbers
   (1, 3, 5, 11, 21, 43, …). The order keeps every binary search within a
   range of size 2^k − 1, which is where binary search is most efficient.

The same algorithm is implemented twice, once for `std::vector` and once for
`std::deque`, and the two are timed against each other.

**Measured comparisons** (random input, `./PmergeMe check …`):

| Elements | Ford-Johnson (measured) | Theoretical worst case |
|---:|---:|---:|
| 21 | 65 | 66 |
| 100 | 527 | 534 |
| 1 000 | 8 563 | 8 641 |
| 3 000 | 30 377 | 30 546 |

The worst case is computed as Σ⌈log₂(3k/4)⌉ for k = 1…n. Over all 40 320
permutations of 8 elements, the average is **15.5 comparisons** for Ford-Johnson
and **21** for `std::sort`; the theoretical maximum is 16.

**vector vs deque.** Both containers run the same algorithm, yet the `deque`
version is several times slower in practice. Insertion into the middle of the
main chain dominates the runtime, and `deque` pays for its segmented memory
layout with slower random access and costlier inserts.

## Instructions

Requirements: a C++ compiler (`c++`, g++ or clang++) and `make`. Each exercise
builds separately with `-Wall -Wextra -Werror -std=c++98`.

```bash
cd ex00 && make    # builds ./btc
cd ex01 && make    # builds ./RPN
cd ex02 && make    # builds ./PmergeMe
```

**ex00** reads the price history from `./data.csv` (format
`date,exchange_rate`). The dataset was supplied with the 42 assignment and is
not part of this repository, so provide your own CSV in that format.

```bash
./btc input.txt
```

**ex01**

```bash
./RPN "1 2 * 2 / 2 * 2 4 - +"
```

**ex02**

```bash
./PmergeMe 3 5 9 7 4                       # sort, print before/after and timings
./PmergeMe check $(shuf -i 1-100000 -n 3000) # verify result and comparison count
./PmergeMe test 4                          # built-in test sets 1–4
./PmergeMe permut 8                        # average comparisons over all permutations
```

`check` compares the result with `std::sort` and the comparison count with the
theoretical worst case, then prints `OK` or `WRONG`.

## Resources

- Donald E. Knuth, *The Art of Computer Programming, Vol. 3: Sorting and
  Searching*, section 5.3.1 – merge insertion
- L. R. Ford Jr., S. M. Johnson, "A Tournament Problem", *The American
  Mathematical Monthly*, 1959
- [Merge-insertion sort – Wikipedia](https://en.wikipedia.org/wiki/Merge-insertion_sort)
- [Jacobsthal number – Wikipedia](https://en.wikipedia.org/wiki/Jacobsthal_number)
- [cppreference: std::map::lower_bound](https://en.cppreference.com/w/cpp/container/map/lower_bound)
- [Reverse Polish notation – Wikipedia](https://en.wikipedia.org/wiki/Reverse_Polish_notation)

### Use of AI

The project was written and submitted in 2025 without AI tools. When preparing
it for publication in 2026, AI assistance was used for:

- reviewing the code and testing it with AddressSanitizer/UBSan,
- small cleanups: aligning `btc` output with the specification, tokenizing RPN
  input by whitespace, fixing a crash on single-element input in `PmergeMe`,
  and moving debug output into the `check` mode,
- drafting this README.

The algorithm and the overall design are my own work.
