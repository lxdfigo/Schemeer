//
//  FileAnalysis.cpp
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
#include "FileAnalysis.h"

FileAnalysis::FileAnalysis(void):dictionary(NULL),scheme(NULL),tree(NULL)
{
}

FileAnalysis::~FileAnalysis(void)
{
}

bool FileAnalysis::setFile(std::string file){
	fileReaders = new StreamReader();
	fileReaders->setDictionary(dictionary);
	if (!fileReaders->initFile(file)) return false;
	
	return true;
}
void FileAnalysis::analyze(){
	std::vector<InputObject*> elements;
	while(true){
		InputObject* object = fileReaders->getNextObject();
		if (object == NULL) break;
		elements.push_back(object);
	}
	std::vector<Memo> &process = scheme->match(elements);

	TreeNode *curNode = tree->getRoot();
	for(unsigned int p = 0; p < process.size(); ++p){
		Memo &m = process[p];
		if (m.operation->getType() == SCHEME_PHRASE){
			SchemePhrase * phrase = dynamic_cast<SchemePhrase*>(m.operation);
			if (phrase->getOperation() == UPCHILD){
				curNode = curNode->getFather();
			}else if (phrase->getOperation() == DOWNCHILD){
				curNode = curNode->getLastChild();
			}
		}else if (m.operation->getType() == NORMAL_WORD){
			curNode->makeChild(dynamic_cast<Word*>(m.operation)->getContent(),
				dynamic_cast<Word*>(m.object)->getContent());
		}
	}
}