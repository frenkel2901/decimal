#ifndef S21_EXTRA_FUNC_H
#define S21_EXTRA_FUNC_H

#include "s21_decimal.h"

/// @brief Проверка состояния бита в позиции
/// @param bit Само число
/// @param order Какую позицию проверить
/// @return Возвращает значение бита в данной позиции
int s21_check_bit(unsigned int bit, int order);

/// @brief Устанавливает бит в указанное значение
/// @param bit Само число
/// @param order Какую позицию установить
/// @param value Какое значение установить
void s21_set_bit(unsigned *bit, int order, int value);

/// @brief Устанавливает указанный бит в состояние 1
/// @param bit Само число
/// @param order Какую позицию установить
void s21_turn_on_bit(unsigned *bit, int order);

/// @brief Устанавливает указанный бит в состояние 0
/// @param bit Само число
/// @param order Какую позицию установить
void s21_turn_off_bit(unsigned *bit, int order);

/// @brief Получение степени Decimal
/// @param num Переменная 3 бита
/// @return Возвращает числовое значение power
int s21_get_scale(unsigned dec);

/// @brief Установка степени Decimal
/// @param num Указатель на переменную 3 бита
/// @param power Степень, которую нужно установить
void s21_set_scale(unsigned *dec, int power);

// /// @brief Вывод на экран двоичное представление инта
// /// @param num Инт который нужно вывести
// void print_bin(unsigned dec);

/// @brief Получение знака Decimal
/// @param num Переменная 3 бита
/// @return Возвращает 0 - плюс 1 - минус
int s21_get_sign(unsigned dec);

/// @brief Установка знака Decimal
/// @param num Указатель на переменную 3 бита
/// @param sign Какой знак нужно поставить 0 - плюс, 1 - минус
void s21_set_sign(unsigned *dec, int sign);

/// @brief Обнуляет decimal
/// @param num Переменная decimal
void s21_nullify(s21_decimal *num);

/// @brief Зануляет биг децимал
/// @param num Указатель на биг децималfdi
void s21_nullify_big(s21_big_decimal *num);

/// @brief Возвращает значение указанного бита
/// @param value число биг децимал
/// @param bit номер бита
/// @return значение указанного бита, 0 или 1
int s21_get_big_bit(const s21_big_decimal value, int bit);

/// @brief Суммирует побитово нормализованный (биг)
/// @param value_1 первое слагаемое (биг)
/// @param value_2 второе слагаемое (биг)
/// @return результат сложения (биг)
s21_big_decimal s21_big_bit_add(s21_big_decimal value_1,
                                s21_big_decimal value_2);

/// @brief Вычитает побитово нормализованный (биг)
/// @param value_1 уменьшаемое (биг)
/// @param value_2 вычитаемое (биг)
/// @return результат вычитания (биг)
s21_big_decimal s21_big_bit_sub(s21_big_decimal value_1,
                                s21_big_decimal value_2);

/// @brief Перемножает побитово нормализованный (биг)
/// @param value_1 первый множитель (биг)
/// @param value_2 второй множитель (биг)
/// @return результат умножения (биг)
s21_big_decimal s21_big_bit_mul(s21_big_decimal value_1,
                                s21_big_decimal value_2);

/// @brief Делит побитово нормализованный (биг)
/// @param value_1 делимое (биг)
/// @param value_2 делитель (биг)
/// @param res Указатель на результат биг
/// @return осттаток от деления (биг)
s21_big_decimal s21_big_bit_div(s21_big_decimal value_1,
                                s21_big_decimal value_2, s21_big_decimal *res);

/// @brief Смещение битов децимала влево до указанного
/// @param value Изначальное значение decimal (big)
/// @param shift На сколько необходимо сместить
/// @return Результирующий decimal после смещение
s21_big_decimal s21_left_shif_decimal(s21_big_decimal value, int shift);

/// @brief Смещение битов на 1 влево
/// @param bit Изначальный бит
/// @return Смещенный бит на 1
unsigned s21_left_shift_bit(unsigned bit);

// /// @brief Возвращает номер первого значащего бита
// /// @param value Где нужно найти
// /// @return Первый значащий бит
// int s21_get_big_long_bin(s21_big_decimal value);

/// @brief Нормализует число
/// @param value Исходный биг децимал
/// @param shift домножает на 10 в указанной степени
/// @return Возвращает нормализованное число
s21_big_decimal s21_normalize(s21_big_decimal value, int shift);

// /// @brief Выводит на экран двоичное представление big_dec
// /// @param value Значение big_dec которое нужно вывести
// void print_big_dec(s21_big_decimal value);

