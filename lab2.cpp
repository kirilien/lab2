// lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "list_funcs.h"

#include "Unit.h"
#include "StendhalTree.h"

int main() {
	
	StendhalTree<int, char> *tree = new StendhalTree<int, char>();
	char ch = 'a';
	int key;
	char val;
	List<int> *listKey = nullptr;
	List<char> *listVal = nullptr;
	std::cout << "\n0: Quit\n1: Insert\n2: Remove\n3: Find\n4: Print\n5: Clear\n6: Get keys\n7: Get values\n8: Testing\n\n";
	while (ch != '0') {

		std::cin >> ch;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		StendhalNode<int, char> *node = nullptr;


		switch (ch) {

		case '1':
		{
			std::cout << "Enter key, then value:\n";
			std::cin >> key >> val;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			tree->insert(key, val);
			std::cout << "Node was added\n";
			break;
		}
		case '2':
		{
			std::cout << "Enter key:\n";
			std::cin >> key;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			tree->remove(key);
			std::cout << "Node was removed\n";
			break;
		}
		case '3':
		{
			std::cout << "Enter key:\n";
			std::cin >> key;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			node = tree->find(key);
			if (node==nullptr) {
				std::cout << "There is no such node.\n";
			}
			else {
				std::cout << *node << std::endl;
			}
			delete node;
			node = nullptr;
			break;
		}
		case '4':
		{
			std::cout << *tree;
			break;
		}
		case '5':
		{
			tree->clear();
			std::cout << "Tree was cleared\n";
			break;
		}
		case '6':
		{
			listKey =  tree->get_keys();
			if (listKey->isEmpty()) {
				std::cout << "Tree is empty\n";
				break;
			}
			listKey->print_to_console();
			listKey->clear();
			std::cout << "\n";
			break;
		}
		case '7':
		{
			listVal = tree->get_values();
			if (listVal->isEmpty()) {
				std::cout << "Tree is empty\n";
				break;
			}
			listVal->print_to_console();
			listVal->clear();
			std::cout << "\n";
			break;
		}
		case '8':
		{
			test_all();
			std::cout << "\n";
			break;
		}
		}
	}

	std::cin.get();
	return 0;
}