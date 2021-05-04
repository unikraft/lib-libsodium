# libsodium for Unikraft

This repository provides a port of [libsodium](https://libsodium.org) as an external library for [Unikraft](https://unikraft.org).

## Configuration

libsodium on Unikraft provides a minimal configuration of the sodium library, ie the
equivalent state of configuring libsodium using `configure --enable-minimal`.

## Dependencies:

libsodium on Unikraft depends on the following Unikraft libraries:
* lib-newlib (external)
* ukswrand (internal)

Both dependencies are automatically enabled via KConfig.
 
In your application's Makefile sure you declare newlib before libsodium:
```
LIBS := $(UK_LIBS)/lib-newlib:$(UK_LIBS)/lib-libsodium
```

## More info
For more information, see:
* https://libsodium.org
* https://unikraft.org
