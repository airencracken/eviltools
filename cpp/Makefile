CXX             = g++
CXXFLAGS        = -Wall
OPTFLAG         = -O2
DEBUGFLAG       = -g
LINKER          = g++


SRC = \
                passwd.cpp \
                ls.cpp 

OBJS = $(SRC:.cpp=.o)

passwd: $(OBJS)
  $(LINKER) $(LFLAGS) $(OBJS) -o $@

ls: $(OBJS)
  $(LINKER) $(LFLAGS) $(OBJS) -o $@

clean:
rm $(OBJS) ls passwd
