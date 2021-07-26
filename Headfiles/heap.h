#pragma once
#include"common.h"
#include"vector.h"
template<class T>
class Tree {
public:
	T value;
	int index;
	Tree* left;
	Tree* right;
	Tree* father;
	Tree() {
		left = NULL;
		right = NULL;
		father = NULL;
		value = T();
		index = -1;
	}
	Tree(const T& lvalue, int lindex) {
		left = NULL;
		right = NULL;
		father = NULL;
		value = lvalue;
		index = lindex;
	}
	void addleft(Tree* tree) {
		left = tree;
		tree->father = this;
	}
	void addright(Tree* tree) {
		right = tree;
		tree->father = this;
	}
	void add(Tree* tree) {
		if (left != NULL) {
			addright(tree);
		}
		else {
			addleft(tree);
		}
	}
};

template<class T, typename pr = less<T>>
class heap {
private:
	vector<Tree<T>*> values;
public:
	heap() {}
	heap(const heap& father) {
		if (father.values.size() > values.size()) {
			for (int i = 0; i < values.size(); i++) {
				values[i]->value = father.values[i]->value;
			}
			for (int i = values.size(); i < father.values.size(); i++) {
				this->push(father.values[i]->value);
			}
		}
		else {
			for (int i = 0; i < father.values.size(); i++) {
				values[i]->value = father.values[i]->value;
			}
			int n = values.size();
			for (int i = father.values.size(); i < n; i++) {
				values.pop_back();
			}
		}
	}
	~heap() {}
	int size() { return values.size(); }
	void push(const T& value);
	void pop();
	T& top();
	T& back();
	void clear() { values.clear(); }
};

template<class T>
class heap <T, greater<T>> {
private:
	vector<Tree<T>*> values;
public:
	heap() {}
	heap(const heap& father) {
		if (father.values.size() > values.size()) {
			for (int i = 0; i < values.size(); i++) {
				values[i]->value = father.values[i]->value;
			}
			for (int i = values.size(); i < father.values.size(); i++) {
				this->push(father.values[i]->value);
			}
		}
		else {
			for (int i = 0; i < father.values.size(); i++) {
				values[i]->value = father.values[i]->value;
			}
			int n = values.size();
			for (int i = father.values.size(); i < n; i++) {
				values.pop_back();
			}
		}
	}
	~heap() {}
	int size() { return values.size(); }
	void push(const T& value);
	void pop();
	T& top();
	T& back();
	void clear() { values.clear(); }
};

/*heap<T,pr>*/
template<class T, typename pr>
void heap<T, pr>::push(const T& value) {
	Tree<T>* newtree = new Tree<T>(value, values.size());
	values.push_back(newtree);
	if (size() > 1) {
		values[size() / 2 - 1]->add(values[size() - 1]);
	}
	while (newtree->father != NULL && newtree->value < newtree->father->value) {
		swap(newtree->value, newtree->father->value);
		newtree = newtree->father;
	}
}

template<class T, typename pr>
void heap<T, pr>::pop() {
	if (size() > 0) {
		values[0]->value = values[size() - 1]->value;
		values.erase(values.end() - 1);
		int cur = 0;
		while (!((values[cur]->left == NULL || values[cur]->left->value >= values[cur]->value)
			&& (values[cur]->right == NULL || values[cur]->right->value >= values[cur]->value)))
		{
			if (values[cur]->right != NULL) {
				if (values[cur]->right->value >= values[cur]->left->value) {
					swap(values[cur]->value, values[cur]->left->value);
					cur = values[cur]->left->index;
				}
				else {
					swap(values[cur]->value, values[cur]->right->value);
					cur = values[cur]->right->index;
				}
			}
			else {
				swap(values[cur]->value, values[cur]->left->value);
				cur = values[cur]->left->index;
			}
		}
	}
}

template<class T, typename pr>
T& heap<T, pr>::top() {
	if (size() > 0) {
		return values[0]->value;
	}
}

template<class T, typename pr>
T& heap<T, pr>::back() {
	if (size() > 0) {
		return values[size() - 1]->value;
	}
}

/*heap<T,greater<T>>*/
template<class T>
void heap<T, greater<T>>::push(const T& value) {
	Tree<T>* newtree = new Tree<T>(value, values.size());
	values.push_back(newtree);
	if (size() > 1) {
		values[size() / 2 - 1]->add(values[size() - 1]);
	}
	while (newtree->father != NULL && newtree->value > newtree->father->value) {
		swap(newtree->value, newtree->father->value);
		newtree = newtree->father;
	}
}

template<class T>
void heap<T, greater<T>>::pop() {
	if (size() > 0) {
		values[0]->value = values[size() - 1]->value;
		delete values[values.size() - 1];
		values[values.size() - 1] = NULL;
		values.erase(values.end() - 1);
		int cur = 0;
		while (!((values[cur]->left == NULL || values[cur]->left->value <= values[cur]->value)
			&& (values[cur]->right == NULL || values[cur]->right->value <= values[cur]->value)))
		{
			if (values[cur]->right != NULL) {
				if (values[cur]->right->value <= values[cur]->left->value) {
					swap(values[cur]->value, values[cur]->left->value);
					cur = values[cur]->left->index;
				}
				else {
					swap(values[cur]->value, values[cur]->right->value);
					cur = values[cur]->right->index;
				}
			}
			else {
				swap(values[cur]->value, values[cur]->left->value);
				cur = values[cur]->left->index;
			}
		}
	}
}

template<class T>
T& heap<T, greater<T>>::top() {
	if (size() > 0) {
		return values[0]->value;
	}
}

template<class T>
T& heap<T, greater<T>>::back() {
	if (size() > 0) {
		return values[size() - 1]->value;
	}
}



