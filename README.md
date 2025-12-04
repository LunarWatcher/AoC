# AoC

Monorepo for my new AoC solutions

These are not the first implementations I've done; previous years are available in separate repos on GitHub.

## Development

[umbra](https://github.com/LunarWatcher/umbra) is having a high return on investment already. To develop previous years, `umbra env <year>`. This also works with the latest year, which is the default environment. There are CMake targets available as well. I don't know which I'll be using yet, so both will be available for A While:tm:. 

The umbra env exposes:

* `run`
* `tests` (I wanted `test`, but this conflicts with a shell builtin)
* `debug` - runs `gdb` against a freshly built test binary
* `callgrind [tests]` - runs callgrind. If `tests` is supplied as an argument, callgrind is run on the tests. This is not recommended, as this includes a lot of catch2 stuff in the output. 
* `profile [tests]` - runs perf. You need (apt) `performance-tools linux-tools-generic`. Unfortunately, this is currently borked on kernel 6.14 due to an upstream bug, so it has not been tested: https://bugs.launchpad.net/ubuntu/+source/linux-hwe-6.14/+bug/2117159

The year is automatically resolved by the env. Unlike CMake targets, both `run` and `tests` allows argument forwarding. 

The following CMake targets are available:

* `run/test` - runs the latest year, or the year I'm currently actively working on if AoC is over and I'm going back to do a previous year. This will shift
* `run-<year>/test-<year>`. 
