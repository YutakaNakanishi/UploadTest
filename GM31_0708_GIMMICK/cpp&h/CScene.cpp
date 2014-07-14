//=============================================================================
//
// CRender�N���X [CScene.cpp]
// Author : ���� �T
//
// �ŏI�X�V�� 4/21
//=============================================================================
//=============================================================================
// �C���N���[�h
//=============================================================================
#include "CScene.h"
#include "CInputKeyboad.h"
//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
CScene* CScene::m_pCur[NUM_PRIORITY]={NULL};
CScene* CScene::m_pTop[NUM_PRIORITY]={NULL};
BOOL g_PauseFlag=FALSE;


//=============================================================================
// �R���X�g���N�^
//=============================================================================
CScene::CScene(int nPriority,OBJTYPE Type)
{
	m_ObjType=Type;
	m_nPriority=nPriority;
	LinkList();
	m_bDelete=false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CScene::~CScene()
{

}


//=============================================================================
// ���X�g�ɒǉ�
//=============================================================================
void CScene::LinkList()
{
	//���������N����Ăւ�Ƃ�
	if(m_pTop[m_nPriority]==NULL)
	{
		//��[�ƏI�[�������ɂ���B
		m_pTop[m_nPriority]=this;
		m_pCur[m_nPriority]=this;
		//������prev�Ǝ�����Next��NULL�������
		this->m_pPrev=NULL;
		this->m_pNext=NULL;
	}
	//��ł������N����Ƃ�����
	else
	{
		//�����̑O�̃|�C���^��prev�ɓ����
		this->m_pPrev=m_pCur[m_nPriority];
		//�I�[��next�������ɂ���
		m_pCur[m_nPriority]->m_pNext=this;
		//�I�[�������ɓh��ւ���
		m_pCur[m_nPriority]=this;
		//�����͍Ō�ɂ���̂�next��NULL
		this->m_pNext=NULL;
	}
}

void CScene::UnlinkList()
{
	if(m_pTop[m_nPriority]!=this)
	{
		//�����̑O�̃|�C���^�[�̎��������̎��ɂ���B
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
		//�����̎��̃|�C���^�[�̑O�������̑O�ɂ���B
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
		//�S�I�u�W�F�N�g���X�V
		for(int i=0;i<NUM_PRIORITY;i++)
		{
			pScene=m_pTop[i];
			while(pScene)
			{
				pScene->Update();
				pScene=pScene->m_pNext;
			}
		}
		//�폜�t���O�������Ă���I�u�W�F�N�g������
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
			//�����Ȃ�����NULL�������Ă���̂Ń��[�v���甲����
			pScene=m_pTop[i];
		}
	}
}

void CScene::Release(void)
{
	m_bDelete=true;
}


//