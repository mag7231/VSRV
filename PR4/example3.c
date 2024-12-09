#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void redirect_stdout(const char *filename);

int main() {
    // Выводим сообщение в стандартный вывод (консоль)
    printf("Hello, World!\n");
    fflush(stdout);

    // Перенаправляем стандартный вывод в файл
    redirect_stdout("foo.txt");

    // Это сообщение будет записано в файл
    printf("Hello to you too, foo\n");
    fflush(stdout);

    return 0;
}

void redirect_stdout(const char *filename) {
    int fd;

    // Открываем файл для записи (создаём, если он не существует)
    if ((fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0666)) < 0) {
        perror(filename); // Вывод ошибки, если файл открыть не удалось
        exit(EXIT_FAILURE);
    }

    // Закрываем стандартный вывод
    close(STDOUT_FILENO);

    // Дублируем дескриптор файла в место стандартного вывода
    if (dup(fd) != STDOUT_FILENO) {
        fprintf(stderr, "Unexpected dup failure\n");
        exit(EXIT_FAILURE);
    }

    // Закрываем оригинальный файловый дескриптор
    close(fd);
}
