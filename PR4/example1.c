#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    // Создаём разрежённый файл
    int fd = open("sparse_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Ошибка открытия файла");
        return 1;
    }

    lseek(fd, 10000000, SEEK_SET); // Перемещаем указатель на 10 МБ
    write(fd, " ", 1);            // Записываем 1 байт
    close(fd);
    printf("Разрежённый файл создан: sparse_file.txt\n");

    // Создаём временный файл
    char tmpname[] = "C:\\Users\\galan\\VSRV\\qqqXXXXXX";
    int tmpfd = mkstemp(tmpname);
    if (tmpfd == -1) {
        perror("Ошибка создания временного файла");
        return 1;
    }
    unlink(tmpname);              // Удаляем имя файла

    write(tmpfd, "X", 1);         // Записываем 1 символ
    lseek(tmpfd, 0, SEEK_SET);    // Перемещаем указатель в начало
    char buffer;
    read(tmpfd, &buffer, 1);      // Читаем 1 символ
    printf("Прочитано из временного файла: '%c'\n", buffer);

    close(tmpfd);
    printf("Все операции завершены успешно.\n");
    return 0;
}
