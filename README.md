# Crail

Crail is a psudo-random block cipher implemented with the rail fence Cipher.

In the Defautl encryption and decryption mode a single byte is encrypted with a randome rail between 2 and 7.
The resulting key will follow a format of the rail number followed by a new line charater.
<br>
**In a future rendition I will modify the code to have no spaces or new line characters to reduce key size by half**

If the program is used in slice mode a random block of bytes specified between 2 and the number specified by the user is selected.
Additionally a psudo-random rail number is selcted for each block from the range of 2 to ((8 * block size) - 1).
The resulting key from slice mode will have the format of (Block Size,  Rail Number) to perform decryption.

### Installing

`gcc main.c`


### Sample Tests

Explain what these tests test and why


## Built With

  - [gcc](https://gcc.gnu.org/) - Used for compiling
  - [rail fence cipher](https://en.wikipedia.org/wiki/Rail_fence_cipher) - Used for theory behind rail fence cipher

