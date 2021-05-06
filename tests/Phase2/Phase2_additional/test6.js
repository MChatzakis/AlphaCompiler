
local x;
{

	local x;

	function f(){ 
		x = 5; //error - cannot access x in previous scope
		local x; // OK 
		::x = 3; //OK -> global
	}
}

