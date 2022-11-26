#ifndef _dxrr
#define _dxrr
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dx10.h>
#include <d3dx10math.h>
#include "TerrenoRR.h"
#include "Agua.h"
#include "Camara.h"
#include "Billboard.h"
#include "ModeloRR.h"
#include "SkyDome.h"
#include "XACT3Util.h"
#include <time.h>
#include "GUI.h"
#include "Text.h"

class DXRR{	

private:
	int ancho;
	int alto;
public:	

	#pragma region Atributos publicos
	HINSTANCE hInstance;
	HWND hWnd;

	D3D_DRIVER_TYPE driverType;
	D3D_FEATURE_LEVEL featureLevel;

	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* d3dContext;
	IDXGISwapChain* swapChain;
	ID3D11RenderTargetView* backBufferTarget;

	ID3D11Texture2D* depthTexture;
	ID3D11DepthStencilView* depthStencilView;

	ID3D11DepthStencilState* depthStencilState;
	ID3D11DepthStencilState* depthStencilDisabledState;

	ID3D11BlendState *alphaBlendState, *commonBlendState;

	int frameBillboard;

	TerrenoRR *terreno = 0;
	Agua* lago;
	SkyDome *skydome = 0;
	BillboardRR* billboard[49] = { 0 };
	Camara *camara = 0;
	Light* light = 0;
	ModeloRR * bici = 0, * biciLejos = 0;
	//Modelos
	ModeloRR* llave = 0;
	ModeloRR* pelota = 0;
	ModeloRR* juego = 0;
	ModeloRR* casa = 0;
	ModeloRR* mesa = 0;
	ModeloRR* kiosko1 = 0;
	ModeloRR* kiosko2 = 0;
	ModeloRR* kiosko3 = 0;
	//Laberinto
	ModeloRR* laberinto = 0;
	
	//GUI
	GUI* vida3;

	//Texto
	Text* Coordenadas;

	float posGlobal[2];
	float izqder;
	float arriaba;
	float vel;
	float vel2;
	bool breakpoint;
	bool inFP = true;
	vector2 uv1[32];
	vector2 uv2[32];
	vector2 uv3[32];
	vector2 uv4[32];

	XACTINDEX cueIndex;
	CXACT3Util m_XACT3;
	#pragma endregion

    DXRR(HWND hWnd, int Ancho, int Alto)
	{
		#pragma region Inicializacion
			breakpoint = false;
			frameBillboard = 0;
			ancho = Ancho;
			alto = Alto;
			driverType = D3D_DRIVER_TYPE_NULL;
			featureLevel = D3D_FEATURE_LEVEL_11_0;
			d3dDevice = 0;
			d3dContext = 0;
			swapChain = 0;
			backBufferTarget = 0;
			IniciaD3D(hWnd);
			izqder = 0;
			arriaba = 0;
			billCargaFuego();
			posGlobal[0] = 0;
			posGlobal[1] = 0;
		#pragma endregion


		camara = new Camara(D3DXVECTOR3(-110,80,6), D3DXVECTOR3(0,80,0), D3DXVECTOR3(0,1,0), Ancho, Alto);
		light = new Light(-30.0f, -50.0f, -30.0f, 0.2f, 0.2f, 1.0f, 1.0f);
		terreno = new TerrenoRR(300, 300, d3dDevice, d3dContext);
		lago = new Agua(79, 111, d3dDevice, d3dContext);
		//skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"Starter_Content/SkyDome.png");
		skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"TextTerreno/Sky/SkyD3.png", L"TextTerreno/Sky/SkyT4_ED.jpg", L"TextTerreno/Sky/SkyN4_ED.jpg", light);

		billboard[0] = new BillboardRR(L"Assets/Billboards/fuego-anim.png",L"Assets/Billboards/fuego-anim-normal.png", d3dDevice, d3dContext, 5);

		
		

		//model = new ModeloRR(d3dDevice, d3dContext, "Assets/Cofre/Cofre.obj", L"Assets/Cofre/Cofre-color.png", L"Assets/Cofre/Cofre-spec.png", 0, 0);

