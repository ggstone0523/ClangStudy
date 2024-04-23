all: build start clean

build:
	@echo "\033[34mbuild and start\033[37m"
	gcc -o entab entab.c
	gcc -o detab detab.c

start:
	@echo "\033[31m"
	tabs 4
	@echo "\033[37m"
	./entab 4 4 < entabtest > result
	@echo "\033[34mentabtest\033[37m"
	@cat -T entabtest
	@echo "\033[34mresult(TAB)\033[37m"
	@cat -T result
	@echo "\033[34mresult(DEFAULT)\033[37m"
	@cat result
	@echo "\033[31m"
	tabs 8
	@echo "\033[37m"
	./detab 8 8 < detabtest >> result
	@echo "\033[34mdetabtest(TAB)\033[37m"
	@cat -T detabtest
	@echo "\033[34mdetabtest(DEFUALT)\033[37m"
	@cat detabtest
	@echo "\033[34mresult\033[37m"
	@cat -T result | tail -n 2

clean:
	rm -rf ./detab ./entab
