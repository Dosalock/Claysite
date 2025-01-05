
mkdir -p build/clay
mkdir -p build/tmp
"C:\Users\ThaoG\llvm-build\llvm-project\build\Release\bin\clang.exe"  \
    -emit-llvm                                                        \
    -c                                                                \
    -Os                                                               \
    -DCLAY_WASM                                                       \
    -mbulk-memory                                                     \
    --target=wasm32                                                   \
    -nostdlib                                                         \
    -o build/tmp/index.ll                                             \
    main.c
"C:\Users\ThaoG\llvm-build\llvm-project\build\Release\bin\llc.exe"    \
    -march=wasm32                                                     \
    -filetype=obj                                                     \
    -o build/tmp/index.o                                              \
    build/tmp/index.ll
"C:\Users\ThaoG\llvm-build\llvm-project\build\Release\bin\wasm-ld.exe"\
    --strip-all                                                       \
    --export-dynamic                                                  \
    --no-entry                                                        \
    --export=__heap_base                                              \
    --export=ACTIVE_RENDERER_INDEX                                    \
    --initial-memory=6553600                                          \
    -o build/tmp/index.wasm                                           \
    build/tmp/index.o
cp index.html build/clay/index.html
cp build/tmp/index.wasm build/clay/index.wasm
cp -r fonts/ build/clay/fonts
cp -r images/ build/clay/images
