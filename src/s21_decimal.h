#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <stdint.h>
#include <stdio.h>

/// @brief Структура децимал
typedef struct {
  unsigned int bits[4];
} s21_decimal;

/// @brief Структура Биг децимал
typedef struct {
  unsigned int bits[16];
} s21_big_decimal;

/// @brief Юнион для последнего бита
typedef union {
  int bits;
  struct {
    uint32_t empty1 : 16;
    uint32_t power : 8;
    uint32_t empty2 : 7;
    uint32_t sign : 1;
  };
} s21_last_bit;

/// @brief Пронумерованный список результатов функций
typedef enum {
  OK = 0,
  TOO_BIG = 1,
  TOO_SMALL = 2,
  DIV_BY_ZERO = 3,
  ERROR = 1
} s21_res_oper;

/// @brief Булевые результаты
typedef enum {
  FALSE = 0,
  TRUE = 1,
} s21_bool;

#include "s21_extra_func.h"

// Математические операции (Паша)

/// @brief Функция сложения
/// @param value_1 Первое слагаемое
/// @param value_2 Второе слагаемое
/// @param result Результат сложения
/// @return 0 — OK; 1 — число слишком велико или равно бесконечности; 2 — число
/// слишком мало или равно отрицательной бесконечности; 3 — деление на 0.
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/// @brief Функция вычетания
/// @param value_1 Уменьшаемое
/// @param value_2 Вычитаемое
/// @param result Результат вычетания
/// @return 0 — OK; 1 — число слишком велико или равно бесконечности; 2 — число
/// слишком мало или равно отрицательной бесконечности; 3 — деление на 0.
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/// @brief Функция умножения
/// @param value_1 Первый множитель
/// @param value_2 Второй множитель
/// @param result Результат произведения
/// @return 0 — OK; 1 — число слишком велико или равно бесконечности; 2 — число
/// слишком мало или равно отрицательной бесконечности; 3 — деление на 0.
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

/// @brief Функция деления
/// @param value_1 Деелимое
/// @param value_2 Делитель
/// @param result Результат деления
/// @return 0 — OK; 1 — число слишком велико или равно бесконечности; 2 — число
/// слишком мало или равно отрицательной бесконечности; 3 — деление на 0.
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

// Операторы сравнения (Максим)

/// @brief Меньше (<)
/// @param  Левый
/// @param  Правый
/// @return Результат из s21_bool
int s21_is_less(s21_decimal, s21_decimal);
/// @brief Меньше либо равно (<=)
/// @param  Левый
/// @param  Правый
/// @return Результат из s21_bool
int s21_is_less_or_equal(s21_decimal, s21_decimal);
/// @brief Больше (>)
/// @param  Левый
/// @param  Правый
/// @return Результат из s21_bool
int s21_is_greater(s21_decimal, s21_decimal);
/// @brief Больше либо равно(>=)
/// @param  Левый
/// @param  Правый
/// @return Результат из s21_bool
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
/// @brief Равно (==)
/// @param  Левый
/// @param  Правый
/// @return Результат из s21_bool
int s21_is_equal(s21_decimal, s21_decimal);
/// @brief Не равно (!=)
/// @param  Левый
/// @param  Правый
/// @return Результат из s21_bool
int s21_is_not_equal(s21_decimal, s21_decimal);

// Преобразователи (Аля)

/// @brief Преобразование из int в децимал
/// @param src Исходный int
/// @param dst Указатель на децимал, куда записать
/// @return Результат ОК или Ошибка из s21_res_oper
int s21_from_int_to_decimal(int src, s21_decimal *dst);
/// @brief Преобразование из float в децимал
/// @param src Исходный float
/// @param dst Указатель на децимал, куда записать
/// @return Результат ОК или Ошибка из s21_res_oper
int s21_from_float_to_decimal(float src, s21_decimal *dst);
/// @brief Преобразование из децимал в int
/// @param src Исходный децимал
/// @param dst Указатель на int, куда записать
/// @return Результат ОК или Ошибка из s21_res_oper
int s21_from_decimal_to_int(s21_decimal src, int *dst);
/// @brief Преобразование из децимал в float
/// @param src Исходный децимал
/// @param dst Указатель на float, куда записать
/// @return Результат ОК или Ошибка из s21_res_oper
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// Другие функции (Леша)

/// @brief Округляет указанное Decimal число до ближайшего целого числа в
/// сторону отрицательной бесконечности.
/// @param value Децимал для округления
/// @param result Указатель на децимал куда записать результат
/// @return Возвращает успешность операции из s21_res_oper
int s21_floor(s21_decimal value, s21_decimal *result);
/// @brief Округляет Decimal до ближайшего целого числа.
/// @param value Децимал для округления
/// @param result Указатель на децимал куда записать результат
/// @return Возвращает успешность операции из s21_res_oper
int s21_round(s21_decimal value, s21_decimal *result);
/// @brief Возвращает целые цифры указанного Decimal числа; любые дробные цифры
/// отбрасываются, включая конечные нули.
/// @param value Децимал для округления
/// @param result Указатель на децимал куда записать результат
/// @return Возвращает успешность операции из s21_res_oper
int s21_truncate(s21_decimal value, s21_decimal *result);
/// @brief Возвращает результат умножения указанного Decimal на -1.
/// @param value Децимал для округления
/// @param result Указатель на децимал куда записать результат
/// @return Возвращает успешность операции из s21_res_oper
int s21_negate(s21_decimal value, s21_decimal *result);

#endif