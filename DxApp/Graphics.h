#pragma once

#include "DxUtil.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <vector>
#include <memory>
#include <random>
#include <DirectXMath.h>


class Graphics
{
public:
	Graphics(HWND hWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void BeginFrame(float red, float green, float blue) noexcept;
	void ClearBuffer() noexcept;
	void DrawIndexed(UINT count) noexcept( !IS_DEBUG );
	void SetProjection(DirectX::FXMMATRIX proj) noexcept;
	DirectX::XMMATRIX GetProjection() const noexcept;
	void SetCamera(DirectX::FXMMATRIX cam) noexcept;
	DirectX::XMMATRIX GetCamera() const noexcept;
	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetContext();
	void EnableImgui() noexcept;
	void DisableImgui() noexcept;
	bool IsImguiEnabled() const noexcept;
private:
	bool imguiEnabled = true;
	DirectX::XMMATRIX projection;
	DirectX::XMMATRIX camera;
	Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};

