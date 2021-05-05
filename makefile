all: GenerateRandomInt QuickSortInt MergeSortInt HeapSortInt

GenerateRandomInt: GenerateRandomInt.c
	gcc GenerateRandomInt.c -o GenerateRandomInt

QuickSortInt: QuickSortInt.c
	gcc QuickSortInt.c -o QuickSortInt

MergeSortInt: MergeSortInt.c
	gcc MergeSortInt.c -o MergeSortInt

HeapSortInt: HeapSortInt.c
	gcc HeapSortInt.c -o HeapSortInt

clean:
	rm GenerateRandomInt QuickSortInt MergeSortInt HeapSortInt