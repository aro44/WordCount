// WordCount.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

// 函数原型
int countCharacters(FILE* file);
int countWords(FILE* file);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s [-c | -w] <file_name>\n", argv[0]);
        return 1;
    }

    char* param = argv[1];
    char* filename = argv[2];
    FILE* file = NULL;
    errno_t err = fopen_s(&file, filename, "r");

    if (err != 0) {
        perror("Error opening file");
        return 1;
    }

    int result = 0;
    if (strcmp(param, "-c") == 0) {
        result = countCharacters(file);
        printf("字符数：%d\n", result);
    }
    else if (strcmp(param, "-w") == 0) {
        result = countWords(file);
        printf("单词数：%d\n", result);
    }
    else {
        printf("Invalid parameter. Use '-c' for characters or '-w' for words.\n");
    }

    fclose(file);
    return 0;
}

int countCharacters(FILE* file) {
    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    // 重置文件指针到文件开头
    fseek(file, 0, SEEK_SET);
    return count;
}

int countWords(FILE* file) {
    int count = 0;
    int ch;
    bool inWord = false;
    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || ch == ',') {
            if (inWord) {
                count++;
                inWord = false;
            }
        }
        else {
            inWord = true;
        }
    }
    // 如果文件以非空格结尾，则最后一个单词不计入
    if (inWord) {
        count++;
    }
    // 重置文件指针到文件开头
    fseek(file, 0, SEEK_SET);
    return count;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
