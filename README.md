# BMtoBMPCpp
A tool for converting proprietary BM image files into bitmap images, written in C++20.

## Installing

Navigate to the releases page and download the latest zip file.

Once downloaded, extract the zip file wherever you'd like and you're done!

See [usage](#Usage) below for more details on running the application.

### Building from Source (Linux/macOS/Unix)

Install dependencies:

```
gcc make cmake mingw32-gcc clang-tools-extra
```

Clone the project:
```bash
$ git clone https://github.com/IcePanorama/BMtoBMPCpp.git
# ... or, alternatively ...
$ git clone git@github.com:IcePanorama/BMtoBMPCpp.git
```

Install:
```bash
$ cd BMtoBMPCpp && ./cmake/make_release.sh
```

## Usage
```
BMtoBMPCpp_x86_64.exe path\to\file.BM path\to\file.PAL # 64-bit Windows Systems
BMtoBMPCpp_i686.exe path\to\file.BM path\to\file.PAL # 32-bit Windows Systems
./BMtoBMPCpp path/to/file.BM path/to/file.PAL # Linux/macOS/Unix Systems
```
