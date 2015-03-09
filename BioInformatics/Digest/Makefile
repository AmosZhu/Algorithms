CC = g++

CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

#PATCH
SRCS += $(wildcard *.cpp)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))

ifeq "$(CXXVERSION)" "4.6.3"
	CFLAGS += -std=c++0x
else
	CFLAGS += -std=c++11
endif

CFLAGS += $(foreach dir, $(INCLUDE_PATH), -I$(dir))
TARGET=Digest

$(TARGET):
	$(CC) -c -g $(CFLAGS) $(SRCS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -rf *.o
	rm -rf $(TARGET)
