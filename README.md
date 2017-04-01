Hashtable implementation
------------------------
Hello. I wrote this mainly as an exercise to run some benchmark tests. I'm comparing this native implementation of hashtable in C with JS objects and Python dicts.

The implementation uses separate chaining with linked lists for collision resolution. Thus, we have a fixed array (malloc'd) which we have O(1) access to it, and each value is actually a linked list.

For benchmarks, check the `benchmarks` folder.

To run the tests, first build by running `make` and then write `make run`.

To just build the library, write `make lib`.

To cleanup, run `make clean`.

Boro Sitnikovski

February 2017
