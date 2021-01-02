UNAME := $(shell uname)

build:
ifeq ($(UNAME), Linux)
	g++ -o main main.cpp timage.cpp	draw.cpp model.cpp geometry.cpp
endif
ifeq ($(UNAME), Darwin)
	clang++ -stdlib=libc++ -std=c++11 -o main main.cpp timage.cpp draw.cpp model.cpp geometry.cpp
endif
