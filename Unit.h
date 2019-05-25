#pragma once
#include "StendhalTree.h"
#include <assert.h>
void test_getKeys_getValues()
{
	StendhalTree<int, char> *tree = new StendhalTree<int, char>();
	List<int> *listKey = nullptr;
	List<char> *listVal = nullptr;
	
	//-----------------------------------

	int keys[10] = { 4, 2,  1,  3,  6, 5, 8, 7,9,10 };
	char vals[] = "dbacfehgij";
	
	//--------------------------------
	tree->insert(1, 'a');
	tree->insert(2, 'b');
	tree->insert(3, 'c');
	tree->insert(4, 'd');
	tree->insert(5, 'e');
	tree->insert(6, 'f');
	tree->insert(7, 'g');
	tree->insert(8, 'h');
	tree->insert(9, 'i');
	tree->insert(10, 'j');

	listKey = tree->get_keys();
	listVal = tree->get_values();
	for (int i = 0; i < listKey->get_size(); i++)
		assert(listKey->at(i) == keys[i]);
	std::cout << "test_getKeys - succeed\n";
	for (int i = 0; i < listKey->get_size(); i++)
		assert(listVal->at(i) == vals[i]);
	std::cout << "test_getValues - succeed\n";

	
	delete tree;
	tree = nullptr;
	
}
void test_insert()
{
	StendhalTree<int, char> *tree = new StendhalTree<int, char>();
	List<int> *listKey = nullptr;
	List<char> *listVal = nullptr;
	List<bool> *listColor = nullptr;
	//-----------------------------------
	
	int keys[10] = { 4, 2,  1,  3,  6, 5, 8, 7,9,10};
	//char vals[] = "dbacfehgij";
	int colors[10] = { 1, 1, 1, 1, 1, 1, 0, 1, 1, 0 };
	//--------------------------------
	tree->insert(1, 'a');
	tree->insert(2, 'b');
	tree->insert(3, 'c');
	tree->insert(4, 'd');
	tree->insert(5, 'e');
	tree->insert(6, 'f');
	tree->insert(7, 'g');
	tree->insert(8, 'h');
	tree->insert(9, 'i');
	tree->insert(10, 'j');

	listKey = tree->get_keys();
	
	listColor = tree->get_colors();
	
	
	for (int i = 0; i < 5; i++)
	{
		assert(listKey->at(i) == keys[i]);
	}

	for (int i = 0; i < 5; i++)
	{
		assert(listColor->at(i) == colors[i]);
	}
	
	delete tree;
	tree = nullptr;
	std::cout << "test_insert - succeed\n";
}
void test_remove()
{
	StendhalTree<int, char> *tree = new StendhalTree<int, char>();
	List<int> *listKey = nullptr;
	//List<char> *listVal = nullptr;
	List<bool> *listColor = nullptr;
	int keys[5] = { 6,1,8,7,10 };
	int colors[5] = {1,1,0,1,1};
	tree->insert(1, 'a');
	tree->insert(2, 'b');
	tree->insert(3, 'c');
	tree->insert(4, 'd');
	tree->insert(5, 'e');
	tree->insert(6, 'f');
	tree->insert(7, 'g');
	tree->insert(8, 'h');
	tree->insert(9, 'i');
	tree->insert(10, 'j');
	//no children
	tree->remove(5);

	//right child
	tree->remove(9);

	//both children
	tree->remove(2);

	//left child
	tree->remove(3);

	//root remove
	tree->remove(4);
	//listVal = tree->get_values();
	listKey = tree->get_keys();
	listColor = tree->get_colors();
	
	for (int i = 0; i < 5; i++)
	{
		assert(listKey->at(i) == keys[i]);
	}
	
	for (int i = 0; i < 5; i++)
	{
		assert(listColor->at(i) == colors[i]);
	}
	delete tree;
	tree = nullptr;
	std::cout << "test_remove - succeed\n";
	return;

	//--------------------------------------------------------

}
void test_clear()
{
	StendhalTree<int, char> *tree = new StendhalTree<int, char>();
	List<int> *listKey = nullptr;
	tree->insert(1, 'a');
	tree->insert(2, 'b');
	tree->insert(3, 'c');
	tree->insert(4, 'd');
	tree->insert(5, 'e');
	tree->insert(6, 'f');
	tree->insert(7, 'g');
	tree->insert(8, 'h');
	tree->insert(9, 'i');
	tree->insert(10, 'j');
	tree->clear();
	listKey = tree->get_keys();
	assert(listKey->isEmpty());
	std::cout << "test_clear - succeed\n";
	return;
}

void test_find()
{
	StendhalTree<int, char> *tree = new StendhalTree<int, char>();
	StendhalNode<int, char> *node = nullptr;
	tree->insert(1, 'a');
	tree->insert(2, 'b');
	tree->insert(3, 'c');
	tree->insert(4, 'd');
	tree->insert(5, 'e');
	tree->insert(6, 'f');
	tree->insert(7, 'g');
	tree->insert(8, 'h');
	tree->insert(9, 'i');
	tree->insert(10, 'j');


	node = tree->find(4);
	assert(node->getKey() == 4);
	assert(node->getValue() == 'd');
	assert (node->isBlack());

	node = tree->find(6);
	assert(node->getKey() == 6);
	assert(node->getValue() == 'f');
	assert(node->isBlack());

	node = tree->find(8);
	assert(node->getKey() == 8);
	assert(node->getValue() == 'h');
	assert(!node->isBlack());

	node = tree->find(9);
	assert(node->getKey() == 9);
	assert(node->getValue() == 'i');
	assert(node->isBlack());

	node = tree->find(10);
	assert(node->getKey() == 10);
	assert(node->getValue() == 'j');
	assert(!node->isBlack());

	node = tree->find(7);
	assert(node->getKey() == 7);
	assert(node->getValue() == 'g');
	assert(node->isBlack());

	node = tree->find(5);
	assert(node->getKey() == 5);
	assert(node->getValue() == 'e');
	assert(node->isBlack());

	node = tree->find(2);
	assert(node->getKey() == 2);
	assert(node->getValue() == 'b');
	assert(node->isBlack());

	node = tree->find(3);
	assert(node->getKey() == 3);
	assert(node->getValue() == 'c');

	node = tree->find(1);
	assert(node->getKey() == 1);
	assert(node->getValue() == 'a');
	assert(node->isBlack());

	node = nullptr;

	delete tree;
	tree = nullptr;
	std::cout << "test_find - succeed\n";
	return;
}
void test_all()
{
	test_getKeys_getValues();
	test_insert();
	test_remove();
	test_clear();
	test_find();
	return;
}