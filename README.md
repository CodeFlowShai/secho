# secho - Simple Echo with Multipliers

**secho** is a minimal C utility designed for GNU/Linux to print a string multiple times, with an optional newline control. Unlike standard `echo`, it allows multiplying strings like `"hello"*3`, making it useful for scripting and automation.

## Features
- Print a string multiple times (`-n` option)
- Control whether repetitions appear on new lines (`-l` option)
- Reverse the string output (`-r` option)
- Change the color (`-c` option)
- Create a wave effect (`-w` option)
- Uses **syscalls (`write()`)** for minimal overhead
- No dependencies beyond **glibc**
- Help menu (`-h` option)
## Installation
Clone the repo and compile with `gcc`:
```sh
sudo curl -L https://github.com/CodeFlowShai/secho/releases/download/v0.2.0/secho -o /usr/local/bin/secho
sudo chmod +x /usr/local/bin/secho
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


Reverse output:
```sh
secho -s "hello" -n 3 -r
```
**Output:**
```
olleh
olleh
olleh
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
