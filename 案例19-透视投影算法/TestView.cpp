// TestView.cpp : implementation of the CTestView class
//

#include "stdafx.h"
#include "Test.h"
#include "TestDoc.h"
#include "TestView.h"
#include "math.h"
#define PI 3.1415926//Բ????
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
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(IDM_PLAY, OnPlay)
	ON_UPDATE_COMMAND_UI(IDM_PLAY, OnUpdatePlay)
	ON_COMMAND(ID_ONEPOINT, OnOnepoint)
	ON_COMMAND(ID_TWOPOINT, OnTwopoint)
	ON_COMMAND(ID_THREEPOINT, OnThreepoint)
	ON_WM_RBUTTONDOWN()
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
	bPlay=FALSE;
	R=1000.0;d=900.0;Phi=90.0;Theta=0.0;	
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

void CTestView::ReadPoint()//????
{
	//????????ά????(x,y,z),???????߳?Ϊ2a
	double a=150;	
	P[0].x=-a;P[0].y=-a;P[0].z=-a;
	P[1].x=+a;P[1].y=-a;P[1].z=-a;
	P[2].x=+a;P[2].y=+a;P[2].z=-a;
	P[3].x=-a;P[3].y=+a;P[3].z=-a;
	P[4].x=-a;P[4].y=-a;P[4].z=+a;
	P[5].x=+a;P[5].y=-a;P[5].z=+a;
	P[6].x=+a;P[6].y=+a;P[6].z=+a;
	P[7].x=-a;P[7].y=+a;P[7].z=+a;
}

void CTestView::ReadFace()//????
{
	//???Ķ??????????Ķ???????
	F[0].SetNum(4);F[0].vI[0]=4;F[0].vI[1]=5;F[0].vI[2]=6;F[0].vI[3]=7;//ǰ??
	F[1].SetNum(4);F[1].vI[0]=0;F[1].vI[1]=3;F[1].vI[2]=2;F[1].vI[3]=1;//????
	F[2].SetNum(4);F[2].vI[0]=0;F[2].vI[1]=4;F[2].vI[2]=7;F[2].vI[3]=3;//????
	F[3].SetNum(4);F[3].vI[0]=1;F[3].vI[1]=2;F[3].vI[2]=6;F[3].vI[3]=5;//????
	F[4].SetNum(4);F[4].vI[0]=2;F[4].vI[1]=3;F[4].vI[2]=7;F[4].vI[3]=6;//????
	F[5].SetNum(4);F[5].vI[0]=0;F[5].vI[1]=1;F[5].vI[2]=5;F[5].vI[3]=4;//????
}

void CTestView::InitParameter()//͸?ӱ任??????ʼ??
{	
	k[1]=sin(PI*Theta/180);
	k[2]=sin(PI*Phi/180);
	k[3]=cos(PI*Theta/180);
	k[4]=cos(PI*Phi/180);
	k[5]=k[2]*k[3];
	k[6]=k[2]*k[1];
	k[7]=k[4]*k[3];
	k[8]=k[4]*k[1];
}

void CTestView::PerProject(CP3 P)//͸?ӱ任
{
	CP3 ViewP;
	ViewP.x=k[3]*P.x-k[1]*P.z;//?۲?????ϵ??ά????
	ViewP.y=-k[8]*P.x+k[2]*P.y-k[7]*P.z;
	ViewP.z=-k[6]*P.x-k[4]*P.y-k[5]*P.z+R;
    ScreenP.x=d*ViewP.x/ViewP.z;//??Ļ????ϵ??ά????
	ScreenP.y=d*ViewP.y/ViewP.z;
}

