// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "math.h"
#define Round(d) int(floor(d+0.5))//��������궨��
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	//{{AFX_MSG_MAP(CTestView)
	ON_COMMAND(IDM_DRAWPIC, OnDrawpic)
	ON_COMMAND(ID_TLEFT, OnLeft)
	ON_COMMAND(ID_TRIGHT, OnRight)
	ON_COMMAND(ID_TUP, OnUp)
	ON_COMMAND(ID_TDOWN, OnDown)
	ON_COMMAND(ID_SINCREASE, OnIncrease)
	ON_COMMAND(ID_SDECREASE, OnDecrease)
	ON_COMMAND(ID_RESET, OnReset)
	ON_COMMAND(ID_TBACK, OnBack)
	ON_COMMAND(ID_TFRONT, OnFront)
	ON_COMMAND(ID_RXAXIS, OnRxaxis)
	ON_COMMAND(ID_RYAXIS, OnRyaxis)
	ON_COMMAND(ID_RZAXIS, OnRzaxis)
	ON_COMMAND(ID_RXOY, OnRxoy)
	ON_COMMAND(ID_RYOZ, OnRyoz)
	ON_COMMAND(ID_RXOZ, OnRzox)
	ON_COMMAND(ID_SXDIRECTIONPLUS, OnSxdirectionplus)
	ON_COMMAND(ID_SYDIRECTIONPLUS, OnSydirectionplus)
	ON_COMMAND(ID_SZDIRECTIONNEG, OnSzdirectionneg)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestView construction/destruction

CTestView::CTestView()
{
	// TODO: add construction code here
}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestView drawing

void CTestView::OnDraw(CDC* pDC)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here	
	DoubleBuffer();
}

/////////////////////////////////////////////////////////////////////////////
// CTestView printing

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestView diagnostics

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestView message handlers
void CTestView::ReadPoint()//���
{
	double a=100;//������߳�Ϊa
	//�������ά����(x,y,z)
	P[0].x=0;P[0].y=0;P[0].z=0;
	P[1].x=a;P[1].y=0;P[1].z=0;
	P[2].x=a;P[2].y=a;P[2].z=0;
	P[3].x=0;P[3].y=a;P[3].z=0;
	P[4].x=0;P[4].y=0;P[4].z=a;
	P[5].x=a;P[5].y=0;P[5].z=a;
	P[6].x=a;P[6].y=a;P[6].z=a;
	P[7].x=0;P[7].y=a;P[7].z=a;
}

void CTestView::ReadFace()//���
{
	//��ı�������Ķ�����
	F[0].SetNum(4);F[0].vI[0]=4;F[0].vI[1]=5;F[0].vI[2]=6;F[0].vI[3]=7;//ǰ��
	F[1].SetNum(4);F[1].vI[0]=0;F[1].vI[1]=3;F[1].vI[2]=2;F[1].vI[3]=1;//����
	F[2].SetNum(4);F[2].vI[0]=0;F[2].vI[1]=4;F[2].vI[2]=7;F[2].vI[3]=3;//����
	F[3].SetNum(4);F[3].vI[0]=1;F[3].vI[1]=2;F[3].vI[2]=6;F[3].vI[3]=5;//����
	F[4].SetNum(4);F[4].vI[0]=2;F[4].vI[1]=3;F[4].vI[2]=7;F[4].vI[3]=6;//����
	F[5].SetNum(4);F[5].vI[0]=0;F[5].vI[1]=1;F[5].vI[2]=5;F[5].vI[3]=4;//����
}

