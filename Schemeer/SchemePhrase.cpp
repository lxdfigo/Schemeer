//
//  SchemePhrase.cpp
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
#include "SchemePhrase.h"

SchemePhrase::SchemePhrase(void):mostRepeat(1),leastRepeat(1),operation(PHRASEREPEAT)
{
	setType(SCHEME_PHRASE);
}

SchemePhrase::SchemePhrase(SchemeOperation op,int ls,int ms){
	operation = op;
	leastRepeat = ls;
	mostRepeat = ms;
	setType(SCHEME_PHRASE);
}
SchemePhrase::~SchemePhrase(void)
{
}

InputObject *SchemePhrase::getObject(unsigned int i){
	if (i >= 0 && i < content.size())
		return content[i];
	else 
		return NULL;
}
void SchemePhrase::setOrPosition(){
	orPosition.push_back(content.size());
}
