#ifndef _camara
#define _camara

//Clase camara hecha por Rafael Rosas para los UltraLMADs
//Videojuegos

#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10math.h>

class Camara{
public:
	D3DXVECTOR3 posCam;
	D3DXVECTOR3 hdveo;
	D3DXVECTOR3 hdvoy;
	D3DXVECTOR3 refUp;
	D3DXVECTOR3 refRight;
	D3DXVECTOR3 refFront;
	D3DXMATRIX vista;
	D3DXMATRIX proyeccion;
	int ancho;
	int alto;

	Camara(D3DXVECTOR3 eye, D3DXVECTOR3 target, D3DXVECTOR3 up, int Ancho, int Alto)
	{
		//posicion de la camara
		posCam = eye;
		//a donde ve
		hdveo = target;
		refUp = up;
		ancho = Ancho;
		alto = Alto;

		//crea la matriz de vista
		D3DXMatrixLookAtLH(&vista, &posCam, &hdveo, &refUp);
		//la de proyeccion
		D3DXMatrixPerspectiveFovLH( &proyeccion, D3DX_PI/4.0, ancho / alto, 0.01f, 1000.0f );
		//las transpone para acelerar la multiplicacion
		D3DXMatrixTranspose( &vista, &vista );
		D3DXMatrixTranspose( &proyeccion, &proyeccion );

		D3DXVec3Normalize(&refUp, &refUp);

		refFront = D3DXVECTOR3(target.x - eye.x, target.y - eye.y, target.z - eye.z);
		D3DXVec3Normalize(&refFront, &refFront);

		D3DXVec3Cross(&refRight, &refFront, &refUp);
		D3DXVec3Normalize(&refRight, &refRight);
		
	}

	D3DXMATRIX UpdateCam(float vel, float vel2, float arriaba, float izqder, float* ver, float altura)
	{
		D3DXVECTOR4 tempo;
		D3DXQUATERNION quatern; //quaternion temporal para la camara
		D3DXMATRIX giraUp, giraRight; //matrices temporales para los giros

		//creamos al quaternion segun el vector up
		D3DXQuaternionRotationAxis(&quatern, &refUp, izqder);
		//lo normalizamos para que no acumule error
		D3DXQuaternionNormalize(&quatern, &quatern);
		//creamos la matriz de rotacion basados en el quaternion
		D3DXMatrixRotationQuaternion(&giraUp, &quatern);
		//transformamos a los vectores ded la camara
		D3DXVec3Transform(&tempo, &refFront, &giraUp);
		//como el resultado de la operacion anterior es Vec4 lo casteamos para hacerlo vec3
		
		refFront = (D3DXVECTOR3)tempo;
		//normalizamos para no acumular error
		D3DXVec3Normalize(&refFront, &refFront);
		//Con el vector de referencia y el nuevo front calculamos right de nuevo
		D3DXVec3Cross(&refRight, &refFront, &refUp);

		//una vez calculado right a partir de front y up ahora rotamos sobre right
		//repetimos el procedimiento anterior
		D3DXQuaternionRotationAxis(&quatern, &refRight, arriaba);
		D3DXQuaternionNormalize(&quatern, &quatern);
		D3DXMatrixRotationQuaternion(&giraRight, &quatern);

		D3DXVec3Transform(&tempo, &refFront, &giraRight);
		refFront = (D3DXVECTOR3)tempo;
		D3DXVec3Normalize(&refFront, &refFront);


		//ajustamos la matriz de vista con lo obtenido
		//--Encontrar una forma de desplazar el vector de vista para movimientos laterales
		//D3DXVECTOR3 aVer = D3DXVECTOR3(ver[0]+1.15, altura + 1.5, ver[1]);
		posCam += refFront * vel / 10.0;

		posCam += refRight * vel2 / 10.0;
		hdveo = posCam + refFront;
		//hdveo = aVer;
		//D3DXMatrixLookAtLH(&vista, &posCam, &hdveo, &refUp);
		D3DXMatrixLookAtLH(&vista, &posCam, &hdveo, &refUp);
		D3DXMatrixTranspose( &vista, &vista );
		//setPosCam(ver[0] + 0.2, altura-1, ver[1]-5);
		//setPosCam(posCam[0], posCam[1], posCam[2]);
		return vista;
	}

	void setPosCam(float x, float y, float z) {
		this->posCam[0] = x;
		this->posCam[1] = y;
		this->posCam[2] = z;
	}
	
	float gethdVeoZ() {
		return hdveo.z;
	}
	float gethdVeoX() {
		return hdveo.x;
	}
	float gethdVeoY() {
		return hdveo.y;
	}

	~Camara()
	{
	}
};
#endif