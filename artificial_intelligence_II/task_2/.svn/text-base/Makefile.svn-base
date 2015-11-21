CXXFLAGS=-fPIC  -march=native $(shell python-config --cflags) -Wnostrict-prototypes

all: fitness.py fitness.so

fitness.o: fitness.cpp

fitness.so fitness.py: fitness.i
	swig -python -c++ fitness.i
	python setup.py build_ext --inplace


# fitness_wrap.o: fitness_wrap.cxx
# 	$(CXX) $(CPFLAGS) $(CXXFLAGS)  -c fitness_wrap.cxx -o fitness_wrap.o

# _fitness.so: fitness.o fitness_wrap.o
# 	$(CXX) -shared fitness.o fitness_wrap.o -o _fitness.so

clean:
	-rm fitness.o fitness.py fitness_wrap.cxx _fitness.so fitness_wrap.o *.pyc
	-rm -rf build
 
