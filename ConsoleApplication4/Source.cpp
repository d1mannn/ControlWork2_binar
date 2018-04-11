#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <Windows.h>


struct MyStruct
{
	int code;
	char name[100];
	int sale;
	int sale2;
	char guarantee[10];
};

void main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("chcp 1251");
	
	FILE * file;
	errno_t err = fopen_s(&file, "pprice.csv", "rb");
	if (err == 0)
	{
		fseek(file, 0, SEEK_END);
		long size = ftell(file);
		printf("%d\n", size);
		rewind(file);
		MyStruct *goods;
		goods = (MyStruct*)calloc(size, sizeof(MyStruct));
		if (goods == NULL)
		{	
			printf("Ошибка при создании структуры\n");
			exit(1);
		}
		fread(goods, sizeof(MyStruct), 1, file);
		FILE * file2;
		err = fopen_s(&file2, "Test.txt", "wb");
		fseek(file, 0, SEEK_END);
		rewind(file);
		fwrite(goods, sizeof(MyStruct), 1, file2);
		printf("Code: %d\n", goods[0].code);
		printf("Name: %s\n", goods[0].name);
		/*for (int i = 0; i < 1; i++)
		{
			printf("%d)\t%d\t%s\t%d\t%d\n\n", i + 1, goods[i].code, goods[i].name, goods[i].sale, goods[i].sale2);
		}*/
		free(goods);
		fclose(file2);
		fclose(file);
	}
	else
	{
		perror("Error");
		exit(1);
	}
}