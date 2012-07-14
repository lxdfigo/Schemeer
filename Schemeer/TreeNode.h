//
//  TreeNode.h
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
#include "BaseNode.h"
#include <vector>

class TreeNode :
	public BaseNode
{
public:
	TreeNode(TreeNode *father = NULL,std::string name="", std::string value = "");
	virtual ~TreeNode(void);

	TreeNode* getNode(std::string name, std::string value = "");

	void addNode(TreeNode node){elements.push_back(node);}
	TreeNode* makeChild(std::string name, std::string value = "");
	TreeNode* getFather();
	TreeNode* getLastChild();

	TreeNode* getElement(int i){return &elements[i];}
	unsigned int size(){return elements.size();}

	std::vector<TreeNode*> getNodes(std::string name, std::string value = "");
	std::string get(std::string name);
	std::vector<std::string> gets(std::string name);

	void clear();
private:
	TreeNode *father;
	std::vector<TreeNode> elements;
};
