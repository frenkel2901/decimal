#!/bin/bash

make test > make_tests.txt 2>&1

# Ищем все названия функций с проваленными тестами
grep -oP '(?<=test:)[^:]*' make_tests.txt | sort | uniq > failed_f.txt
