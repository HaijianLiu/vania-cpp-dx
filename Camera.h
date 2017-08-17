
#ifndef _CAMERA_H_
#define _CAMERA_H_

class Camera {
private:

public:
	D3DXVECTOR2 position = D3DXVECTOR2(0.0f, 0.0f);

	Camera();
	virtual ~Camera();
};

#endif
