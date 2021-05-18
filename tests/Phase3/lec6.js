//DONE

x = (function (a, b) {
  return a + b;
});
(function () {})();
/* 
1: FUNCSTART _f1
2: ADD a b _t1
3: RETURN _t1
4: FUNCEND _f1
5: ASSIGN x _f1
6: FUNCSTART _f2
7: FUNCEND _f2
8: CALL _f2
9: GETRETVAL _t1
*/
