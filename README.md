# Dynamic C String Library

A safe, auto-resizing dynamic string implementation in pure C.

Replaces risky fixed-size `char[]` arrays with a proper `DynamicString` struct that grows automatically — no buffer overflows, no manual `realloc` needed.

---

##  Features

- Constructor & destructor (`createString` / `destroyString`)
- Automatic capacity doubling when the string grows
- Safe input via `getstring()` (auto-resizes on the fly)
- Complete string operations: copy, compare, concatenate, n-concatenate, reverse, to-lower, to-upper
- Null-pointer safety in every function
- Tracks both length (`nullCharIndex`) and capacity internally for speed
- Clean memory management — no leaks when used correctly


---

