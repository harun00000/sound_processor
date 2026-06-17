# sound_processor

## Run tests

```bash
cmake -S . -B build -DBUILD_TESTS=ON
cmake --build build
./build/bin/tests
```

## Run program

```bash
cmake -S . -B build
cmake --build build

./build/bin/sound_processor -i input.wav -o output.wav -f reverse
```

## Generate documentation

```bash
doxygen Doxyfile
```

Open documentation:

```bash
xdg-open html/index.html
```
