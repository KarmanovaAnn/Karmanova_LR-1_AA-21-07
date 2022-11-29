#pragma once
#include <iostream>
#include <string>
#include <map>
#include <set>

template <typename T>
T GetCorrectNumber(T min, T max)
{
	T x;
	while ((std::cin >> x).fail()	// check type
		|| std::cin.peek() != '\n'	// is buffer empty (int/float check)
		|| x < min || x > max)		// check range
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "Ошибка ввода!";
	}
	return x;
}

template <typename T>
void Tryanswer(T& input) {
	while ((std::cin >> input).fail() || (input != 0 && input != 1)) {
		std::cout << "Ошибка ввода!" << std::endl;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}
}



template <typename TObj, typename Tp>
using Filter = bool(*)(const TObj&, Tp);

template <typename TObj>
bool Names(const TObj& obj, std::string param) {
    return(strstr(obj.Pname.c_str(), param.c_str()));
}

template <typename TObj, typename Tp>

std::set<int> FilterObjects(std::map <int, TObj>& objs, Filter<TObj, Tp> f, Tp param)
{
	std::set<int> found;
    for (auto& [id, obj] : objs)
        if (f(obj, param))
            found.emplace(id);
    return found;
}