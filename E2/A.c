/********************************************************************
** E2 - A
*/

#include <stdio.h>
#include <stdlib.h>

#ifdef INTERNAL
#pragma warning(disable: 4996)
#endif

#define MAX_NUM 100010

/********************************************************************
** Utility functions.
*/
typedef unsigned char byte_t;
typedef int (*CompareFunction)(const void*, const void*);

#define _OFFSET(X, OFFSET, SIZE) (((byte_t*)X) + (OFFSET) * (SIZE))
#define _LAST(N) (((N) >> (1)) - (1))
#define _ROOT(X) (((X) - (1)) >> 1)
#define _LEFT(X) (((X) << (1)) + (1))
#define _RIGHT(X) (((X) << (1)) + (2))

void _swap(byte_t* _dest, byte_t* _src)
{
	*_dest ^= *_src;
	*_src ^= *_dest;
	*_dest ^= *_src;
}

void swap(void* _dest, void* _src, size_t _size)
{
	if (_dest == _src)
		return;

	byte_t* dest = (byte_t*)_dest;
	byte_t* src = (byte_t*)_src;

	while (_size--)
	{
		_swap(dest, src);
		dest++;
		src++;
	}
}

void _copy(byte_t* _dest, const byte_t* _src)
{
	*_dest = *_src;
}

void copy(void* _dest, const void* _src, size_t _size)
{
	if (_dest == _src)
		return;

	byte_t* dest = (byte_t*)_dest;
	const byte_t* src = (const byte_t*)_src;

	while (_size--)
	{
		_copy(dest, src);
		dest++;
		src++;
	}
}

/*
**+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
** Heap Region
**+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/
#define HEAP_SIZE MAX_NUM

typedef struct tagPriorityQueue
{
	void* _base;
	size_t _size;
	size_t _elemSize;

	CompareFunction _comp;

	void (*push)(struct tagPriorityQueue*, void*);
	void* (*top)(struct tagPriorityQueue*);
	void (*pop)(struct tagPriorityQueue*);
	int (*empty)(struct tagPriorityQueue*);
} Heap;

void _top_down_heapify(byte_t* _base, size_t _num, size_t _size, CompareFunction _comp)
{
	if (_num < 2)
		return;

	size_t p, i, j, k;	// parent, left child, right child, chosen child
	byte_t* pivot;
	byte_t* candidate;

	p = 0;
	for (; ; )
	{
		i = _LEFT(p);
		if (i >= _num)
			break;
		j = _RIGHT(p);

		// largest of child
		k = i;
		if (j < _num)
		{
			if (_comp(_OFFSET(_base, i, _size), _OFFSET(_base, j, _size)) > 0)
				k = j;
		}

		pivot = _OFFSET(_base, p, _size);
		candidate = _OFFSET(_base, k, _size);

		// check if already good
		if (_comp(pivot, candidate) < 0)
			break;

		// adjust
		swap(pivot, candidate, _size);
		p = k;
	}
}

void _down_top_heapify(byte_t* _base, size_t _num, size_t _size, CompareFunction _comp)
{
	if (_num < 2)
		return;

	size_t i;	// current node
	size_t p;	// parent
	byte_t* pivot;
	byte_t* candidate;

	i = _num - 1;
	for (; ; )
	{
		if (i == 0)
			break;
		p = _ROOT(i);

		pivot = _OFFSET(_base, i, _size);
		candidate = _OFFSET(_base, p, _size);

		// check if already good
		if (_comp(pivot, candidate) > 0)
			break;

		// adjust
		swap(pivot, candidate, _size);
		i = p;
	}
}

void _heap_push(Heap* heap, void* element)
{
	if (heap->_size < HEAP_SIZE)
	{
		copy(_OFFSET(heap->_base, heap->_size, heap->_elemSize), element, heap->_elemSize);
		heap->_size++;
		_down_top_heapify(heap->_base, heap->_size, heap->_elemSize, heap->_comp);
	}
}

void* _heap_top(Heap* heap)
{
	if (heap->_size == 0)
		return NULL;
	else
		return heap->_base;
}

void _heap_pop(Heap* heap)
{
	if (heap->_size > 0)
	{
		swap(heap->_base, _OFFSET(heap->_base, heap->_size - 1, heap->_elemSize), heap->_elemSize);
		heap->_size--;
		_top_down_heapify(heap->_base, heap->_size, heap->_elemSize, heap->_comp);
	}
}

int _heap_empty(Heap* heap)
{
	return heap->_size == 0;
}

void heap_init(Heap* heap, size_t _elemSize, CompareFunction _comp)
{
	heap->_base = malloc(_elemSize * HEAP_SIZE);
	heap->_size = 0;
	heap->_elemSize = _elemSize;

	heap->_comp = _comp;

	heap->push = _heap_push;
	heap->top = _heap_top;
	heap->pop = _heap_pop;
	heap->empty = _heap_empty;
}

void heap_destroy(Heap* heap)
{
	free(heap->_base);
	heap->_base = NULL;
}


/********************************************************************
** Custom functions.
*/
int greater(const void* a, const void* b)
{
	return *((int*)b) - *((int*)a);
}

int less(const void* a, const void* b)
{
	return *((int*)a) - *((int*)b);
}


Heap master;
Heap slave;

void initialize(void);
void destroy(void);

void push(int x);
int pop(void);
int top(void);
void erase(int x);
void _erase(void);
void show(void);
int main(void)
{
	int n;
	int op, x;

	initialize();

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d", &x);
			push(x);
		}
		else if (op == 2)
			pop();
		else if (op == 3)
		{
#ifdef INTERNAL
			printf("\t> ");
#endif
			printf("%d\n", top());
		}
		else
		{
			scanf("%d", &x);
			erase(x);
		}
	}

	show();

	destroy();

	return 0;
}

void initialize(void)
{
	heap_init(&master, sizeof(int), less);
	heap_init(&slave, sizeof(int), less);
}

void destroy(void)
{
	heap_destroy(&master);
	heap_destroy(&slave);
}

void push(int x)
{
	master.push(&master, &x);
}

int pop(void)
{
	int ret = 0;

	_erase();
	if (!master.empty(&master))
	{
		ret = *((int*)master.top(&master));
		master.pop(&master);
	}

	return ret;
}

int top(void)
{
	int ret = 0;

	_erase();

	if (!master.empty(&master))
		ret = *((int*)master.top(&master));

	return ret;
}

void erase(int x)
{
	slave.push(&slave, &x);
}

void _erase(void)
{
	int mv, sv;

	// no need to check master
	while (!slave.empty(&slave))
	{
		mv = *((int*)master.top(&master));
		sv = *((int*)slave.top(&slave));

		if (mv == sv)
		{
			master.pop(&master);
			slave.pop(&slave);
		}
		else
			break;
	}
}

void show(void)
{
	_erase();
	while (!master.empty(&master))
	{
		printf("%d ", *((int*)master.top(&master)));
		master.pop(&master);
		_erase();
	}
}
