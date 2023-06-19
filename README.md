# false

hopefully a completely utterly readable programming language. written in C.  
still in development

# syntax

```
var !immutable = "value";
var variable = "value";

func function(arg1, arg2) {
  return arg1 + arg2;
}

# types
"string" # string
false # boolean
null # null
123 # integer
123.123 # float
[1, 2, 3](0) # array
```

# todo

- [ ] lexer
  - [x] numbers
  - [x] strings
  - [x] punctuators & operators (symbols)
  - [x] identifiers
  - [x] keywords
  - [x] null
  - [x] booleans
  - [ ] comments
- [ ] parser
- [ ] interpreter
- [ ] optimizer
