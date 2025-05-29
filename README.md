# TKoz Template Library

This is a personal C++ library for various ideas, including useful data
structures, reimplementations of things in other libraries, template
metaprogramming, and more. For now, it is something for learning advanced C++
features and possibly something that can be useful in other projects.

The header files can be copied into other projects for use. Currently, backward
compatibility is not guaranteed as it is in well established libraries.
Everything is written only to compile on Linux with GCC using C++23 for now.

## todo

license (gnu agpl)

### strings

- `cstr` - extended c string
- `astr` - array string
- `lstr` - linked list string
- `istr` - interned (array) string
- `icstr` - interned (c) string

### possible libraries

Some of these ideas are better for other libraries

- `tkoz::stl` - standard template library
- `tkoz::math`- math
- `tkoz::cont` - containers
- `tkoz::meta` - template metaprogramming
- `tkoz::util` - utilities
- `tkoz::file`- files and filesystem
- `tkoz::mem` - memory
- `tkoz::net` - network
- `tkoz::func` - functional
- `tkoz::num` - numbers
- `tkoz::linalg` - linear algebra
- `tkoz::time` - date and time
- `tkoz::algo` - algorithms
- `tkoz::graph` - graph structures and algorithms
- `tkoz::ml` - machine learning
- `tkoz::conc` - concurrency
- `tkoz::io` - input and output
- `tkoz::rng` - random number generation
- `tkoz::stat` - statistics
- `tkoz::csv` - CSV (comma/tab separated values)
- `tkoz::json` - JSON
- `tkoz::xml` - XML format
- `tkoz::hdf5` - HDF5 format
- `tkoz::nbt` - NBT format (Minecraft stuff)
- `tkoz::zip` - compression
- `tkoz::unit` - scientific measurement units

### ideas

General programming stuff
- documentation (doxygen)
- code coverage
- performance testing
- clang format

Some of these ideas are better for other libraries

- 2d arrays (square/rectangular/triangular)
- hash/tree set/map with designated empty value
- hash tables with open address / chaining
- balanced trees (red black, avl)
- b/b+ trees
- array set/map (to have the option for being slow)
- disjoint sets
- graph (adjacency list/matrix/set)
- trie (prefix tree)
- interned string (and possibly other types)
- generic interned type
- segment tree
- fenwick tree (binary indexed tree)
- bloom filter
- circular list
- wrap around grid
- thread safe data structures
- sorting algorithm library (including parallel algorithms)
- n-ary heaps
- quad/oct trees
- priority queue (with random access to any element)
- data structures that remember insertion order
- custom memory allocators
- file system level RAID
- tools for multithreading
- filesystem library
- compressed archive library
- file formats like csv, tsv, json, yml
- output formatting stuff
- arbitrary precision arithmetic
- math functionality
- larger fixed size integers (signed and unsigned, overflow options)
- larger fixed size floats (ieee and use multiple of an ieee type)
- custom arbitrary precision integer/float/rational/complex
- statistics
- linear algebra
- linear optimization
- nonlinear optimization
- reinvent stl
- iterators/generators
- graph algorithms
- optional
- testing
- rng
- number theory
- text/data encode/escape
- base64/85
- hashing
- cryptography
- multidimensional linked lists
- bidirectional map
- multiset
- graphics/drawing
- gui/cli stuff
- half precision float, quad precision float, ...
- testing framework
- bit packing for boolean flags
- useful small functions for functional programming
- functions for the operators (see old code for it)
- tagged pointers (both low and high bits)
- xor (doubly linked) linked list
- regex compiler with template metaprogramming
- various calculationts with template metaprogramming
- tuples and named tuples (including some with useful names)
- primitive numbers requiring explicit conversions
- tagged floats/doubles (use some exponent/mantissa bits to store data)
- memory allocators optimized for various sizes or use cases
