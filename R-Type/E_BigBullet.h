#pragma once

#include "BulletParent.h"

namespace Tmpl8{
	class E_BigBullet : public BulletParent
	{
	public:
		E_BigBullet(Surface* screen);
		~E_BigBullet();
	};

}