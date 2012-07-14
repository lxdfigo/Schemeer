//
//  InputObject.h
//
//  Created by LIU XiaoDan on 7/10/2012.
//

/***********************************************************************************
*
* All code (C) LIU XiaoDan (lxdfigo), 2012
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
************************************************************************************/
#pragma once
#include "DataType.h"

enum ObjectType{
	NORMAL_WORD,
	KEY_WORD,
	INVALID_WORD,
	SEPARATE_LETTER,
	SPECIAL_LETTER,
	IGNORE_LETTER,
	NORMAL_LETTER,
	INVALID_LETTER,
	SCHEME_PHRASE
};

class InputObject
{
public:
	InputObject(void);
	virtual ~InputObject(void);

	void setType(enum ObjectType t){type = t;};
	ObjectType getType(){return type;};
private:
	ObjectType type;
};
