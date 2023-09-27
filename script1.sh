#!/bin/bash

if [$# -ne 4]; then #проверяем, что передано необходимое количество аргументов 
echo "Using: $0 <directory> <suffix> <minimum length> <file to add path>"
exit 1
fi
#извлекаем аргументы 
directory="$1"
suffix ="$2"
min_length= "$3"
file_to_add= "$4"

#проверяем, что директория существует 
if 
    [! -d "$directory"]; then
    echo  "Directory $directory does not exist."
    exit 1
 fi 

 #проверяем, что файл добавления существует 
 if 
    [! -f "$file_to_add"]; then
    echo "File to add $file_to_add does not exist."
    exit 1
 fi

#проходимся по файлам в директории с указанным суффиксом 
for file in "$directory"/*"$suffix"; do 
#проверяем, является ли файл меньше указанной длины
    file_length= $(wc -c <"$file")
        if [ "$file_length" -lt "$min_length"]; then
        #вычисляем, cколько копий нужно добавить, чтобы получить заданную длину
            num_copies=$((($min_length - $file_length + $(wc -c <"$file_to_add") - 1)/$ (wc -c <"$file_to_add"))
    #добавляем необходимое количество копий 
        for (i=0; i < num_copies; i++) do
            cat "$file_to_add" >> "$file"
        done 
    echo "File '$file' was extended for $min_length bytes."
   else 
   echo "File $file has already required length."
   fi
done
