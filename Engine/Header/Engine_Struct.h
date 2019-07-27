#ifndef Engine_Struct_h__
#define Engine_Struct_h__

namespace Engine 
{
	typedef struct tagVertex_Texture
	{
		D3DXVECTOR3			vPosition;
		D3DXVECTOR2			vTexUV;
	}VTXTEX;

	typedef struct tagPolygon16
	{
		unsigned short		_1, _2, _3;
	}POLYGON16;

	typedef struct tagView_Matrix
	{
		D3DXVECTOR3 m_vAt, m_vEye;
		D3DXVECTOR3 m_vAxisY = { 0.f,1.f,0.f };
	}DESC_VIEW;
	typedef struct tagProj_Matrix
	{
		int		m_iBackCX, m_iBackCY;		// â�� ũ�� -> â�� ũ���� ���� 800:800 => 1:1 800:600 -> �����������ä��Ϥ�
		float	m_fNear, m_fFar;			// ����ؾ��� ������ �ִ�Ÿ� : Far, �� �ٷ� �ձ����� �Ÿ� : Near
	}DESC_PROJ;


}

#endif   