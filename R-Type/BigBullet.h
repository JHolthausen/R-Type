#pragma once

#include "BulletParent.h"

namespace Tmpl8{
	class BigBullet : public BulletParent
	{
	public:
		BigBullet(Surface* screen);
		~BigBullet();
	};

}