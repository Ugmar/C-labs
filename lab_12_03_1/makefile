CC := gcc

CFLAGS := -std=c99 -Wall -Werror -I inc/
DYNAMIC_FLAGS := $(CFLAGS) -fPIC
CHECKFLAGS := -lcheck -lm -lrt -lpthread
LDFLAGS := -lm
OUT := out
SRC := src
UNIT_TESTS := unit_tests
AR := ar
ARFLAGS := crs

LIB_SRCS := $(wildcard $(SRC)/*_lib.c)
LIB_OBJS := $(LIB_SRCS:$(SRC)/%.c=$(OUT)/%.o)

SRCS := $(wildcard $(SRC)/*.c)
SRCS := $(filter-out $(LIB_SRCS), $(SRCS))
OBJS := $(SRCS:$(SRC)/%.c=$(OUT)/%.o)

SRCS_UNIT := $(wildcard $(UNIT_TESTS)/*.c)
OBJS_UNIT := $(SRCS_UNIT:$(UNIT_TESTS)/%.c=$(OUT)/%.o)
OBJS_UNIT := $(filter-out $(OUT)/main.o, $(OBJS)) $(OBJS_UNIT)

STATIC_LIB := $(OUT)/libio.a
DYNAMIC_LINK_LIB := $(OUT)/libfilter.so
DYNAMIC_LOAD_LIB := $(OUT)/libsort.so

LIBS := $(STATIC_LIB) $(DYNAMIC_LINK_LIB) $(DYNAMIC_LOAD_LIB)

$(shell mkdir -p $(OUT))

.SECONDARY: $(LIB_OBJS)
.PHONY: clean unit release debug func

debug: app.exe
debug: CFLAGS += -g -O0 --coverage
debug: LDFLAGS := --coverage

release: app.exe
release: CFLAGS += -O3

unit: unit_tests.exe
	./unit_tests.exe	

func: debug
	./collect_coverage.sh

app.exe: $(OBJS) $(LIBS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(STATIC_LIB) $(DYNAMIC_LINK_LIB) -ldl

unit_tests.exe: $(OBJS_UNIT) $(LIBS)
	$(CC) -o $@ $(OBJS_UNIT) $(CHECKFLAGS) $(STATIC_LIB) $(DYNAMIC_LINK_LIB) -ldl

$(OUT)/lib%.a: $(OUT)/%_lib.o
	$(AR) $(ARFLAGS) $@ $<

$(OUT)/lib%.so: CFLAGS = $(DYNAMIC_FLAGS)
$(OUT)/lib%.so: $(OUT)/%_lib.o
	$(CC) -o $@ -shared $< 

$(OUT)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)/%.o: $(UNIT_TESTS)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)/%.d: $(SRC)/%.c
	$(CC) $(CFLAGS) -MM -MT $(OUT)/$*.o $< > $@

$(OUT)/%.d: $(UNIT_TESTS)/%.c
	$(CC) $(CFLAGS) -MM -MT $(OUT)/$*.o $< > $@

include $(SRCS:$(SRC)/%.c=$(OUT)/%.d)
include $(SRCS_UNIT:$(UNIT_TESTS)/%.c=$(OUT)/%.d)

clean:
	$(RM) -rf $(OUT)/ ./*.exe ./func_tests/data/*_file_res.txt ./unit_tests/tests/*_out.txt
