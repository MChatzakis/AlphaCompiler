func = [
	{"()" : (function (t, msg){
		print("Call ", t.class, "'s print\n");
		print(msg);
	})},
	{"class": "Functor"}
];

func("LALA\n");