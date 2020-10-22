#pragma once

// �ּ� ����

// ID3D11 : com Interface , ���������� ���

// device�� �ڿ��� buffer�� texture
// buffer�� ��� RAM���� VRAM���� ����
// Texture 1D,2D,3D, pixel,texel
// �ؽ�ó�� �ִ� �ڿ���
// 1. RenderTargetView		�׷��پ�, ��ȭ�� ������ (���� ����) : �׸� ���ִ¾�
// 2. ShaderResourceView	ȿ��??, �׷��� ī�带 �̿��ؼ� �ټ��մ� ȿ��, �ڿ�?? (�б� ����): �ִ°� ������ ���ڴ�
// 3. DepthStencilView		���̰����� �ִ� �ڿ� (3D�Ҷ� ���)
// 4. UnorderedAccessView	����������� �����ϴ� �ڿ� (�б�,���� �Ѵ� ��) 

// Device Context : DC
// ������ �׸��� �ſ� ��������.
// �� �ȿ� �ؿ��� ������� 
// Rendering Pipeline : �׸��� �ܰ�??
//						IA (Input Assembler(�Է� ������))
//					 	�׸��� ���� �ʿ��� �������� �־��ִ� �ܰ� 
//						VS (Vertex Shader)	����(Vertex)	Shader: �׷���ī�带 ������ �� �ִ� �Լ����� ����
//						�������� ����						
//						RS (Rasterizer Stage)
//						3D ������ 2D(ȭ��)�� ǥ���ϱ� ���� �ȼ�ȭ??
//						PS (Pixel Shader)
//						�ȼ����� ���� ( ���� ���� ���� �ٲ�� �� )
//						OM (Output Merger)
//						���������� RenderTagetView�� �׷��ִ� �ܰ�

// �츮�� �ڵ��� ���ִ°� Shader ���� �ֵ�	
// �������� ������ �Է����ִ°� �ۿ� ����

// DXGI ����Ʈ����� �ϵ����(�׷��� ī��) ���̿��� ������ , swapchain : ������۸��� ���� �ִ� ��, adapter : �׷��� ī��, output : �����
// SwapChain : ��ȭ���� �ϳ��� ����� �� ���� ������ �׸������� �յڷ� ���̴°� �Ⱥ��̰� �ϴµ�
//			   (����� ������ �Ⱥ���, �����̴°� �����) �̶� ��ӵ��ư��� ��

// Viewport : �׸� �����ȿ��� ȭ�鿡 ������ ���� 

// d3dxcolor : RGBA float 4��(16����Ʈ) ����ü (0 ���� 1������ ������ ���) ����ȭ����


/*
DXGI �⺻���� ��Ȱ
�׷���ī�� ������ ����
���÷��� ����� ����
�����ġ�� ����
����ü�� ����(���� ���۸�)
*/

/*
* Rasterizer State���� �ϴ� ��
* ������ �ʴ� ������Ƽ�� ����(��������, �ø�)
* ���� �׽�Ʈ??
* ���� ���̾ ���
* ������Ƽ����� ���� Ÿ�� ���� �ؼ� ������ ����
* ��Ƽ ���ø��̳� �� ����� ������ ���� ó��
* ��ó :
* https://m.blog.naver.com/PostView.nhn?blogId=sorkelf&logNo=40162947758&proxyReferer=https:%2F%2Fwww.google.com%2F
* 
*	����Ʈ 
* 	rasterizerDesc.AntialiasedLineEnable = false;
*	rasterizerDesc.CullMode = D3D11_CULL_BACK;
*	rasterizerDesc.DepthBias = 0;
*	rasterizerDesc.DepthBiasClamp = 0.0f;
*	rasterizerDesc.DepthClipEnable = true;
*	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
*	rasterizerDesc.FrontCounterClockwise = false;
*	rasterizerDesc.MultisampleEnable = false;
*	rasterizerDesc.ScissorEnable = false;
*	rasterizerDesc.SlopeScaledDepthBias = 0.0f;
* 
* 
*/