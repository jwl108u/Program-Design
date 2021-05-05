all: GenerateRandomInt GenerateRandomStr QuickSortInt QuickSortStr MergeSortInt MergeSortStr HeapSortInt HeapSortStr

GenerateRandomInt: GenerateRandomInt.c
	gcc GenerateRandomInt.c -o GenerateRandomInt

GenerateRandomStr: GenerateRandomStr.c
	gcc GenerateRandomStr.c -o GenerateRandomStr

QuickSortInt: QuickSortInt.c
	gcc QuickSortInt.c -o QuickSortInt

QuickSortStr: QuickSortStr.c
	gcc QuickSortStr.c -o QuickSortStr

MergeSortInt: MergeSortInt.c
	gcc MergeSortInt.c -o MergeSortInt

MergeSortStr: MergeSortStr.c
	gcc MergeSortStr.c -o MergeSortStr

HeapSortInt: HeapSortInt.c
	gcc HeapSortInt.c -o HeapSortInt

HeapSortStr: HeapSortStr.c
	gcc HeapSortStr.c -o HeapSortStr

clean:
	rm GenerateRandomInt GenerateRandomStr QuickSortInt QuickSortStr MergeSortInt MergeSortStr HeapSortInt HeapSortStr