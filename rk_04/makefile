CC := gcc

CFLAGS := -std=c99 -Wall -Werror

SRCS := $(wildcard ./*.c)
OBJS := $(SRCS:./%.c=./%.o)

.PHONY : clean 

app.exe : $(OBJS)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

%.d : %.c
	$(CC) $(CFLAGS) -MM $< > $@

include $(SRCS:%.c=%.d)

clean :
	$(RM) -rf ./*.exe ./*.d ./*.o
