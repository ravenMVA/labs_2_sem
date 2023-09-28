#!/bin/bash

# Проверяем, что передано два параметра
if [ $# -ne 2 ]; then
    echo "Использование: $0 <суффикс> <длина[байт]>"
    exit 1
fi

# Извлекаем параметры
suff="$1"
length="$2"

# Выводим параметры
echo "Расширение файлов: $suff"
echo "Желаемый размер: $length байт"

echo "Найденные файлы:"
file_list=$(find . -type f -name "*.$suff")
files_to_increase=()

# Смотрим, какие файлы подходят для увеличения
for file_path in ${file_list[@]}; do
    file=$(basename "$file_path")
    file_size=$(stat -f%z "$file")
    echo "$file [$file_size байт]"
    if [ "$file_size" -lt "$length" ]; then
        files_to_increase+=("$file_path")
    fi
done

# Получаем путь файла, который следует прибавить к остальным
read -r -p "Введите путь к файлу, который следует использовать для заполнения: " add_file_path

# Проверка на то, есть ли этот файл в списке найденных
for file_path in ${file_list[@]}; do
    if [ "$(realpath $file_path)" = "$(realpath $add_file_path)" ]; then
        echo "Нельзя использовать файлы из списка"
        exit 1
    fi
done

# Существует ли файл
if [ -f "$add_file_path" ]; then
    if [ -s "$add_file_path" ]; then
        file_size=$(stat -f%z "$add_file_path")
        echo "Файл существует: $add_file_path [$file_size байт]"
    else
        echo "Размер указанного файла равен 0 байт"
        exit 2
    fi
else
    echo "Введенный путь неверен: $add_file_path"
    exit 3
fi

# Пробегаемся по файлам
for file_path in ${files_to_increase[@]}; do
    # Увеличиваем до тех пор, пока размер не станет >= $length
    while true; do
        file_size=$(stat -f%z "$file_path")

        if [ "$file_size" -lt "$length" ]; then
            cat "$add_file_path" >> "$file_path"
        else
            break 
        fi
    done
done

# Вывод измененных файлов с их новыми размерами
echo "Размер файлов увеличен:"
for file_path in ${files_to_increase[@]}; do
    file=$(basename "$file_path")
    file_size=$(stat -f%z "$file")
    echo "$file [$file_size байт]"
done

exit 0
