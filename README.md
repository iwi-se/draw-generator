# General
Author: [Ulrich Eisenecker](https://www.wifa.uni-leipzig.de/personenprofil/mitarbeiter/prof-dr-ulrich-eisenecker)

The Draw-generator is an implementation for permutation and combinatorics in C++. These are represented by a simplified model based on an urn. 
Three main concepts are used: Urn, Balls, and Draw are used. 
The urns can then be used to generate all possibilities of the respective specification.
The following urn models are possible:

The implementations of the urn models are called: 
 * `UrnOR` – urn where the order is important and which contains repetitions.
 * `UrnO` – urn where the order is important and does not include repetitions.
 * `UrnR` – urn with unimportant order and with repetitions.
 * `Urn` – urn with unimportant order and without repetitions.
 * `GenericUrn` - Template-Wrapper for the urn models/draw-generator.
   
|                         | With repetition                      | Without repetition              | 
| ----------------------- | ------------------------------------ | ------------------------------- |
| Order is important      | $`n^k,¬(n=0∧k=0)∨(n>0)`$             | $`n! \over (n−k)!`$ $`,k≤n`$    |
| Order is not important  | $`(k+n−1)! \over k!(n−1!)`$ $`,n>0`$ | $`n! \over (n−k)!k!`$ $`, k≤n`$ |


## Compilation
The instructions for the compilation create an executable for the unit tests.

For compiling the `makefile` is recommended.
* Generating executable with: `make`
* Delete the files from the obj/ and doc/ subdirectories with : `make clean`
  
Note: `make` must be installed!

Another way to compile is to type the following commands one after another into the console: 
 * `g++ -std=c++20 -o obj/urn.o -c src/urn.cpp`
 * `g++ -std=c++20 -o obj/UrnUnitTests.o -c src/UrnUnitTests.cpp`
 * `g++ -std=c++20 -o obj/UrnUnitTests obj/UrnUnitTests.o obj/urn.o`


## Usage

## Documentation
Generating documentation with: make doc
