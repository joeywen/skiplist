skiplist
========

simple skiplist implementation using C++.

The codes are compiled by scons. If you have already installed scons
just type scons command in linux like

- joey@debian:~/joey/skiplist$ scons
the output will be:

    scons: Reading SConscript files ...
    scons: done reading SConscript files.

    scons: warning: Support for pre-2.7.0 Python version (2.6.6) is deprecated.
    If this will cause hardship, contact dev@scons.tigris.org.
    File "/home/index/wzhg/bin/scons", line 192, in <module>
    scons: Building targets ...
    g++ -o SkipList.o -c SkipList.cpp
    g++ -o skiplist SkipList.o
    scons: done building targets.


Reference
----------
http://www.drdobbs.com/cpp/skip-lists-in-c/184403579

Contact
----------
joey.wen@outlook.com
