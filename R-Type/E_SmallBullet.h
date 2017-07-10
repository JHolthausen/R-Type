#pragma once

#include "BulletParent.h"

namespace Tmpl8{
	class E_SmallBullet : public BulletParent
	{
	public:
		E_SmallBullet(Surface* screen);
		~E_SmallBullet();
	};

}