# secho - Simple Echo with Multipliers

**secho** is a minimal C utility for printing a string multiple times, with optional newline control. Unlike standard `echo`, it allows multiplying strings like `"hello"*3`, making it useful for scripting and automation.

## Features
- Print a string multiple times (`-n` option)
- Control whether repetitions appear on new lines (`-l` option)
- Uses **syscalls (`write()`)** for minimal overhead
- No dependencies beyond **glibc**
- Help menu (`-h` option)

## Installation
Clone the repo and compile with `gcc`:
```sh
git clone https://github.com/CodeFlowShai/secho.git
cd secho
gcc -o secho main.c
sudo mv secho /usr/local/bin/
```

## Usage
```sh
secho -s "hello" -n 3
```
**Output:**
```
hello
hello
hello
```

Print on the same line:
```sh
secho -s "hello" -n 3 -l
```
**Output:**
```
hellohellohello
```

### **The Ultimate Use Case**
```sh
secho -s "chicken" -n 3 | cowsay
```
**Output:**
```
 _________________________
< chicken chicken chicken >
 -------------------------
        \   ^__^
         \  (oo)\_______
            (__)\       )\/\
                ||----w |
                ||     ||
```

Show help menu:
```sh
secho -h
```
## License
Licensed under **GPL-3.0**. See `LICENSE` for details.
