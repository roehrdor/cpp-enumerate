## cpp-enumerate
C++ 14 based, python like enumeration of C++ iterables, returning the index and value.
Also works with custom iterables that require ADL.

```cpp
std::vector<int> v{1, 2, 3, 4};
for (auto&& [idx, val] : rz::enumerate(v)) {
    // 
}
```
