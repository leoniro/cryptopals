all:
	@g++ ex1.cpp -o ex1
	@g++ ex2.cpp -o ex2
	@g++ ex3.cpp -o ex3
	@g++ ex4.cpp -o ex4
	@g++ ex5.cpp -o ex5
	@g++ ex6.cpp -o ex6
	@g++ ex8.cpp -o ex8
	@./ex1
	@./ex2
	@./ex3
	@./ex4
	@./ex5
	@./ex6
	@./ex8
	@make clear

ex7:
	g++ ex7.cpp -o ex7 -lcrypto
	./ex7
	@make clear

clear:
	@rm -f ex1 ex2 ex3 ex4 ex5 ex6 ex7 ex8 7d.txt 7p.txt