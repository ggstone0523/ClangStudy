all: build start clean

build:
	@echo "\033[34mbuild and start\033[37m"
	gcc -o entab entab.c
	gcc -o detab detab.c

start:
	./entab -2 +8 < entabtest > result
	@echo "\033[34mentabtest\033[37m"
	@cat -T entabtest
	@echo "\033[34mresult(TAB)\033[37m"
	@cat -T result
	@echo "\033[34mresult(DEFAULT)\033[37m"
	@cat result
	./detab -2 +8 < detabtest >> result
	@echo "\033[34mdetabtest(TAB)\033[37m"
	@cat -T detabtest
	@echo "\033[34mdetabtest(DEFUALT)\033[37m"
	@cat detabtest
	@echo "\033[34mresult(TAB)\033[37m"
	@cat -T result | tail -n 2
	@echo "\033[34mresult(DEFAULT)\033[37m"
	@tail -n 2 result

clean:
	rm -rf ./detab ./entab
