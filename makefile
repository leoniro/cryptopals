all:
	@g++ ex1.cpp -o ex1
	@g++ ex2.cpp -o ex2
	@g++ ex3.cpp -o ex3
	@g++ ex4.cpp -o ex4
	@g++ ex5.cpp -o ex5
	@g++ ex6.cpp -o ex6
	@./ex1
	@./ex2
	@./ex3
	@./ex4
	@./ex5
	@./ex6
	@make clear

clear:
	@rm -f ex1 ex2 ex3 ex4 ex5 ex6 ex7