//
//  Dictionary.h
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
#include "InputObject.h"
#include <string>
#include <set>
#include <map>

class Dictionary
{
public:
	Dictionary();
	~Dictionary(void);

	bool init(std::string configFile);
	InputObject * checkLetter(char c);
	InputObject * checkWord(std::string word);
private:

	std::map<std::string,InputObject*> wordContents;
	std::map<char,InputObject*> letterContents;
private:
	void insertLetters(FILE *file,ObjectType type);
	void insertWords(FILE *file,ObjectType type);

};
