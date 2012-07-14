//
//  Scheme.cpp
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
#include "Scheme.h"
#include "Word.h"

const std::string ITSELF = "self";
const char ORCHAR = '|';
const char REPEATLEFT = '[';
const char REPEATRIGHT = ']';
const char ZERO2MORE = '*';
const char ONE2MORE = '+';
const char ZERO2ONE = '1';
const char SENTENCEEND = ';';
const char SPECIALCHAR = '\\';
const char DOWNCHILDC = 'd';
const char UPCHILDC = 'u';
const char SEPERATECHAR = ' ';

Scheme::Scheme(Dictionary *dic):dictionary(dic)
{
}

Scheme::~Scheme(void)
{
}
void Scheme::readSentence(FILE* file,std::string &sentence){

	while(true){
		char c =fgetc(file);
		if (c <= 0 || c == SENTENCEEND) break;
		sentence.push_back(c);
	}
}
void Scheme::analyzeSubSentenceByDictionary(const std::string &sentence,SchemePhrase *phrase){

	std::string input;
	for(unsigned int offset = 0; offset < sentence.size(); ++offset){
		char ic = sentence[offset];
	
		InputObject *object = dictionary->checkLetter(ic);

		if (object->getType() == NORMAL_LETTER){
			input.push_back(ic);
		}else if (object->getType() == IGNORE_LETTER || object->getType() == INVALID_LETTER){
			continue;
		}else if (object->getType() == SPECIAL_LETTER){
			if (input.empty() == true){
				phrase->addObject(object);
			}else{
				offset--;
				InputObject *object = dictionary->checkWord(input);
				phrase->addObject(object);
				input.clear();
			}
		}else if (object->getType() == SEPARATE_LETTER){
			if (input.empty() == true){ 
				continue;
			}else{
				InputObject *object = dictionary->checkWord(input);
				phrase->addObject(object);
				input.clear();
			}
		}
	}
	if (input.empty() != true){
		InputObject *object = dictionary->checkWord(input);
		phrase->addObject(object);
	}

	return;
}
void Scheme::analyzeSentence(const std::string &sentence,unsigned int &offset,SchemePhrase *phrase){
	InputObject *object = NULL;
	std::string substring;
	int sign = 0;
	while(offset < sentence.size()){
		char ic = sentence[offset];
		offset++;

		if (ic == SEPERATECHAR || ic == REPEATLEFT || ic == SPECIALCHAR || ic == REPEATRIGHT || ic == ORCHAR){
			if (substring.empty() != true) {
				if (substring == ITSELF){
					phrase->addObject(new SchemePhrase(SCHEMESELF));
				}else{
					object =  dictionary->checkWord(substring);
					analyzeSubSentenceByDictionary(dynamic_cast<Word*>(object)->getContent(),phrase);
				}
				substring.clear();
			}
		}else{
			substring.push_back(ic);
		}
		if (ic == ORCHAR){
			phrase->setOrPosition();
		}else if (ic == REPEATLEFT){
			SchemePhrase *subphrase = new SchemePhrase(PHRASEREPEAT);
			analyzeSentence(sentence,offset,subphrase);
			phrase->addObject(subphrase);
		}else if (ic == SPECIALCHAR){
			ic = sentence[offset];
			offset++;
			if (ic == UPCHILDC){
				object = new SchemePhrase(UPCHILD);
				phrase->addObject(object);
			}else if (ic == DOWNCHILDC){
				object = new SchemePhrase(DOWNCHILD);
				phrase->addObject(object);
			}else if (ic == REPEATLEFT || ic == REPEATRIGHT){
				substring.push_back(ic);
			}
		}else if (ic == REPEATRIGHT){
			ic = sentence[offset];
			offset++;
			if (ic == ZERO2MORE){
				phrase->setLeastNum(0);
				phrase->setMostNum(-1);
			}else if (ic == ZERO2ONE){
				phrase->setLeastNum(0);
				phrase->setMostNum(1);
			}else if (ic == ONE2MORE){
				phrase->setLeastNum(1);
				phrase->setMostNum(-1);
			}
			return;
		}
	}
	if (substring.empty() != true) {
		if (substring == ITSELF){
			phrase->addObject(new SchemePhrase(SCHEMESELF));
		}else{
			object =  dictionary->checkWord(substring);
			substring.clear();
			analyzeSubSentenceByDictionary(dynamic_cast<Word*>(object)->getContent(),phrase);
		}
	}
}
void Scheme::init(std::string config){
	if (dictionary == NULL) return;

	FILE *file = NULL;
	fopen_s(&file,config.c_str(),"r");


	while(file != NULL && !feof(file)){
		std::string sentence;
		readSentence(file,sentence);
		if (sentence.empty() == true) continue;

		SchemePhrase equation;
		unsigned int offset = 0;
		analyzeSentence(sentence,offset,&equation);
		equations.push_back(equation);
	}

	if (file != NULL) fclose(file);
}

int Scheme::matchEquation(std::vector<InputObject *> input,unsigned int& offset,SchemePhrase * equation,int eqb,int eqe){

	unsigned int originalMemo = process.size();
	int originalOffset = offset;
	int eqi = eqb;
	while(offset < input.size() && eqi < eqe){
		InputObject *object = equation->getObject(eqi);
		if (object == NULL) return 0;

		if (object->getType() == SCHEME_PHRASE)	{
			SchemePhrase *phrase = dynamic_cast<SchemePhrase*>(object);
			if (phrase->getOperation() == SCHEMESELF){
				if (matchEquations(input,offset) != 0){
					offset = originalOffset;
					while(originalMemo < process.size()) process.pop_back();
					return -1;
				}
			}else if (phrase->getOperation() == PHRASEREPEAT){
				unsigned int ls = 0;
				unsigned int lastoffset = 0;
				for(ls = 1; ls <= phrase->getMostNum(); ++ls){
					lastoffset = offset;
					int sign = 0;

					unsigned int subset = 0;
					for(int o = 0; o < phrase->getOrSize(); ++o){
						if (matchEquation(input,offset,phrase,subset,phrase->getOrPosition(o)) == 0) {
							sign = 1;
							break;
						}
						subset = phrase->getOrPosition(o);
					}
					if (sign == 1) continue;

					if (matchEquation(input,offset,phrase,subset,phrase->size()) != 0) {
						offset = lastoffset;
						break;
					}
				}
				if (ls < phrase->getLeastNum()){
					offset = originalOffset;
					while(originalMemo < process.size()) process.pop_back();
					return -1;
				}
			}else{
				process.push_back(Memo(phrase));
			}
			++eqi;
			continue;
		}

		if (!((input[offset]->getType() == NORMAL_WORD && object->getType() == input[offset]->getType()) ||
			object == input[offset])){
				offset = originalOffset;
				while(originalMemo < process.size()) process.pop_back();
				return -1;
		}else{
			process.push_back(Memo(object,input[offset]));
		}
		++offset;
		++eqi;
	}
	return 0;
}
int Scheme::matchEquations(std::vector<InputObject *> input,unsigned int& offset){

	int originalOffset = offset;
	for(unsigned int e = 0; e < equations.size(); ++e){
		SchemePhrase &equation = equations[e];
		if (matchEquation(input,offset,&equation,0,equation.size()) == 0)
			return 0;
	}
	offset = originalOffset;
	return -1;
}

std::vector<Memo> Scheme::match(std::vector<InputObject *> input){
	process.clear();
	unsigned int offset = 0;
	while(offset < input.size()){
		int eqi = matchEquations(input,offset);
		if (eqi == -1)	break;
	}
	return process;
}