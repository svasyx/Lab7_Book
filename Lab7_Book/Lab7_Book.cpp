#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>



struct Book //оголошення струтури 
{
    char name_of_book[256];
    char author[256];
    int year_of_publication;
};

int StrCount(FILE* fp);//підрахунок строк у файлі
Book* SearchByYear(Book* arr, int size, int serchYear, int& newsize);//сортування
void print(Book* students, int count);//друк структури в консоль\


int main(int argc, char* argv[])
{
    FILE* fp = NULL; // створення файлового дескриптора
    FILE* fd = NULL; // створення файлового дескриптора


    Book* book = NULL; // створення змінної типу  Book
    Book* tempbook = NULL;

    char filename_input[256]; // ім'я файлу
    char filename_output[256];

    int newsize = 0;
    int count = 0;//к-сть строк у файлі

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    //введення назви файлу
    if (argc < 2) {
        printf("введіть назву файлу: ");
        do {
            fgets(filename_input, 256, stdin);
            if (filename_input[0] == '\n')
            {
                printf("Введіть ім'я файлу: ");
            }
        } while (filename_input[0] == '\n');
        filename_input[strlen(filename_input) - 1] = ' ';
    }
    else
    {
        strcpy(filename_input, argv[1]);
    }
    //відкриття файлу
    if ((fp = fopen(filename_input, "r")) == NULL)
    {
        printf("Помилка!\n");
        return 1;
    }
    //виділення пам'яті під змінну 
    if (!(book = (Book*)malloc(sizeof(Book) * StrCount(fp))))
    {
        printf("Помилка виділення пам'яті");
        return 3;

    }
    //зчитування з файлу та запис елементів до структури
     //Записуємо всі елементи структури поки не дійдемо до кінця файлу
    while (feof(fp) == 0)
    {
        /*Перевірка чи вдалося зчитати данні з файлу*/
        if ((fscanf(fp, "\n%[^;];", &book[count].name_of_book)) != 1)
        {
            printf("He вдалося зчитати файл!\nПомилка в рядку %d", count + 1);
            return 1;
        }

        /*Перевірка чи вдалося зчитати данні з файлу*/
        if ((fscanf(fp, "%[^;];", &book[count].author)) != 1)
        {
            printf("He вдалося зчитати файл!\nПомилка в рядку %d", count + 1);
            return 1;
        }

        /*Перевірка чи вдалося зчитати данні з файлу*/
        if ((fscanf(fp, "%d", &book[count].year_of_publication)) != 1)
        {
            printf("He вдалося зчитати файл!\nПомилка в рядку %d", count + 1);
            return 1;
        }


        count++;
    }

    //закриття файлу
    if (fclose(fp) == EOF)
    {
        printf("не вдалося закрити файл!");
        return 2;

    }

    //Книги після зчитування
    printf("Книги після зчитування:\n");
    print(book, count);


    tempbook = SearchByYear(book, count, 2002, newsize);

    //Книги після пошуку
    printf("Книги після пошуку:\n");
    print(tempbook, newsize);


    //відкриття файлу для запису результату

    strcpy(filename_output, filename_input);
    filename_output[strlen(filename_input) - 4] = 'd';
    filename_output[strlen(filename_input) - 3] = 'a';
    filename_output[strlen(filename_input) - 2] = 't';
    filename_output[strlen(filename_input) - 1] = '\0';



    if (!(fd = fopen(filename_output, "w+")))
    {
        printf("не вдалося відкрити файл!");
        return 1;

    }


    for (int i = 0; i < newsize; i++)
    {
        fprintf(fd, "%s;%s;%d\n", tempbook[i].name_of_book, tempbook[i].author, tempbook[i].year_of_publication);
    }




    //закриття файлу
    if (fclose(fp) == EOF)
    {
        printf("не вдалося закрити файл!");
        return 2;

    }

    return 0;
}

int StrCount(FILE* fp)
{
    int count = 0;


    while (!feof(fp))
    { //ігноруємо перехід на нову строку
        fscanf(fp, "%*[^\n]\n");
        count++;
    }
    //переміщщеня вказівнику на початок файлу
    rewind(fp);

    return count;
}


void print(Book* book, int count)
{
    for (int i = 0; i < count; i++)
    {
        //вивід структури на екран, використовуючи індексацію
        printf("Автор: %s Назва книги: %s Рік випуску: %d\n ", book[i].author, book[i].name_of_book, book[i].year_of_publication);

    }
}



Book* SearchByYear(Book* arr, int size, int serchYear, int& newsize)
{

    Book* tempbook = NULL;
    int count=0;

    if (!(tempbook = (Book*)malloc(sizeof(Book))))
    {
        printf("Помилка виділення пам'яті");
        return 0;

    }


    for (int i = 0; i < size; i++)
    {
        if (arr[i].year_of_publication == serchYear)
        {

            strcpy(tempbook[newsize].author,arr[i].author);
            strcpy(tempbook[newsize].name_of_book, arr[i].name_of_book);
            tempbook[newsize].year_of_publication = arr[i].year_of_publication;

            newsize++;

        }
    }
    //повертаємо структуру
    return tempbook;
}


