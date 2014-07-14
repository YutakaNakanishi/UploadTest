//=============================================================================
//
// CRenderクラス [CScene.cpp]
// Author : 中西 裕
//
// 最終更新日 4/21
//=============================================================================
//=============================================================================
// インクルード
//=============================================================================
#include "CScene.h"
#include "CInputKeyboad.h"
//=============================================================================
//グローバル変数
//=============================================================================
CScene* CScene::m_pCur[NUM_PRIORITY]={NULL};
CScene* CScene::m_pTop[NUM_PRIORITY]={NULL};
BOOL g_PauseFlag=FALSE;


//=============================================================================
// コンストラクタ
//=============================================================================
CScene::CScene(int nPriority,OBJTYPE Type)
{
	m_ObjType=Type;
	m_nPriority=nPriority;
	LinkList();
	m_bDelete=false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{

}


//=============================================================================
// リストに追加
//=============================================================================
void CScene::LinkList()
{
	//何もリンクされてへんとき
	if(m_pTop[m_nPriority]==NULL)
	{
		//先端と終端を自分にする。
		m_pTop[m_nPriority]=this;
		m_pCur[m_nPriority]=this;
		//自分のprevと自分のNextにNULLをいれる
		this->m_pPrev=NULL;
		this->m_pNext=NULL;
	}
	//一つでもリンクされとったら
	else
	{
		//自分の前のポインタをprevに入れる
		this->m_pPrev=m_pCur[m_nPriority];
		//終端のnextを自分にする
		m_pCur[m_nPriority]->m_pNext=this;
		//終端を自分に塗り替える
		m_pCur[m_nPriority]=this;
		//自分は最後にいるのでnextはNULL
		this->m_pNext=NULL;
	}
}

void CScene::UnlinkList()
{
	if(m_pTop[m_nPriority]!=this)
	{
		//自分の前のポインターの次を自分の次にする。
		this->m_pPrev->m_pNext=this->m_pNext;
	}
	else
	{
		m_pTop[m_nPriority]=this->m_pNext;
		if(m_pTop[m_nPriority])
		{
			m_pTop[m_nPriority]->m_pPrev=NULL;
		}
	}
	if(m_pCur[m_nPriority]!=this)
	{
		//自分の次のポインターの前を自分の前にする。
		this->m_pNext->m_pPrev=this->m_pPrev;
	}
	else
	{
		m_pCur[m_nPriority]=this->m_pPrev;
		if(m_pCur[m_nPriority])
		{
			m_pCur[m_nPriority]->m_pNext=NULL;
		}
	}

}


void CScene::UpdateAll()
{
	CScene *pScene=NULL;
	CScene *pNext=NULL;
	
	if(!g_PauseFlag)
	{
		if(CInputKeyboard::GetTrig(DIK_P))
	{
		g_PauseFlag=true;
		}
		//全オブジェクトを更新
		for(int i=0;i<NUM_PRIORITY;i++)
		{
			pScene=m_pTop[i];
			while(pScene)
			{
				pScene->Update();
				pScene=pScene->m_pNext;
			}
		}
		//削除フラグが立っているオブジェクトを消す
		for(int i=0;i<NUM_PRIORITY;i++)
		{
			pScene=m_pTop[i];
			while(pScene)
			{
				pNext=pScene->m_pNext;
				if(pScene->m_bDelete)
				{
				
					pScene->UnlinkList();
					delete pScene;
				
				}
				pScene=pNext;
			}
		}
	}
	else
	{
		if(CInputKeyboard::GetTrig(DIK_P))
		{
			g_PauseFlag=false;
		}
	}
	
}

void CScene::DrawAll()
{
	CScene *pScene=NULL;
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		pScene=m_pTop[i];
		while(pScene)
		{
			pScene->Draw();
			pScene=pScene->m_pNext;
		}
	}
}

void CScene::ReleaseAll(void)
{
	CScene *pScene=NULL;
	for(int i=0;i<NUM_PRIORITY;i++)
	{
		pScene=m_pTop[i];
		while(pScene)
		{
			pScene->Uninit();
			pScene->UnlinkList();
			delete pScene;
			//何もない時はNULLが入っているのでループから抜ける
			pScene=m_pTop[i];
		}
	}
}

void CScene::Release(void)
{
	m_bDelete=true;
}


//