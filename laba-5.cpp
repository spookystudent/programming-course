#include <iostream>
#include <vector>

using namespace std;

/*
drafts...
	Set tree;

	tree.append(13);
	tree.append(14);

	struct ElementSet
		ElementSet* up;
		ElementSet* left;
		ElementSet* right;

	Set tree
		ElementSet* top;

		append():
...
*/

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


	// add element to tree as ElementSet
    void add(ElementSet *&element, const T &value, ElementSet *parent = nullptr) {

        if (!element) {
            element = new ElementSet(value);
            element->up = parent;

			if (!this->root) this->root = element;

		// Рекурсивное движение по дереву влево-вправо в зависимости сравнения,
		// по итогу натыкаемся на element, у которого нет left или right
        } else if (value < element->value) {
			
            this->add(element->left, value, element);

        } else if (value > element->value) {

            this->add(element->right, value, element);

        }
    }
	void clear(ElementSet *element) {
        if (element) {
            clear(element->left);
            clear(element->right);
            delete element;
        }
    }

	public:
		Set() {
			cout << "Constructor\n";
		};
		Set(const Set &other) {
			cout << "Constructor other\n";
		};
		~Set() {
			cout << "Clear\n";
			clear(this->root);
		}


		Set &operator += (const T &value)
		{
			//    add(ElementSet, T    )
			this->add(this->root, value);

			return *this;
		};

		// Удаление элемента из множества
		// Set operator - (const T &t) const;
		Set &operator-=(const T &t)
		{

			return *this;
		};

		void printTreeRecursive(ElementSet* element, int depth = 0) const {
			if (!element) {
				for (int i = 0; i < depth; ++i) cout << "\t";
				cout << "None" << endl;
				return;
			}

			printTreeRecursive(element->right, depth + 1);
			
			for (int i = 0; i < depth; ++i) cout << "\t";
			cout << element->value << " <" << endl;

			printTreeRecursive(element->left, depth + 1);
		}

		void printTree() const {
			printTreeRecursive(this->root);
		}
};
int main(void)
{
    Set<int> a;
    
	a += 13;
	a += 8;
	a += 5;
	a += 2;
	a += 4;
	a += 1;
	a += 0;

	a += 34;
	a += 23;
	a += 35;

	a.printTree();
        

    // for (int i=0; i<=50; i+=2) a-=i;
    // for (int i=0; i<=50; i+=3) a-=i;
    // cout << a << endl;
    // for (int i=0; i<=50; i+=2) a-=i;
    // for (int i=0; i<=50; i+=3) a-=i;

    //   cout << a << endl;
    //   Set<int> b = ((a + 999)+9999) - 89;
    //   cout << b.size() << endl;
    //   cout << b.exists(1) << b.exists(2)
    //     << b.exists(3) << b.exists(4)
    //     << b.exists(5) << endl;
    //   Set<int> *c = new Set<int>;
    //   *c +=1; *c +=5; *c +=6;
    //   cout << c->size() << endl;
    //   cout << a-*c << endl;
    //   *c += 1111;
    //   cout << a+*c << endl;
    //   delete c;
    return 0;
};