/********************************************************************
** C2 - B
*/

#include <stdio.h>
#include <stdlib.h>

// #define INTERNAL

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

void show_heap(Heap* heap);
int main(void)
{
	int n;
	int op;
	int x;

	Heap heap;

	heap_init(&heap, sizeof(int), greater);

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &op);
		if (op == 1)
		{
			scanf("%d", &x);
			heap.push(&heap, &x);
		}
		else if (op == 2)
			heap.pop(&heap);
		else
		{
#ifdef INTERNAL
			printf("\t> ");
#endif
			printf("%d\n", *((int*)heap.top(&heap)));
		}
	}
	show_heap(&heap);

	heap_destroy(&heap);

	return 0;
}

void show_heap(Heap* heap)
{
	while (!heap->empty(heap))
	{
		printf("%d ", *((int*)heap->top(heap)));
		heap->pop(heap);
	}
}
