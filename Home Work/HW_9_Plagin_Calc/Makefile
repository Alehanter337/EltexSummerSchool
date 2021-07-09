OBJECT_FILES = obj/add.o
SOURCE_FILES = src/add.c

all: create_object_files create_dynamic_lib linking

create_object_files: $(OBJECT_FILES)
	
obj/add.o:
	gcc -o obj/add.o -fPIC -c src/add.c

create_dynamic_lib: libmyadd

libmyadd:
	gcc -shared obj/add.o -o libmyadd.so
	
linking:
	gcc src/main.c -o main -ldl
	
run:
	LD_LIBRARY_PATH=.:LD_LIBRARY_PATH ./main libmyadd.so

clean:
	rm -f obj/*.o ./main *.so
	
