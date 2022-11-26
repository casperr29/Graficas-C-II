#ifndef _light
#define _modelo

class Light
{
public:
	Light();
	Light(const Light& other);
	Light(float posx, float posy, float posz, float r, float g, float b, float a);
	~Light();

	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);
	
	/*void SetDiffuseColor(XMFLOAT4);
	void SetDirection(XMFLOAT3);*/

	void GetDiffuseColor(float*);
	void GetDirection(float*);
	
	float* GetDiffuseColor();
	float* GetDirection();

private:
	float m_diffuseColor[4] = {0.7f};
	float m_direction[3] = {0};
};

#endif