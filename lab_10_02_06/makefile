CC := gcc

CFLAGS := -std=gnu99 -Wall -Werror -pedantic -I inc/
CHECKFLAGS := -lcheck -lm -lrt -lpthread
LDFLAGS := -lm
OUT := out
SRC := src
UNIT_TESTS := unit_tests

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(SRCS:$(SRC)/%.c=$(OUT)/%.o)

SRCS_UNIT := $(wildcard $(UNIT_TESTS)/*.c)
OBJS_UNIT := $(SRCS_UNIT:$(UNIT_TESTS)/%.c=$(OUT)/%.o)
OBJS_UNIT := $(filter-out $(OUT)/main.o, $(OBJS)) $(OBJS_UNIT)

$(shell mkdir -p $(OUT))

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

app.exe : $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

unit_tests.exe : $(OBJS_UNIT)
	$(CC) $^ -o $@ $(CHECKFLAGS)

$(OUT)/%.o : $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)/%.o : $(UNIT_TESTS)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)/%.d : $(SRC)/%.c
	$(CC) $(CFLAGS) -MM -MT $(OUT)/$*.o $< > $@

$(OUT)/%.d : $(UNIT_TESTS)/%.c
	$(CC) $(CFLAGS) -MM -MT $(OUT)/$*.o $< > $@

include $(SRCS:$(SRC)/%.c=$(OUT)/%.d)
include $(SRCS_UNIT:$(UNIT_TESTS)/%.c=$(OUT)/%.d)

clean :
	$(RM) -rf $(OUT)/ ./*.exe ./func_tests/data/*_result.txt ./unit_tests/tests/*_out.txt
