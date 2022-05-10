C Plus Plus is a little bit trickier to run as it requires a specific operating systems version of the compiler.

Windows: https://docs.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170

mac: type gcc into a command line and follow the instructions to get xcode installed


Clang - a toolset that sits on top of the compiler and provides many benefits including optimisation and error handling
    windows: https://github.com/llvm/llvm-project/releases/download/llvmorg-11.0.0/LLVM-11.0.0-win64.exe
    linux: brew install clang++


Once your tool chain is installed run the shell script: ./build_cpp_prog.sh

then you can run ./stats_generator ../data/data_file.txt
