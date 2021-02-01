CXX      = g++
CCLINK   = $(CXX)
CXXFLAGS = -g -Wall -std=c++11
EXEC     = firewall.exe
OBJS     = main.o libfirewall.so libinput.so ip.o field.o port.o string.o
RM       = rm -rf *.o libfirewall.so *.exe

$(EXEC): $(OBJS)
	$(CCLINK) $(OBJS) -o $(EXEC)

main.o: main.cpp input.h ip.h string.h field.h port.h
	$(CCLINK) $(CXXFLAGS) -c main.cpp

libfirewall.so: ip.o port.o field.o string.o
	$(CCLINK) $(CXXFLAGS) -shared ip.o field.o port.o string.o -o libfirewall.so

ip.o: ip.cpp ip.h field.h
	$(CCLINK) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.cpp port.h field.h
	$(CCLINK) $(CXXFLAGS) -c -fpic port.cpp

field.o: field.cpp field.h string.h ip.h port.h
	$(CCLINK) $(CXXFLAGS) -c -fpic field.cpp

string.o: string.cpp string.h
	$(CCLINK) $(CXXFLAGS) -c -fpic string.cpp

clean:
	$(RM)