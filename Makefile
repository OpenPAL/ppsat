CC = g++ -Wall -O3 -DNDEBUG
HEADERS = cnf.h cnf_manager.h sat_solver.h pdqsort.h
OBJS = cnf.o cnf_manager.o sat_solver.o main.o

ppsat: $(OBJS)
	$(CC) $(OBJS) -o ppsat

$(OBJS): $(HEADERS) Makefile

.cpp.o: 
	$(CC) -c $< 
