//
//  main.c
//  SqBiTree
//
//  Created by Eason on 2020/8/7.
//  Copyright © 2020 Eason. All rights reserved.
//

#include <stdio.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define MAXSIZE 100
typedef int Status;  //作为返回状态 如ERROR OK FALSE TRUE，其实也就是返回一个int值
typedef int ElemType;   //元素数据类型，这里就先定义为int
typedef ElemType BiTree[MAXSIZE];   //二叉树的元素存储数组，通过数组的下标实现二叉树结构
//这里一定要注意的是这里存储容量MAXSIZE 因为获取孩子的判断是要判断T[2*MAXSIZE]这个数量级的，所以实际存储容量要比真实存储的内容大一倍
//比如放了10个元素，这时候我的存储容量至少为21以上，不然判断的时候数组越界会报错，数值原因见获取孩子方法
ElemType null=0;   //将0作为空元素

//初始化一个二叉树
Status initTree(BiTree T){
    for(int i=0;i<MAXSIZE;i++){   //将二叉树中所有元素位置置为空元素标志null即0
        T[i] = null;  //即将空元素存入
    }
    printf("二叉树初始化完成\n");
    return OK;
}

//清空一个二叉树(也可以使用#define clearTree initTree)
Status clearTree(BiTree T){   //同初始化一个二叉树相同
    for(int i=0;i<MAXSIZE;i++){
        T[i] = null;
    }
    return OK;
}

//创建一个二叉树
Status creatBTree(BiTree T){
    printf("创建一个元素为1-10的二叉树\n");
    int i=0;   //当前数组位置计位器
    int data=1;   //存入的数据元素
    while(data<=10){   //准备存入1-10
        T[i]=data;   //将当前数据元素存入当前数组位置处
        if(i!=0 && i>=MAXSIZE && T[(i+1)/2-1]==null && T[i]!=0){   //即当前结点是非根无双亲且不为空的结点，即为一个悬浮的结点，那么是不能给这个结点赋值的
            printf("出现了无双亲的非根结点\n");
            return ERROR;
        }
        i++;   //数组位置进一
        data++;   //数据元素+1
    }
    return OK;
}

//判断二叉树是否为空
Status isEmpty(BiTree T){
    if(T[0]==null){   //若二叉树没有根结点，则表明当前二叉树是空二叉树
        return TRUE;
    }else{
        return FALSE;
    }
}

//获取当前二叉树的根结点数据
Status getRoot(BiTree T, int *e){
    if(isEmpty(T)){   //如果当前二叉树为空，则没有根结点
        printf("当前二叉树为空，无根结点数据\n");
        return ERROR;
    }
    *e = T[0];   //如果不为空则将根结点的数据存入e中供返回查看
    return OK;
}

//获取二叉树的深度
int getDepth(BiTree T){
    int i;   //数组位置计位器
    for(i=MAXSIZE-1;i>=0;i--){   //从二叉树数组的最后位置向前找
        if(T[i]!=null){   //找到最后一个不为空的元素后推出循环
            break;
        }
    }
    i++;   //将i作为位置
    int depth = 1;   //初始depth为1
    while(i>=powl(2, depth)){   //2的depth次方，当2的depth次方大于当前最后元素位置时，depth就为当前二叉树的深度
        depth++;   //若当前深度仍不包含最后一个元素，则继续加深深度
    }
    return depth;   //返回深度值
}

//获取二叉树某个结点的parent（获取二叉树中e元素的双亲结点元素）
ElemType getParent(BiTree T, ElemType e){
    if(isEmpty(T)){   //判断当前二叉树是否为空
        printf("二叉树为空，无法查找\n");
        return ERROR;
    }
    for(int i=0;i<MAXSIZE;i++){   //寻找指定数值结点的位置
        if(T[i]==e){   //若当前位置元素与指定元素相等
            return T[(i+1)/2-1];   //则返回此位置元素的双亲结点数据，若返回0则表示无双亲结点
        }
    }
    printf("二叉树中无此结点，无法查找\n");
    return ERROR;
}

