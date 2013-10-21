#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>

#include "SkipList.h"
#include "Comparator.h" 

using namespace std;

const float P = 0.5;

float frand() {
	return (float) rand() / RAND_MAX;
}

int random_level() {
	static bool first = true;

	if (first) {
		srand((unsigned) time(NULL));
		first = false;
	}

	int lvl = (int) (log(frand())) / log(1.-P);

	return lvl < MAX_LEVEL ? lvl : MAX_LEVEL;
}

template <class T>
void SkipSet<T>::print() const {
	const SkipNode<T> *x = header->forward[0];
	cout << "{";

	while (x != NULL) {
		cout << x->value;
		x = x->forward[0];
		if (x != NULL)
			cout << ",";
	}

	cout << "}" << endl;
}

template <class T>
bool SkipSet<T>::contains(const T& search_val) const {
	const SkipNode<T> *x = header;
	for (int i = level; i >= 0; --i) {
		while (x->forward[i] != NULL && x->forward[i]->value < search_val) {
			x = x->forward[i];
		}
	}

	x = x->forward[0];
	return x != NULL && x->value == search_val;
}

template<class T>
T SkipSet<T>::advance(const T& target) const {
    Comparator<T> compareTo;

	const SkipNode<T> *x = header;
	for (int i = level; i >= 0; --i) {
		while (x->forward[i] != NULL && !compareTo(x->forward[i]->value, target)/*x->forward[i]->value < target*/) {
			x = x->forward[i];
		}
	}

	x = x->forward[0];
	return x;
}

template <class T>
void SkipSet<T>::insert(const T &value) {
	SkipNode<T> *x = header;
	SkipNode<T> *update[MAX_LEVEL + 1];
	memset(update, 0, sizeof(SkipNode<T>*) * (MAX_LEVEL + 1));

	for (int i = level; i >= 0; --i) {
		while (x->forward[i] != NULL && x->forward[i]->value < value) {
			x = x->forward[i];
		}

		update[i] = x;
	}

	x = x->forward[0];

	if (x == NULL || x->value != value) {
		int lvl = random_level();
		if (lvl > level) {
			for (int i = level + 1; i <= lvl; ++i) {
				update[i] = header;
			}
		}
		level = lvl;

		x = new SkipNode<T>(lvl, value);
		for (int i = 0; i <= lvl; ++i) {
			x->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = x;
		}
	}
}

template <class T>
void SkipSet<T>::erase(const T &value) {
	SkipNode<T> *x = header;
	SkipNode<T> *update[MAX_LEVEL + 1];
	memset(update, 0, sizeof(SkipNode<T>*) * (MAX_LEVEL + 1));

	for (int i = level; i >= 0; --i) {
		while(x->forward[i] != NULL && x->forward[i]->value < value) {
			x = x->forward[i];
		}

		update[i] = x;
	}

	x = x->forward[0];

	if (x->value == value ) {
		for (int i = 0; i <= level; i++) {
			if (update[i]->forward[i] != x) break;
			update[i]->forward[i] = x->forward[i];
		}

		delete x;

		while(level > 0 && header->forward[level] == NULL)
			level --;
	}
}

int main() {
	SkipSet<int> ss;
	ss.print();

	ss.insert(7);
	ss.insert(14);
	ss.insert(21);
	ss.insert(32);
	ss.insert(37);
	ss.insert(71);
	ss.insert(85);
	ss.insert(117);

	if (ss.contains(7)) {
		cout << "7 in list" << endl;
	}

	ss.print();

	ss.erase(7);
	ss.print();

	if (!ss.contains(7))
		cout << "7 has been deleted" << endl;

	return 0;
}
