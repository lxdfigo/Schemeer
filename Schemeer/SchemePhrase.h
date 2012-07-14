//
//  SchemePhrase.h
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
#include "inputobject.h"
#include <vector>
enum SchemeOperation{
	SCHEMESELF,
	PHRASEREPEAT,
	DOWNCHILD,
	UPCHILD
};
class SchemePhrase :
	public InputObject
{
public:
	SchemePhrase(void);
	SchemePhrase(SchemeOperation operation,int least = 1,int most = 1);
	~SchemePhrase(void);

	void addObject(InputObject*object){content.push_back(object);}
	void setOrPosition();

	unsigned int size(){return content.size();}

	InputObject *getObject(unsigned int i);

	void setLeastNum(int n){leastRepeat = n;}
	void setMostNum(int n){mostRepeat = n; }
	unsigned int getLeastNum(){return leastRepeat;}
	unsigned int getMostNum(){return mostRepeat; }

	SchemeOperation getOperation(){return operation;}

	std::vector<InputObject*> getContents(){return content;}

	int getOrSize(){return orPosition.size();}
	int getOrPosition(int i){return orPosition[i];}
private:
	std::vector<InputObject*> content;
	std::vector<int> orPosition;
	unsigned int leastRepeat;
	unsigned int mostRepeat;
	SchemeOperation operation;

};