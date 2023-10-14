# About

Lazar's Integer Forth is small interpreter for Forth language written in C++.  At this moment it has support for most of base words defined in  FORTH-79 standard which can be found [here](https://www.complang.tuwien.ac.at/forth/fth79std/FORTH-79.TXT). At the moment it supports execution of simple if-else-then statements, do-loop and user defined words.
Some of example programs that have been tested are:
```3 5 < IF 1 . ELSE 0 . THEN```
```10 0 DO I . I 1 + LOOP```
```: SQUARE DUP * . ; 4 SQUARE```

## TODO
1. Work needs to be put in integrating if-then-else statements with user defined words and loops.
2. Finish support for all FOTH-79 base words
3. Restructure code to be more compact