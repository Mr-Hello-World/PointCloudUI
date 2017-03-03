#ifndef _3DKDTREE_H_
#define _3DKDTREE_H_

#define TYPE double

#include <iostream>


//-------------------------------
//     KD���ڵ�
//-------------------------------
typedef struct kdNode
{
	TYPE pos[3];  //�ڵ�����
	short plane;  //�ڵ�ķָ�ƽ��
	int id;       //��UCD�ļ���ʽ��ȡ�Ľڵ��ID
}kdNode;

//-------------------------------------------
//    KD��
//-------------------------------------------
class nNearestNodes;
class kdTree
{
public:
	//
	//  ���캯��
	//  nodes:�������ڵ���Ŀ�����������ڴ�ռ�
	//
	kdTree(const int nodes);
	kdTree(){}	//�޲ι��캯��
	//
	//  ��������
	//
	~kdTree();
	//
	//   �����д洢һ���ڵ�,����ȡ˳��洢��
	//
	inline void store(const TYPE xCoord,const TYPE yCoord,const TYPE zCoord,const int pId);
	inline void store(const TYPE coords[3],const int pId);

	//
	//  ƽ����
	//
	void treeBalance();

	//
	//  ��index��ʼ��������Ѱ���ڽ���
	//
	void locateNodes(nNearestNodes * const nNN,const int index)const;

	//
	//  
	//
	void balancePartition(kdNode** pBalanced,kdNode** pOriginal,const int index,const int start,const int end);

	//
	//
	//
	void medianPartition(kdNode** pOrig,const int start,const int end,const int median,const int axis);
protected:
	kdNode* kdNodes;

	int storedKDNodes;
	int halfStoredKDNodes;  //��Ҷ�ӽڵ���
	int maxNumOfNodes;

	double boundrayMin[3];  //�����������Сֵ
	double boundrayMax[3];  //������������ֵ��������ֵ�൱��������ά��İ�Χ��
};

//----------------------------------------
//   ����ٽڵ�
//----------------------------------------
class nNearestNodes
{
public:
	int max;       //����ٽڵ����Ŀ
	int found;     //�����������ҵ���nNN����Ŀ
	int got_Heap;  //Ѱ��nNNʱ�Ƿ��Ѿ�����  0��ʾû�н���
	double pos[3]; //ָ���������
	double* dist2; //�ҵ�����ٵ㵽ָ����ľ����ƽ��
	const kdNode** index;  //�ҵ�������ٵ�

	//
	//   ���캯��
	//
	nNearestNodes(const int maximum)
	{
		max = maximum;
		found = got_Heap = 0;
	}
	//
	//    ��������
	//
	~nNearestNodes()
	{
		delete[]dist2;
		delete[]index;
	}

	//dis �������������ֵ
	void setDistandIndx(double dis = 1.0)
	{
		dist2 = new double[max + 1];
		dist2[0] = dis * dis;   //��С���������ƽ��,С���������ĵ���Ϊ��Ҫ������
		//dist2[0] = dis;
		index = new const kdNode*[max + 1];
	}

	void setSearchPnt(const double x,const double y,const double z)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}
};

//-----------------------------------------------------------------
void kdTree::store(const TYPE xCoord,const TYPE yCoord,const TYPE zCoord,const int pId)
{
	const TYPE coords[3] = {xCoord,yCoord,zCoord};
	store(coords,pId);
}

void kdTree::store(const TYPE coords[3],const int pId)
{
	if(storedKDNodes > maxNumOfNodes)
	{
		std::cout << "No room for more nodes..." << std::endl;
		return;
	}

	storedKDNodes++;
	kdNode *const node = &kdNodes[storedKDNodes];
	for(int i = 0; i < 3; i++)
	{
		node->pos[i] = coords[i];

		if(node->pos[i] < boundrayMin[i])
			boundrayMin[i] = node->pos[i];
		if(node->pos[i] > boundrayMax[i])
			boundrayMax[i] = node->pos[i];
	}
	node->id = pId;
}

#endif