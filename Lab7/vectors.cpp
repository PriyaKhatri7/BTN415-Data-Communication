#include <iostream>
#include <string>
#include "vectors.h"

//constructor for an empty Vector
Vector::Vector() {
	this->name = "";
	this->next = nullptr;
	this->size = 0;
	this->elements = nullptr;
}

//constructor for a named Vector
Vector::Vector(std::string name) {
	this->name = name;
	this->next = nullptr;
	std::cout << "Setting vector: " << name << std::endl;
	std::cout << "Enter vector size: ";
	std::cin >> this->size;
	this->elements = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		std::cout << "Enter element " << i << " : ";
		std::cin >> this->elements[i];
	}
}

//destructor for Vector, note that it frees up *elements
Vector::~Vector() {
	std::cout << "Deleted vector: " << this->name << std::endl;
	delete[] this->elements;
}

//constructor for List
List::List() {
	head = nullptr;
	current = nullptr;
}

void List::add_vector(std::string name) {
	//create new vector and trigger the constructor
	Vector* add = new Vector(name);

	if (this->head == nullptr) //if head is emplty then create a structure
	{
		this->head = add;
		this->current = add;
	}
	else
	{
		this->current->next = add; //checks the current object to point to new object
		this->current = add; //also say the current would point
	}
}

//removes an item from the List
bool List::remove_vector(std::string name) {
	Vector* parse, * auxptr;
	bool check = false; //checks if found
	parse = this->head; 

	if (this->head == nullptr) //check for empty and quit after
		return false;

	if (parse->name == name) { //checks for 1 item
		if (this->current == this->head) { //will point to first element
			this->head = nullptr;
			this->current = nullptr;
		}
		else
		{
			this->head = this->head->next;
		}
		delete parse; //since it's a pointer, delete at end
	}

	else {
		while (parse != nullptr) {
			if (parse->next->name != name) { //checks if the object same as before
				parse = parse->next; //checks through the list
			}
			else {
				//if it is the same then delete first and go to next object
				auxptr = parse->next;
				if (parse->next->next == nullptr) {
					this->current == parse; //it will check next next and remove the parse/element from lists
				}
				parse->next = parse->next->next; //it will relate to a nullptr
				delete auxptr;
				check = true;
				break;
			}
		}
	}
	return check;
}

bool List::print_vector(std::string name) {
	bool check = false;
	Vector* parser = this->head;
	while (parser != nullptr) {
		if (parser->name == name) {
			std::cout << "vector " << parser->name << ": [ ";

			for (int i = 0; i < parser->size; i++)
				std::cout << parser->elements[i] << ", ";
			std::cout << "]" << std::endl;
			check = true;
			break;
		}
		else
			parser = parser->next;
	}
	return check;
}

bool List::append_vector(std::string name) {
	bool check = false;
	Vector* parser = this->head; 
	int* auxptr;
	int new_element;
	
	while (parser != nullptr) { 
		if (parser->name != name) { //checks if matches the name
			parser = parser->next; //goes to next element and keeps checking
		}
		else {
			std::cout << "How many elements to add? " << std::endl;
			std::cin >> new_element;
			auxptr = new int[parser->size + new_element]; //holds og size plus new elements 

			for (int i = 0; i < parser->size; i++)
				auxptr[i] = parser->elements[i]; //copies the og elements

			for (int i = 0; i < new_element; i++) {
				std::cout << "adding element: " << parser->size + i << " : ";
				std::cin >> auxptr[parser->size + i];
			}
			delete parser->elements; //delete old ones
			parser->elements = auxptr; //link to aadress of element to the new ones
			parser->size = parser->size + new_element; //set size with new elements
			check = true;
			break;
		}
	}
	return check;
}