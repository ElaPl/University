Flags = -Wall -W
CPP = g++

OBJECTS = project.o functions.o receive_functions.o send_functions.o  

traceroute : $(OBJECTS)
	$(CPP) $(Flags) $(OBJECTS) -o traceroute

project.o : project.cpp functions.h receive_functions.h send_functions.h library.h
	$(CPP) -c $(Flags) project.cpp -o project.o

funkcje.o : functions.cpp functions.h library.h
	$(CPP) -c $(Flags) functions.cpp -o functions.o

receive_functions.o : receive_functions.cpp receive_functions.h library.h
	$(CPP) -c $(Flags) receive_functions.cpp -o receive_functions.o

send_functions.o : send_functions.cpp send_functions.h library.h
	$(CPP) -c $(Flags) send_functions.cpp -o send_functions.o


clean : 
	rm *.o

distclean :
	rm *.o traceroute	 




