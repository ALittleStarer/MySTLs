#pragma once
#include"common.h"
#include"draw.h"
enum color
{
	RED = 4, BLACK=7
};
template<class T>
class RBtreenode {
public:
	int x;
	int y;
	int width;
	color nodecolor;
	T value;
	RBtreenode* left;
	RBtreenode* right;
	RBtreenode* father;
	RBtreenode* find_next();
	RBtreenode* find_parent();
	RBtreenode();
	RBtreenode(const T& value);
	RBtreenode(const RBtreenode& val);
};

template<class T>
RBtreenode<T>::RBtreenode() {
	nodecolor = RED;
	value = T();
	left = NULL;
	right = NULL;
	x = 0;
	y = 0;
}

template<class T>
RBtreenode<T>::RBtreenode(const T& val) {
	nodecolor = RED;
	value = val;
	left = NULL;
	right = NULL;
	x = 0;
	y = 0;
}
template<class T>
RBtreenode<T>::RBtreenode(const RBtreenode<T>& val) {
	nodecolor = val.nodecolor;
	value = val.value;
	left =val.left;
	right = val.right;
	x = 0;
	y = 0;
}
template<class T>
RBtreenode<T>* RBtreenode<T>::find_next() {
	RBtreenode<T>* cur = this;
	if (cur) {
		if (cur->right) {
			cur = cur->right;
			while (cur->left) {
				cur = cur->left;
			}
			return cur;
		}
		else {
			if (cur->father) {
				if (cur->father->left == cur) {
					return cur->father;
				}
				else {
					return NULL;
				}
			}
			return NULL;
		}
	}
	return NULL;
}

template<class T>
RBtreenode<T>* RBtreenode<T>::find_parent() {
	RBtreenode<T>* cur = this;
	if (cur) {
		if (cur->left) {
			cur = cur->left;
			while (cur->right) {
				cur = cur->right;
			}
			return cur;
		}
		else {
			if (cur->father) {
				if (cur->father->right == cur) {
					return cur->father;
				}
				else {
					return NULL;
				}
			}
			return NULL;
		}
	}
	return NULL;
}
template<class T>
class RBtree {
private:
	int nsize;
	int minX=0;
	void recover(RBtreenode<T>* cur);
	void TurnLeft(RBtreenode<T>* cur);
	void TurnRight(RBtreenode<T>* cur);
	void shownode(RBtreenode<T>* node);
	void setxy(RBtreenode<T>* root);
	void setwidth(RBtreenode<T>* root);
public:
	RBtreenode<T>* root;
	RBtree();
	RBtree(const RBtree& tree);
	int size() const { return nsize; }
	RBtreenode<T>* insert(const T& value);
	void erase(RBtreenode<T>* cur);
	void erase(const T& value);
	void clear(RBtreenode<T>* cur);
	RBtreenode<T>* begin();
	RBtreenode<T>* end();
	RBtreenode<T>* find(const T& value);
	RBtreenode<T>* find_next(const T& value);//中序遍历后继
	RBtreenode<T>* find_parent(const T& value);//中序遍历前继
	void show();
};

template<class T>
RBtreenode<T>* RBtree<T>::end() {
	RBtreenode<T>* cur = root;
	RBtreenode<T>* real = cur;
	while (cur) {
		real = cur;
		cur = cur->find_next();
	}
	return real;
}
template<class T>
RBtreenode<T>* RBtree<T>::begin() {
	RBtreenode<T>* cur = root;
	RBtreenode<T>* real = cur;
	while (cur) {
		real = cur;
		cur = cur->find_parent();
	}
	return real;
}
template<class T>
RBtree<T>::RBtree() {
	root = NULL;
	nsize = 0;
}

