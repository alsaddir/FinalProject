#include "Player.h"
#include "GameEngine.h"
#include <algorithm>	// for min max function
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

void Player::UpdateBullets()
{
	for (int i = 0; i < (int)m_vBullets.size(); i++)
	{
		m_vBullets[i]->Update();

		if (m_vBullets[i]->m_X < 0 || m_vBullets[i]->m_X >
			1024 ||
			m_vBullets[i]->m_Y < 0 || m_vBullets[i]->m_Y > 768)
		{
			delete m_vBullets[i];
			m_vBullets[i] = nullptr;
			m_vBullets.erase(m_vBullets.begin() + i);



		}

	}

	m_vBullets.shrink_to_fit();
}


void Player::npcAi( Player * target )
{
	srand(time(NULL));
	int randomInt = rand() % 10 + 1;

	if (this->GetX() > target->GetX())
		m_X -= 1;
	else if (this->GetX() < target->GetX())
		m_X += 1;
		
	this->UpdatePlayer();
	this->UpdateBullets();

	if ((randomInt % 5) == 0)
	{
		this->SpawnBullet();
	}
}


Player::Player(SDL_Texture* tex, double x, double y)
	:SpriteExAnimated(tex, x - 50, y - 50, 0, 1, 4, 0.1f)
{
	spriteSrcRect = { 0,0,100,100 };
	spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50),100,100 };
	m_dRadius = 50;
}

Player::Player(SDL_Texture* tex, double x, double y , bool npc)
	:SpriteExAnimated(tex, x - 50, y - 50, 0, 1, 4, 0.1f)
{
	spriteSrcRect = { 0,0,100,100 };
	spriteDestRect = { (int)(m_X - 50),(int)(m_Y - 50),100,100 };
	m_dRadius = 50;
	this->npc = npc;

	if (npc)
	{
		// rotate 180 degrees so enemy is looking at player
		angle = -180;
	}
}

Player::~Player()
{
	for (int i = 0; i < (int)m_vBullets.size(); i++)
	{
		delete m_vBullets[i];
		m_vBullets[i] = nullptr;
	}
	m_vBullets.clear();
	m_vBullets.shrink_to_fit();
}

void Player::Render()
{


	for (int i = 0; i < (int)m_vBullets.size(); i++)
	{
		m_vBullets[i]->Render();

	}
	this->SpriteExAnimated::Render();
}

void Player::Update()
{
	//implement a rotation mechanism

	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_A))
		angle -= 6.0;
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_D))
		angle += 6.0;

	this->UpdatePlayer();
	this->UpdateBullets();
}

void Player::SetIdle()
{
	spriteSrcRect.y = 0;
	m_iFrame = 0;
	m_iSprte = 0;

}


void Player::SpawnBullet()
{
	//converting rge player spaceship angel to deltax and deltay
	float dx = (float)cos((angle - 90) * M_PI / 180);
	float dy = (float)sin((angle - 90) * M_PI / 180);
	m_vBullets.push_back(new Bullet(texture, m_X, m_Y, angle, dx, dy));
}

void Player::MoveForward()
{
	//converting the player spaceship's angle to deltaX and deltaY 
	m_DX = (float)cos((angle - 90) * M_PI / 180);
	m_DY = (float)sin((angle - 90) * M_PI / 180);

	//update the velocities
	m_velX += m_DX * m_dSpeed;
	m_velY += m_DY * m_dSpeed;

	//clamp the velocities. and need to maintain previous vector i.e. dx and dy

	m_velX = min(max(m_velX, -(m_velMax * fabs(m_DX))), (m_velMax * fabs(m_DX)));
	m_velY = min(max(m_velY, -(m_velMax * fabs(m_DY))), (m_velMax * fabs(m_DY)));
}

void Player::UpdatePlayer()
{
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_W))
	{
		spriteSrcRect.y = 100;//set y to the 100 so that we start playing the 2nd row
		this->Animate();

		if (!this->npc)
		{
			this->MoveForward();
		}

	}
	else
	{
		//add some drag to slow down 
		m_velX *= 0.975;
		m_velY *= 0.975;

	}

	m_X += m_velX; //update x coord
	m_Y += m_velY;  //update y coord
	this->UpdateDestRect();

	spriteSrcRect.x = spriteSrcRect.w * m_iSprte; //updates the animation

}

void Player::Invincible(int durationInMilli)
{

}



//void Player::UpdatePos()
//{
//	m_X += m_velX; //update x coord
//	m_Y += m_velY;  //update y coord
//
//	this->UpdateDestRect();
//
//	spriteSrcRect.x = spriteSrcRect.w * m_iSprte; //updates the animation
//}

void Player::SetPosition(int newXCoord, int newYCoord)
{
	this->m_DX = newXCoord;
	this->m_DY = newYCoord;
}


void Player::setInvincibleWearOffTimeIntimeInSeconds(int timeInSeconds)
{
	int currentTimeInSeconds = time(0);

	this->invincibleWearOffTimeInSeconds = currentTimeInSeconds + timeInSeconds;
}
