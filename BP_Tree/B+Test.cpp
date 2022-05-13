#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../code/Data_Structure.h"
#include "BPlusTree.cpp"

// �������һ����
void Test1(BPlusTree *pTree, int count)
{
    pTree->ClearTree();

    // srand( (unsigned)time( NULL ) );//����һ�����ӣ������Ҫ������ܣ���Ѵ˾仰ע�͵�
    for (int i = 0; i < count; i++)
    {
        int x = rand() % 999 + 1;
        (void)pTree->Insert(x, NULL); //
    }

    printf("successed!\n");
}

// �����в���ĳ����
void Test2(BPlusTree *pTree, int data)
{
    // char sPath[255] = {
    //     0,
    // };

    Registration *r = pTree->Search(data);
    if (r == NULL)
    {
        cout << "Search failed!" << endl;
        return;
    }

    cout << "key=" << data << " Reg_id=" << r->reg_id << endl;
    
}

// �����в���ĳ����
void Test3(BPlusTree *pTree, int data, Registration *Reg)
{
    bool success = pTree->Insert(data, Reg);
    if (true == success)
    {
        printf("\nsuccessed!\n");
    }
    else
    {
        printf("\nfailed!\n");
    }
}

// ������ɾ��ĳ����
void Test4(BPlusTree *pTree, int data)
{
    bool success = pTree->Delete(data);
    if (true == success)
    {
        printf("\nsuccessed!\n");
    }
    else
    {
        printf("\nfailed!\n");
    }
}

// // ����������ת
// BPlusTree *Test5(BPlusTree *pTree)
// {
//     BPlusTree *pNewTree = pTree->RotateTree();
//     delete pTree;
//     printf("\nsuccessed!\n");
//     return pNewTree;
// }

// ��ӡ
void Test6(BPlusTree *pTree)
{
    pTree->PrintTree();
}

// �������м��
void Test7(BPlusTree *pTree)
{
    bool success = pTree->CheckTree();
    if (true == success)
    {
        printf("\nsuccessed!\n");
    }
    else
    {
        printf("\nfailed!\n");
    }
}


int main(int argc, char *argv[])
{
    BPlusTree *pTree = new BPlusTree;

    int x = 1;
    int y = 0;
    Registration *n = NULL;
    
    while (0 != x)
    {
        printf("\n\n");
        printf("    *******************************************************************\n");
        printf("    *           ��ӭ����B+����ʾ������ѡ����Ӧ���ܡ�                *\n");
        printf("    *           1���������һ��B+����                                 *\n");
        printf("    *           2����B+���в���һ������                               *\n");
        printf("    *           3����B+���в���һ����(Reg=NULL)��                     *\n");
        printf("    *           4����B+����ɾ��һ������                               *\n");
        // printf("    *           5����B+����ת����������ƽ�⣻                         *\n");
        printf("    *           6����ʾ����B+����                                     *\n");
        printf("    *           7���������B+����                                     *\n");
        printf("    *           0���˳�����                                         *\n");
        printf("    *           11.Test(Insert 16 Reg information);                  *\n");
        printf("    *           12.Clear Tree;                                        *\n");
        printf("    *******************************************************************\n");
        printf("\n    ����ѡ���ǣ�");

        scanf("%d", &x);
        switch (x)
        {
        case 1:
            printf("���������ݸ���(10-150)��");
            scanf("%d", &y);
            Test1(pTree, y);
            break;

        case 2:
            printf("������Ҫ���ҵ���ֵ��");
            scanf("%d", &y);
            Test2(pTree, y);
            break;

        case 3:
            printf("������Ҫ�������ֵ��ע����Ϣ��");
            scanf("%d", &y);
            Test3(pTree, y, n);
            break;

        case 4:
            printf("������Ҫɾ������ֵ��");
            scanf("%d", &y);
            Test4(pTree, y);
            break;

        // case 5:
        //     pTree = Test5(pTree);
        //     break;

        case 6:
            Test6(pTree);
            break;

        case 7:
            Test7(pTree);
            break;

        case 0:
            delete pTree;
            return 0;
            break;

        case 11:
        {
            Registration *r[16];
            int key[16] = {8, 14, 2, 15, 3, 1, 16, 6, 5, 27, 37, 18, 25, 7, 13, 20};
            for (int i = 0; i < 16; i++)
            {
                r[i] = new Registration;
                r[i]->reg_id = i;
                pTree->Insert(key[i], r[i]);
                cout << "Insert " << key[i] << endl;
            }
            for (int i = 0; i < 16; i++)
            {
                cout << r[i]->reg_id << endl;
            }
            
            break;
        }
        case 12:
        {
            pTree->ClearTree();
            break;
        }
        // case 17: (in test_Vaccination_System.cpp)
        // {
        //     int d[21] = {0,11,21,31,41,51,61,71,81,91,100,4,14,24,75,95,34,74,72,3,8};
        //     for (int i = 0; i < 21; i++)
        //     {
        //         system.Reg_List.Delete(d[i]);
        //         system.Reg_List.PrintTree();
        //     }
        //     break;
        // }
        default:
            break;
        }
    }

    delete pTree;
    return 0;
}