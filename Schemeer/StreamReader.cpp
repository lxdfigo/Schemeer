//
//  StreamReader.cpp
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
#include "StreamReader.h"

const char NEWLINEC = '\n';

StreamReader::StreamReader():
file(NULL),
curCol(0),
curLine(0),
dictionary(NULL)
{
}

StreamReader::~StreamReader(void)
{
	if(file != NULL) fclose(file);
}

bool StreamReader::initFile(std::string filename){
	fopen_s(&file,filename.c_str(),"r");
	if (file == NULL) return false;
	return true;
}
InputObject* StreamReader::getNextObject(){
	if (file == NULL)return NULL;

	std::string input;
	while(true){
		char ic = fgetc(file);
		if (ic < 0) break;
		curCol++;
		if (ic == NEWLINEC){
			curLine++;
			curCol = 0;
		}
		InputObject *object = dictionary->checkLetter(ic);

		if (object->getType() == NORMAL_LETTER){
			input.push_back(ic);
		}else if (object->getType() == IGNORE_LETTER){
			continue;
		}else if (object->getType() == SPECIAL_LETTER){
			if (input.empty() == true)	return object;
			fseek(file,-1,SEEK_CUR);
			break;
		}else if (object->getType() == SEPARATE_LETTER){
			if (input.empty() == true) continue;
			else break;
		}else if (object->getType() == INVALID_LETTER){
			reportError();
		}
	}

	if (input.empty() == true) return NULL;

	InputObject *object = dictionary->checkWord(input);
	
	if (object->getType() == INVALID_WORD){
		reportError();
	}

	return object;
}

void StreamReader::reportError(){
	printf("Error in Line %d Colume %d\n",curLine,curCol);
}