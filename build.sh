"C:\Users\ThaoG\llvm-build\llvm-project\build\Release\bin\clang.exe"  \
-Wall                                                                 \
-Werror                                                               \
-Os                                                                   \
-DCLAY_WASM                                                           \
-mbulk-memory                                                         \
--target=wasm32                                                       \
-nostdlib                                                             \
-Wl,--strip-all                                                       \
-Wl,--export-dynamic                                                  \
-Wl,--no-entry                                                        \
-Wl,--export=__heap_base                                              \
-Wl,--export=ACTIVE_RENDERER_INDEX                                    \
-Wl,--initial-memory=6553600                                          \
-o clay.wasm                                                          \
"C:\Users\ThaoG\source\C\Claysite\main.c"                             \
