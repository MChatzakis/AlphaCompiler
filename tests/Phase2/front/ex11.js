//DONE
{
  {
    function x() {}
    function y() {
      x();
    }
  }
}

{
  y = 1;
  function ex(a) {
    y = 3; // error variable y in line 2 is not accessible in function ex
  }
}

{ 
    y = 1;
    function ex (a) {
      local y = 3; // define new local variable in scope 2 in line 4 
    }
}

{ 
    y = 1;
    function ex (a) {
        ::y = 3; // error, undefined global variable y in line 4 
    }
}