template<class T>
RBtreenode<T>* RBtree<T>::insert(const T& value) {
	if (nsize == 0) {
		root = new RBtreenode<T>(value);
		root->nodecolor = BLACK;
		nsize++;
		return root;
	}
	else {
		RBtreenode<T>* newnode = new RBtreenode<T>(value);
		RBtreenode<T>* cur = root;
		RBtreenode<T>* father = root;
		while (cur!=NULL) {
			father = cur;
			if (cur->value >= value) {
				cur = cur->left;
				if (cur == NULL) {
					newnode->father = father;
					father->left = newnode;
				}
			}
			else {
				cur = cur->right;
				if (cur == NULL) {
					newnode->father = father;
					father->right = newnode;
				}
			}
		}
		cur = newnode;
		recover(cur);
		nsize++;
		return newnode;
	}
}

template<class T>
void RBtree<T>::clear(RBtreenode<T>* cur) {
	if (cur->left || cur->right) {
		if (cur->left) {
			clear(cur->left);
		}
		if (cur->right) {
			clear(cur->right);
		}
	}
	delete cur;
	cur = NULL;
	nsize--;
}
template<class T>
void RBtree<T>::erase(RBtreenode<T>* cur) {
	if (nsize <= 1) {
		nsize=0;
	}
	else {
		if (!cur->left && !cur->right) {
			nsize--;
			if (cur->father->left == cur) {
				if (cur->father->right) {
					cur->father->left = NULL;
					delete cur;
				}
				else {
					if (cur->nodecolor == RED) {
						cur->father->left = NULL;
						delete cur;
					}
					else {
						cur->father->left = NULL;
						RBtreenode<T>* p = cur->father;
						RBtreenode<T>* now = cur;
						while (p && !(p->left && p->right)) {
							now = p;
							p = p->father;
						}
						if (p) {
							if (p->left == now) {
								TurnLeft(p->right);
								p->right->nodecolor = RED;
							}
							else {
								TurnRight(p->left);
								p->left->nodecolor = RED;
							}
						}
						while (root->father) {
							root = root->father;
						}
						root->nodecolor = BLACK;
						delete cur;
					}
				}
			}
			else {
				if (cur->father->left) {
					cur->father->right = NULL;
					delete cur;
				}
				else {
					if (cur->nodecolor == RED) {
						cur->father->right = NULL;
						delete cur;
					}
					else {
						cur->father->right = NULL;
						RBtreenode<T>* p = cur->father;
						RBtreenode<T>* now = cur;
						while (p && !(p->left && p->right)) {
							now = p;
							p = p->father;
						}
						if (p) {
							if (p->left == now) {
								TurnLeft(p->right);
								p->right->nodecolor = RED;
							}
							else {
								TurnRight(p->left);
								p->left->nodecolor = RED;
							}
						}
						while (root->father) {
							root = root->father;
						}
						root->nodecolor = BLACK;
						delete cur;
					}
				}
			}
		}
		else if (!cur->left || !cur->right) {
			nsize--;
			if (!cur->left) {
				if (cur->nodecolor == RED)
				{
					if (cur->father) {
						cur->right->father = cur->father;
						if (cur->father->left == cur) {
							cur->father->left = cur->right;
						}
						else {
							cur->father->right = cur->right;
						}
					}
					else {
						root = cur->right;
						root->father = NULL;
					}
					delete cur;
				}
				else {
					if (cur->right->nodecolor == RED) {
						if (cur->father) {
							cur->right->father = cur->father;
							if (cur->father->left == cur) {
								cur->father->left = cur->right;
							}
							else {
								cur->father->right = cur->right;
							}
						}
						else {
							root = cur->right;
							root->father = NULL;
						}
						auto p = cur;
						cur = cur->right;
						cur->nodecolor = BLACK;
						delete p;
					}
					else {
						if (cur->father) {
							cur->right->father = cur->father;
							if (cur->father->left == cur) {
								cur->father->left = cur->right;
							}
							else {
								cur->father->right = cur->right;
							}
						}
						else {
							root = cur->right;
							root->father = NULL;
						}
						auto pr = cur;
						cur = cur->right;
						delete pr;
						RBtreenode<T>* p = cur->father;
						RBtreenode<T>* now = cur;
						while (p && !(p->left && p->right)) {
							now = p;
							p = p->father;
						}
						if (p) {
							if (p->left == now) {
								TurnLeft(p->right);
								p->right->nodecolor = RED;
							}
							else {
								TurnRight(p->left);
								p->left->nodecolor = RED;
							}
						}
						while (root->father) {
							root = root->father;
						}
						root->nodecolor = BLACK;
					}
				}
			}
			else {
				if (cur->nodecolor == RED)
				{
					if (cur->father) {
						cur->left->father = cur->father;
						if (cur->father->left == cur) {
							cur->father->left = cur->left;
						}
						else {
							cur->father->right = cur->left;
						}
					}
					else {
						root = cur->left;
						root->father = NULL;
					}
					delete cur;
				}
				else{
					if (cur->left->nodecolor == RED) {
						if (cur->father) {
							cur->left->father = cur->father;
							if (cur->father->left == cur) {
								cur->father->left = cur->left;
							}
							else {
								cur->father->right = cur->left;
							}
						}
						else {
							root = cur->left;
							root->father = NULL;
						}
						auto p = cur;
						cur = cur->left;
						cur->nodecolor = BLACK;
						delete p;
					}
					else {
						if (cur->father) {
							cur->left->father = cur->father;
							if (cur->father->left == cur) {
								cur->father->left = cur->left;
							}
							else {
								cur->father->right = cur->left;
							}
						}
						else {
							root = cur->left;
							root->father = NULL;
						}
						auto pr = cur;
						cur = cur->left;
						delete pr;
						RBtreenode<T>* p = cur->father;
						RBtreenode<T>* now = cur;
						while (p && !(p->left && p->right)) {
							now = p;
							p = p->father;
						}
						if (p) {
							if (p->left == now) {
								TurnLeft(p->right);
								p->right->nodecolor = RED;
							}
							else {
								TurnRight(p->left);
								p->left->nodecolor = RED;
							}
						}
						while (root->father) {
							root = root->father;
						}
						root->nodecolor = BLACK;
					}
				}
			}
		}
		else {
			RBtreenode<T>* now = cur->left;
			while (now->right) {
				now = now->right;
			}
			cur->value = now->value;
			erase(now);
		}
	}
}