// /// @brief Выводит на экран двоичное представление dec
// /// @param value Значение dec которое нужно вывести
// void print_dec(s21_decimal value);

/// @brief Превращает dec в big_dec
/// @param value Изначальный dec
/// @return big_dec
s21_big_decimal s21_convert_to_big(s21_decimal value);

/// @brief Нормализует два биг децимала
/// @param value1 big_decimal
/// @param value2 big_decimal
void s21_normalize_two_big(s21_big_decimal *value1, s21_big_decimal *value2);

/// @brief Проверка нулевой ли децимал
/// @param val
/// @return Возвращает 1 - если ноль, 0 - если не ноль.
int s21_is_dec_zero(s21_decimal val);

/// @brief Проверка нулевой ли биг децимал
/// @param val
/// @return Возвращает 1 - если ноль, 0 - если не ноль.
int s21_is_big_zero(s21_big_decimal val);

/// @brief Функция больше для биг деци
/// @param val1 Левый
/// @param val2 Правый
/// @return Результат 1 больше, 0 меньше
int s21_is_greater_big(s21_big_decimal val1, s21_big_decimal val2);

/// @brief Возвращает, первый встреченный больший бит
/// @param val1 Левый
/// @param val2 Правый
/// @return 1 Левый больше, -1 Правый больше, 0 - равны
int s21_first_bigger_bit(s21_big_decimal val1, s21_big_decimal val2);

/// @brief Функция сравнения для биг
/// @param val1 Левый
/// @param val2 Правый
/// @return 1 - равны, 0 - не равны
int s21_is_equal_big(s21_big_decimal val1, s21_big_decimal val2);

/// @brief Функция меньше для биг
/// @param val1 Левый
/// @param val2 Правый
/// @return 1 - Меньше, 0 - Больше
int s21_is_less_big(s21_big_decimal val1, s21_big_decimal val2);

/// @brief Функция меньше либо равно для биг
/// @param val1 Левый
/// @param val2 Правый
/// @return Результат 1 или 0
int s21_is_less_or_equal_big(s21_big_decimal val1, s21_big_decimal val2);

/// @brief Функция больше либо равно для биг
/// @param val1 Левый
/// @param val2 Правый
/// @return Результат 1 или 0
int s21_is_greater_or_equal_big(s21_big_decimal val1, s21_big_decimal val2);

/// @brief Функция не равно для биг
/// @param val1 Левый
/// @param val2 Правый
/// @return Результат 1 или 0
int s21_is_not_equal_big(s21_big_decimal val1, s21_big_decimal val2);

/// @brief Отделение дробной части от целой части
/// @param val Где отделять
/// @param res Куда записать результат
/// @return Отделенная часть
s21_big_decimal s21_big_bit_truncate(s21_big_decimal val, s21_big_decimal *res);

// /// @brief Узнает длину битов числа
// /// @param val Биг дец
// /// @return Кол-во значимых битов
// int s21_len_big_bit(s21_big_decimal val);

/// @brief Конвертация бига в децимал
/// @param val Биг Децимал
/// @param res Указатель на децимал
/// @return Возвращает 1 в случае ошибки и 0 в случае ок
int s21_convert_to_dec(s21_big_decimal val, s21_decimal *res);

/// @brief Возвращает модуль бига
/// @param val Передваемый биг
/// @return Возвращаемый биг
s21_big_decimal s21_big_bit_abs(s21_big_decimal val);

/// @brief Округление биг деци
/// @param val Значение для округления
/// @param scale Степень 10
/// @return Возвращает округленный биг
s21_big_decimal s21_big_rounding(s21_big_decimal val, int scale);

/// @brief Банковское округление биг деци
/// @param val Значение для округления
/// @param rest Число, которое было после запятой
/// @param scale Кол-во чисел после запятой
/// @return Результат банковского округления
s21_big_decimal s21_big_bank_rounding(s21_big_decimal val, s21_big_decimal rest,
                                      int scale);

/// @brief Проверяет дополнительные биты в биге
/// @param val Биг деци
/// @return 1 - Если есть, 0 - Если заполнено только 3 первые бита
int s21_check_extra_bit(s21_big_decimal val);

/// @brief Деление на 10
/// @param result Указатель на биг деци которое нужно поделить на 10
/// @return Остаток от деления на 10
s21_big_decimal s21_div_by_ten_big(s21_big_decimal *result);

/// @brief Умножает биг деци на 10
/// @param result Указатель на биг деци которое нужно умножить на 10
void s21_mul_by_ten_big(s21_big_decimal *result);

#endif