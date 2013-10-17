#ifndef __SKIPLIST_H__
#define __SKIPLIST_H__

#define MAX_LEVEL 100 

template <class T>
class SkipNode {
public:
	//T value;
	//SkipNode<T> **forward; //array of poniter

	SkipNode(int level, const T &value) {
		forward = new SkipNode<T> * [level + 1];
		memset(forward, 0, sizeof(SkipNode<T>*) * (level + 1));
		this->value = value;
	}

	~SkipNode() {
		delete[] forward;
	}

public:
    T value;
    SkipNode<T> **forward;
};

template <class T>
class SkipSet {
public:
	//SkipNode<T> *header;
	//int level;

	SkipSet() {
		header = new SkipNode<T>(MAX_LEVEL, T());
		level = 0;
	}

	~SkipSet() {
		delete header;
	}

	void print() const;
	bool contains(const T &) const;
	void insert(const T &);
	void erase(const T &);
    T advance(const T &) const;

private:
    SkipNode<T> *header;
    int level;
};

#endif // __SKIPLIST_H__
