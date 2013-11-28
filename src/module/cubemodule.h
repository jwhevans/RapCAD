/*
 *   RapCAD - Rapid prototyping CAD IDE (www.rapcad.org)
 *   Copyright (C) 2010-2013 Giles Bathgate
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CUBEMODULE_H
#define CUBEMODULE_H

#include "primitivemodule.h"
#include "node/primitivenode.h"

class CubeModule : public PrimitiveModule
{
public:
	CubeModule();
	Node* evaluate(Context*);
private:
	void makeSideZ(PrimitiveNode*,double,double,double,double,double);
	void makeSideY(PrimitiveNode*,double,double,double,double,double);
	void makeSideX(PrimitiveNode*,double,double,double,double,double);
};

#endif // CUBEMODULE_H
