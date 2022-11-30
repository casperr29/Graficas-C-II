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

	int TotalKeys = 0;
	bool key1 = false;
	bool key2 = false;
	bool key3 = false;
	int vida = 5;

	bool pinchos1 = false;
	bool pinchos2 = false;
	bool pinchos3 = false;
	bool pinchos4 = false;
	bool pinchos5 = false;

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
	ModeloRR* llave2 = 0;
	ModeloRR* llave3 = 0;
	ModeloRR* pelota = 0;
	ModeloRR* juego = 0;
	ModeloRR* casa = 0;
	ModeloRR* mesa = 0;
	ModeloRR* kiosko1 = 0;
	ModeloRR* kiosko2 = 0;
	ModeloRR* kiosko3 = 0;
	ModeloRR* pinos = 0;
	ModeloRR* rocas = 0;
	ModeloRR* banca = 0;
	ModeloRR* lampara = 0;
	ModeloRR* plano = 0;

	//Interactuables
	ModeloRR* pincho1 = 0;
	ModeloRR* pincho2 = 0;
	ModeloRR* pincho3 = 0;
	ModeloRR* pincho4 = 0;
	ModeloRR* pincho5 = 0;

	//Laberinto
	ModeloRR* laberinto = 0;
	ModeloRR* puerta = 0;
	
	//GUI
	GUI* vida3;
	GUI* Ganaste;
	GUI* Perdiste;
	GUI* Tiempo;
	GUI* Llave;
	GUI* PaperUI;

	GUI * BarraVida5;
	GUI * BarraVida4;
	GUI * BarraVida3;
	GUI * BarraVida2;
	GUI * BarraVida1;
	GUI * BarraVida0; //cuando morimos xd


	//Texto
	Text* Coordenadas;
	Text* CuentaRegresiva;
	Text* TiempoMuestra;
	Text* TiempoMuestraGanar;
	Text* TotalK;
	Text* TextoGanador;
	Text* TextoGanador2;

	float posGlobal[2];
	float izqder;
	float arriaba;
	float vel;
	float vel2;
	bool breakpoint;
	bool inFP = true;
	bool ReadPaper;
	int MePega;
	bool MusicaWin;
	bool I_Win;
	float TotTime;


	//Para el tiempo
	float segundos;
	float TimeShow;
	float TimeWinShow;

	vector2 uv1[32];
	vector2 uv2[32];
	vector2 uv3[32];
	vector2 uv4[32];

	XACTINDEX cueIndex;
	CXACT3Util m_XACT3;

	XACTINDEX MusicWin;
	XACTINDEX Item;
	XACTINDEX YouLose;
	XACTINDEX Hit;

	CXACT3Util m_InteractivoXACT3;

	#pragma endregion

    DXRR(HWND hWnd, int Ancho, int Alto)
	{
		#pragma region Inicializacion
			breakpoint = false;
			segundos = 301;
			TimeShow = 3;
			TimeWinShow = 1.5;
			ReadPaper = false;
			MusicaWin = false;
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
			MePega = 0;

			I_Win = false;
			TotTime = 0; 
		#pragma endregion

			                                                  //0, 80, 0
          //**Esta es la posición donde es el final
		//camara = new Camara(D3DXVECTOR3(-199.52,80,-49.39), D3DXVECTOR3(10,80,-40), D3DXVECTOR3(0,1,0), Ancho, Alto);

         //Aquí donde comenzaría, se puede cambiar si gustan
		camara = new Camara(D3DXVECTOR3(-39.794, 80, 196.667), D3DXVECTOR3(400, 80, 0), D3DXVECTOR3(0, 1, 0), Ancho, Alto);

		light = new Light(-30.0f, -50.0f, -30.0f, 0.2f, 0.2f, 1.0f, 1.0f);
		terreno = new TerrenoRR(480, 480, d3dDevice, d3dContext);
		lago = new Agua(100, 100, d3dDevice, d3dContext);
		//skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"Starter_Content/SkyDome.png");
		skydome = new SkyDome(32, 32, 100.0f, &d3dDevice, &d3dContext, L"TextTerreno/Sky/SkyD3.png", L"TextTerreno/Sky/SkyT4_ED.jpg", L"TextTerreno/Sky/SkyN4_ED.jpg", light);
		//billboard[0] = new BillboardRR(L"Assets/Billboards/fuego-anim.png",L"Assets/Billboards/fuego-anim-normal.png", d3dDevice, d3dContext, 5);

		billboard[0] = new BillboardRR(L"Assets/Billboards/Mountain1.png", L"Assets/Billboards/Mountain1Normal.png", d3dDevice, d3dContext, 1);
		billboard[1] = new BillboardRR(L"Assets/Billboards/Mountain1.png", L"Assets/Billboards/Mountain1Normal.png", d3dDevice, d3dContext, 1);
		billboard[2] = new BillboardRR(L"Assets/Billboards/Mountain1.png", L"Assets/Billboards/Mountain1Normal.png", d3dDevice, d3dContext, 1);
		billboard[3] = new BillboardRR(L"Assets/Billboards/Mountain1.png", L"Assets/Billboards/Mountain1Normal.png", d3dDevice, d3dContext, 1);
		billboard[4] = new BillboardRR(L"Assets/Billboards/Mountain1.png", L"Assets/Billboards/Mountain1Normal.png", d3dDevice, d3dContext, 1);
		billboard[5] = new BillboardRR(L"Assets/Billboards/Mountain2.png", L"Assets/Billboards/Mountain2Normal.png", d3dDevice, d3dContext, 1);
		billboard[6] = new BillboardRR(L"Assets/Billboards/Mountain2.png", L"Assets/Billboards/Mountain2Normal.png", d3dDevice, d3dContext, 1);
		billboard[7] = new BillboardRR(L"Assets/Billboards/Mountain3.png", L"Assets/Billboards/Mountain3Normal.png", d3dDevice, d3dContext, 1);
		billboard[8] = new BillboardRR(L"Assets/Billboards/Mountain3.png", L"Assets/Billboards/Mountain3Normal.png", d3dDevice, d3dContext, 1);
		billboard[9] = new BillboardRR(L"Assets/Billboards/Mountain3.png", L"Assets/Billboards/Mountain3Normal.png", d3dDevice, d3dContext, 1);


		//model = new ModeloRR(d3dDevice, d3dContext, "Assets/Cofre/Cofre.obj", L"Assets/Cofre/Cofre-color.png", L"Assets/Cofre/Cofre-spec.png", 0, 0);
      #pragma region MODELOS CARGADOS AQUÍ
		bici = new ModeloRR(d3dDevice, d3dContext, "Assets/Bici/Manubrio.obj", L"Assets/Bici/Bicicleta_Color.jpg", L"Assets/Bici/Bicicleta_Spec.jpg", 0, 0);
		biciLejos = new ModeloRR(d3dDevice, d3dContext, "Assets/Bici/Manubrio3erP.obj", L"Assets/Bici/Bicicleta_Color.jpg", L"Assets/Bici/Bicicleta_Spec.jpg", 0, 0);
		llave = new ModeloRR(d3dDevice, d3dContext, "Assets/Llave/Llave.obj", L"Assets/Llave/Llave Color.jpg", L"Assets/Llave/Llave Specular.jpg", -92, 30);
		llave2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Llave/Llave2.obj", L"Assets/Llave/Llave Color.jpg", L"Assets/Llave/Llave Specular.jpg", 78, 89);
		llave3 = new ModeloRR(d3dDevice, d3dContext, "Assets/Llave/Llave3.obj", L"Assets/Llave/Llave Color.jpg", L"Assets/Llave/Llave Specular.jpg", -32, -116);
		pelota = new ModeloRR(d3dDevice, d3dContext, "Assets/Pelota/Pelota.obj", L"Assets/Pelota/Pelota Color.png", L"Assets/Pelota/Pelota Specular.jpg", 0, 0);
		juego = new ModeloRR(d3dDevice, d3dContext, "Assets/Juego/Juego.obj", L"Assets/Juego/Juego Color.jpg", L"Assets/Juego/Juego Specular.jpg",0, 0);
		casa = new ModeloRR(d3dDevice, d3dContext, "Assets/Casa/houseA_obj.obj", L"Assets/Casa/1casa.jpg", L"Assets/Casa/1casaS.jpg", -118, 98);
		mesa = new ModeloRR(d3dDevice, d3dContext, "Assets/mesita/mesita.obj", L"Assets/mesita/Default_albedo.jpg", L"Assets/mesita/Default_roughness.jpg", -138, 61);
		kiosko1 = new ModeloRR(d3dDevice, d3dContext, "Assets/Kiosko/Kiosko_1.obj", L"Assets/Kiosko/Kiosko_1 Color.png", L"Assets/Kiosko/Kiosko_1 Specular.png", -74, 124);
		kiosko2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Kiosko/Kiosko_2.obj", L"Assets/Kiosko/Kiosko_2 Color.png", L"Assets/Kiosko/Kiosko_2 Specular.png", -74, 124);
		kiosko3 = new ModeloRR(d3dDevice, d3dContext, "Assets/Kiosko/Kiosko_3.obj", L"Assets/Kiosko/Kiosko_3 Color.png", L"Assets/Kiosko/Kiosko_3 Specular.png", -74, 124);
		pinos = new ModeloRR(d3dDevice, d3dContext, "Assets/Pinos/Pinos.obj", L"Assets/Pinos/Pinos_Color.png", L"Assets/Pinos/Pinos Specular.jpg", 0, 0);
		rocas = new ModeloRR(d3dDevice, d3dContext, "Assets/Rocas/Roca.obj", L"Assets/Rocas/Roca Color.jpg", L"Assets/Rocas/Roca Specular.jpg", 0, 0);
		banca = new ModeloRR(d3dDevice, d3dContext, "Assets/Banca/Banca.obj", L"Assets/Banca/Banca Color.png", L"Assets/Banca/Banca Specular.png", 0, 0);
		lampara = new ModeloRR(d3dDevice, d3dContext, "Assets/Lamparas/Lamparas.obj", L"Assets/Lamparas/Lampara.jpg", L"Assets/Lamparas/Lampara Specular.jpg", 0, 0);

		//interactuable
		pincho1 = new ModeloRR(d3dDevice, d3dContext, "Assets/Pinchos/Pincho1.obj", L"Assets/Pinchos/Pinchos Color.jpg", L"Assets/Pinchos/Pinchos Specular.jpg", 65, 79);
		pincho2 = new ModeloRR(d3dDevice, d3dContext, "Assets/Pinchos/Pincho2.obj", L"Assets/Pinchos/Pinchos Color.jpg", L"Assets/Pinchos/Pinchos Specular.jpg", 40, 90);
		pincho3 = new ModeloRR(d3dDevice, d3dContext, "Assets/Pinchos/Pincho3.obj", L"Assets/Pinchos/Pinchos Color.jpg", L"Assets/Pinchos/Pinchos Specular.jpg", 25, 95);
		pincho4 = new ModeloRR(d3dDevice, d3dContext, "Assets/Pinchos/Pincho4.obj", L"Assets/Pinchos/Pinchos Color.jpg", L"Assets/Pinchos/Pinchos Specular.jpg", 89, 96);
		pincho5 = new ModeloRR(d3dDevice, d3dContext, "Assets/Pinchos/Pincho5.obj", L"Assets/Pinchos/Pinchos Color.jpg", L"Assets/Pinchos/Pinchos Specular.jpg", 6, 83);

		//plano = new ModeloRR(d3dDevice, d3dContext, "Assets/Plano/Plano.obj", L"Assets/Kiosko/Kiosko_3 Color.png", L"Assets/Kiosko/Kiosko_3 Specular.png", 0, 0);
		//Modelos para escenario principal
		laberinto = new ModeloRR(d3dDevice, d3dContext, "Assets/Laberinto/Laberinto.obj", L"Assets/Laberinto/LaberintoColor.jpg", L"Assets/Laberinto/LaberintoSpecular.jpg", 0, 0);
		puerta = new ModeloRR(d3dDevice, d3dContext, "Assets/Puerta/Puerta.obj", L"Assets/Puerta/Puerta Color.png", L"Assets/Puerta/Puerta Specular.png", 0, 0);

      #pragma endregion 

	   //GUI
	   Ganaste = new GUI(d3dDevice, d3dContext, 1.85, 1.6, L"Assets/GUI/Interface/GANASTE.png");
	   Perdiste = new GUI(d3dDevice, d3dContext, 1.80, 1.5, L"Assets/GUI/Interface/PERDISTE.png");
	   Tiempo = new GUI(d3dDevice, d3dContext, 1.85, 1.6, L"Assets/GUI/Interface/TIEMPO.png");
	   Llave = new GUI(d3dDevice, d3dContext, 0.13, 0.08, L"Assets/GUI/Llave.png");
	   PaperUI = new GUI(d3dDevice, d3dContext, 1.55, 1.4, L"Assets/GUI/Interface/Objetivos.png");


		//Cuando te vayas quedando sin vida 
		BarraVida5 = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/GUI/BarraVidas/Vida_5.png");
		BarraVida4 = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/GUI/BarraVidas/Vida_4.png");
		BarraVida3 = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/GUI/BarraVidas/Vida_3.png");
		BarraVida2 = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/GUI/BarraVidas/Vida_2.png");
		BarraVida1 = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/GUI/BarraVidas/Vida_1.png");
		BarraVida0 = new GUI(d3dDevice, d3dContext, 0.15, 0.26, L"Assets/GUI/BarraVidas/Vida_0.png");


	
	   //Texto
		Coordenadas = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/GUI/font.jpg", XMFLOAT4(0.5f, 0.6f, 0.8f, 1.0f));
		CuentaRegresiva = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/GUI/font.jpg", XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

		TiempoMuestra = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/GUI/font.jpg", XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		TiempoMuestraGanar = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/GUI/font.jpg", XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
		TotalK = new Text(d3dDevice, d3dContext, 3.6, 1.2, L"Assets/GUI/font.jpg", XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		TextoGanador = new Text(d3dDevice, d3dContext, 5.6, 3.2, L"Assets/GUI/font.jpg", XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		TextoGanador2 = new Text(d3dDevice, d3dContext, 5.6, 3.2, L"Assets/GUI/font.jpg", XMFLOAT4(0.0f, 0.7f, 0.0f, 1.0f));
    }

	~DXRR()
	{
		LiberaD3D();
		m_XACT3.Terminate();
		m_InteractivoXACT3.Terminate();
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
		compileResult = m_XACT3.LoadWaveBank(L"sInteractive\\Win\\WaveBank.xwb");
		if (!compileResult) return false;
		compileResult = m_XACT3.LoadSoundBank(L"sInteractive\\Win\\SoundBank.xsb");
		if (!compileResult) return false;


		srand(time(0));
		//XACTINDEX cueIndex = rand() % (3 - 0 + 1) + 0;
		XACTINDEX cueIndex = m_XACT3.m_pSoundBank->GetCueIndex("Forest 1");
		m_XACT3.m_pSoundBank->Play(cueIndex, 0, 0, 0);



		////INICIALIZAMOS NUESTROS SONIDOS INTERACTIVOS
		//bool Compilado = m_InteractivoXACT3.Initialize();
		//if (!Compilado) return false;
		//Compilado = m_InteractivoXACT3.LoadWaveBank(L"InteractiveS\\Win\\MyBank.xwb");
		//if (!Compilado) return false;
		//compileResult = m_InteractivoXACT3.LoadSoundBank(L"InteractiveS\\Win\\SoundBank.xsb");
		//if (!Compilado) return false;

		
		

		//MusicWin = m_InteractivoXACT3.m_pSoundBank->GetCueIndex("VictoryMusic");
		//YouLose = m_InteractivoXACT3.m_pSoundBank->GetCueIndex("YouLose");
		//Item = m_InteractivoXACT3.m_pSoundBank->GetCueIndex("GrabItem");
		//Hit = m_InteractivoXACT3.m_pSoundBank->GetCueIndex("Golpe");

		
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

			if (llave2) {
				delete llave2;
				llave2 = 0;
			}

			if (llave3) {
				delete llave3;
				llave3 = 0;
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
		//Trabaja el XACT
		m_XACT3.DoWork();
		m_InteractivoXACT3.DoWork();

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

		
		
		
		

		static float onda = 0.0;
		onda += 0.01;
		TurnOffDepth();
		skydome->Render(camara->posCam);
		TurnOnDepth();

		terreno->Draw(camara->vista, camara->proyeccion, light->GetDirection(), light->GetDiffuseColor(), camara->posCam);

		lago->Draw(camara->vista, camara->proyeccion, camara->posCam, onda, light->GetDirection(), light->GetDiffuseColor(), 150.0f, -9.0f, 150.1f);

		//TurnOnAlphaBlending();
		/*billboard[0]->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-11, -78, 4, 5, 1, 1, uv1, uv2, uv3, uv4, frameBillboard, 'D', neutralLightD, neutralLightC);*/

		billboard[0]->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-235.0f, 200.0f, -5.0f,
			60, 1, 1, 0, 0, 0, 0, 0, 'S', light->GetDirection(), light->GetDiffuseColor(), 'Y', 0);
		billboard[1]->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-240.0f, 100.0f, -5.0f,
			60, 1, 1, 0, 0, 0, 0, 0, 'S', light->GetDirection(), light->GetDiffuseColor(), 'Y', 0);
		billboard[2]->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-235.0f, 0.0f, -5.0f,
			60, 1, 1, 0, 0, 0, 0, 0, 'S', light->GetDirection(), light->GetDiffuseColor(), 'Y', 0);
		billboard[3]->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-240.0f, -100.0f, -5.0f,
			60, 1, 1, 0, 0, 0, 0, 0, 'S', light->GetDirection(), light->GetDiffuseColor(), 'Y', 0);
		billboard[4]->Draw(camara->vista, camara->proyeccion, camara->posCam,
			-235.0f, -200.0f, -5.0f,
			60, 1, 1, 0, 0, 0, 0, 0, 'S', light->GetDirection(), light->GetDiffuseColor(), 'Y', 0);
		billboard[5]->Draw(camara->vista, camara->proyeccion, camara->posCam,
			200.0f, 240.0f, -15.0f,
			60, 1, 1, 0, 0, 0, 0, 0, 'S', light->GetDirection(), light->GetDiffuseColor(), 'Y', 360);
		billboard[6]->Draw(camara->vista, camara->proyeccion, camara->posCam,
			90.0f, 240.0f, -20.0f,
			60, 1, 1, 0, 0, 0, 0, 0, 'S', light->GetDirection(), light->GetDiffuseColor(), 'Y', 360);
		billboard[7]->Draw(camara->vista, camara->proyeccion, camara->posCam,
			235.0f, 200.0f, -5.0f,
			60, 1, 1, 0, 0, 0, 0, 0, 'S', light->GetDirection(), light->GetDiffuseColor(), 'Y', 15);
		billboard[8]->Draw(camara->vista, camara->proyeccion, camara->posCam,
			235.0f, 150.0f, -5.0f,
			60, 1, 1, 0, 0, 0, 0, 0, 'S', light->GetDirection(), light->GetDiffuseColor(), 'Y', 10);


		////(vita, proyección, altura en Y, posición de la cámara, fuerza especular, ángulo de rotación, angulo en que se rotará, escala)
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

		
		pelota->Draw(camara->vista, camara->proyeccion, terreno->Superficie(300, 0), camara->posCam, 10.0f, 0, 'A', 2, light->GetDirection(), light->GetDiffuseColor());
		juego->Draw(camara->vista, camara->proyeccion, terreno->Superficie(200,0), camara->posCam, 10.0f, 0, 'A', 2, light->GetDirection(), light->GetDiffuseColor());
		casa->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 0, 'A', 1, light->GetDirection(), light->GetDiffuseColor());
		mesa->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0) + 1.5, camara->posCam, 10.0f, 0, 'A', 1, light->GetDirection(), light->GetDiffuseColor());
		kiosko1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		kiosko2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		kiosko3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		pinos->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		rocas->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		banca->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		lampara->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		//plano->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20) + 1, camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());

		//interactuable
		/*pincho1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		pincho2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		pincho3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		pincho4->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		pincho5->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		*/

		laberinto->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0) + 4, camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
		
		stringstream ss_textoFinal;
		string sTiempo;
		//float camPosXZ[2] = { camara->posCam.x, camara->posCam.z };
		//stringstream ss;
		//ss << camara->posCam.x;
		//Coordenadas->DrawText(-0.95, 0.95, "X: " + ss.str(), 0.01);
		//ss.str(std::string());
		//ss << camara->posCam.z;
		//Coordenadas->DrawText(-0.95, 0.85, "Z: " + ss.str(), 0.01);


		if (TotalKeys != 3)
		{
			puerta->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0) + 4, camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
			CollisionZ(-75, -43, -135, -134, true, 1);
		}
		else
		{
			CollisionZ(-75, -43, -135, -134, false, 1);
			//Poner el otro modelo de la puerta abierta
		}

		//Leer los objetivos
		if (ReadPaper == true)
		{
			PaperUI->Draw(-0.28, 0.33);
			m_XACT3.m_pSoundBank->Stop(7, 0);
			m_XACT3.m_pSoundBank->Play(7, 0, 0, 0);
		}
		//--------------------------------------------------COLISIONES------------------------------

		 //ESFERICAS
		//if (isPointInsideSphere(camara->getPos(), pelota->getSphere(5)))
		//{
		// //MessageBox(hWnd, L"Colision", L"Advertencia", MB_OK);
		// camara->posCam = camara->pastPosCam;
		//}
		

		//if (TotalKeys == 3)
		//{
		//	I_Win = true;
		//}

	    
        #pragma region Cuando ganas pasa esto
		//COLISIÓN DE GANADOR
		
		//CollisionWin(-70,-42, -140 , -139, true); 
		
		if (camara->posCam.z > -72  && camara->posCam.z<-42 && camara->posCam.x > -228 && camara->posCam.x < -132)
		{
			
			if (TimeWinShow >= 0 && TotalKeys == 3)
			{
				
				MusicaWin = true;
				if (MusicaWin == true &&
					camara->posCam.z > -72 && camara->posCam.z<-42 && camara->posCam.x > -228 && camara->posCam.x < -124)
				{
					m_XACT3.m_pSoundBank->Stop(0, 0);
					m_XACT3.m_pSoundBank->Play(0, 0, 0, 0);
				}
				TiempoMuestraGanar->Time(TimeShow);
				Ganaste->Draw(-0.28, 0.4);
				m_XACT3.m_pSoundBank->Stop(0, 0);
				m_XACT3.m_pSoundBank->Play(0, 0, 0, 0);
				
				TimeWinShow -= 0.02;
			}
			else {
				if (TotalKeys < 3)
				{
					//Poner condicionales de que te faltan tantas llaves aquí
					camara->posCam.x = camara->posCam.x + 1;
					m_XACT3.m_pSoundBank->Stop(2, 0);
					m_XACT3.m_pSoundBank->Play(2, 0, 0, 0);

				}else 
					if (TotalKeys == 3)
					{
						I_Win = true;
					}
			     
			}

		}
		

		
		
    #pragma endregion

        #pragma region Las colisiones lineales