template<class T>
void RBtree<T>::erase(const T& value) {
	RBtreenode<T>* cur = find(value);
	while (cur != NULL) {
		erase(cur);
		cur = find(value);
	}
}

template<class T>
void RBtree<T>::TurnLeft(RBtreenode<T>* cur) {
	RBtreenode<T>* father = cur->father;
	cur->father = father->father;
	if (cur->father) {
		if (cur->father->left == father) {
			cur->father->left = cur;
		}
		else {
			cur->father->right = cur;
		}
	}
	father->right = cur->left;
	if(cur->left)
		cur->left->father = father;
	cur->left = father;
	father->father = cur;
}

template<class T>
void RBtree<T>::TurnRight(RBtreenode<T>* cur) {
	RBtreenode<T>* father = cur->father;
	cur->father = father->father;
	if (cur->father) {
		if (cur->father->right == father) {
			cur->father->right = cur;
		}
		else {
			cur->father->left = cur;
		}
	}
	father->left = cur->right;
	if (cur->right)
		cur->right->father = father;
	cur->right = father;
	father->father = cur;
}
template<class T>
void RBtree<T>::recover(RBtreenode<T>* cur) {
	RBtreenode<T>* father = cur->father;
	while (father&& father->nodecolor == RED) {
		RBtreenode<T>* gfather = father->father;
		if (father == gfather->left) {
			RBtreenode<T>* uncle = gfather->right;
			if (uncle&& uncle->nodecolor == RED) {
				father->nodecolor = uncle->nodecolor = BLACK;
				gfather->nodecolor = RED;

				cur = gfather;
				father = cur->father;
			}
			else {
				if (cur == father->right) {
					TurnLeft(cur);
					swap(cur, father);
				}
				TurnRight(father);
				father->nodecolor = BLACK;
				gfather->nodecolor = RED;
			}
		}
		else {
			RBtreenode<T>* uncle = gfather->left;
			if (uncle&& uncle->nodecolor == RED) {
				father->nodecolor = uncle->nodecolor = BLACK;
				gfather->nodecolor = RED;

				cur = gfather;
				father = cur->father;
			}
			else {
				if (cur == father->left) {
					TurnRight(cur);
					swap(cur, father);
				}
				TurnLeft(father);
				father->nodecolor = BLACK;
				gfather->nodecolor = RED;
			}
		}
	}
	while (root->father) {
		root = root->father;
	}
	root->nodecolor = BLACK;

}

