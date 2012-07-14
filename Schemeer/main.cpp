//
//  Main.cpp
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

void printNode(TreeNode *node,int dep){

	for(int d = 0; d < dep; ++d) printf("\t");
	printf("%s : %s\n",node->getName().c_str(),node->getValue().c_str());

	std::vector<TreeNode*> attri = node->getNodes("attribute");
	for(unsigned int i = 0; i < attri.size(); i++){
		printNode(attri[i],dep+1);
	}

	std::vector<TreeNode*> values = node->getNodes("value");
	for(unsigned int i = 0; i < values.size(); i++){
		printNode(values[i],dep+1);
	}

	std::vector<TreeNode*> nodes = node->getNodes("element");
	for(unsigned int i = 0; i < nodes.size(); i++){
		printNode(nodes[i],dep+1);
	}
}

int main(){
	ModelTree tree;
	Dictionary dic;
	Scheme sch(&dic);
	FileAnalysis analysis;
	TreeNode * root;

	analysis.setDictionary(&dic);
	analysis.setScheme(&sch);
	analysis.setTree(&tree);

	dic.init("config\\config.txt");
	sch.init("config\\scheme.txt");
	analysis.setFile("input.txt");
	analysis.analyze();

	root = tree.getRoot();
	printNode(root,0);


	printf("\n");


	tree.clear();
	dic.init("config\\config2.txt");
	sch.init("config\\scheme2.txt");
	analysis.setFile("input2.txt");
	analysis.analyze();

	root = tree.getRoot();
	printNode(root,0);

	getchar();
	return 0;
}