#include <iostream>
#include <vector>

using namespace std;


template <class T>
class Set {
    /*
        Класс коллекция представляет собой двоичное дерево состоящее
        из struct ElementSet, которые ссылаются между собой тремя ссылками

        ------------------(root)---------------------
        ----------------ElementSet------------------
        ----------------/-------\-------------------
        ------------(left)-----(right)--------------
        ---------ElementSet---ElementSet------------

        Описание ElementSet

        struct ElementSet
            up -> link to upper ElementSet
            left -> link to less left ElementSet
            right -> link to bigger right ElementSet
            value -> value of ElementSet
    */

	// Private var-s

	struct ElementSet {
        T value;
        ElementSet *up = nullptr;
        ElementSet *left = nullptr;
        ElementSet *right = nullptr;

        ElementSet(const T &val) : value(val) {}
    };

    ElementSet *root = nullptr;
	ElementSet *elementMin = nullptr;
	ElementSet *elementMax = nullptr;
	ElementSet *elementMiddle = nullptr;

	// int diff_points = -1;
    int length = 0;


	// add element to tree as ElementSet
    void add(ElementSet *&element, const T &value, ElementSet *element_up = nullptr) {
		if (!this->root) { // Если дерево пустое, создаём корень
			this->root = new ElementSet(value);
			this->length++;
			return;
		}

		if (this->exists(value)) return; // Проверяем на наличие значения

		if (!element) { // Если дошли до пустого места, добавляем элемент
			element = new ElementSet(value);
			element->up = element_up;
			this->length++;
			return;
		}

		// Рекурсивный вызов
		if (value < element->value) {
			add(element->left, value, element);
		} else {
			add(element->right, value, element);
		}
	}

    void _remove(ElementSet *element, const T &value) {
		if (element == nullptr || !this->exists(value)) return;

		if (value < element->value) {
			this->_remove(element->left, value);
		} else if (element->value < value) {
			this->_remove(element->right, value);
		} else if (value == element->value) { 
			if (element == this->root) {
				if (element->right) {
					this->move_left(element->left, element->right);
					element->right->up = nullptr;
					this->root = element->right;
				} else if (element->left) {
					this->root = element->left;
					this->root->up = nullptr;
				} else {
					this->root = nullptr;
				}
				
				delete element;
				

				this->length--;
				return;
			}

			// Удаляем элемент, не являющийся корневым
			if (element->right) {
				this->move_left(element->left, element->right);
				element->right->up = element->up;
			} else if (element->left) {
				element->left->up = element->up;
			}

			if (value < element->up->value) {
				element->up->left = (element->right) ? element->right : element->left;
			} else {
				element->up->right = (element->right) ? element->right : element->left;
			}

			delete element;
			
			this->length--;
		}
	}
    

    void move_left(ElementSet *element_from, ElementSet* element_to) {
		if (!element_from) return;

		ElementSet *current = element_to;

		while (current->left != nullptr) {
			current = current->left;
		}
		current->left = element_from;
		element_from->up = current;
	}
    

	void clear(ElementSet *element) {
        if (element != nullptr) {
			if (element->left != nullptr) clear(element->left);
			if (element->right != nullptr) clear(element->right);

			delete element;
			
		}
    }


	void printElements(ostream& os, ElementSet* element) const {
		if (element == nullptr) return;

		printElements(os, element->left);

		os << element->value << " ";

		printElements(os, element->right);
	}


    void createTreeRecursive(ElementSet* element, int depth = 0) const {
        if (!element) {
            for (int i = 0; i < depth; ++i) cout << "\t";
            cout << "None" << endl;
            return;
        }

        createTreeRecursive(element->right, depth + 1);
        
        for (int i = 0; i < depth; ++i) cout << "\t";
        cout << element->value << " <" << endl;

        createTreeRecursive(element->left, depth + 1);
    }

    bool existsRecursive(ElementSet* element, const T& value) const {
		if (element == nullptr) {
			return false;
		}
		if (element->value == value) {
			return true;
		}

		if (value < element->value) {
			return existsRecursive(element->left, value);
		}
		return existsRecursive(element->right, value);
	}

    void copy(ElementSet* element) {
		if (element == nullptr) return;

		this->add(this->root, element->value);
		copy(element->left);
		copy(element->right);
	}



	public:
		Set() : root(nullptr), elementMin(nullptr), elementMax(nullptr), elementMiddle(nullptr), length(0) {}

