all: main test

.PHONY: docs test

main:
	mkdir -p bin
	gcc src/main.c -I include -o bin/main.out
	./bin/main.out

test:
	mkdir -p bin
	g++ test/test.cpp -I include -o bin/test.out &&\
	./bin/test.out -s ||\
	./bin/test.out -s

docs:
	pandoc doc/relatorio.md -s -o doc/relatorio.pdf -N
	evince doc/relatorio.pdf


