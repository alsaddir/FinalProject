#pragma once
#include"SpriteEx.h"
#include"vector"
#include"Bullet.h"

using namespace std;
class Player : public SpriteExAnimated
{
private:
	vector<Bullet*> m_vBullets;
	bool invincible = false;
	int invincibleWearOffTimeInMilli;
	double m_velX = 0,
		m_velY = 0,
		m_velMax = 10;

	void UpdateBullets();
	void MoveForward();
	void UpdatePlayer();
public:
	Player(SDL_Texture* tex, double x, double y);
	~Player();
	void Render();
	void Update();
	void SetIdle();
	void SpawnBullet();
	void Invincible(int durationInMilli);
	void SetPosition(int newXCoord, int newYCoord);
	void setInvincible(bool invincible) { this->invincible = invincible; }

	bool isInvincible() { return this->invincible; }
	vector<Bullet*>& GetBullets() { return m_vBullets; }


};

