
void swap(int *, int *);
int *GenerateData(int );
int *GenerateSearchData(int , int );

struct treenode *InsertBST(struct treenode *, int );
struct treenode *SearchBST(struct treenode *, int );
void FreeBST(struct treenode *);
void BST(int *, int *, int , int );

int comp(const void *, const void *);
void SearchBS(int *, int , int );
void BS(int *, int *, int , int );

void SearchArr(int *, int , int );
void Arr(int *, int *, int , int );

struct listnode *InsertLL(struct listnode *, int );
void SearchLL(struct listnode *, int );
void FreeList(struct listnode *);
void LL(int *, int *, int , int );

int HashFunction(int );
struct listnode *InsertHash(struct listnode *, int );
void SearchHash(struct listnode *, int );
void Hash(int *, int *, int , int );