//获取二叉树某个结点的左孩子（获取二叉树中e元素的左孩子）
ElemType getLeftChild(BiTree T, ElemType e){
    if(isEmpty(T)){   //判断当前二叉树是否为空
        printf("二叉树为空，无法查找\n");
        return ERROR;
    }
    for(int i=0;i<MAXSIZE;i++){   //寻找指定数值结点的位置
        if(T[i]==e){   //若当前位置元素与指定元素相等
            return T[i*2+1];   //则返回此位置元素的左孩子结点的数据，若返回0则表示无左孩子
        }
    }
    return ERROR;
}

//获取二叉树某个结点的右孩子（获取二叉树中e元素的右兄弟）
ElemType getRightChild(BiTree T, ElemType e){
    if(isEmpty(T)){   //判断当前二叉树是否为空
        printf("二叉树为空，无法查找\n");
        return ERROR;
    }
    for(int i=0;i<MAXSIZE;i++){   //寻找指定数值结点的位置
        if(T[i]==e){   //若当前位置元素与指定元素相等
            return T[i*2+2];   //则返回此位置元素的右孩子结点的数据，若返回0则表示无右孩子
        }
    }
    return ERROR;
}

//获取二叉树某个结点的左兄弟（获取二叉树中e元素的左兄弟）
ElemType getLeftBrother(BiTree T, ElemType e){
    if(isEmpty(T)){   //判断当前二叉树是否为空
        printf("二叉树为空，无法查找\n");
        return ERROR;
    }
    for(int i=0;i<MAXSIZE;i++){   //寻找指定数值结点的位置
        if(T[i]==e && i%2==0){   //若当前位置元素与指定元素相等，并且本身位置为右
            return T[i-1];   //则返回此位置右孩子的数据
        }
    }
    return 0;   //若无可满足条件的元素则返回0，也就是说若返回0则表示这个结点是左结点，也可能是没有左兄弟
}

//获取二叉树某个结点的右兄弟（获取二叉树中e元素的右兄弟）
ElemType getRightBrother(BiTree T, ElemType e){
    if(isEmpty(T)){   //判断当前二叉树是否为空
        printf("二叉树为空，无法查找\n");
        return ERROR;
    }
    for(int i=0;i<MAXSIZE;i++){   //寻找指定数值结点的位置
        if(T[i]==e && i%2!=0){   //若当前位置元素与指定元素相等，并且本身位置为左
            return T[i+1];   //则返回此位置左孩子的数据
        }
    }
    return 0;   //若无可满足条件的元素则返回0，也就是说若返回0则表示这个结点是右结点，也可能是没有又兄弟
}

//获取某指定位置的结点数据（获取二叉树中第level层第num个结点元素）
ElemType getValue(BiTree T, int level, int num){
    if(isEmpty(T)){   //判断当前二叉树是否为空
        printf("二叉树为空，无法查找\n");
        return ERROR;
    }
    return T[(int)pow(2, level-1)+num-2];
}

//替换某指定位置的结点数据（将二叉树第level层第num个数据元素替换为value)
Status replace(BiTree T, int level, int num, ElemType value){
    int i = (int)pow(2, level-1)+num-2;   //将指定的level层第num个数据元素替换成在数组中的下标位置
    if(T[i+1/2-1]==null){   //若指定位置的结点无双亲结点则无法赋值
        printf("此结点的双亲结点为空，无法赋值\n");
        return ERROR;
    }
    if(value==null && (T[i*2+1]!=null || T[i*2+2]!=null)){   //若此结点有孩子结点那么则不可为这个结点赋控制
        printf("此结点的孩子结点不为空，不可以为其赋空值\n");
        return ERROR;
    }
    T[i] = value;   //将value存入指定位置
    return OK;
}

//--------------------二叉树的遍历----------------------
//均利用递归的方式进行遍历
//先序访问输出（供先序遍历调用）
void preOrderVisit(BiTree T, int now){   //先序遍历即先访问根结点然后遍历左子树最后访问右子树
    printf("%d ", T[now]);   //访问当前结点数据并打印
    if(T[now*2+1]!=null){   //若当前位置有左子树则先访问左子树
        preOrderVisit(T, now*2+1);   //访问左子树
    }
    if(T[now*2+2]!=null){   //若当前位置有右子树则访问右子树
        preOrderVisit(T, now*2+2);    //访问右子树
    }
}
//先序遍历
Status preOrderTraverse(BiTree T){
    if(isEmpty(T)){   //判断二叉树是否为空
        printf("二叉树为空，无法遍历\n");
        return ERROR;
    }
    preOrderVisit(T, 0);   //调用前序遍历函数
    printf("\n");
    return OK;
}

