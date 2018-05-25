#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bin_tree.h"
#include "seqqueue.h"
#include "seqstack.h"

TreeNode* CreateTreeNode(TreeNodeType value){
	TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
	new_node->data = value;
	new_node->lchild = NULL;
	new_node->rchild = NULL;
	return new_node;
}

void DestroyTreeNode(TreeNode* node){
	free(node);
}

void TreeInit(TreeNode** pRoot){
	if(pRoot == NULL){
		//非法输入
		return;
	}
	*pRoot = NULL;
	return;
}

void TreePreOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	//先访问根结点，访问即打印
	printf("%c ",root->data);
	//然后递归的遍历左子树
	TreePreOrder(root->lchild);
	//最后在递归的遍历右子树
	TreePreOrder(root->rchild);
	return;
}

void TreeInOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	//先递归的遍历左子树
	TreeInOrder(root->lchild);
	//再访问根结点
	printf("%c ",root->data);
	//最后递归的遍历右子树
	TreeInOrder(root->rchild);
	return;
}

void TreePostOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	//先递归的遍历左子树
	TreePostOrder(root->lchild);
	//再递归的遍历右子树
	TreePostOrder(root->rchild);
	//最后访问根结点
	printf("%c ",root->data);
	return;
}

void TreeLevelOrder(TreeNode* root){
	if(root == NULL){
		//空树
		return;
	}
	SeqQueue queue;
	SeqQueueInit(&queue);
	SeqQueuePush(&queue,root);
	while(1){
		SeqQueueType front;
		int ret = SeqQueueFront(&queue,&front);
		if(ret == 0){
			//如果队列取队首元素失败，说明队列为空
			//如果队列为空就说明遍历结束了
			break;
		}
		//访问树中的元素，打印当前值
		printf("%c ",front->data);
		//把当前队首元素出队列
		SeqQueuePop(&queue);
		//把当前元素的左右子树入队列
	
		if(front->lchild != NULL){
			SeqQueuePush(&queue,front->lchild);
		}
		if(front->rchild != NULL){
			SeqQueuePush(&queue,front->rchild);
		}
	}
	return;
}

TreeNode* _TreeCreate(TreeNodeType arry[],size_t size,size_t* index,TreeNodeType null_node){
	if(index == NULL){
		//非法输入
		return NULL;
	}
	if(*index >= size){
		return NULL;
	}
	if(arry[*index] == null_node){
		return NULL;
	}
	TreeNode* new_node = CreateTreeNode(arry[*index]);
	++(*index);
	new_node->lchild = _TreeCreate(arry,size,index,null_node);
	++(*index);
	new_node->rchild = _TreeCreate(arry,size,index,null_node);
	return new_node;
}

TreeNode* TreeCreate(TreeNodeType arry[],size_t size,char null_node){
	//表示当前取数组中的那个元素
	size_t index = 0;
	return _TreeCreate(arry,size,&index,null_node);
}

TreeNode* TreeClone(TreeNode* root){
	if(root == NULL){
		//空树
		return NULL;
	}
	//按照先序方式来遍历
	TreeNode* new_node = CreateTreeNode(root->data);
	new_node->lchild = TreeClone(root->lchild);
	new_node->rchild = TreeClone(root->rchild);
	return new_node;
}
//销毁的过程中一定要保证左右子树能够被正确找到，所有按照后序的方式来销毁
void TreeDestroy(TreeNode* root){
    if(root == NULL){
        //空树
        return;
    }
    //按照后序遍历的方式来销毁整个树
    TreeDestroy(root->lchild);
    TreeDestroy(root->rchild);
    DestroyTreeNode(root);
    return;
}

//方法一
//void _TreeSize(TreeNode* root,size_t* size){
//    if(root == NULL){
//        //空树
//        return;
//    }
//    //按照前序的方式遍历，这里的访问是++
//    ++(*size);
//    _TreeSize(root->lchild,size);
//    _TreeSize(root->rchild,size);
//}
//size_t TreeSize(TreeNode* root){
//    size_t size = 0;
//    _TreeSize(root,&size);
//    return size;
//}
//方法二
size_t TreeSize(TreeNode* root){
    if(root == NULL){
        //空树
        return 0;
    }
    return 1 + TreeSize(root->lchild) + TreeSize(root->rchild);
}

size_t TreeLeafSize(TreeNode* root){
    if(root == NULL){
        //空树
        return 0;
    }
    if(root->lchild == NULL && root->rchild == NULL){
        //root是叶子结点
        return 1;
    }
    //root不是叶子结点
    return TreeLeafSize(root->lchild) + TreeLeafSize(root->rchild);
}

size_t TreeKLevelSize(TreeNode* root,int K){
    if(root == NULL || K < 1){
        //root等于空是空树，K<1是非法输入
       return 0;
    }
    if(K == 1){
      return 1;
    }
    return TreeKLevelSize(root->lchild ,K - 1) + TreeKLevelSize(root->rchild,K - 1);

}

