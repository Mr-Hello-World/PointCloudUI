#include "../KDTree/3dKDtree.h"

kdTree::kdTree(const int nodes)
{
	storedKDNodes = 0;
	maxNumOfNodes = nodes;

	kdNodes = new kdNode[maxNumOfNodes + 1];
	if(!kdNodes)
	{
		std::cout<<"��ʼ��kd��ʱ�ڴ������"<<std::endl;
		exit(-1);
	}

	boundrayMin[0] = boundrayMin[1] = boundrayMin[2] = 1e8f;
	boundrayMax[0] = boundrayMax[1] = boundrayMax[2] = -1e8f;
}

kdTree::~kdTree()
{
	delete [] kdNodes;
}

void kdTree::treeBalance()
{
	if(storedKDNodes > 1)
	{
		kdNode **pa1 = new kdNode*[storedKDNodes + 1];  //��֯�������ָ��
		kdNode **pa2 = new kdNode*[storedKDNodes + 1];  //ԭʼԪ�ص�ָ��

		for(int i =0; i <= storedKDNodes; i++)
			pa2[i] = &kdNodes[i];

		balancePartition(pa1, pa2, 1, 1, storedKDNodes);
		delete []pa2;

		//����������
		//__w64 int d, j = 1;                  // According to the warning given when 'int ' is used
		int d, j = 1; //jλ��Ԫ���Ѿ�ת����
		int foo = 1;  //fooNodes�洢��Ԫ�ص����λ��
		kdNode fooNodes = kdNodes[j];

		for(int i = 1; i <= storedKDNodes; i++)
		{
			d = pa1[j] - kdNodes;
			pa1[j] = NULL;

			if(d != foo)
				kdNodes[j] = kdNodes[d];
			else
			{
				kdNodes[j] = fooNodes;

				if(i < storedKDNodes)
				{
					for(; foo <= storedKDNodes; foo++)
						if(NULL != pa1[foo])
							break;

					fooNodes = kdNodes[foo];
					j = foo;
				}
				continue;
			}
			j = d;
		}
		delete []pa1;
	}
	halfStoredKDNodes = storedKDNodes/2 - 1;
}

void kdTree::locateNodes(nNearestNodes * const nNN,const int index)const
{
	const kdNode *p = &kdNodes[index];
	double dist1;

	if(index < halfStoredKDNodes)
	{
		dist1 = nNN->pos[p->plane] - p->pos[p->plane];

		if(0.0 < dist1)
		{
			locateNodes(nNN, 2 * index + 1);
			if(nNN->dist2[0] > dist1 * dist1)
				locateNodes(nNN, 2 * index);
		}
		else
		{
			locateNodes(nNN, 2 * index);
			if(nNN->dist2[0] > dist1 * dist1)
				locateNodes(nNN, 2 * index + 1);
		}//if
	}//if

	// �������
	dist1 = p->pos[0] - nNN->pos[0];
	double dist2 = dist1 * dist1;
	dist1 = p->pos[1] - nNN->pos[1];
	dist2 += dist1 * dist1;
	dist1 = p->pos[2] - nNN->pos[2];
	dist2 += dist1 * dist1;

	if(nNN->dist2[0] > dist2)
	{
		if(nNN->found < nNN->max)
		{
			nNN->found++;
			nNN->dist2[nNN->found] = dist2;
			nNN->index[nNN->found] = p;
		}
		else
		{
			int j, parent;
			if(0 == nNN->got_Heap)//�����󶥶�
			{
				double dst2;
				const kdNode *nd;
				int halfFound = nNN->found >> 1;

				for(int k = halfFound; k >= 1; k--)
				{
					parent = k;
					nd = nNN->index[k];
					dst2 = nNN->dist2[k];

					while(parent <= halfFound)
					{
						j = parent + parent;

						if(j < nNN->found && nNN->dist2[j] < nNN->dist2[j + 1])
							j ++;

						if(dst2 >= nNN->dist2[j])
							break;

						nNN->dist2[parent] = nNN->dist2[j];
						nNN->index[parent] = nNN->index[j];

						parent = j;
					}//while
					nNN->dist2[parent] = dst2;
					nNN->index[parent] = nd;
				}//for
				nNN->got_Heap = 1;
			}//if

			//����
			parent = 1;
			//if()
			j = 2;

			while(j <= nNN->found)
			{
				if(j < nNN->found && nNN->dist2[j] < nNN->dist2[j + 1])
					j++;

				if(dist2 > nNN->dist2[j])
					break;

				nNN->dist2[parent] = nNN->dist2[j];
				nNN->index[parent] = nNN->index[j];
				parent = j;
				j += j;
			}//while

			if((parent != 1)||(dist2 < nNN->dist2[parent]))
			{
				nNN->index[parent] = p;
				nNN->dist2[parent] = dist2;
			}
			nNN->dist2[0] = nNN->dist2[1];//??????
		}//else
	}//if	
}

#define swap(kdN,a,b){ kdNode* tmp = kdN[a]; kdN[a] = kdN[b]; kdN[b] = tmp;}

void kdTree::medianPartition(kdNode** pOrig,const int start,const int end,const int median,const int axis)
{
	int left = start;
	int right = end;

	while(right > left)
	{
		const TYPE v = pOrig[right]->pos[axis];

		int i = left - 1;
		int j = right;

		for(;;)
		{
			while(pOrig[++i]->pos[axis] < v);
			while(pOrig[--j]->pos[axis] > v && j > left);
			if(i >= j)
				break;

			swap(pOrig, i, j);
		}

		swap(pOrig, i, right);
		if(i >= median)
			right = i - 1;
		if(i <= median)
			left = i + 1;
	}
}
void kdTree::balancePartition(kdNode** pBalanced,kdNode** pOriginal,const int index,const int start,const int end)
{
	//����median��������ô������أ�����
	int median = 1;
	while((4 * median) <= (end - start + 1))
		median += median;  //median*=2;

	if((3 * median) <= (end - start +1))
	{
		median += median;
		median += start - 1;
	}
	else
		median = end - median + 1;

	// Ѱ�ҷָ����ݵ���
	int axis = 2;
	if((boundrayMax[0] - boundrayMin[0]) > (boundrayMax[1] - boundrayMin[1])&&
		(boundrayMax[0] - boundrayMin[0]) > (boundrayMax[2] - boundrayMin[2]))
		axis = 0;
	else if((boundrayMax[1] - boundrayMin[1]) > (boundrayMax[2] - boundrayMin[2]))
		axis = 1;

	// ��median�ָ�ڵ�
	medianPartition(pOriginal, start, end, median, axis);

	pBalanced[index] = pOriginal[median];
	pBalanced[index]->plane = axis;

	// ����ƽ����������
	if(median > start)
	{
		if(start < median - 1)
		{
			const double tmp = boundrayMax[axis];
			boundrayMax[axis] = pBalanced[index]->pos[axis];
			balancePartition(pBalanced, pOriginal, 2 * index, start, median - 1);
			boundrayMax[axis] = tmp;
		}
		else
			pBalanced[2 * index] = pOriginal[start];
	}
	if(median < end)
	{
		if(median + 1 < end)
		{
			const double tmp = boundrayMin[axis];
			boundrayMin[axis] = pBalanced[index]->pos[axis];
			balancePartition(pBalanced, pOriginal, 2 * index + 1, median + 1, end);
			boundrayMin[axis] = tmp;
		}
		else
			pBalanced[2 * index + 1] = pOriginal[end];
	}
}