//
//  TreeNode.cpp
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
#include "TreeNode.h"

TreeNode::TreeNode(TreeNode *f,std::string name, std::string value):father(f)
{
	setName(name);
	setValue(value);
}

TreeNode::~TreeNode(void)
{
}
void TreeNode::clear(){
	for(unsigned int i = 0; i < elements.size(); ++i)
		elements[i].clear();
	std::vector<TreeNode>().swap(elements);
}

TreeNode* TreeNode::getNode(std::string name, std::string value){
	for(unsigned int i = 0; i < elements.size(); ++i){
		if (elements[i].getName() == name && (value == "" || elements[i].getValue() == value)){
			return &(elements[i]);
		}
	}
	return NULL;
}


TreeNode* TreeNode::makeChild(std::string name, std::string value){
	//TreeNode *node = getNode(name,value);
	//if (node != NULL) 
	//	return node;

	elements.push_back(TreeNode(this,name,value));
	return &(elements[elements.size()-1]);
}
TreeNode* TreeNode::getFather(){
	return father;
}
TreeNode* TreeNode::getLastChild(){
	return &(elements[elements.size()-1]);
}

std::vector<TreeNode*> TreeNode::getNodes(std::string name, std::string value){
	std::vector<TreeNode *> result;
	for(unsigned int i = 0; i < elements.size(); ++i){
		if (elements[i].getName() == name && (value == "" || elements[i].getValue() == value)){
			result.push_back(&(elements[i]));
		}
	}
	return result;
}
std::string TreeNode::get(std::string name){
	for(unsigned int i = 0; i < elements.size(); ++i){
		if (elements[i].getName() == name){
			return elements[i].getValue();
		}
	}
	return "";
}
std::vector<std::string> TreeNode::gets(std::string name){
	std::vector<std::string> result;
	for(unsigned int i = 0; i < elements.size(); ++i){
		if (elements[i].getName() == name){
			result.push_back(elements[i].getValue());
		}
	}
	return result;
}