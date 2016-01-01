SRCS=main.cpp
FLAGS="-Wall"
LFLAGS="-I/usr/include/bullet -lstdc++ -pthread -l/usr/lib64/bullet -lGL -lGLU"

gcc -o bullet-physics $FLAGS $SRCS $LFLAGS
