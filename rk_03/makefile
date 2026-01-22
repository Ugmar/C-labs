CC := gcc

CFLAGS := -std=c99 -Wall -Werror -pedantic -I inc/
LDFLAGS := -lm
OUT := out
SRC := src

SRCS := $(wildcard $(SRC)/*.c)
OBJS := $(SRCS:$(SRC)/%.c=$(OUT)/%.o)

$(shell mkdir -p $(OUT))

.PHONY : clean

app.exe : $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

$(OUT)/%.o : $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(OUT)/%.d : $(SRC)/%.c
	$(CC) $(CFLAGS) -MM -MT $(OUT)/$*.o $< > $@


-include $(SRCS:$(SRC)/%.c=$(OUT)/%.d)

clean :
	$(RM) -rf $(OUT)/ ./*.exe
