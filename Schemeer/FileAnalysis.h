//
//  FileAnalysis.h
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
#include "StreamReader.h"
#include "Scheme.h"
#include "Dictionary.h"
#include "ModelTree.h"

class FileAnalysis
{
public:
	FileAnalysis(void);
	~FileAnalysis(void);

	bool setFile(std::string file);

	void setTree(ModelTree *t){tree = t;}
	void setDictionary(Dictionary * dic){dictionary = dic;}
	void setScheme(Scheme * sch){scheme = sch;}

	void analyze();

private:
	StreamReader * fileReaders;
	Dictionary *dictionary;
	Scheme* scheme;
	ModelTree *tree;
};
