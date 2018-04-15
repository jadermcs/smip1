all: clean build test

.PHONY: docs test

build:
	mkdir -p bin
	gcc src/* -I include -o bin/main.out
	./bin/main.out

test:
	mkdir -p bin
	g++ test/test.cpp -I include -o bin/test.out &&\
	./bin/test.out -s ||\
	./bin/test.out -s

clean:
	rm -r bin

docs:
	pandoc doc/relatorio.md -s -o doc/relatorio.pdf -N
	evince doc/relatorio.pdf


