//=============================================================================
//
// ���f������ [camera.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
class CCamera
{
public:
	//�R���X�g���N�^
	CCamera();
	//�f�X�g���N�^
	~CCamera();
	//������
	HRESULT Init(void);
	//�I��
	void Uninit(void);
	//�X�V
	void Update(void);
	//�J�����Z�b�g
	void SetCamera(LPDIRECT3DDEVICE9 pDevice);
	//��]�p�擾
	static D3DXVECTOR3 GetRot(void);
	//�s��Q�b�g
	static D3DXMATRIX GetMtxView(void);
private:
	D3DXVECTOR3				m_posCameraP;		//���_
	D3DXVECTOR3				m_posCameraR;		//�����_
	D3DXVECTOR3				m_vecCameraU;		//������x�N�g��
	static D3DXVECTOR3		m_rotCamera;		//�J�����̌���(��]�p)
	D3DXVECTOR3				m_posCameraPDest;
	D3DXVECTOR3				m_posCameraRDest;
	D3DXVECTOR3				m_rotDestCamera;
	//�}�g���b�N�X	
	static D3DXMATRIX		m_mtxView;			//�r���[�}�g���b�N�X
	D3DXMATRIX				m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3				m_vecDir;
	float					m_fAngle;			//�p�x
	float					m_fLength;			//����
	float					m_fradian;			//���a
};
	#endif
	