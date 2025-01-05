
mkdir -p build/clay
mkdir -p build/tmp
clang                                                                 \
    -emit-llvm                                                        \
    -c                                                                \
    -Os                                                               \
    -DCLAY_WASM                                                       \
    -mbulk-memory                                                     \
    --target=wasm32                                                   \
    -nostdlib                                                         \
    -o build/tmp/index.ll                                             \
    main.c
llc                                                                   \
    -march=wasm32                                                     \
    -filetype=obj                                                     \
    -o build/tmp/index.o                                              \
    build/tmp/index.ll
wasm-ld                                                               \
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
