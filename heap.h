#ifndef HEAP
#define HEAP

#include<vector>
using namespace std;
template <typename Key> class heap {
public:
	heap(bool min = false) :pq(2), reverse(min),N(0) {};
	heap(Key *keys, int size, bool min):pq(2 * size),reverse(min),N(size) {
		pq.assign(keys, keys + size);
		pq[size] = pq[0];
		for (int i = size / 2; i > 0; --i)
			sink(i);
	};

	void insert(Key key);
	Key top();
	Key pop();
	bool empty();
	int size();
private:
	vector<Key> pq;
	bool reverse;
	int N;
	bool compare(int i, int j);
	void exch(int i, int j);
	void swim(int i);
	void sink(int i);
};

template<typename Key>
void heap<Key>::insert(Key key) {
	if (N + 1 == pq.size())
		pq.resize(2 * pq.size());
	pq[++N] = key;
	swim(N);
}

template<typename Key>
Key heap<Key>::top() {
	return pq[1];
}

template<typename Key>
Key heap<Key>::pop()
{
	Key k = pq[1];
	exch(1, N--);
	sink(1);
	if (N > 0 && N == pq.size() / 4)
		pq.resize(pq.size() / 2);
	return k;
}

template<typename Key>
bool heap<Key>::empty() {
	return N < 1;
}

template<typename Key>
int heap<Key>::size() {
	return N;
}

template<typename Key>
bool heap<Key>::compare(int i, int j) {
	return (pq[i] < pq[j]) ^ reverse;
}

template<typename Key>
void heap<Key>::exch(int i, int j) {
	Key tmp = pq[i];
	pq[i] = pq[j];
	pq[j] = tmp;
}

template<typename Key>
void heap<Key>::swim(int i) {
	while (i > 1 && compare(i / 2, i)) {
		exch(i / 2, i);
		i /= 2;
	}
}

template<typename Key>
void heap<Key>::sink(int i) {
	while (2 * i <= N) {
		int j = 2 * i;
		if (j < N&&compare(j, j + 1))
			j++;
		if (!compare(i, j))
			break;
		exch(i, j);
		i = j;
	}
}
#endif // !HEAP