void CTestView::DoubleBuffer()//˫����
{
	CDC* pDC=GetDC();
	GetClientRect(&rect);//��ÿͻ����Ĵ�С
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC�Զ�������ϵ
	pDC->SetWindowExt(rect.Width(),rect.Height());//���ô��ڷ�Χ
	pDC->SetViewportExt(rect.Width(),-rect.Height());//x��ˮƽ���ң�y�ᴹֱ����
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//��Ļ����Ϊԭ��
	CDC MemDC;//�ڴ�DC
	CBitmap NewBitmap,*pOldBitmap;//�ڴ��г���ͼ�����ʱλͼ
	MemDC.CreateCompatibleDC(pDC);//��������ĻpDC���ݵ�MemDC 
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//��������λͼ 
	pOldBitmap=MemDC.SelectObject(&NewBitmap); //������λͼѡ��MemDC 
	MemDC.FillSolidRect(&rect,pDC->GetBkColor());//��ԭ���������ͻ����������Ǻ�ɫ
	MemDC.SetMapMode(MM_ANISOTROPIC);//MemDC�Զ�������ϵ
	MemDC.SetWindowExt(rect.Width(),rect.Height());
	MemDC.SetViewportExt(rect.Width(),-rect.Height());
	MemDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	DrawObject(&MemDC);
	pDC->BitBlt(-rect.Width()/2,-rect.Height()/2,rect.Width(),rect.Height(),&MemDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//���ڴ�λͼ��������Ļ
	MemDC.SelectObject(pOldBitmap);//�ָ�λͼ
	NewBitmap.DeleteObject();//ɾ��λͼ
	ReleaseDC(pDC);//�ͷ�DC	
}

void CTestView::ObliqueProject(CP3 p)//б�Ȳ�任
{
	ScreenP.x=p.x-p.z/sqrt(2);
	ScreenP.y=p.y-p.z/sqrt(2);	
}

void CTestView::DrawObject(CDC *pDC)//����ͼ��
{
	CLine *line=new CLine;//��������ϵ
	line->MoveTo(pDC,0,0);//����x��
	line->LineTo(pDC,rect.Width()/2,0);
	pDC->TextOut(rect.Width()/2-20,-20,"x");
	line->MoveTo(pDC,0,0);//����y��
	line->LineTo(pDC,0,rect.Height()/2);
	pDC->TextOut(-20,rect.Height()/2-20,"y");
	line->MoveTo(pDC,0,0);//����z��
	line->LineTo(pDC,-rect.Width()/2,-rect.Width()/2);
	pDC->TextOut(-rect.Height()/2-20,-rect.Height()/2+20,"z");
	pDC->TextOut(10,-10,"O");
	DrawPolygon(pDC,line);
	delete line;
}

void CTestView::DrawPolygon(CDC *pDC,CLine *line)//�����������߿�ģ��
{
	for(int nFace=0;nFace<6;nFace++)
	{
		CP2 t;	
		for(int nVertex=0;nVertex<F[nFace].vN;nVertex++)//����ѭ��
		{
			ObliqueProject(P[F[nFace].vI[nVertex]]);//б�Ȳ�ͶӰ
			if(0==nVertex)
			{
				line->MoveTo(pDC,ScreenP.x,ScreenP.y);
				t=ScreenP;
			}
			else
				line->LineTo(pDC,ScreenP.x,ScreenP.y);
		}
		line->LineTo(pDC,t.x,t.y);//�պ϶����
	}
}

void CTestView::OnDrawpic() 
{
	// TODO: Add your command handler code here
	MessageBox("��ʹ��ͼ�갴ť������ά���α任","��ʾ",MB_OK);
}

void CTestView::OnLeft()//����ƽ�� 
{
	// TODO: Add your command handler code here
	trans.Translate(-10,0,0);
	Invalidate(FALSE);
}

void CTestView::OnRight()//����ƽ�� 
{
	// TODO: Add your command handler code here
	trans.Translate(10,0,0);
	DoubleBuffer();
}

void CTestView::OnUp()//����ƽ��  
{
	// TODO: Add your command handler code here
	trans.Translate(0,10,0);
	Invalidate(FALSE);	
}

void CTestView::OnDown()//����ƽ�� 
{
	// TODO: Add your command handler code here
    trans.Translate(0,-10,0);
	Invalidate(FALSE);	
}

void CTestView::OnFront()//��ǰƽ�� 
{
	// TODO: Add your command handler code here
	trans.Translate(0,0,10);
	Invalidate(FALSE);	
}

void CTestView::OnBack()//���ƽ�� 
{
	// TODO: Add your command handler code here
	trans.Translate(0,0,-10);
	Invalidate(FALSE);	
}

void CTestView::OnIncrease()//�ȱȷŴ�  
{
	// TODO: Add your command handler code here
    trans.Scale(2,2,2);
	Invalidate(FALSE);	
}

void CTestView::OnDecrease()//�ȱ���С 
{
	// TODO: Add your command handler code here
    trans.Scale(0.5,0.5,0.5);
	Invalidate(FALSE);	
}

void CTestView::OnRxaxis()//��x����ת 
{
	// TODO: Add your command handler code here
	trans.RotateX(30,P[0]);
	Invalidate(FALSE);
}

void CTestView::OnRyaxis()//��y����ת  
{
	// TODO: Add your command handler code here
	trans.RotateY(30,P[0]);
	Invalidate(FALSE);
}

void CTestView::OnRzaxis()//��z����ת  
{
	// TODO: Add your command handler code here
	trans.RotateZ(30,P[0]);
	Invalidate(FALSE);
}

void CTestView::OnRxoy()//����xOy�淴�� 
{
	// TODO: Add your command handler code here
	trans.ReflectXOY();
	Invalidate(FALSE);
}

void CTestView::OnRyoz()//����yOz�淴�� 
{
	// TODO: Add your command handler code here
	trans.ReflectYOZ();
	Invalidate(FALSE);
}

void CTestView::OnRzox()//����zOx�淴��  
{
	// TODO: Add your command handler code here
	trans.ReflectZOX();
	Invalidate(FALSE);
}

void CTestView::OnSxdirectionplus()//��x��������� 
{
	// TODO: Add your command handler code here
	trans.ShearX(1,1);
	Invalidate(FALSE);	
}

void CTestView::OnSydirectionplus()//��y���������  
{
	// TODO: Add your command handler code here
	trans.ShearY(1,1);
	Invalidate(FALSE);	
}

void CTestView::OnSzdirectionneg()//��z��������� 
{
	// TODO: Add your command handler code here
	trans.ShearZ(1,1);
	Invalidate(FALSE);	
}

void CTestView::OnReset()//��λ 
{
	// TODO: Add your command handler code here
	ReadPoint();
	Invalidate(FALSE);	
}

void CTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	ReadPoint();
	ReadFace();
	trans.SetMat(P,8);
}














