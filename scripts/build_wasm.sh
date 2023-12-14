# -fPIC 
emcc -c -O3 ../pitch/*.c ../pitch/*/*.c
rm libpitch_wasm.a
emar rcs libpitch_wasm.a *.o
rm *.o