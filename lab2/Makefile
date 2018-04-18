all: clean build run test

.PHONY: docs test

build:
	mkdir -p bin
	gcc src/* -I include -o bin/main.out

test:
	mkdir -p bin
	gcc test/test.cpp -I include -o bin/test.out &&\
	./bin/test.out -s ||\
	./bin/test.out -s

clean:
	rm -r bin

run:
	./bin/main.out

docs:
	pandoc doc/relatorio.md -s -o doc/relatorio.pdf -N
	evince doc/relatorio.pdf