		bici = new ModeloRR(d3dDevice, d3dContext, "Assets/Bici/Manubrio.obj", L"Assets/Bici/Bicicleta_Color.jpg", L"Assets/Bici/Bicicleta_Spec.jpg", 0, 0);
		biciLejos = new ModeloRR(d3dDevice, d3dContext, "Assets/Bici/Manubrio3erP.obj", L"Assets/Bici/Bicicleta_Color.jpg", L"Assets/Bici/Bicicleta_Spec.jpg", 0, 0);
		llave = new ModeloRR(d3dDevice, d3dContext, "Assets/Llave/Llave.obj", L"Assets/Llave/Llave Color.jpg", L"Assets/Llave/Llave Specular.jpg", 0, 0);
		pelota = new ModeloRR(d3dDevice, d3dContext, "Assets/Pelota/Pelota.obj", L"Assets/Pelota/Pelota Color.png", L"Assets/Pelota/Pelota Specular.jpg", 0, 0);
		juego = new ModeloRR(d3dDevice, d3dContext, "Assets/Juego/Juego.obj", L"Assets/Juego/Juego Color.jpg", L"Assets/Juego/Juego Specular.jpg",0, 0);
		casa = new ModeloRR(d3dDevice, d3dContext, "Assets/Casa/houseA_obj.obj", L"Assets/Casa/1casa.jpg", L"Assets/Casa/1casaS.jpg", -118, 98);
		mesa = new ModeloRR(d3dDevice, d3dContext, "Assets/mesita/mesita.obj", L"Assets/mesita/Default_albedo.jpg", L"Assets/mesita/Default_roughness.jpg", -138, 61);
		kiosko1 = new ModeloRR(d3dDevice, d3dContext, "Assets/Kiosko/Kiosko_1.obj", L"Assets/Kiosko/Kiosko_1 Color.png", L"Assets/Kiosko/Kiosko_1 Specular.png", -74, 124);
		kiosko2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Kiosko/Kiosko_2.obj", L"Assets/Kiosko/Kiosko_2 Color.png", L"Assets/Kiosko/Kiosko_2 Specular.png", -74, 124);
		kiosko3 = new ModeloRR(d3dDevice, d3dContext, "Assets/Kiosko/Kiosko_3.obj", L"Assets/Kiosko/Kiosko_3 Color.png", L"Assets/Kiosko/Kiosko_3 Specular.png", -74, 124);

		//Modelos para escenario principal
		laberinto = new ModeloRR(d3dDevice, d3dContext, "Assets/Laberinto/Laberinto.obj", L"Assets/Laberinto/LaberintoColor.jpg", L"Assets/Laberinto/LaberintoSpecular.jpg", 0, 0);
	//GUI
		vida3 = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/GUI/health_full.png");
	
