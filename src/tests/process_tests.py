import os

def read_failed_tests(file_path):
    with open(file_path, 'r') as f:
        return [line.strip() for line in f.readlines()]

def process_file(file_path, failed_tests, error_file):
    temp_file_path = f"{file_path}.tmp"
    with open(file_path, 'r') as f, open(temp_file_path, 'w') as temp_file, open(error_file, 'a') as error_f:
        inside_test = False
        current_test = ""
        buffer = []

        for line in f:
            if line.startswith("#test"):
                if inside_test:
                    if current_test in failed_tests:
                        error_f.write("".join(buffer))
                    else:
                        temp_file.write("".join(buffer))
                    buffer = []
                current_test = line.split()[1]
                buffer.append(line)
                inside_test = True
            else:
                buffer.append(line)
        
        if inside_test:
            if current_test in failed_tests:
                error_f.write("".join(buffer))
            else:
                temp_file.write("".join(buffer))

    os.replace(temp_file_path, file_path)

def main():
    failed_tests_file = 'failed_f.txt'
    error_file = 'error.check'

    if os.path.exists(error_file):
        os.remove(error_file)

    failed_tests = read_failed_tests(failed_tests_file)

    check_files = [f for f in os.listdir('.') if f.endswith('.check') and f != 'error.check' and f != '_header.check']

    for check_file in check_files:
        print(f"Обработка файла: {check_file}")
        process_file(check_file, failed_tests, error_file)

    if os.path.exists(error_file):
        print("error.check был успешно создан и заполнен.")
    else:
        print("Ошибка: error.check не был создан.")

if __name__ == "__main__":
    main()
