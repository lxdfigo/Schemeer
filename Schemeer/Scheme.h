//
//  Scheme.h
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
#include "SchemePhrase.h"
#include "Dictionary.h"

struct Memo{
	InputObject *operation;
	InputObject *object;
	Memo(InputObject *op,InputObject * ob = NULL):operation(op),object(ob){}
};
class Scheme
{
public:
	Scheme(Dictionary *dic);
	~Scheme(void);
	void init(std::string config);
	void setDictionary(Dictionary *dic){dictionary = dic; }
	std::vector<Memo> match(std::vector<InputObject *> object);

private:
	std::vector<SchemePhrase> equations;
	Dictionary *dictionary;

	std::vector<Memo> process;
private:
	void readSentence(FILE* file,std::string &sentence);
	void analyzeSentence(const std::string &sentence,unsigned int &offset,SchemePhrase *phrase);
	void analyzeSubSentenceByDictionary(const std::string &sentence,SchemePhrase *phrase);


	int matchEquation(std::vector<InputObject *> input,unsigned int& offset,SchemePhrase * equation,int eqb,int eqe);
	int matchEquations(std::vector<InputObject *> input,unsigned int& offset);
};
