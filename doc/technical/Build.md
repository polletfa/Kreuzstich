# Build

Kreuzstich uses CMake for the C++ components and npm for the TypeScript components. The `make` script is a convenience wrapper around CMake and supports separate Debug and Release build directories.

## Requirements

The complete build requires:

- CMake 3.19 or newer
- A C++23 compiler
- GNU Make on Linux and macOS, or the generator selected by CMake on Windows
- Node.js and npm
- An installed Emscripten SDK, with `EMSDK` set by sourcing `emsdk_env.sh`
- Qt6 for the desktop GUI
- Docker, when running the web data-layer integration tests
- `lcov` and `genhtml`, when generating C++ coverage reports
- ImageMagick and Bash, only when regenerating thread lists

The WebAssembly wrapper checks for `EMSDK` during configuration. Before configuring a build, activate Emscripten, for example:

```bash
source /path/to/emsdk/emsdk_env.sh
```

On Windows, use the corresponding Emscripten environment script from an Emscripten-enabled shell.

## Convenience build script

The `make` script accepts `debug` or `release` as its first argument and passes all remaining arguments to the generated build tool:

```bash
./make debug <target>
./make release <target>
```

It configures the build in `build/debug` or `build/release` and builds with `make -j$(nproc)`.

Useful targets include:

| Target | Description |
|---|---|
| `all` | Build all configured components |
| `build-native` | Build the C++ core, desktop data layer, and desktop GUI |
| `build-web` | Build the WebAssembly wrapper, web data layer, and Angular GUI |
| `runtests-native` | Run the C++ and desktop data-layer tests |
| `runtests-web` | Run the web data, WebAssembly wrapper, and Angular tests |
| `runtests` | Run all native and web tests |
| `coverage` | Run tests and generate coverage reports when coverage tools are installed |

For example:

```bash
# Build native components
./make release build-native

# Build web components
./make release build-web

# Build everything
./make release all

# Run native tests
./make release runtests-native

# Run web tests
./make release runtests-web

# Run all tests
./make release runtests

# Generate coverage reports
./make debug coverage
```

The CMake build writes test reports below `build/<configuration>/test-results`. Coverage reports are written below `build/<configuration>/coverage_report`.

## Configure and build with CMake directly

The convenience script is optional. The equivalent direct commands on Unix-like systems are:

```bash
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release
cmake --build build/release --target build-native
cmake --build build/release --target runtests-native
```

To select a compiler explicitly:

```bash
cmake -S . -B build/release \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_C_COMPILER=gcc \
  -DCMAKE_CXX_COMPILER=g++
cmake --build build/release --target build-native
```

For a Debug build, use `-DCMAKE_BUILD_TYPE=Debug` and `build/debug`. Debug builds enable debug symbols, disable optimization, compiler coverage instrumentation, and additional WebAssembly assertions and safety checks.

On multi-configuration generators such as Visual Studio, select the configuration at build time:

```powershell
cmake -S . -B build -DCMAKE_CXX_STANDARD=23
cmake --build build --config Release --target build-native
cmake --build build --config Release --target runtests-native
```

## WebAssembly and web application

A standard build invokes a nested Emscripten build for `wrapper-wasm`. It creates separate Node and browser WebAssembly targets:

- `wrapper-wasm-node`
- `wrapper-wasm-web`
- `wrapper-wasm`, which depends on both targets

The generated wrapper and TypeScript library are then copied into `src/gui-web/build/wrapper-wasm` before Angular is built. The web GUI also depends on the `data-web` backend build because it imports generated data-layer files.

Build the complete web stack with:

```bash
source /path/to/emsdk/emsdk_env.sh
./make release build-web
```

The web build performs the following work automatically:

1. Install `src/data-web` npm dependencies and build the Fastify service.
2. Build the Node and browser WebAssembly wrappers.
3. Install `src/gui-web` npm dependencies.
4. Build the thread-list resources used by the web and native components when needed.
5. Copy web resources and the generated WebAssembly files.
6. Build the Angular application.

The installable web application can be staged with:

```bash
cmake --install build/release --component common
cmake --install build/release --component web-app
```

or through the convenience target:

```bash
./make release install-web-app
```

## Native desktop application

Build the C++ core, desktop data layer, and Qt desktop GUI with:

```bash
./make release build-native
```

The desktop application can be staged with:

```bash
./make release install-desktop-app
```

## Thread lists

Thread lists are shared project resources used by both the native desktop application and the web application. The DMC source files are stored under `resources/threadlists/DMC`; the generated `.threads` and `.sql` files are consumed by the corresponding native and web data components.

The generated thread-list files are committed in the repository and are not regenerated during every build. To regenerate them after changing the source files, ensure ImageMagick and Bash are installed, then build the explicit target:

```bash
./make release threadlists
```

The generated SQL files are imported into the web data layer as TypeScript strings, while the generated thread-list files are installed for the desktop application.

## Tests

Google Test is downloaded by CMake through `FetchContent`. Native tests are executed by CTest and include the core and desktop data-layer tests:

```bash
./make release runtests-native
```

Web tests run the TypeScript data-layer, WebAssembly wrapper, and Angular test targets:

```bash
./make release runtests-web
```

The `data-web` tests use a PostgreSQL database exposed via Docker Compose at `localhost:5555`.

Start the test database from the `src/data-web` directory:

```bash
cd src/data-web
npm run start:db:tests
```

Stop it when finished:

```bash
npm run stop:db:tests
```

The test database credentials are:

- Host: `localhost`
- Port: `5555`
- Database: `test`
- User: `test`
- Password: `test`

The CMake target `runtests-web` starts this database automatically, waits for it to become available, runs the tests, and stops the database afterward. If you run Vitest directly, start the database manually first.

Individual TypeScript projects can also be tested directly:

```bash
cd src/data-web
npm install
npm test
npm run coverage

cd ../gui-web
npm install
npm test
npm run coverage
```

## Coverage

C++ coverage requires both `lcov` and `genhtml`. If either program is unavailable, CMake skips the coverage target. With the tools installed:

```bash
./make debug coverage
```

The coverage target resets counters, runs the native and web test targets, removes external/test sources from the C++ report, and generates HTML reports under `build/debug/coverage_report`.

## Cleaning

CMake tracks generated dependency, build, distribution, and coverage directories for the web components. To start over, remove the build directory and the generated npm artifacts:

```bash
rm -rf build
rm -rf src/data-web/node_modules src/data-web/build src/data-web/coverage
rm -rf src/gui-web/node_modules src/gui-web/build src/gui-web/dist src/gui-web/coverage
```

The generated thread-list files are intentionally excluded from normal cleaning because they are committed resources.
