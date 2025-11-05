CC := gcc
CFLAGS := -std=c99 -Wall -Werror -pedantic -I inc/
CHECKFLAGS := -lcheck -lm -lrt -lpthread
LDFLAGS := 
OUT := out
CREATE_OUT := $(shell mkdir -p $(OUT))
SRCS := $(wildcard src/*.c unit_tests/*.c)

all :  $(CREATE_OUT)

.PHONY : clean unit release debug func

debug : app.exe
debug: CFLAGS += -g -O0 --coverage
debug: LDFLAGS := --coverage
 
release : app.exe
release: CFLAGS += -O3

unit: unit_tests.exe
		./unit_tests.exe	

func: debug
		./collect_coverage.sh

app.exe : $(OUT)/main.o $(OUT)/arr.o $(OUT)/utils.o
	$(CC) $(LDFLAGS) $^ -o $@

unit_tests.exe : $(OUT)/check_main.o $(OUT)/check_arr.o $(OUT)/check_utils.o $(OUT)/arr.o $(OUT)/utils.o
	$(CC) $^ -o $@ $(CHECKFLAGS)

$(OUT)/check_%.o : unit_tests/check_%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)/%.o : src/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)/%.d : %.c
	$(CC) -M $< > $@

-include $(SRCS:.c=.d)

clean :
	$(RM) -rf $(OUT)/ ./*.exe ./func_tests/data/*out_file_res.txt
