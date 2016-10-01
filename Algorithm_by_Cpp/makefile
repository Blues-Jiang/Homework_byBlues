cc=g++
exe=main
obj=main.o

all: $(exe)

$(exe):$(obj)
	$(cc) -o $(exe) $(obj)
main.o:main.cpp
	$(cc) -c main.cpp
clean:
	rm -rf *.o main
