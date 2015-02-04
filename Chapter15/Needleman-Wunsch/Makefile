CC = g++

CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

#PATCH
TEMP += $(wildcard ../*.cpp)

ifeq "$(CXXVERSION)" "4.6.3"
	CFLAGS += -std=c++0x
else
	CFLAGS += -std=c++11
endif

CFLAGS += $(foreach dir, $(INCLUDE_PATH), -I$(dir))
TARGET1=BLOSUM50
TARGET2=NeedlemanWunsch


$(TARGET1):
	$(CC) -c -g $(CFLAGS) BLOSUM50.cpp
	$(CC) $(CFLAGS) BLOSUM50.o -o $@ -lsqlite3

$(TARGET2):
	$(CC) -c -g $(CFLAGS) NeedlemanWunsch.cpp
	$(CC) $(CFLAGS) NeedlemanWunsch.o main.cpp -o $@ -lsqlite3

clean:
	rm -rf *.o
	rm -rf $(TARGET1)
	rm -rf $(TARGET2)
