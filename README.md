# Short Algorithm Code

## Huffman coding
Using STL *vector*, *map*, *queue* to achieve a short Huffman coding.

## IP info
Bit opeation to calculate IP information.

## Radix tree

### Introduction
Patricia data structure (Radix tree) is a data structure that represents a space-optimized __Trie__ (Dictionary tree) in which each node that is the only child is merged with its parent. Radix tree is efficient to insert and search word stored in the tree. Operations like `insert`, `find` and `delete` are `O(k)` where `k` is the maximum length of all strings in the set.

### Details of class
+ Language: Python (3.6.5)

+ __Node__ class
	__Node__ class is node in radix tree. It has `prefix` which is the edge information from its parent to itself. `link` is prefix's link interface number. `next` is child pointers, where `next[0]` is the child which prefix started with 0 and `next[1]` is the child which prefix started with 1.

+ __RadixTree__ class
	__RadixTree__ class is the implement of radix tree structure. Function `ip2bin` transfer IP address to its 32 bits binary string. Function `common_prefix` finds the common prefix between two ip address. `find_link` returns the result of an IP address or binary string. `insert` can add prefix information to the tree. `print_tree` can display the radix tree information in preorder.

Here is an example of this program:
```
a = '11001000 00010111 0001 0'
b = '11001000 00010111 0001 1000'
c = '11001000 00010111 0001 1'
r = RadixTree(5)   # default interface is 5
r.insert(a,1)
r.insert(b,2)
r.insert(c,3)
r.print_tree()  #print tree
```
The output is as follows:
```
11001000000101110001[20] -> D
   0[1] -> 1
   1[1] -> 3
      000[3] -> 2
```
The output means that first common prefix is `11001000000101110001`, it has child 0 (`110010000001011100010`) and 1 (`110010000001011100011`). Also 1 has another child 000 (`110010000001011100011000`). The arrow means the link interface number. `D` means default link interface number.
Here is the find function example code:
```
f1=r.find_link("11001000 00011110 10100000 00001011")  # default 
f2=r.find_link("11001000 00010111 00011000 00011110")  # 2
f3=r.find_link("11001000 00010111 00011111 00100010")  # 3
print(f1,f2,f3)
```
Output is:
```
5 2 3
```

### Problems

The edge information is saved at every Node, which leads a problem that root could have only one starting prefix.
In this implementation, you cannot insert both `0011` and `1111`.

The solution is you can place a `0` when insert and find.
Like __0__`0011` and __0__`1111`.
When user want to search an IP like `0010110101`, you can just search  __0__`0010110101`.
Thus, all prefix will store at same 0 root tree.


