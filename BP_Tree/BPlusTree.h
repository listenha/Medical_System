/* BPlusTree.h

B+树定义文件，本程序实行一个简单的B+树

Definition (from http://www.seanster.com/BplusTree/BplusTree.html ):
(1) A B+ tree of order v consists of a root, internal nodes and leaves.
(2) The root my be either leaf or node with two or more children.
(3) Internal nodes contain between v and 2v keys, and a node with k keys has k + 1 children.
(4) Leaves are always on the same level.
(5) If a leaf is a primary index, it consists of a bucket of records, sorted by search key. If it is a secondary index, it will have many short records consisting of a key and a pointer to the actual record.

(1) 一个v阶的B+树由根结点、内部结点和叶子结点组成。
(2) 根结点可以是叶子结点，也可以是有两个或更多子树的内部结点。
(3) 每个内部结点包含v - 2v个键。如果一个内部结点包含k个键，则有且只有k+1个指向子树的指针。
(4) 叶子结点总是在树的同一层上。
(5) 如果叶子结点是主索引，它包含一组按键值排序的记录；如果叶子结点是从索引，它包含一组短记录，每个短记录包含一个键以及指向实际记录的指针。
(6) 内部结点的键值和叶子结点的数据值都是从小到大排序的。
(7) 在中间结点中，每个键的左子树中的所有的键都小于这个键，每个键的右子树中的所有的键都大于等于这个键。

*/

/* B+ 树的阶，即内部结点中键的最小数目v。
   也有些人把阶定义为内部结点中键的最大数目，即2v。
   一般而言，叶子结点中最大数据个数和内部结点中最大键个数是一样的，也是2v。(我想这样做的目的是为了把内部结点和叶子结点统一到同一个结构中吧)
*/
#define ORDER_V 2 /* 为简单起见，把v固定为2，实际的B+树v值应该是可配的。这里的v是内部节点中键的最小值 */

#define MAXNUM_KEY (ORDER_V * 2)        /* 内部结点中最多键个数，为2v */
#define MAXNUM_POINTER (MAXNUM_KEY + 1) /* 内部结点中最多指向子树的指针个数，为2v+1 */
#define MAXNUM_DATA (ORDER_V * 2)       /* 叶子结点中最多数据个数，为2v */

/* 键值的类型*/
typedef int KEY_TYPE; /* 为简单起见，定义为int类型，实际的B+树键值类型应该是可配的 */
/*备注： 为简单起见，叶子结点的数据也只存储键值*/

/* 结点类型 */
enum NODE_TYPE
{
    NODE_TYPE_ROOT = 1,     // 根结点
    NODE_TYPE_INTERNAL = 2, // 内部结点
    NODE_TYPE_LEAF = 3,     // 叶子结点
};

#define NULL 0
#define INVALID 0

#define FLAG_LEFT 1
#define FLAG_RIGHT 2

//Declare Registration datatype
class Registration;

/* 结点数据结构，为内部结点和叶子结点的父类 */
class CNode
{
public:
    CNode();
    virtual ~CNode();

    //获取和设置结点类型
    NODE_TYPE GetType() { return m_Type; }
    void SetType(NODE_TYPE type) { m_Type = type; }

    // 获取和设置有效数据个数
    int GetCount() { return m_Count; }
    void SetCount(int i) { m_Count = i; }

    // 获取和设置某个元素，对中间结点指键值，对叶子结点指数据
    virtual KEY_TYPE GetElement(int i) { return 0; }
    virtual void SetElement(int i, KEY_TYPE value) {}

    // 获取和设置某个指针，对中间结点指指针，对叶子结点无意义
    virtual CNode *GetPointer(int i) { return NULL; }
    virtual void SetPointer(int i, CNode *pointer) {}

    // 获取和设置父结点
    CNode *GetFather() { return m_pFather; }
    void SetFather(CNode *father) { m_pFather = father; }

    // 获取一个最近的兄弟结点
    CNode *GetBrother(int &flag);

    // 删除结点
    void DeleteChildren();

protected:
    NODE_TYPE m_Type; // 结点类型，取值为NODE_TYPE类型

    int m_Count; // 有效数据个数，对中间结点指键个数，对叶子结点指数据个数

    CNode *m_pFather; // 指向父结点的指针，标准B+树中并没有该指针，加上是为了更快地实现结点分裂和旋转等操作
};

/* 内部结点数据结构 */
class CInternalNode : public CNode
{
public:
    CInternalNode();
    virtual ~CInternalNode();

    // 获取和设置键值，对用户来说，数字从1开始，实际在结点中是从0开始的
    KEY_TYPE GetElement(int i)
    {
        if ((i > 0) && (i <= MAXNUM_KEY))
        {
            return m_Keys[i - 1];
        }
        else
        {
            return INVALID;
        }
    }