//Colisiones en X
		CollisionX(-54, 101, 113, 114, true, 1); //Pared interna de lab

		CollisionX(-54, 96.7, 97, 98, true, -1); //Pared interna de lab

		CollisionX(-141.2, -77, 111, 112, true, 1); //Pared EXTERNA de lab
		CollisionX(-134, -82, 98, 99, true, -1); //Pared interna de lab
									
		CollisionX(-73, -47, 83, 84, true, 1); //Pared interna de lab
		
		CollisionX(-82, -47, 67, 68, true, -1); //Pared cerca de salida de laberinto
		CollisionX(-52, -23, 51, 52, true, 1);
		CollisionX(-45, -16, 36, 37, true, -1);
		//Pared de atrás Laberinto
		CollisionX(-135, 97, -123, -122, true, 1);
		CollisionX(-140, 102, -140, -139, true, -1);
		
		//Donde se ubican las rocas del costado del laberinto
		CollisionX(-236, -142, -70, -69, true, 1);
		CollisionX(-236, -142, -38, -37, true, -1);

		//Pa que no se salga del terreno
		CollisionX(-195, -140, 112, 113, true, 1);
		CollisionX(-235, -197, 157, 158, true, 1);
		CollisionX(-235, 238, 226, 227, true, -1);
		CollisionX(103, 228, 123, 124, true, 1);

		//Para la otra entrada que creía que era la salida:(
		//CollisionX(-73, -50, 99, 100, true, -1);
		                                            
													 
	


		//Colisiones en Z
		CollisionZ(102, 107, -57, -56, true, -1); //Pared cerca de salida
		CollisionZ(80, 108.7, -73, -72, true, 1); //Pared cerca de salida

		CollisionZ(73.3, 98, -87, -86, true, -1); //Pared interna cerca de salida
		//
		CollisionZ(50, 98, -28, -27, true, -1); 
		CollisionZ(43.9, 98, -12, -11, true, 1);

		CollisionZ(72, 78.8, -42, -41, true, 1);

        //Paredes costados
		CollisionZ(-45.8, 108, -146, -145, true, -1); 
		CollisionZ(-135, 109, 108, 109, true, 1);

		CollisionZ(-129, 98, 90, 91, true, -1);
		CollisionZ(-39, 98, -130, -129, true, 1);
	
		
		CollisionZ(-134.8, -70, -146, -145, true, -1);
		CollisionZ(-123, -75, -130, -129, true, 1);

		//Donde está el descanso con los pinos, al costado del laberinto
		CollisionZ(-76, -26, -230, -229, true, 1);

		//Pa que no se salga
		CollisionZ(111, 157, -189, -188, true, 1);
		CollisionZ(149, 238, -228, -227, true, 1);

		CollisionZ(93, 235, 227, 228, true, -1);

		CollisionZ(113, 117, 98, 99, true, -1);


		                                                            //*****COLISIÓN DE LA PUERTA******** 
		                                                           
		                                                            //Es una colisión invisible que impide salir de adentro hacia afuera
		                                                            // donde se ubica el playground, el kiosko y lo demás
		                                                            //Cuando se implemente bien la puerta, cambien el segundo parámetro (x2)
		                                                            // para que sea más ancha la colisión y no se pueda salir 


	


     #pragma endregion

        #pragma region Lógica de las llaves y los pinchos

		Llave->Draw(0.28, 0.93);
		string sTotalKeys = std::to_string(TotalKeys);
		TotalK->DrawText(0.32, 0.89, ": " + sTotalKeys, 0.015);

		if (key1 == false)
		{
			llave->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 0, 'A', 2, light->GetDirection(), light->GetDiffuseColor());
			
			if (isPointInsideSphere(camara->getPos(), llave->getSphere(8)))
			{
				//m_InteractivoXACT3.m_pMySB->Play(2, 0, 0, 0);
				m_XACT3.m_pSoundBank->Stop(1, 0);
				m_XACT3.m_pSoundBank->Play(1, 0, 0, 0);
				key1 = true;
				TotalKeys++;
			}
		}

		if (key2 == false)
		{
			llave2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 0, 'A', 2, light->GetDirection(), light->GetDiffuseColor());

			if (isPointInsideSphere(camara->getPos(), llave2->getSphere(8)))
			{
				m_XACT3.m_pSoundBank->Stop(1, 0);
				m_XACT3.m_pSoundBank->Play(1, 0, 0, 0);
				key2 = true;
				TotalKeys++;
			}
		}

		if (key3 == false)
		{
			llave3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(0, 0), camara->posCam, 10.0f, 0, 'A', 2, light->GetDirection(), light->GetDiffuseColor());

			if (isPointInsideSphere(camara->getPos(), llave3->getSphere(20)))
			{
				m_XACT3.m_pSoundBank->Stop(1, 0);
				m_XACT3.m_pSoundBank->Play(1, 0, 0, 0);
				key3 = true;
				TotalKeys++;
			}
		}

		//Colision de pinchazo

		if (pinchos1 == false)
		{
			pincho1->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
			if (isPointInsideSphere(camara->getPos(), pincho1->getSphere(8)))
			{
				m_XACT3.m_pSoundBank->Stop(2, 0);
				m_XACT3.m_pSoundBank->Play(2, 0, 0, 0);
				vida = vida - 1;
				pinchos1 = true;
		
			}
		}

		if (pinchos2 == false)
		{
			pincho2->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
			if (isPointInsideSphere(camara->getPos(), pincho2->getSphere(8)))
			{
				m_XACT3.m_pSoundBank->Stop(2, 0);
				m_XACT3.m_pSoundBank->Play(2, 0, 0, 0);
				vida = vida - 1;
				pinchos2 = true;
			}
		}

		if (pinchos3 == false)
		{
			pincho3->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
			if (isPointInsideSphere(camara->getPos(), pincho3->getSphere(8)))
			{
				m_XACT3.m_pSoundBank->Stop(2, 0);
				m_XACT3.m_pSoundBank->Play(2, 0, 0, 0);
				vida = vida - 1;
				pinchos3 = true;
				
			}
		}

		if (pinchos4 == false)
		{
			pincho4->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
			if (isPointInsideSphere(camara->getPos(), pincho4->getSphere(8)))
			{
				m_XACT3.m_pSoundBank->Stop(2, 0);
				m_XACT3.m_pSoundBank->Play(2, 0, 0, 0);
				vida = vida - 1;
				pinchos4 = true;
			}
		}

		if (pinchos5 == false)
		{
			pincho5->Draw(camara->vista, camara->proyeccion, terreno->Superficie(100, 20), camara->posCam, 10.0f, 0, 'A', 1.5, light->GetDirection(), light->GetDiffuseColor());
			if (isPointInsideSphere(camara->getPos(), pincho5->getSphere(8)))
			{
				m_XACT3.m_pSoundBank->Stop(2, 0);
				m_XACT3.m_pSoundBank->Play(2, 0, 0, 0);
				vida = vida - 1;
				pinchos5 = true;
				
			}
		}

     #pragma endregion

        #pragma region Cuando se resta vida en la barra de vida y PIERDES
		////TurnOffAlphaBlending();  //antes habia en supercifie (100, 20)
		//vida3->Draw(-0.86, -0.3);
		

		if (vida == 5)
		{
		   BarraVida5->Draw(-0.86, -0.3);

		} 

		if (vida == 4)
		{
			BarraVida4->Draw(-0.86, -0.3);
		}

		if (vida == 3)
		{
			BarraVida3->Draw(-0.86, -0.3);
		}

		if (vida == 2)
		{
			BarraVida2->Draw(-0.86, -0.3);
		}

		if (vida == 1)
		{
			BarraVida1->Draw(-0.86, -0.3);
		}

		//Globales
		//if (MePega == 5)
		//{
		//	m_XACT3.m_pSoundBank->Stop(5, 0);
		//	m_XACT3.m_pSoundBank->Play(5, 0, 0, 0);
		//}
	
		if (vida == 0)
		{
			m_XACT3.m_pSoundBank->Stop(5, 0);
			m_XACT3.m_pSoundBank->Play(5, 0, 0, 0);
			
			BarraVida0->Draw(-0.86, -0.3);
			Perdiste->Draw(-0.28, 0.4);
			
			if (segundos >= 0)
			{
			  segundos = 300;
			}


		}
		
    #pragma endregion

        #pragma region Cuenta regresiva
		
		if (I_Win == false)
		{
			CuentaRegresiva->DrawText(-0.45, 0.95, "Tiempo: " + CuentaRegresiva->Time(segundos), 0.015);
			segundos -= 0.02;
			ss_textoFinal << CuentaRegresiva->Time(segundos);
			sTiempo = ss_textoFinal.str();
		} else 
			if (I_Win == true)
		    {
		    	//ss_textoFinal.str(std::string());
		    	TextoGanador->DrawText(-0.55, 0.5, "¡Felicidades!" + sTiempo, 0.015);
				TextoGanador2->DrawText(-0.52, 0.35, "Eres genial" + sTiempo, 0.015);

				Coordenadas->DrawText(-0.6, -0.3, "Presiona ESC para salir:)" + sTiempo, 0.015);
		    }
		

		bool TiempoFuera = false;

		
		if (segundos <= 0)
		{
			TiempoFuera = true;
			segundos = 0;
			
			if (TimeShow >= 0)
			{
				TiempoMuestra->Time(TimeShow);
				Tiempo->Draw(-0.28, 0.4);
				
				TimeShow -= 0.08;
				m_XACT3.m_pSoundBank->Stop(5, 0);
				m_XACT3.m_pSoundBank->Play(5, 0, 0, 0);
			}
			else{
				Perdiste->Draw(-0.28, 0.4);
			
			}
			
		}
		

		if (segundos <= 6)
		{
			m_XACT3.m_pSoundBank->Stop(6, 0);
			m_XACT3.m_pSoundBank->Play(6, 0, 1, 0);
			

		}
		
		
		
		
		
        #pragma endregion

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

	void CollisionWin(float P1, float P2, float P3, float P4, bool colision)
	{
		if (colision)
		{
			   if (camara->posCam.x > P1 && camara->posCam.x < P2 && camara->posCam.z > P3 && camara->posCam.z < P4)
				   Ganaste->Draw(-0.38, 0.4);
			
		}
	}

	//Hace colisión en el eje Z y te empuja en X
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