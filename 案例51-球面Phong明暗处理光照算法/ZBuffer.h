// ZBuffer.h: interface for the CZBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_)
#define AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Pi3.h"//三维点头文件
#include "Bucket.h"//桶头文件
#include "Vector.h"//矢量头文件
#include "Lighting.h"
#include "Material.h"

class CZBuffer  
{
public:
	CZBuffer();
    virtual ~CZBuffer();
	void CreateBucket();//创建桶
	void CreateEdge();//边表
	void AddEt(CAET *);//合并ET表
	void ETOrder();//ET表排序
	void Phong(CDC *,CP3,CLighting *,CMaterial *);//Phong填充函数
	void InitDeepBuffer(int,int,double);//初始化深度缓冲器
    CRGB Interpolation(double,double,double,CRGB,CRGB);//线性插值
	CVector Interpolation(double,double,double,CVector,CVector);//法矢线性插值
	void SetPoint(CPi3 *,CVector *,int);
	void ClearMemory();//清理内存
	void DeleteAETChain(CAET* pAET);//删除边表
protected:
	int PNum;//顶点个数
	CPi3 *P;//顶点数组
	CVector *N;//顶点的法矢量动态数组
	CAET *pHeadE,*pCurrentE,*pEdge;//有效边表结点指针
	CBucket *pCurrentB,*pHeadB;
	double **zBuffer;//缓深度冲区
	int Width,Height;//缓冲区参数
};

#endif // !defined(AFX_ZBUFFER_H__ED93E842_7399_49B8_B579_6A52FBA1289D__INCLUDED_)
