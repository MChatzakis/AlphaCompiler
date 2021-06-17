/*
//proper	output
parent
childL
grandChildLL
grandChildLR
childR
grandChildRL
grandChildRR




parent
childR
grandChildRR
grandChildRL
childL
grandChildLR
grandChildLL
*/
nl = "\n";

function TreeNode (p, l, r) {
	parent  = 0;
	left	= 0;
	right	= 0; 

	return  [
		{"class" : "TreeNode"},
		{"parent": parent},	
		{"left"	 : left},
		{"right" : right},
		{"info"	 : 0},
		{"marked": false}
	];
}

function Stack () {

	return [
		{"class" : "Stack"},
		{"next"  : 0},
		{"data"  : []},
		{"empty" : (function (self){
			return self.next == 0;
		})},
		
		{"push"	 : (function (self, data){
			self.data[self.next++] = data;
		})},
		
		{"pop"	 : (function (self){
			if (self.next > 0)
				self.data[--self.next] = nil;
		})},
		
		{"top" 	 : (function (self){
			return self.data[self.next-1];
		})}
	];
}

function PrintTree (root) {
	if (root)
		print(root.info, ::nl);

	if (root.left)
		PrintTree(root.left);

	if (root.right)
		PrintTree(root.right);
}

function PostOrder(root) {
	k = Stack();
	k..push(root);

	while(not k..empty()){
		tmp = k..top();
		k..pop();
		
		if (tmp.marked)
			print(tmp.info, nl);
		else {
			if (tmp.left)   k..push(tmp.left);
			if (tmp.right)	k..push(tmp.right);
			tmp.marked = true;
			k..push(tmp);
		}
	}
}
/*
							  root
							 /    \   
						    /      \
						   /  	    \
						  /    	     \
					  childL	     childR
					  /     \        /     \
					 /       \  grandChildRR\
				    /         \			     \
			grandChildLL  grandChildLR      grandChildRR
*/

root 			= TreeNode();
childL 			= TreeNode();
childR 			= TreeNode();
grandChildLL 	= TreeNode();
grandChildLR 	= TreeNode();
grandChildRL 	= TreeNode();
grandChildRR 	= TreeNode();

root.info 	  		= "parent";
childL.info 	  	= "childL";
childR.info 	  	= "childR";
grandChildLL.info 	= "grandChildLL";
grandChildLR.info 	= "grandChildLR";
grandChildRL.info 	= "grandChildRL";
grandChildRR.info 	= "grandChildRR";

root.left  = childL;
root.right = childR;

childL.parent	= root;
childL.left		= grandChildLL;
childL.right	= grandChildLR;

childR.parent 	= root;
childR.left		= grandChildRL;
childR.right	= grandChildRR;


grandChildLL.parent = childL;
grandChildLR.parent = childL;

grandChildRL.parent = childR;
grandChildRL.parnet = childR;


PrintTree(root);
print("\n", ::nl, "\n", nl);
PostOrder(root);



