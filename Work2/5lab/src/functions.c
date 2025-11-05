// должна брать строки из первого
// если строка меньше 80 то стираем все пробельные символы в начале и пихаем иначе надо думоть

/*  Реализуйте программу, которая принимает на вход 2 строки(в интерактивном 
режиме) – пути к файлам ввода и вывода. Программа должна переносить текст 
из первого файла во второй файл. При этом производится разбиение каждой 
считанной  строки  исходного  текста  на  строки  по  80  символов,  где  80-й  – 
последняя  буква  некоторого  слова  (записанная  без  пробелов 
последовательность любых читаемых символов). Для этого между словами в 
строке  равномерно  добавляются  пробелы.  Если  в  считанном  куске  <  80 
символов, он просто переписывается в новый файл. Первым символом новой 
строки должен быть читаемый символ
*/
#include "../include/functions.h"

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define LINE_W 80

// завести функцию trimLSpaces
char* trimLSpaces(char** buf) {
    while (**buf && isspace(**buf)) {
        ++(*buf);
    }
    return *buf;
}

void splitLongLine(char* curLine, char** src) {
    int idx = LINE_W;

    while (idx >= 0 && !isspace((*src)[idx])) // going back po last slovu
        idx--;

    while (idx >= 0 && isspace((*src)[idx])) // idx points to last letter of pred last word
        idx--;


    if (idx == -1) { // out of bounds stroka iz probelov
        strncpy(curLine, *src, LINE_W);
        curLine[LINE_W] = '\0';
        *src += LINE_W;

    } else {
        idx++;
        strncpy(curLine, *src, idx);
        curLine[idx] = '\0';
        *src += idx;
    }
}

void addSpaces(char* line, FILE* out) {
    int len = strlen(line);
    int wordCount = 1;


    for (int i = 1; i < len; ++i)
        if (line[i - 1] != ' ' && line[i] == ' ')
            wordCount++;

    int extraNeeded = LINE_W - len;
    if (wordCount == 1) {
        fputs(line, out);
        fputc('\n', out);
        return;
    }

    int gap = extraNeeded / (wordCount - 1); // every pair po tvare (spaces)
    int rem = extraNeeded % (wordCount - 1); // lishnie

    char result[LINE_W + 1];
    int j = 0;


    for (int i = 0; i < len && j < LINE_W; ++i) {
        result[j++] = line[i];

        if (!isspace(line[i]) && isspace(line[i + 1])) { // если встретили пробел

            for (int k = 0; k < gap && j < LINE_W; ++k) { // fill in with k spaces
                result[j++] = ' ';
            }
            if (rem-- > 0 && j < LINE_W) { // tyta add not even spaces
                result[j++] = ' ';
            }
        }
    }
    result[LINE_W] = '\0';
    fputs(result, out);
    fputc('\n', out);
}

void handleString(char* str, FILE* fOut) {
    while (str && *str) {
        str = trimLSpaces(&str);

        if (!*str)
            break;

        if (strlen(str) <= LINE_W) {
            fputs(str, fOut);
            break;
        }


        char curLine[LINE_W + 1] = {[0] = '\0'};
        if (str[LINE_W] == ' ') { // все хорошо строка уместилась, пихаем, убирая пробелы в конце
            strncpy(curLine, str, LINE_W);

            int end = LINE_W - 1;

            while (end >= 0 && curLine[end] == ' ') {
                --end;
            }

            curLine[++end] = '\0';
            str += LINE_W;

        } else {
            splitLongLine(curLine, &str); // too long nado splitanut
        }


        if (strlen(curLine) < LINE_W) {
            addSpaces(curLine, fOut);
        } else {
            fputs(curLine, fOut);
            fputc('\n', fOut);
        }
    }
}

void refactor(FILE* fIn, FILE* fOut) {
    char buf[4096];
    while (fgets(buf, sizeof(buf), fIn)) {
        char* ptr = buf;


        trimLSpaces(&ptr);
        size_t len = strlen(ptr);

        if (len == 0 || *ptr == '\n')
            continue;

        if (len <= LINE_W)
            fputs(ptr, fOut);

        else
            handleString(ptr, fOut);
    }
}
