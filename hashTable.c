#define _CRT_SECURE_NO_WARNINGS 1

#include<iostream>
#include<map>
#include<stdlib.h> // memset	
#include<string.h> // malloc
#include<Windows.h>
//#include<multimap>
using namespace std;

/*

	hash : 哈希表 散列表 散列法
	加密算法 查找数据结构

	// 查找二叉树 方便查找

	// 打怪掉落物品： 数据
	数据种类非常多 需要一种数据结构 保存所有数据 并能够以很快的速度找到对应的数据

	哈希的组成：
		1、确定的数据范围
		2、合适的查找函数
		3、解决冲突的方式

		一开始就设计好数字
		身份证号 第10000个人出生时会出现冲突
		出现冲突，要有解决冲突的方法

		php 函数名做hash,新加入不好取名
		名字不好找得很慢

*/

struct node{
	int _data;
	node* pNext;
};
// 哈希表
struct HashTable{
	node** pArray;
	//vector<node> arr;
};
// 创建hash表
// 由于在main函数中定义的是*，因此现在需要改的是*,所以需要传的参数为**
void CreateHashTable(HashTable** pHash){
	*pHash = new HashTable;
	memset(*pHash,0,sizeof(HashTable));
}
// 初始化hashTable
void InitHashTable(HashTable* pHash){
	pHash->pArray = new node*[10];
	memset(pHash->pArray,0,sizeof(node*)*10);
}
// 创建节点
node* createNode(int data){
	node* pNew = new node;
	pNew->_data = data;
	pNew->pNext = NULL;
	return pNew;
}
// 向hash表中添加数据
void insertNode2HashTable(HashTable* hash,int data){
	// 1、丛数据获知放到hash表中哪一个位置
	int idx = data % 10;
	// 2、创建节点
	node* pNew = createNode(data);
	node*  pTemp = NULL;
	node*  prev = NULL;
	//3、放入hash表
	if (hash->pArray[idx]){	//3、2 有冲突插入链表
		pTemp = hash->pArray[idx]; // 头节点
		while (pTemp->pNext){
			pTemp = pTemp->pNext;
		}
		pTemp->pNext = pNew;
		//while (pTemp){ // 找尾节点
		//	prev = pTemp;
		//	pTemp = pTemp->pNext;
		//}
		//prev->pNext = pNew; //新元素入链表
	}
	else{		//3、1 没有冲突直接放
		hash->pArray[idx] = pNew;
	}
}
// 查找返回地址orNULL
node* findNode(HashTable* hash,int data){
	// 1、定位下标 返回指定的地方的地址
	// 2、返回地址
	return hash->pArray[data%10];
}
int main(){
	HashTable* pHash = NULL;
	CreateHashTable(&pHash);
	InitHashTable(pHash);
	for (int i = 0; i < 6;i++){
		insertNode2HashTable(pHash,rand());
	}
	node* p = NULL;
	for (int i = 0; i < 10;i++){
		p = findNode(pHash, i);
		if (p){
			printf("%d\n", p->_data);
		}
		else{
			printf("找不到\n");
		}
	}
	/*
	insertNode2HashTable(pHash, 0);
	insertNode2HashTable(pHash, 10);
	insertNode2HashTable(pHash, 340);
	insertNode2HashTable(pHash, 345);
	insertNode2HashTable(pHash, 635);
	insertNode2HashTable(pHash, 32);
	insertNode2HashTable(pHash, 78);
	insertNode2HashTable(pHash, 435);
	*/
	system("pause");
	return 0;
}

//// "%d%*c%d" 中间的 %*c 为跳过一个字符