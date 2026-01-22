from tkinter import Tk, Label, Entry, Button, Text, messagebox, END
from ctypes import CDLL, POINTER, c_int, c_size_t

def include_library(name):
    global fill_arr_primary, add_number_after_even

    lib = CDLL(name)

    fill_arr_primary = lib.fill_arr_primary
    fill_arr_primary.argtypes = (POINTER(c_int), c_size_t, c_size_t)
    fill_arr_primary.restype = c_int

    add_number_after_even = lib.add_number_after_even
    add_number_after_even.argtypes = (POINTER(c_int), c_size_t, POINTER(c_int), c_size_t, c_int)
    add_number_after_even.restype = c_int

def calculate_primes():
        try:
            n = int(n_entry.get())
        except ValueError:
             messagebox.showerror("", "Не корректное число")
             return
        
        if n < 0:
             messagebox.showerror("", "Количсетво чисел должно быть больше 0")
             return
        
        arr = (c_int * n)()
        
        rc = fill_arr_primary(arr, n, n)
        
        if rc == 0:
            primes = list(arr)
            primes_result.delete(1.0, END)
            primes_result.insert(END, f"{primes}")
        else:
            messagebox.showerror("", "Ошибка в вычисление простых чисел")

def fill_arr_1():
    try:
        src_arr = [int(x) for x in array_entry.get().split()]
    except ValueError:
        messagebox.showerror("", "Введите числа через пробел")
        return

    try:
        digit = int(digit_entry.get())
    except ValueError:
        messagebox.showerror("", "Не корректное число")
        return
        
    if not src_arr:
        messagebox.showerror("", "Массив не должен быть пустым")
        return
        
    src_len = len(src_arr)
    src = (c_int * src_len)(*src_arr)

    dst = (c_int * (src_len * 2))()

    result = add_number_after_even(src, src_len, dst, src_len * 2, digit)
    
    if result > 0:
        output = list(dst[:result])
        array_result.delete(1.0, END)
        array_result.insert(END, f"{output}")
    else:
        messagebox.showerror("Ошибка", "Ошибка в выделении памяти")

def fill_arr_2():
    try:
        src_arr = [int(x) for x in array_entry.get().split()]
    except ValueError:
        messagebox.showerror("", "Введите числа через пробел")
        return

    try:
        digit = int(digit_entry.get())
    except ValueError:
        messagebox.showerror("", "Не корректное число")
        return
        
    if not src_arr:
        messagebox.showerror("", "Массив не должен быть пустым")
        return
        
    src_len = len(src_arr)
    src = (c_int * src_len)(*src_arr)

    dst_len = add_number_after_even(src, src_len, None, 0, digit)
    dst = (c_int * dst_len)()

    result = add_number_after_even(src, src_len, dst, dst_len, digit)
    
    if result > 0:
        output = list(dst)
        array_result.delete(1.0, END)
        array_result.insert(END, f"{output}")
    else:
        messagebox.showerror("Ошибка", "Ошибка в выделении памяти")
    
window = Tk()
window.title("ЛР №12")
window.geometry("700x600")

title_label = Label(window, text="Лабораторная работа №12")
title_label.place(relx=0.5, rely=0.05, anchor="center")

text1 = Label(window, text="1. Простые числа:")
text1.place(relx=0.1, rely=0.1)

n_label = Label(window, text="N:")
n_label.place(relx=0.1, rely=0.15)

n_entry = Entry(window, width=10)
n_entry.place(relx=0.15, rely=0.15)
n_entry.insert(0, "10")

primes_button = Button(window, text="Посчитать", command=calculate_primes)
primes_button.place(relx=0.32, rely=0.15)

primes_result = Text(window, height=8, width=50)
primes_result.place(relx=0.1, rely=0.2, relwidth=0.8)
primes_result.insert("1.0", "Результат")

text2 = Label(window, text="2. Обработка массива:")
text2.place(relx=0.1, rely=0.5)

array_label = Label(window, text="Массив:")
array_label.place(relx=0.1, rely=0.55)

array_entry = Entry(window, width=20)
array_entry.place(relx=0.2, rely=0.55)
array_entry.insert(0, "1 2 3 4")

digit_label = Label(window, text="Цифра:")
digit_label.place(relx=0.5, rely=0.55)

digit_entry = Entry(window, width=5)
digit_entry.place(relx=0.6, rely=0.55)
digit_entry.insert(0, "0")

method1_button = Button(window, text="Способ 1", command=fill_arr_1)
method1_button.place(relx=0.7, rely=0.55)

method2_button = Button(window, text="Способ 2", command=fill_arr_2)
method2_button.place(relx=0.85, rely=0.55)

array_result = Text(window, height=8, width=50)
array_result.place(relx=0.1, rely=0.6, relwidth=0.8)
array_result.insert("1.0", "Результат")

include_library("./out/libarr.so")

window.mainloop()