		Set(const Set &other_set) {
            this->copy(other_set.root);
 	    };
		~Set() {
            // cout << "Delete " << this << endl;
			// clear(this->root);
		}


        Set operator + (const T &value) {
            Set<T> other_set = *this;

            other_set.add(other_set.root, value);

			return other_set;
        };
        friend Set operator + (const T &value, const Set &set) {
            Set other_set = set;
            other_set.add(other_set.root, value);
            return other_set;
        }
		Set &operator += (const T &value) {
			this->add(this->root, value);

			return *this;
		};

		// Удаление элемента из множества
		Set operator - (const T &t) const {
            Set other_set = *this;

            other_set._remove(other_set.root, t);

            return other_set;
        };

		Set &operator -= (const T &t) {
            this->_remove(this->root, t);
            
			return *this;
		};


        void diffSetRecursive(ElementSet* element, const Set &set) {
            if (element == nullptr) return;

            diffSetRecursive(element->left, set);
            diffSetRecursive(element->right, set);

            if (set.exists(element->value)) {
                this->_remove(element, element->value);
            }
        }
        Set operator - (const Set &set) {
            Set copy_set = *this;

            diffSetRecursive(copy_set.root, set);

            return copy_set;
        };
        Set& operator -= (const Set &set) {
            diffSetRecursive(this->root, set);

            return *this;
        };



        void addSetRecursive(ElementSet* element, Set &set) {
            if (element == nullptr) return;

            addSetRecursive(element->left, set);
            addSetRecursive(element->right, set);

            this->add(this->root, element->value);
        }
        Set operator + (Set &set) {
            Set copy_set = *this;

            copy_set.addSetRecursive(set.root, set);

            return copy_set;
        };
        Set& operator += (const Set &set) {
            addSetRecursive(set.root, set);

            return *this;
        }

		
		void createTree() const {
			createTreeRecursive(this->root);
		}


		friend ostream& operator << (ostream& os, const Set& set) {
			set.printElements(os, set.root);
			return os;
		}

        int size(void) const {
            return this->length;
        }

        bool exists(const T &t) const {
            return this->existsRecursive(this->root, t);
        };
};
int main(void)
{
    Set<int> set;

    // 1. Тест: Добавление элементов через оператор "+"
    set = set + 10;
    set = set + 5;
    set = set + 15;
    set = set + 5; // Повторное добавление (не должно изменить множество)
    std::cout << set << std::endl; // Ожидаемый вывод: {5, 10, 15}

    // 2. Тест: Удаление элемента через оператор "-"
    set = set - 5;
    std::cout << set << std::endl; // Ожидаемый вывод: {10, 15}

    // 3. Тест: Попытка удалить несуществующий элемент
    set = set - 100;
    std::cout << set << std::endl; // Ожидаемый вывод: {10, 15}

    // 4. Тест: Проверка существования элементов
    // std::cout << (set ? 10 : -1) << std::endl; // Ожидаемый вывод: 10
    // std::cout << (set ? 5 : -1) << std::endl;  // Ожидаемый вывод: -1

    // 5. Тест: Операция объединения через оператор "+"
    Set<int> set2;
    set2 = set2 + 20 + 30;
    Set<int> unionSet = set + set2;
    std::cout << unionSet << std::endl; // Ожидаемый вывод: {10, 15, 20, 30}

    // 6. Тест: Пересечение множеств через оператор "*"
    Set<int> set3;
    set3 = set3 + 10 + 20;
    // Set<int> intersectionSet = set * set3;
    std::cout << set3 << std::endl; // Ожидаемый вывод: {10, 20}

    // 7. Тест: Разность множеств через оператор "-"
    // Set<int> differenceSet = set - set3;
    // std::cout << differenceSet << std::endl; // Ожидаемый вывод: {15}

    // 8. Тест: Печать пустого множества
    Set<int> emptySet;
    std::cout << emptySet << std::endl; // Ожидаемый вывод: {}

    // 9. Тест: Сложное дерево (добавление большого количества элементов)
    for (int i = 1; i <= 10; ++i) {
        set = set + (i * 10);
    }
    std::cout << set << std::endl; // Ожидаемый вывод: {10, 15, 10, 20, ..., 100}

    // 10. Тест: Удаление корневого элемента
    set = set - 10;
    std::cout << set << std::endl; // Ожидаемый вывод: {15, 20, ..., 100}
    return 0;
};