//中序访问输出（供中序遍历调用）
void inOrderVisit(BiTree T, int now){   //中序遍历即先遍历左子树后访问根结点最后遍历右子树（参考前序遍历，只是访问次序变更）
    if(T[now*2+1]!=null){
        inOrderVisit(T, now*2+1);
    }
    printf("%d ", T[now]);
    if(T[now*2+2]!=null){
        inOrderVisit(T,now*2+2);
    }
}

//中序遍历
Status inOrderTraverse(BiTree T){
    if(isEmpty(T)){
        printf("二叉树为空，无法遍历\n");
        return ERROR;
    }
    inOrderVisit(T, 0);
    printf("\n");
    return OK;
}

//后序访问输出（供后序遍历使用）
void postOrderVisit(BiTree T, int now){   //后序遍历即先遍历左子树后遍历右子树最后访问根结点（参考前序遍历，只是访问次序变更）
    if(T[now*2+1]!=null){
        postOrderVisit(T,now*2+1);
    }
    if(T[now*2+2]!=null){
        postOrderVisit(T,now*2+2);
    }
    printf("%d ", T[now]);
}

//后序遍历
Status postOrderTraverse(BiTree T){
    if(isEmpty(T)){
        printf("二叉树为空，无法遍历\n");
        return ERROR;
    }
    postOrderVisit(T, 0);
    printf("\n");
    return OK;
}

//层序遍历
Status levelOrderTraverse(BiTree T){   //即一层一层的访问元素，这里主要是判断哪些元素在哪一层
    if(isEmpty(T)){  //判断二叉树是否为空
        printf("二叉树为空，无法遍历\n");
        return ERROR;
    }
    int level = 1;   //初始为第一层
    int e;   //用于存储获取的元素数值
    for(int i=level;i<=getDepth(T);i++){   //从第一层到此二叉树的深度
        printf("第%d层：", i);   //打印当前层数
        for(int j=1;j<=pow(2,i-1);j++){   //从本层的第一个元素到本层的最后元素
            e = getValue(T, i, j);   //获取当前位置的元素数值
            printf("%d ", e);   //访问并打印当前获得的元素数值
        }
        printf("\n");
    }
    return OK;
}

//测试
int main(int argc, const char * argv[]) {
    BiTree T;
    int e;
    initTree(T);
    printf("初始化后的二叉树是否为空？（1是0否）：%d\n", isEmpty(T));
    creatBTree(T);
    printf("创建完成后二叉树是否为空？（1是0否)：%d\n", isEmpty(T));
    printf("前序遍历二叉树T：\n");
    preOrderTraverse(T);
    printf("中序遍历二叉树T：\n");
    inOrderTraverse(T);
    printf("后序遍历二叉树T：\n");
    postOrderTraverse(T);
    printf("层序遍历二叉树T：\n");
    levelOrderTraverse(T);
    getRoot(T, &e);
    printf("当前二叉树的根结点为：%d\n", e);
    printf("当前二叉树的深度为：%d\n", getDepth(T));
    e = getParent(T, 5);
    printf("结点5的parent为：%d\n", e);
    e = getLeftBrother(T, 5);
    printf("结点5的左兄弟为：%d\n", e);
    e = getRightBrother(T, 5);
    printf("结点5的右兄弟为：%d\n", e);
    e = getLeftChild(T, 5);
    printf("结点5的左孩子为：%d\n", e);
    e = getRightChild(T, 5);
    printf("结点5的右孩子为：%d\n", e);
    e = getValue(T, 4, 2);
    printf("获取第4层的第2个元素：%d\n", e);
    replace(T, 4, 2, 666);
    e = getValue(T, 4, 2);
    printf("将第4层的第2个元素替换为666后得：%d\n", e);
    printf("将二叉树清空后可得：\n");
    clearTree(T);
    levelOrderTraverse(T);
    return 0;
}