size_t TreeHeight(TreeNode* root){
    if(root == NULL){
        //空树
        return 0;
    }
    if(root->lchild == NULL && root->rchild == NULL){
        return 1;
    }
    size_t lheight = TreeHeight(root->lchild);
    size_t rheight = TreeHeight(root->rchild);

    return 1 + (lheight > rheight ? lheight : rheight);
}

TreeNode* TreeFind(TreeNode* root,TreeNodeType to_find){
    if(root == NULL){
        //空树
        return NULL;
    }
    if(root->data == to_find){
        return root;
    }
    TreeNode* lresult = TreeFind(root->lchild,to_find);
    TreeNode* rresult = TreeFind(root->rchild,to_find);
    //不等于空，说明找到了
    return lresult != NULL ? lresult : rresult;
}

TreeNode* FindParent(TreeNode* root,TreeNode* child){
    if(root == NULL || child == NULL){
        return NULL;
    }
    if(root->lchild == child || root->rchild == child){
        return root;
    }
    TreeNode* lresult = FindParent(root->lchild,child);
    TreeNode* rresult = FindParent(root->rchild,child);
    return lresult != NULL ? lresult : rresult;
}

TreeNode* LChild(TreeNode* node){
    if(node == NULL){
        return NULL;
    }
    return node->lchild;
}

TreeNode* RChild(TreeNode* node){
    if(node == NULL){
        return NULL;
    }
    return node->rchild;
}

void TreePreOrderByLoop(TreeNode* root){
    if(root == NULL){
        return;
    }
    //1.先把根结点入栈
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,root);
    //2.循环取栈顶元素，访问，并且出栈，在将根结点的左右子树入栈
    TreeNode* top = NULL;
    while(1){
        int ret = SeqStackTop(&stack,&top);
        if(ret == 0){
            printf("\n");
            //取栈顶元素失败，遍历结束
            break;
        }
        SeqStackPop(&stack);
        printf("%c ",top->data);
        if(top->rchild != NULL){
            SeqStackPush(&stack,top->rchild);
        }
        if(top->lchild != NULL){
            SeqStackPush(&stack,top->lchild);
        }
    }
    return;
}

void TreeInOrderByLoop(TreeNode* root){
    if(root == NULL){
        return;
    }
    //定义cur指针指向根结点
    SeqStack stack;
    SeqStackInit(&stack);
    TreeNode* cur = root;
    while(1){
        //1.循环判定cur是否为空，如果不为空，将cur入栈，并且cur指向cur->lchild
        while(cur != NULL){
            SeqStackPush(&stack,cur);
            cur = cur->lchild;
        }
        //2.如果cur为空，取栈顶元素，访问，出栈
        TreeNode* top = NULL;
        int ret = SeqStackTop(&stack,&top);
        if(ret == 0){
            printf("\n");
            //此时说明已经没有栈顶元素，遍历完了
            return;
        }
        printf("%c ",top->data);
        SeqStackPop(&stack);
        //3.让cur指向栈顶元素的右子树，重复循环刚才判空的过程
        cur = top->rchild;
    }
}

void TreePostOrderByLoop(TreeNode* root){
    if(root == NULL){
        return;
    }
    //1.定义一个cur指针指向root
    SeqStack stack;
    SeqStackInit(&stack);
    TreeNode* cur = root;
    TreeNode* pre = NULL;//保存上一个访问过的节点
    //2.循环判定cur是否为空，如果cur不为空，就将cur入栈，并且cur指向cur->lchild
    while(1){
        while(cur != NULL){
            SeqStackPush(&stack,cur);
            cur = cur->lchild;
        }
        //3.如果cur为空,循环取栈顶元素
        TreeNode* top = NULL;
        int ret = SeqStackTop(&stack,&top);
        if(ret == 0){
            printf("\n");
            //取栈顶元素失败，遍历结束
            return;
        }
        //4.对栈顶元素进行判定
        //  a)如果栈顶元素的右子树和上一个访问过的元素相等
        //  b)或者栈顶元素的右子树为空
        //  此时访问栈顶元素，同时进行出栈
        //5.如果不满足刚才的条件，就让cur指向栈顶元素的右子树，重复循环
        if(top->rchild == pre || top->rchild == NULL){
            printf("%c ",top->data);
            SeqStackPop(&stack);
            pre = top;
        }else{
            cur = top->rchild;
        }
    }
}

void Swap(TreeNode** a,TreeNode** b){
    TreeNode* tmp = *a;
    *a = *b;
    *b = tmp;
}
void TreeMirror(TreeNode* root){
    if(root == NULL){
        return;
    }
    //访问动作就是交换左右子树
    Swap(&root->lchild,&root->rchild);
    TreeMirror(root->lchild);
    TreeMirror(root->rchild);
}

