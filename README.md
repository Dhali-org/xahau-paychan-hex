# Xahau Payment Channel Hex Generator

The Xahau Payment Channel Hex Generator allows you to generate hex strings to be signed when using Xahau payment channels. It uses the core `xahaud` C++ source code and must be built from source to be used. It is compatible with `node` and `python`.

## Setup

Pull the `xahaud` submodule:
```
git clone --recurse-submodules --shallow-submodules --depth 1
```

## Build and run the `example.py` example

```
docker build -f Dockerfile.python -t pychan .
docker run -t pychan
```

## Build and run the `example.js` example

```
docker build -f Dockerfile.node -t nodechan .
docker run -t nodechan
```