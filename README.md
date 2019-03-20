## cpp-enumerate
C++ 14 based, python like enumeration of C++ iterables, returning the index and value.
Also works with custom iterables that require ADL.

#### Examples:
- with `std::vector`
```cpp
std::vector<int> v{1, 2, 3, 4};
for (auto&& [idx, val] : rz::enumerate(v)) {
    // 
}
```

- custom iterable
```cpp
struct Foo {
    int x;
    int * begin() { return &x; }
    int * end() { return &x + 1; }
};

for (auto&& [idx, val] : rz::enumerate(Foo{7})) {
    //
}
```
