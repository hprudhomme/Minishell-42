# Build
## MacOS
On MacOS, you first need to install `readline`:
```bash
brew install readline
```
The return of `brew info readline` will give you an `LDFLAGS` and a `CPPGLAGS` to export to achieve the build :
```bash
export LDFLAGS="-L/usr/local/opt/readline/lib"
export CPPFLAGS="-I/usr/local/opt/readline/include"
```
(you can add the values, without the `export` keyword, at the top of the `Makefile` to make it permanent)