void CTestView::DoubleBuffer()//˫????
{
	CDC* pDC=GetDC();
	CRect rect;//?????ͻ???
	GetClientRect(&rect);//???ÿͻ????Ĵ?С
	pDC->SetMapMode(MM_ANISOTROPIC);//pDC?Զ???????ϵ
	pDC->SetWindowExt(rect.Width(),rect.Height());//???ô??ڷ?Χ
	pDC->SetViewportExt(rect.Width(),-rect.Height());//x??ˮƽ???ң?y?ᴹֱ????
	pDC->SetViewportOrg(rect.Width()/2,rect.Height()/2);//??Ļ????Ϊԭ??
	CDC MemDC;//?ڴ?DC
	CBitmap NewBitmap,*pOldBitmap;//?ڴ??г???ͼ??????ʱλͼ
	MemDC.CreateCompatibleDC(pDC);//????????ĻpDC???ݵ?MemDC 
	NewBitmap.CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());//????????λͼ 
	pOldBitmap=MemDC.SelectObject(&NewBitmap); //??????λͼѡ??MemDC 
	MemDC.FillSolidRect(&rect,pDC->GetBkColor());//??ԭ???????????ͻ??????????Ǻ?ɫ 
	MemDC.SetMapMode(MM_ANISOTROPIC);//MemDC?Զ???????ϵ
	MemDC.SetWindowExt(rect.Width(),rect.Height());
	MemDC.SetViewportExt(rect.Width(),-rect.Height());
	MemDC.SetViewportOrg(rect.Width()/2,rect.Height()/2);
	DrawObject(&MemDC);
	pDC->BitBlt(-rect.Width()/2,-rect.Height()/2,rect.Width(),rect.Height(),&MemDC,-rect.Width()/2,-rect.Height()/2,SRCCOPY);//???ڴ?λͼ????????Ļ
	MemDC.SelectObject(pOldBitmap);//?ָ?λͼ
	NewBitmap.DeleteObject();//ɾ??λͼ
	ReleaseDC(pDC);//?ͷ?DC
}

void CTestView::DrawObject(CDC* pDC)//???????????߿?
{
	CP2 t;
	CLine *line=new CLine;
	for(int nFace=0;nFace<6;nFace++)//??ѭ??
	{		
		for(int nPoint=0;nPoint<F[nFace].vN;nPoint++)//????ѭ??
		{
			PerProject(P[F[nFace].vI[nPoint]]);
			if(0==nPoint)
			{
				line->MoveTo(pDC,ScreenP);
				t=ScreenP;
			}
			else
				line->LineTo(pDC,ScreenP);
		}
		line->LineTo(pDC,t);//?պ϶?????
	}
	delete line;
}

void CTestView::OnLButtonDown(UINT nFlags, CPoint point)//????????????
{
	// TODO: Add your message handler code here and/or call default
	R=R+100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnLButtonDown(nFlags, point);
}

void CTestView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	R=R-100;
	InitParameter();
	Invalidate(FALSE);
	CView::OnRButtonDown(nFlags, point);
}

void CTestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	if(!bPlay)
	{
		switch(nChar)
		{
		case VK_UP:
			Phi+=5;//?趨????
			break;
		case VK_DOWN:
			Phi-=5;
			break;
		case VK_LEFT:
			Theta+=5;
			break;
		case VK_RIGHT:
		    Theta-=5;
			break;
		default:
			break;	
		}
		InitParameter();
		Invalidate(FALSE);		
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTestView::OnTimer(UINT nIDEvent)//????ʱ?亯?? 
{
	// TODO: Add your message handler code here and/or call default
	Phi-=5;//?趨????
	Theta-=5;
	InitParameter();
	Invalidate(FALSE);	
	CView::OnTimer(nIDEvent);
}

BOOL CTestView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}

void CTestView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	// TODO: Add your specialized code here and/or call the base class
	ReadPoint();
	ReadFace();
	InitParameter();
}

void CTestView::OnPlay() //?˵?????
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->SetWindowText("????19??͸??ͼ?㷨");
	bPlay=bPlay?FALSE:TRUE;
	if (bPlay)//???ö?ʱ??
		SetTimer(1,150,NULL);	
	else
		KillTimer(1);
}

void CTestView::OnUpdatePlay(CCmdUI* pCmdUI) //?˵????ƺ???
{
	// TODO: Add your command update UI handler code here
	if(bPlay)
	{
		pCmdUI->SetCheck(TRUE);
		pCmdUI->SetText("ֹͣ");
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
		pCmdUI->SetText("??ʼ");
	}
}

void CTestView::OnOnepoint()  //һ??͸?Ӻ???
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->SetWindowText("????19??һ??͸??");
	KillTimer(1);
	bPlay=FALSE;
	Phi=90;Theta=0;
	InitParameter();
	Invalidate(FALSE);		
}

void CTestView::OnTwopoint()//????͸?Ӻ??? 
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->SetWindowText("????19??????͸??");
	KillTimer(1);
	bPlay=FALSE;
	Phi=90;Theta=30;
	InitParameter();
	Invalidate(FALSE);	
}

void CTestView::OnThreepoint()//????͸?Ӻ??? 
{
	// TODO: Add your command handler code here
	AfxGetMainWnd()->SetWindowText("????19??????͸??");
	KillTimer(1);
	bPlay=FALSE;
	Theta=45;Phi=45;
	InitParameter();
	Invalidate(FALSE);	
}


