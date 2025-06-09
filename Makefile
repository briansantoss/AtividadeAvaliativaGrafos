CC = gcc
CFLAGS = -Wall

.PHONY: all run1 ru2 clean

all: run1 run2

run1: main1
	@echo "Executando projeto 1..."
	@./$<

run2: main2
	@echo "Executando projeto 2..."
	@./$<

main1: projeto1/main.c
	@$(CC) $(CFLAGS) $< -o $@

main2: projeto2/main.c
	@$(CC) $(CFLAGS) $< -o $@

clean:
	@rm -f main1 main2