	//Texto
		Coordenadas = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/GUI/font.jpg", XMFLOAT4(0.5f, 0.6f, 0.8f, 1.0f));
	
	}

	~DXRR()
	{
		LiberaD3D();
		m_XACT3.Terminate();
	}
	
	bool IniciaD3D(HWND hWnd)
	{
		this->hInstance = hInstance;
		this->hWnd = hWnd;

		//obtiene el ancho y alto de la ventana donde se dibuja
		RECT dimensions;
		GetClientRect(hWnd, &dimensions);
		unsigned int width = dimensions.right - dimensions.left;
		unsigned int heigth = dimensions.bottom - dimensions.top;

		//Las formas en como la pc puede ejecutar el DX11, la mas rapida es D3D_DRIVER_TYPE_HARDWARE pero solo se puede usar cuando lo soporte el hardware
		//otra opcion es D3D_DRIVER_TYPE_WARP que emula el DX11 en los equipos que no lo soportan
		//la opcion menos recomendada es D3D_DRIVER_TYPE_SOFTWARE, es la mas lenta y solo es util cuando se libera una version de DX que no sea soportada por hardware
		D3D_DRIVER_TYPE driverTypes[]=
		{
			D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP, D3D_DRIVER_TYPE_SOFTWARE
		};
		unsigned int totalDriverTypes = ARRAYSIZE(driverTypes);

		//La version de DX que utilizara, en este caso el DX11
		D3D_FEATURE_LEVEL featureLevels[]=
		{
			D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0
		};
		unsigned int totalFeaturesLevels = ARRAYSIZE(featureLevels);

		DXGI_SWAP_CHAIN_DESC swapChainDesc;
		ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
		swapChainDesc.BufferCount = 1;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.Height = heigth;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = true;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;

		HRESULT result;
		unsigned int driver = 0, creationFlags = 0;
		for(driver = 0; driver<totalDriverTypes; driver++)
		{
			result = D3D11CreateDeviceAndSwapChain(0, driverTypes[driver], 0,
				creationFlags, featureLevels, totalFeaturesLevels, 
				D3D11_SDK_VERSION, &swapChainDesc, &swapChain,
				&d3dDevice, &featureLevel, &d3dContext);

			if(SUCCEEDED(result))
			{
				driverType = driverTypes[driver];
				break;
			}
		}

		if(FAILED(result))
		{

			//Error al crear el Direct3D device
			return false;
		}
		
		ID3D11Texture2D* backBufferTexture;
		result = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&backBufferTexture);
		if(FAILED(result))
		{
			//"Error al crear el swapChainBuffer
			return false;
		}

		result = d3dDevice->CreateRenderTargetView(backBufferTexture, 0, &backBufferTarget);
		if(backBufferTexture)
			backBufferTexture->Release();

		if(FAILED(result))
		{
			//Error al crear el renderTargetView
			return false;
		}


		D3D11_VIEWPORT viewport;
		viewport.Width = (FLOAT)width;
		viewport.Height = (FLOAT)heigth;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		d3dContext->RSSetViewports(1, &viewport);

		D3D11_TEXTURE2D_DESC depthTexDesc;
		ZeroMemory(&depthTexDesc, sizeof(depthTexDesc));
		depthTexDesc.Width = width;
		depthTexDesc.Height = heigth;
		depthTexDesc.MipLevels = 1;
		depthTexDesc.ArraySize = 1;
		depthTexDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthTexDesc.SampleDesc.Count = 1;
		depthTexDesc.SampleDesc.Quality = 0;
		depthTexDesc.Usage = D3D11_USAGE_DEFAULT;
		depthTexDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthTexDesc.CPUAccessFlags = 0;
		depthTexDesc.MiscFlags = 0;
		
		result = d3dDevice->CreateTexture2D(&depthTexDesc, NULL, &depthTexture);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear la DepthTexture", MB_OK);
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
		ZeroMemory(&descDSV, sizeof(descDSV));
		descDSV.Format = depthTexDesc.Format;
		descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		descDSV.Texture2D.MipSlice = 0;

		result = d3dDevice->CreateDepthStencilView(depthTexture, &descDSV, &depthStencilView);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el depth stencil target view", MB_OK);
			return false;
		}

		d3dContext->OMSetRenderTargets(1, &backBufferTarget, depthStencilView);

		// Initialize XACT3
		bool compileResult = m_XACT3.Initialize();
		if (!compileResult) return false;
		compileResult = m_XACT3.LoadWaveBank(L"Audio\\Win\\WaveBank.xwb");
		if (!compileResult) return false;
		compileResult = m_XACT3.LoadSoundBank(L"Audio\\Win\\SoundBank.xsb");
		if (!compileResult) return false;


		srand(time(0));
		XACTINDEX cueIndex = rand() % (3 - 0 + 1) + 0;
		//XACTINDEX cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("ccr_bad_moon");
		m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);
		return true;			
		
	}

	void LiberaD3D(void)
	{
		if(depthTexture)
			depthTexture->Release();
		if(depthStencilView)
			depthStencilView->Release();
		if(backBufferTarget)
			backBufferTarget->Release();
		if(swapChain)
			swapChain->Release();
		if(d3dContext)
			d3dContext->Release();
		if(d3dDevice)
			d3dDevice->Release();

		if (light){
			delete light;
			light = 0;
		}
		if (camara) {
			delete camara;
			camara = 0;
		}

		#pragma region Liberacion modelos

			if (laberinto) {
				delete laberinto;
				laberinto = 0;
			}
			if (pelota) {
				delete pelota;
				pelota = 0;
			}
			if (juego) {
				delete juego;
				juego = 0;
			}
			if (casa) {
				delete casa;
				casa = 0;
			}
			if (mesa) {
				delete mesa;
				mesa = 0;
			}
			if (kiosko1) {
				delete kiosko1;
				kiosko1 = 0;
			}
			if (kiosko2) {
				delete kiosko2;
				kiosko2 = 0;
			}
			if (kiosko3) {
				delete kiosko3;
				kiosko3 = 0;
			}

			if (bici) {
				delete bici;
				bici = 0;
			}
			if (biciLejos) {
				delete biciLejos;
				biciLejos = 0;
			}

			if (llave) {
				delete llave;
				llave = 0;
			}
		#pragma endregion



		if (skydome) {
			delete skydome;
			skydome = 0;
		}

		if (terreno) {
			delete terreno;
			terreno = 0;
		}

		depthTexture = 0;
		depthStencilView = 0;
		d3dDevice = 0;
		d3dContext = 0;
		swapChain = 0;
		backBufferTarget = 0;
	}
	
	void Render(void)
	{
		float sphere[3] = { 0,0,0 };
		float prevPos[3] = { camara->posCam.x, camara->posCam.z, camara->posCam.z };
		static float angle = 0.0f;
		angle += izqder; //modificacion
		if (angle >= 360) angle = 0.0f;
		bool collide = false;

		static float neutralLightC[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		static float neutralLightD[3] = { 30.0f, 10.0f, 30.0f };

		int maxX = 63;
		int minX = -20;
		int maxZ = 120;
		int minZ = -120;
		static int posX[38] = { -200 };
		static int posZ[38] = { -200 };

		if (posX[0] == -200)
		{
			srand(time(0));
			for (int i = 0; i < 38; i++) {
				posX[i] = rand() % (maxX - minX + 1) + minX;
				posZ[i] = rand() % (maxZ - minZ + 1) + minZ;
			}
		}
		if( d3dContext == 0 )
			return;

		float clearColor[4] = { 0, 0, 0, 1.0f };
		d3dContext->ClearRenderTargetView( backBufferTarget, clearColor );
		d3dContext->ClearDepthStencilView( depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );
		camara->posCam.y = terreno->Superficie(camara->posCam.x, camara->posCam.z) + 5 ;

		float altura = terreno->Superficie(camara->gethdVeoX(), camara->gethdVeoZ()) +2;

		camara->UpdateCam(vel, vel2, arriaba, izqder, posGlobal, altura);

		skydome->Update(camara->vista, camara->proyeccion);

		float camPosXZ[2] = { camara->posCam.x, camara->posCam.z };
		stringstream ss;
		ss << camara->posCam.x;
		Coordenadas->DrawText(-0.95, 0.95, "X: " + ss.str(), 0.01);
		ss.str(std::string());
		ss << camara->posCam.z;
		Coordenadas->DrawText(-0.95, 0.85, "Z: " + ss.str(), 0.01);


		static float onda = 0.0;
		onda += 0.01;
		TurnOffDepth();
		skydome->Render(camara->posCam);
		TurnOnDepth();

		terreno->Draw(camara->vista, camara->proyeccion, light->GetDirection(), light->GetDiffuseColor(), camara->posCam);

		lago->Draw(camara->vista, camara->proyeccion, camara->posCam, onda, light->GetDirection(), light->GetDiffuseColor(), 79.3f, -3.0f, 111.1f);

		//TurnOnAlphaBlending();


		billboard[0]->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-11, -78, 4, 5, 1, 1, uv1, uv2, uv3, uv4, frameBillboard, 'D', neutralLightD, neutralLightC);

		
		

		////TurnOffAlphaBlending();  //antes habia en supercifie (100, 20)
		vida3->Draw(-0.86, -0.3);

		////(vita, proyecci�n, altura en Y, posici�n de la c�mara, fuerza especular, �ngulo de rotaci�n, angulo en que se rotar�, escala)
		if (inFP) {
			bici->setX(camara->gethdVeoX());
			bici->setZ(camara->gethdVeoZ());
			bici->rotation = (D3DXToRadian(-140.0f) + angle);
			bici->Draw(camara->vista, camara->proyeccion, altura, camara->posCam, 10.0f, bici->rotation + 0.9f, 'Y', 1, light->GetDirection(), light->GetDiffuseColor());
		}
		else {
			biciLejos->setX(camara->gethdVeoX());
			biciLejos->setZ(camara->gethdVeoZ());
			biciLejos->rotation = (D3DXToRadian(-140.0f) + angle);
			biciLejos->Draw(camara->vista, camara->proyeccion, altura, camara->posCam, 10.0f, biciLejos->rotation + 0.9f, 'Y', 1, light->GetDirection(), light->GetDiffuseColor());
		}


		llave->Draw(camara->vista, camara->proyeccion, terreno->Superficie(150, 20), camara->posCam, 10.0f, 0, 'A', 2, light->GetDirection(), light->GetDiffuseColor());
		pelota->Draw(camara->vista, camara->proyeccion, terreno->Superficie(300, 0), camara->posCam, 10.0f, 0, 'A', 2, light->GetDirection(), light->GetDiffuseColor());
		juego->Draw(camara->vista, camara->proyeccion, terreno->Superficie(200,0), camara->posCam, 10.0f, 0, 'A', 2, light->GetDirection(), light->GetDiffuseColor());
		casa->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 180, 'A', 0.4, light->GetDirection(), light->GetDiffuseColor());
		mesa->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0) +1.5, camara->posCam, 10.0f, 180, 'A', 0.05, light->GetDirection(), light->GetDiffuseColor());
		kiosko1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) +1, camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		kiosko2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) +1, camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		kiosko3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) +1, camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		laberinto->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0) + 4, camara->posCam, 10.0f, 0, 'A', 1, light->GetDirection(), light->GetDiffuseColor());



		//--------------------------------------------------COLISIONES------------------------------

					 //ESFERICAS--Chinga tu madre Hugo
					//if (isPointInsideSphere(camara->getPos(), pelota->getSphere(5)))
					//{
					// //MessageBox(hWnd, L"Colision", L"Advertencia", MB_OK);
					// camara->posCam = camara->pastPosCam;
					//}

							 //LINEALES
							 //***Collision(PX1, PX2, Pz1, Pz2, bool, int);***

									//Colisi�n de una piedra cerca del laberinto
								 //	CollisionX(-139, -97, -19, true, 1);
								 //
								 //	//Unos pinos por el laberinto
								 //	CollisionX(-139, -135, -29, true, 1);
								 //
								 //	//Otra roca enorme
								 //	CollisionX(-149, -100, -82, true, 1);