template<class T>
RBtreenode<T>* RBtree<T>::find(const T& value) {
	RBtreenode<T>* cur = root;
	while (cur!=NULL&&cur->value != value) {
		if (value <=cur->value) {
			cur = cur->left;
		}
		else{
			cur = cur->right;
		}
	}
	return cur;
}

template<class T>
RBtreenode<T>* RBtree<T>::find_next(const T& value) {
	RBtreenode<T>* cur = find(value);
	if (cur->right) {
		cur = cur->right;
		while (cur->left) {
			cur = cur->left;
		}
		return cur;
	}
	else {
		if (cur->father) {
			if (cur->father->left == cur) {
				return cur->father;
			}
			else {
				return NULL;
			}
		}
		return NULL;
	}
}

template<class T>
RBtreenode<T>* RBtree<T>::find_parent(const T& value) {
	RBtreenode<T>* cur = find(value);
	if (cur->left) {
		cur = cur->left;
		while (cur->right) {
			cur = cur->right;
		}
		return cur;
	}
	else {
		if (cur->father) {
			if (cur->father->right == cur) {
				return cur->father;
			}
			else {
				return NULL;
			}
		}
		return NULL;
	}
}
template<class T>
void RBtree<T>::setxy(RBtreenode<T>* root) {
	if (root->left) {
		root->left->x = root->x - root->left->width;
		minX = min(minX, root->left->x);
		root->left->y = root->y + 4;
		setxy(root->left);
	}
	if (root->right) {
		root->right->x = root->x + root->right->width;
		root->right->y = root->y + 4;
		setxy(root->right);
	}

}
template<class T>
void RBtree<T>::show() {
	setwidth(root);
	setxy(root); 
	shownode(root);
}

template<class T>
void RBtree<T>::shownode(RBtreenode<T>* node) {
	SetColor(7);
	if (node->father) {
		SetCursorPosition(node->x - minX, node->y - 1);
		cout << "|";
	}
	if (node->left || node->right) {
		SetCursorPosition(node->x - minX, node->y + 1);
		cout << "|";
	}
	SetColor(node->nodecolor);
	SetCursorPosition(node->x-minX, node->y);
	cout << node->value;
	if (node->left) {
		SetColor(7);
		SetCursorPosition(node->left->x - minX, node->y + 2);
		for (int i = node->left->x - minX; i <node->x - minX; i++) {
			cout << "--";
		}
		shownode(node->left);
	}
	if (node->right) {
		SetColor(7);
		SetCursorPosition(node->x - minX, node->y + 2);
		for (int i = node->x - minX; i <node->right->x - minX; i++) {
			cout << "--";
		}
		cout << "-";
		shownode(node->right);
	}
}

template<class T>
void RBtree<T>::setwidth(RBtreenode<T>* root) {
	if (root->left == NULL && root->right == NULL) {
		root->width= 1;
	}
	else {
		if (root->left) {
			setwidth(root->left);
			root->width += root->left->width;
		}
		if (root->right) {
			setwidth(root->right);
			root->width += root->right->width;
		}
	}
}