    void SetElement(int i, KEY_TYPE key)
    {
        if ((i > 0) && (i <= MAXNUM_KEY))
        {
            m_Keys[i - 1] = key;
        }
    }

    // 获取和设置指针，对用户来说，数字从1开始
    CNode *GetPointer(int i)
    {
        if ((i > 0) && (i <= MAXNUM_POINTER))
        {
            return m_Pointers[i - 1];
        }
        else
        {
            return NULL;
        }
    }

    void SetPointer(int i, CNode *pointer)
    {
        if ((i > 0) && (i <= MAXNUM_POINTER))
        {
            m_Pointers[i - 1] = pointer;
        }
    }

    // 在结点pNode上插入键value
    bool Insert(KEY_TYPE value, CNode *pNode);
    // 删除键value
    bool Delete(KEY_TYPE value);

    // 分裂结点
    KEY_TYPE Split(CInternalNode *pNode, KEY_TYPE key);
    // 结合结点(合并结点)
    bool Combine(CNode *pNode);
    // 从另一结点移一个元素到本结点
    bool MoveOneElement(CNode *pNode);

protected:
    KEY_TYPE m_Keys[MAXNUM_KEY];       // 键数组
    CNode *m_Pointers[MAXNUM_POINTER]; // 指针数组
};

/* 叶子结点数据结构 */
class CLeafNode : public CNode
{
public:
    CLeafNode();
    virtual ~CLeafNode();

    // 获取和设置数据
    KEY_TYPE GetElement(int i)
    {
        if ((i > 0) && (i <= MAXNUM_DATA))
        {
            return m_Datas[i - 1];
        }
        else
        {
            return INVALID;
        }
    }

    void SetElement(int i, KEY_TYPE data)
    {
        if ((i > 0) && (i <= MAXNUM_DATA))
        {
            m_Datas[i - 1] = data;
        }
    }

    // 获取和设置指针，对叶子结点无意义，只是实行父类的虚函数
    CNode *GetPointer(int i)
    {
        return NULL;
    }

    // 插入数据
    bool Insert(KEY_TYPE value, Registration *data); //modified
    // 删除数据
    bool Delete(KEY_TYPE value);

    // 分裂结点
    KEY_TYPE Split(CLeafNode *pNode);
    // 结合结点
    bool Combine(CLeafNode *pNode);

public:
    // 以下两个变量用于实现双向链表
    CLeafNode *m_pPrevNode; // 前一个结点
    CLeafNode *m_pNextNode; // 后一个结点

protected:
    KEY_TYPE m_Datas[MAXNUM_DATA]; // 数据数组
public:
    Registration *Reg_Datas[MAXNUM_DATA]; // modified
};

/* B+树数据结构 */
class BPlusTree
{
public:
    BPlusTree();
    virtual ~BPlusTree();

    // 查找指定的数据
    Registration *Search(KEY_TYPE data); //modified
    // 插入指定的数据
    bool Insert(KEY_TYPE data, Registration *Reg_data); //modified
    // 删除指定的数据
    bool Delete(KEY_TYPE data);

    // 清除树
    void ClearTree();

    // 打印树
    void PrintTree();

    // 旋转树
    BPlusTree *RotateTree();

    // 检查树是否满足B+树的定义
    bool CheckTree();

    void PrintNode(CNode *pNode);

    // 递归检查结点及其子树是否满足B+树的定义
    bool CheckNode(CNode *pNode);

    // 获取和设置根结点
    CNode *GetRoot()
    {
        return m_Root;
    }

    void SetRoot(CNode *root)
    {
        m_Root = root;
    }

    // 获取和设置深度
    int GetDepth()
    {
        return m_Depth;
    }

    void SetDepth(int depth)
    {
        m_Depth = depth;
    }

    // 深度加一
    void IncDepth()
    {
        m_Depth = m_Depth + 1;
    }

    // 深度减一
    void DecDepth()
    {
        if (m_Depth > 0)
        {
            m_Depth = m_Depth - 1;
        }
    }

public:
    // 以下两个变量用于实现双向链表
    CLeafNode *m_pLeafHead; // 头结点
    CLeafNode *m_pLeafTail; // 尾结点

protected:
    // 为插入而查找叶子结点
    CLeafNode *SearchLeafNode(KEY_TYPE data);
    //插入键到中间结点
    bool InsertInternalNode(CInternalNode *pNode, KEY_TYPE key, CNode *pRightSon);
    // 在中间结点中删除键
    bool DeleteInternalNode(CInternalNode *pNode, KEY_TYPE key);

    CNode *m_Root; // 根结点
    int m_Depth;   // 树的深度
};