﻿// cparser_test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "./cparse-master/shunting-yard.h"
#include "./cparse-master/builtin-features.inc"
//using namespace cparser;
int main()
{
	cparse_startup();
	TokenMap vars;
	vars["pi"] = 3.14;
	const char* exp = "a=-pi+1;b=90";
	const char* rest = exp;
	packToken t1 = calculator::calculate(rest,vars,";",&rest);
	rest++;
	packToken t2 = calculator::calculate(rest, vars, ";", &rest);
	if (vars.find("c") == NULL)
		std::cout << "Undefined";
	else
		std::cout << vars["c"];
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.