void TreeMirrorByLoop(TreeNode* root){
    if(root == NULL){
        return;
    }
    SeqQueue q;
    SeqQueueInit(&q);
    SeqQueuePush(&q,root);
    TreeNode* front = NULL;
    while(SeqQueueFront(&q,&front)){
        Swap(&front->lchild,&front->rchild);
        SeqQueuePop(&q);
        if(front->lchild != NULL){
            SeqQueuePush(&q,front->lchild);
        }
        if(front->rchild != NULL){
            SeqQueuePush(&q,front->rchild);
        }
    }
    return;
}

//判定一颗树是否是完全二叉树
int IsCompleteTree(TreeNode* root){
    if(root == NULL){
        return 0;
    }
    SeqQueue q;
    SeqQueueInit(&q);
    SeqQueuePush(&q,root);
    //这个变量表示是否要进入第二阶段
    int if_start_step_two_flag = 0;
    TreeNode* cur = NULL;
    while(SeqQueueFront(&q,&cur)){
        SeqQueuePop(&q);
        if(if_start_step_two_flag == 0){
            //阶段一
            if(cur->lchild != NULL && cur->rchild != NULL){
                //同时具备左右子树
                SeqQueuePush(&q,cur->lchild);
                SeqQueuePush(&q,cur->rchild);
            }else if(cur->rchild != NULL && cur->lchild == NULL){
                //不是完全二叉树
                return 0;
            }else if(cur->rchild == NULL && cur->lchild != NULL){
                //当前节点只有左子树没有右子树，进入第二阶段
                if_start_step_two_flag = 1;
                SeqQueuePush(&q,cur->lchild);
            }else {
                //没有左右子树
                if_start_step_two_flag = 1;
            }
        }else {
            //阶段二
            if(cur->lchild == NULL && cur->rchild ==NULL){
                ;
            }else{
                return 0;
            }
        }//end阶段一和阶段二的判定
    }//循环结束
    //所有节点都判定完了，此时又没有return 0,此时一定是完全二叉树
    return 1;
}

size_t Find(TreeNodeType arry[],size_t left,size_t right,TreeNodeType to_find){
    size_t i = left;
    for(;i<right;i++){
        if(arry[i] == to_find){
            return i;
        }
    }
    return (size_t)-1;
}

TreeNode* _TreeRebuild(TreeNodeType pre_order[],size_t pre_order_size,size_t* pre_order_index,
                       TreeNodeType in_order[],size_t in_order_left,size_t in_order_right){
    if(in_order_left >= in_order_right){
        //无效区间，当前子树中序遍历结果为空，此时说明这棵子树是空树
        return NULL;
    }
    if(pre_order_index == NULL || *pre_order_index >= pre_order_size){
        //pre_order_index == NULL非法输入
        //*pre_order_index >= pre_order_size 遍历完了
        return NULL;
    }
    //根据先序遍历结果取出当前值，基于这个值构建一个节点
    //new_node 相当于当前子树的根结点
    TreeNode* new_node = CreateTreeNode(pre_order[*pre_order_index]);
    //查找一下当前节点在中序遍历中的位置
    size_t cur_root_in_order_index = Find(in_order,in_order_left,in_order_right,new_node->data);
    //assert(cur_root_in_order_index != (size_t)-1);
    ++(*pre_order_index);
    //左子树区间[in_order_left,cur_root_in_order_index)
    new_node->lchild = _TreeRebuild(pre_order,pre_order_size,pre_order_index,in_order,in_order_left,cur_root_in_order_index);
    //右子树区间[cur_root_in_order_index+1,in_order_right)
    new_node->rchild = _TreeRebuild(pre_order,pre_order_size,pre_order_index,in_order,cur_root_in_order_index+1,in_order_right);
    return new_node;
}
TreeNode* TreeRebuild(TreeNodeType pre_order[],TreeNodeType in_order[],size_t size){
    size_t pre_order_index = 0;
    size_t in_order_left = 0;
    size_t in_order_right = size;
    //[in_order_left,in_order_right)
    return _TreeRebuild(pre_order,size,&pre_order_index,in_order,in_order_left,in_order_right);
}
//////////////////////////////////////
//以下为测试代码
/////////////////////////////////////
#if 1
#include <stdio.h>
#define TEST_HEADER printf("\n=============================%s===========================\n",__FUNCTION__)

void TestInit(){
    TEST_HEADER;
    TreeNode* root;
    TreeInit(&root);
    printf("root expected NULL,actual %p\n",root);
}