#pragma region Las colisiones de la entrada frente al juego, que por extra�a raz�n dejaron de jalar bien, aiuda
//Colisiones en X
		CollisionX(-34, 68, 68, 69, true, -1); //Pared interna de lab

		CollisionX(-89, -54, 68, 69, true, -1); //Pared interna de lab
		CollisionX(-89, 64, -86, -85, true, 1); //Pared interna de lab

		CollisionX(-34.8, 67, 72, 73, true, 1); //Pared EXTERNA de lab
		CollisionX(-94.6, -51, 72, 73, true, 1); //Pared EXTERNA de lab

		CollisionX(-50, -31, 52, 53, true, 1); //Pared cerca de salida de laberinto
		CollisionX(-54, -31, 47, 48, true, -1); //Pared cerca de salida

		CollisionX(-34.9, -15, 33, 34, true, 1);
		CollisionX(-70, -35, 13, 14, true, 1);

		CollisionX(-69, -50, 28, 29, true, -1);
		CollisionX(-69, -50, 33, 34, true, 1);

		CollisionX(-74, -31, 8, 9, true, -1);
		CollisionX(-31, -11, 27, 28, true, -1);

		CollisionX(-121, -94.7, 73, 74, true, 1); //Rocas cerca del laberinto



		//Colisiones en Z
		CollisionZ(-25, 69, -90, -89, true, 1); //Pared interna lab
		CollisionZ(-86, -49, -90, -89, true, 1); //Pared interna lab
		CollisionZ(-86, 67, 63, 64, true, -1); //Pared interna lab

		CollisionZ(53, 72, -50, -49, true, 1); //Pared cerca de salida
		CollisionZ(67, 72, -36, -35, true, -1); //Pared cerca de salida
		CollisionZ(49, 53, -30, -29, true, 1); //Pared cerca de salida
		CollisionZ(48, 68, -56, -55, true, -1); //Pared cerca de salida
		CollisionZ(13, 32.7, -36, -35, true, -1);

		CollisionZ(32, 68.5, -16, -15, true, -1);

		CollisionZ(12, 52.8, -70, -69, true, 1);
		CollisionZ(8.9, 52.8, -76, -75, true, -1);

		CollisionZ(9.41, 28.3, -30, -29, true, 1);
		CollisionZ(29.6, 68, -10, -9, true, 1);

		// CollisionX(-34, 68, 73, true, 1); //pared externa�
		// CollisionZ(69, 73, -36, true, -1); //Donde me muevo en X

