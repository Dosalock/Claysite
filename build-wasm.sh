mkdir -p build/clay
mkdir -p build/tmp
clang                                                                 \
    -std=c99                                                          \
    -emit-llvm                                                        \
    -c                                                                \
    -Os                                                               \
    -DCLAY_WASM                                                       \
    -mbulk-memory                                                     \
    --target=wasm32                                                   \
    --include-directory C:/MinGW/include                              \
    -nostdlib                                                         \
    -Wall                                                             \
    -Werror                                                           \
    -o build/tmp/index.ll                                             \
    main.c
llc                                                                   \
    -march=wasm32                                                     \
    -filetype=obj                                                     \
    -o build/tmp/index.o                                              \
    --stats                                                           \
    build/tmp/index.ll
wasm-ld                                                               \
    --strip-all                                                       \
    --export-dynamic                                                  \
    --no-entry                                                        \
    --export=__heap_base                                              \
    --export=ACTIVE_RENDERER_INDEX                                    \
    --initial-memory=6553600                                          \
    --gc-sections                                                     \
    -o build/tmp/index.wasm                                           \
    build/tmp/index.o
cp index.html build/clay/index.html
cp build/tmp/index.wasm build/clay/index.wasm
cp -r fonts/ build/clay/fonts
cp -r images/ build/clay/images