void TestPreOrder(){
    TEST_HEADER;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    TreeNode* g = CreateTreeNode('g');

    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    c->rchild = f;
    printf("前序遍历结果：");
    TreePreOrder(a);
    printf("\n");
}
void TestInOrder(){
    TEST_HEADER;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    TreeNode* g = CreateTreeNode('g');

    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    c->rchild = f;
    printf("中序遍历结果：");
    TreeInOrder(a);
    printf("\n");
}
void TestPostOrder(){
    TEST_HEADER;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    TreeNode* g = CreateTreeNode('g');

    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    c->rchild = f;
    printf("后序遍历结果：");
    TreePostOrder(a);
    printf("\n");
}
void TestLevelOrder(){
    TEST_HEADER;
    TreeNode* a = CreateTreeNode('a');
    TreeNode* b = CreateTreeNode('b');
    TreeNode* c = CreateTreeNode('c');
    TreeNode* d = CreateTreeNode('d');
    TreeNode* e = CreateTreeNode('e');
    TreeNode* f = CreateTreeNode('f');
    TreeNode* g = CreateTreeNode('g');

    a->lchild = b;
    a->rchild = c;
    b->lchild = d;
    b->rchild = e;
    e->lchild = g;
    c->rchild = f;
    printf("层序遍历结果：");
    TreeLevelOrder(a);
    printf("\n");
}

void TestCreate(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');

    printf("\n先序遍历：");
    TreePreOrder(root);
    printf("\n中序遍历：");
    TreeInOrder(root);
    printf("\n后序遍历：");
    TreePostOrder(root);
    printf("\n层序遍历：");
    TreeLevelOrder(root);
    printf("\n");
}
void TestClone(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');

    TreeNode* new_node = TreeClone(root);
    printf("\n先序遍历：");
    TreePreOrder(new_node);
    printf("\n中序遍历：");
    TreeInOrder(new_node);
    printf("\n后序遍历：");
    TreePostOrder(new_node);
    printf("\n层序遍历：");
    TreeLevelOrder(new_node);
    printf("\n");
}
void TestSize(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');
    size_t size = TreeSize(root);
    printf("size expected 7,actual %lu\n",size);
}
void TestLeafSize(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');
    size_t size = TreeLeafSize(root);
    printf("size expected 3,actual %lu\n",size);

}
void TestLevelSize(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');
    size_t size = TreeKLevelSize(root,3);
    printf("size expected 3,actual %lu\n",size);

}
void TestHeight(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');
    size_t height = TreeHeight(root);
    printf("size expected 4,actual %lu\n",height);
}
void TestFind(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');
    TreeNode* result = TreeFind(root,'b');
    printf("result expected %p,actual %p\n",root->lchild,result);
}
void TestFindParent(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');
    TreeNode* result = FindParent(root,root->rchild->rchild);
    printf("result expected %c,actual %c\n",root->rchild->data,result->data);
}

void TestPreOrderByLoop(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');
    printf("先序遍历结果：");
    TreePreOrderByLoop(root);
}
void TestInOrderByLoop(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');
    printf("中序遍历结果：");
    TreeInOrderByLoop(root);
}
void TestPostOrderByLoop(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');
    printf("后序遍历结果：");
    TreePostOrderByLoop(root);
}

void TestMirror(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##eg###c#f##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');
    TreeMirror(root);
    printf("先序遍历：");
    TreePreOrder(root);
    printf("\n");
    printf("中序遍历：");
    TreeInOrder(root);
    printf("\n");
    printf("后序遍历：");
    TreePostOrder(root);
    printf("\n");
}

void TestIsCompleteTree(){
    TEST_HEADER;
    TreeNodeType arry[] = "abd##e##c##";
    TreeNode* root = TreeCreate(arry,sizeof(arry)/sizeof(arry[0])-1,'#');
    int ret = IsCompleteTree(root);
    printf("ret expected 1 ,actual %d\n",ret);
}

void  TestRebuild(){
    TEST_HEADER;
    TreeNodeType pre_order[] = "abdecf";
    TreeNodeType in_order[] = "dbeacf";
    TreeNode* root = TreeRebuild(pre_order,in_order,sizeof(pre_order)/sizeof(pre_order[0])-1);
    printf("先序遍历结果：");
    TreePreOrder(root);
    printf("\n");
    printf("中序遍历结果：");
    TreeInOrder(root);
    printf("\n");
    printf("后序遍历结果：");
    TreePostOrder(root);
    printf("\n");
}
int main(){
    TestInit();
    TestPreOrder();
    TestInOrder();
    TestPostOrder();
    TestLevelOrder();
    TestCreate();
    TestClone();
    TestSize();
    TestLeafSize();
    TestLevelSize();
    TestHeight();
    TestFind();
    TestPreOrderByLoop();
    TestInOrderByLoop();
    TestPostOrderByLoop();
    TestMirror();
    TestIsCompleteTree();
    TestRebuild();
    return 0;
}
#endif
