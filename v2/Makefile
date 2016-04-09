dll:
	gcc sample.c -dynamiclib -o sample.dylib
all:    
	gcc plugin_test.c plugin.c plugin_osx_adp.c -o plugin_test.bin
clean:
	rm -rf *.o
	rm -rf *.dylib
	rm -rf *.bin

