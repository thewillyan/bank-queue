# Bank queue :bank:
[![license](https://img.shields.io/github/license/thewillyan/bank-queue)](https://github.com/thewillyan/bank-queue/blob/main/LICENSE)
[![issues](https://img.shields.io/github/issues/thewillyan/bank-queue)](https://github.com/thewillyan/bank-queue/issues)

Final assignment of the programming course.

## Build

**Dependencies:**

- [automake](https://www.gnu.org/software/automake/)
- [check](https://libcheck.github.io/check/)
- [make](https://www.gnu.org/software/make/)


To follow the steps below you need to clone this repo to your machine: 
```sh
git clone https://github.com/thewillyan/bank-queue.git
cd bank-queue
```

### GNU Autotools environment
```sh
autoreconf --install
./configure
```

### Run
```sh
make
./src/bank
```

### Test
```sh
make check
```
