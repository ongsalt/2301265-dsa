# Common gcc flag
`-std=c++23 -lstdc++exp -g`

## Why
- `-lstdc++exp`: `std::print` dont work on windows if we dont pass this. Its seem like clang automatically do this tho.
- `-g` with debug info
