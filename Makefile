CFLAGS = -g -Wall
LDFLAGS =

install: mail-in mail-out
		 cp mail-in mail-out $(DEST)/bin
		 cp -R inputFiles/. $(DEST)/inputs


mail-in: mail-in.o
	g++ -std=c++17 -o mail-in mail-in.cpp

mail-out: mail-out.o
	g++ -std=c++17 -o mail-out mail-out.cpp

.PHONY: test clean
clean: 
	rm -f *.o mail-in mail-out

test:
	@./create-tree.sh email_system
	make install DEST=./email_system
	@./test.sh email_system