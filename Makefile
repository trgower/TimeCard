run: CommandLine.o PayPeriod.o WorkShift.o Date.o
	g++ CommandLine.o PayPeriod.o WorkShift.o Date.o -o run

CommandLine.o: CommandLine.cpp PayPeriod.h WorkShift.h Date.h
	g++ -c CommandLine.cpp

PayPeriod.o: PayPeriod.cpp WorkShift.h Date.h
	g++ -c PayPeriod.cpp

WorkShift.o: WorkShift.cpp Date.h
	g++ -c WorkShift.cpp

Date.o: Date.cpp
	g++ -c Date.cpp