//			CollisionX(-94, -54, 74, true, 1); //Pared externa de lab
//	CollisionX(-89, -52, 68, true, -1); //interna


	//CollisionZ(49, 72, -56, true, -1);
	 //CollisionZ(54, 71, -48, true, 1);
#pragma endregion
//--------------------------------------------------------------------

//Colisiones de las otras paredes, no todas tienen unu
   //CollisionZ(-86, 66, 64, true, -1);
   //CollisionZ(-86, 66, 64, true, 1);
	   //CollisionX(-93, 68, -92, true, -1); //este s� jala XD
	   //CollisionX(-92, 66, -83, true, 1); //Este no, son la misma pared

		swapChain->Present( 1, 0 );
	}

	void CollisionX(float P1, float P2, float P3, float P4, bool colision, int move)
	{
		if (colision)
		{
			if (camara->posCam.x > P1 && camara->posCam.x < P2 && camara->posCam.z > P3 && camara->posCam.z < P4)
				camara->posCam.z = camara->posCam.z + move; //Empuja en Z
		}

	}

	//Hace colisi�n en el eje Z y te empuja en X
	void CollisionZ(float P1, float P2, float P3, float P4, bool colision, int move)
	{
		if (colision)
		{
			if (camara->posCam.z > P1 && camara->posCam.z < P2 && camara->posCam.x > P3 && camara->posCam.x < P4)
				camara->posCam.x = camara->posCam.x + move; // empuja en X
		}

	}

	bool isPointInsideSphere(float* point, float* sphere) {
		bool collition = false;

		float distance = sqrt((point[0] - sphere[0]) * (point[0] - sphere[0]) +
			(point[1] - sphere[1]) * (point[1] - sphere[1]));

		if (distance < sphere[2])
			collition = true;
		return collition;
	}

	//Activa el alpha blend para dibujar con transparencias
	void TurnOnAlphaBlending()
	{
		float blendFactor[4];
		blendFactor[0] = 0.0f;
		blendFactor[1] = 0.0f;
		blendFactor[2] = 0.0f;
		blendFactor[3] = 0.0f;
		HRESULT result;

		D3D11_BLEND_DESC descABSD;
		ZeroMemory(&descABSD, sizeof(D3D11_BLEND_DESC));
		descABSD.RenderTarget[0].BlendEnable = TRUE;
		descABSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descABSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descABSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descABSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descABSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;

		result = d3dDevice->CreateBlendState(&descABSD, &alphaBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(alphaBlendState, blendFactor, 0xffffffff);
	}

	//Regresa al blend normal(solido)
	void TurnOffAlphaBlending()
	{
		D3D11_BLEND_DESC descCBSD;
		ZeroMemory(&descCBSD, sizeof(D3D11_BLEND_DESC));
		descCBSD.RenderTarget[0].BlendEnable = FALSE;
		descCBSD.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		descCBSD.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		descCBSD.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		descCBSD.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		descCBSD.RenderTarget[0].RenderTargetWriteMask = 0x0f;
		HRESULT result;

		result = d3dDevice->CreateBlendState(&descCBSD, &commonBlendState);
		if(FAILED(result))
		{
			MessageBox(0, L"Error", L"Error al crear el blend state", MB_OK);
			return;
		}

		d3dContext->OMSetBlendState(commonBlendState, NULL, 0xffffffff);
	}

	void TurnOnDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDSD;
		ZeroMemory(&descDSD, sizeof(descDSD));
		descDSD.DepthEnable = true;
		descDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDSD.StencilEnable=true;
		descDSD.StencilReadMask = 0xFF;
		descDSD.StencilWriteMask = 0xFF;
		descDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDSD, &depthStencilState);
		
		d3dContext->OMSetDepthStencilState(depthStencilState, 1);
	}

	void TurnOffDepth()
	{
		D3D11_DEPTH_STENCIL_DESC descDDSD;
		ZeroMemory(&descDDSD, sizeof(descDDSD));
		descDDSD.DepthEnable = false;
		descDDSD.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		descDDSD.DepthFunc = D3D11_COMPARISON_LESS;
		descDDSD.StencilEnable=true;
		descDDSD.StencilReadMask = 0xFF;
		descDDSD.StencilWriteMask = 0xFF;
		descDDSD.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		descDDSD.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		descDDSD.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		descDDSD.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		descDDSD.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

		d3dDevice->CreateDepthStencilState(&descDDSD, &depthStencilDisabledState);
		d3dContext->OMSetDepthStencilState(depthStencilDisabledState, 1);
	}

	void billCargaFuego()
	{
		uv1[0].u = .125;
		uv2[0].u = .125;
		uv3[0].u = 0;
		uv4[0].u = 0;

		uv1[0].v = .25;
		uv2[0].v = 0;
		uv3[0].v = 0;
		uv4[0].v = .25;


		for (int j = 0; j < 8; j++) {
			uv1[j].u = uv1[0].u + (j * .125);
			uv2[j].u = uv2[0].u + (j * .125);
			uv3[j].u = uv3[0].u + (j * .125);
			uv4[j].u = uv4[0].u + (j * .125);

			uv1[j].v = .25;
			uv2[j].v = 0;
			uv3[j].v = 0;
			uv4[j].v = .25;
		}
		for (int j = 0; j < 8; j++) {
			uv1[j + 8].u = uv1[0].u + (j * .125);
			uv2[j + 8].u = uv2[0].u + (j * .125);
			uv3[j + 8].u = uv3[0].u + (j * .125);
			uv4[j + 8].u = uv4[0].u + (j * .125);

			uv1[j + 8].v = .5;
			uv2[j + 8].v = .25;
			uv3[j + 8].v = .25;
			uv4[j + 8].v = .5;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 16].u = uv1[0].u + (j * .125);
			uv2[j + 16].u = uv2[0].u + (j * .125);
			uv3[j + 16].u = uv3[0].u + (j * .125);
			uv4[j + 16].u = uv4[0].u + (j * .125);

			uv1[j + 16].v = .75;
			uv2[j + 16].v = .5;
			uv3[j + 16].v = .5;
			uv4[j + 16].v = .75;
		}

		for (int j = 0; j < 8; j++) {
			uv1[j + 24].u = uv1[0].u + (j * .125);
			uv2[j + 24].u = uv2[0].u + (j * .125);
			uv3[j + 24].u = uv3[0].u + (j * .125);
			uv4[j + 24].u = uv4[0].u + (j * .125);

			uv1[j + 24].v = 1;
			uv2[j + 24].v = .75;
			uv3[j + 24].v = .75;
			uv4[j + 24].v = 1;
		}
	}

};
#endif