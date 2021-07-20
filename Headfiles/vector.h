#pragma once
#include"common.h"
template<class T>
class vector
{
private:
	T* data;
	int rsize;
	int capa;
public:
	vector() {
		data = new T[1024];
		rsize = 0;
		capa = 1024;
	}
	vector(int nsize) {
		data = new T[nsize];
		rsize = 0;
		capa = nsize;
	}
	vector(int nsize, const T& value) {
		data = new T[nsize];
		for (int i = 0; i < nsize; i++) {
			data[i] = value;
		}
		rsize = nsize;
		capa = nsize;
	}
	vector(const vector& copy) {
		data = new T[copy.rsize];
		rsize = copy.rsize;
		for (int i = 0; i < rsize; i++)
		{
			data[i] = copy.data[i];
		}
		capa = copy.capa;
	}
	vector(int begin, int end, const, vector& copy) {
		data = new T[end - begin];
		rsize = end - begin;
		for (int i = 0; i < rsize; i++)
		{
			data[i] = copy.data[begin + i];
		}
		capa = copy.capa;
	}
	~vector()
	{
		delete[]data;
		rsize = 0;
		capa = 0;
	}
	int size() const { return rsize; }
	int capacity() const { return capa; }
	int max_size() const { return INT_MAX; }
	void push_back(T& value) {
		if (rsize >= capa)
		{
			T& ndata = new T[capa * 2];
			for (int i = 0; i < rsize; i++)
			{
				ndata[i] = data[i];
			}
			delete[]data;
			data = ndata;
			capa = capa * 2;
		}
		data[rsize] = value;
		rsize++;
	}
	void pop_back() {
		if (rsize > 0)
			rsize--;
	}
	bool empty() { return rsize == 0; }
	T& front() { return data[0]; }
	T& back() { return data[rsize - 1]; }
	void erase(int index) {
		if (rsize > 0)
		{
			for (int i = index; i < rsize - 1; i++)
			{
				data[i] = data[i + 1];
			}
			rsize--;
		}
	}
	void insert(int index,T& value) {
		if (rsize >= capa)
		{
			T& ndata = new T[capa * 2];
			for (int i = 0; i < rsize; i++)
			{
				ndata[i] = data[i];
			}
			delete[]data;
			data = ndata;
			capa = capa * 2;
		}
		for (int i = index + 1; i < rsize + 1; i++)
		{
			data[i] = data[i - 1];
		}
		data[index] = value;
		rsize++;
	}
	void swap(vector& p){
		T* temp = data;
		int tempsize = rsize;
		int tempc = capa;
		data = p.data;
		rsize = p.rsize;
		capa = p.capa;
		p.data = temp;
		p.rsize = tempsize;
		p.capa = tempc;
	}
	int partition_less(int begin, int end) {
		int target = data[begin];
		int s = begin+1;
		for (int i = begin+1; i < end; i++)
		{
			if (data[i] < target)
			{
				T temp = data[i];
				data[i] = data[s];
				data[s] = temp;
				s++;
			}
		}
		data[begin] = data[s - 1];
		data[s - 1] = target;
		return s;
	}
	int partition_greater(int begin, int end) {
		int target = data[begin];
		int s = begin + 1;
		for (int i = begin + 1; i < end; i++)
		{
			if (data[i] > target)
			{
				T temp = data[i];
				data[i] = data[s];
				data[s] = temp;
				s++;
			}
		}
		data[begin] = data[s - 1];
		data[s - 1] = target;
		return s;
	}
	void sort_less(int begin, int end) {
		if (end - begin > 1) {
			int nmid = partition_less(begin, end);
			sort_less(begin, nmid-1);
			sort_less(nmid, end);
		}
	}
	void sort_greater(int begin, int end) {
		if (end - begin > 1) {
			int nmid = partition_greater(begin, end);
			sort_greater(begin, nmid - 1);
			sort_greater(nmid, end);
		}
	}
	void sort(int begin, int end, string cmp) {
		if (cmp == "less") {
			sort_less(begin, end);
		}
		else if (cmp == "greater") {
			sort_greater(begin, end);
		}
	}
};