//=============================================================================
//
// ���C������ [main.h]
// Author : yutaka nakanishi
//
// �ŏI�X�V�� 4/14
//=============================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

//*****************************************************************************
// �C���N���[�h�t�@�C��
//*****************************************************************************
#include <windows.h>
#include "d3dx9.h"

#define DIRECTINPUT_VERSION (0x0800)    // �x���΍��p
#include "dinput.h"

//*****************************************************************************
// ���C�u�����̃����N
//*****************************************************************************
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "winmm.lib")

//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �Q�c�|���S�����_�t�H�[�}�b�g( ���_���W[2D] / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
// �R�c�|���S�����_�t�H�[�}�b�g( ���_���W[3D] / �@�� / ���ˌ� / �e�N�X�`�����W )
#define	FVF_VERTEX_3D	(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1)

#define SCREEN_WIDTH	(1280.0f)				// �E�C���h�E�̕�
#define SCREEN_HEIGHT	(720.0f)				// �E�C���h�E�̍���

#define SCENE_MAX		(10)


typedef enum
{
	MODE_TITLE=0,
	MODE_TUTORIAL,
	MODE_GAME,
	MODE_RESULT,
	MODE_MAX
}MODE;



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LPDIRECT3DDEVICE9 GetDevice(void);
//*****************************************************************************
//�\����
//*****************************************************************************
// ��L�Q�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	float rhw;				// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_2D;

// ��L�R�c�|���S�����_�t�H�[�}�b�g�ɍ��킹���\���̂��`
typedef struct
{
	D3DXVECTOR3 vtx;		// ���_���W
	D3DXVECTOR3 nor;		// �@���x�N�g��
	D3DCOLOR diffuse;		// ���ˌ�
	D3DXVECTOR2 tex;		// �e�N�X�`�����W
} VERTEX_3D;

typedef struct
{
	float vx;
	float vy;
	float vz;
}VECTOR;

typedef struct
{
	LPDIRECT3DTEXTURE9		g_pD3DTexture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff;	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	D3DXVECTOR3				g_pos;			// ���W
	D3DXVECTOR3				g_rot;			// �p�x
	D3DXVECTOR3				g_scl;			// �g�k
	VERTEX_3D*				pVtx;			// ���_�f�[�^�|�C���^�[
	//�}�g���b�N�X
	D3DXMATRIX				g_mtx;			//���[���h�}�g���b�N�X
	D3DXMATRIX mtxScl,mtxRot,mtxTranslate;	//�}�g���b�N�X���
	VECTOR					Speed;
}DEFAULT;

typedef struct
{
	BYTE r;
	BYTE g;
	BYTE b;
	BYTE a;
}COLORRGBA;



#endif