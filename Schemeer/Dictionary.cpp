//
//  Dictionary.cpp
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
#include "Dictionary.h"
#include "Letter.h"
#include "Word.h"

Dictionary::Dictionary()
{
}

Dictionary::~Dictionary(void)
{
	for(std::map<std::string,InputObject*>::iterator itr = wordContents.begin(); itr != wordContents.end(); ++itr){
		delete itr->second;
	}
	for(std::map<char,InputObject*>::iterator itr = letterContents.begin(); itr != letterContents.end(); ++itr){
		delete itr->second;
	}
}

void Dictionary::insertLetters(FILE *file,ObjectType type){
	char ib = 0;
	while(true){
		char ic = fgetc(file);
		if (ic == '\n' || ic < 0) break;

		if (ic != ';'){
			ib = ib * 10 + ic-48;
		}else if (ib != 0){
			letterContents[ib] = new Letter(ib,type);
			ib = 0;
		}
	}

}
void Dictionary::insertWords(FILE *file,ObjectType type){
	std::string word;
	while(true){
		char ic = fgetc(file);
		if (ic == '\n' || ic < 0) break;

		if (ic != ';'){ 
			word.push_back(ic);
		}else if (word != ""){
			wordContents[word] = new Word(word,type);
			//words.insert(word);
			word.clear();
		}
	}
}

bool Dictionary::init(std::string configFile){

	FILE *file = NULL;
	fopen_s(&file,configFile.c_str(),"r");
	if (file == NULL) return false;

	insertWords(file,KEY_WORD);
	insertLetters(file,SPECIAL_LETTER);
	insertLetters(file,SEPARATE_LETTER);
	insertLetters(file,IGNORE_LETTER);
	insertLetters(file,INVALID_LETTER);

	fclose(file);
	return true;
}
InputObject * Dictionary::checkLetter(char c){
	InputObject *result = letterContents[c];
	if (result == NULL){
		result = new Letter(c,NORMAL_LETTER);
		letterContents[c] = result;
	}
	return result;
}
InputObject * Dictionary::checkWord(std::string word){
	InputObject *result = wordContents[word];
	if (result == NULL){
		result = new Word(word,NORMAL_WORD);
		wordContents[word] = result;
	}
	return result;
}