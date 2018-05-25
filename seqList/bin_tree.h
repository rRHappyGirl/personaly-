#pragma once
#include <stdio.h>
typedef char TreeNodeType;
//使用孩子表示法来表示一棵树
typedef struct TreeNode {
	TreeNodeType data;
	struct TreeNode* lchild;
	struct TreeNode* rchild;
}TreeNode;

//对于链表来说，使用链表的头节点指针来表示一个链表
//对于二叉树来说，使用跟结点的指针来表示一棵树

void TreeInit(TreeNode** pRoot);

void TreePreOrder(TreeNode* root);

void TreeInOrder(TreeNode* root);

void TreePostOrder(TreeNode* root);

void TreeLevelOrder(TreeNode* root);

//输入一个数组（数组中的每个元素就是树上的结点），根据数组的内容
//构建出一颗树，数组中元素的内容符合树的先序遍历结果（包含所有空结点）
TreeNode* TreeCreate(TreeNodeType arry[],size_t size,char null_node);

//求二叉树中结点的个数
size_t TreeSize(TreeNode* root);
//求二叉树中叶子结点的个数
size_t TreeLeafSize(TreeNode* root);
//求二叉树中第K层结点的个数
size_t TreeKLevelSize(TreeNode* root,int K);

//求二叉树的高度/深度
size_t TreeHeight(TreeNode* root);

void TreeDestroy(TreeNode* root);

//在二叉树中查找结点，给定一个数值，求出对应结点的指针
//假设二叉树中的结点是不重复的
TreeNode* TreeFind(TreeNode* root,TreeNodeType to_find);

//求出child的父节点
TreeNode* FindParent(TreeNode* root,TreeNode* child);

//求出当前节点的左子树和右子树
TreeNode* LChild(TreeNode* node);
TreeNode* RChild(TreeNode* node);

//非递归前序遍历
void TreePreOrderByLoop(TreeNode* root);

void TreeInOrderByLoop(TreeNode* root);

void TreePostOrderByLoop(TreeNode* root);
