
input(x);               //Αυτόματη δήλωση global x, χρήση global input library function

print(typeof(x));       //χρήση global print, typeof και x

::print(::typeof(::x)); //χρήση global print, typeof και x

function g(x,y) {       // g global, x,y local με scope 1, τυπικά ορίσματα
    print(x+y);         //  x, y είναι τα arguments (local) της συνάρτησης g
                        
    local print = y;    //FIXME:error δεν επιτρέπεται shadowing of library functions                         

    ::print(print);     //      και τα δύο αναφέρονται στο print library function

    function h() {      //          νέα συνάρτηση h με scope 1

        return x+y;     //        FIXME:error τα x και y είναι formal της g.

    }                   //       
    return h;           //       το h είναι η αναγνωριστικό τοπικής συνάρτησης με scope 1
        
}
b();  //FIXME: ERROR
h[c]; //FIXME: ERROR
add = (function(x,y){return x+y; });    //    το add είναι global, τα x,y είναι local arguments με scope 1.
{                                            

    local x = ::x;                      //   το x είναι νέο local με scope 1, το ::x είναι το global x.
    x++;                                //        
    local f = (function(){return x;});  //  FIXME:το f είναι νέο local με scope 1, η πρόσβαση στο x είναι το προηγούμενο local με scope 1 
                                        // (εκτός της f, αλλά όχι top global δηλ. error reporting).                                           
}                                      //
                                         //
function f(a,b){                        //   τα a,b είναι arguments με scope 1
             
    local a = local b;                  //   τα local a και local b είναι αναφορές στα τυπικά ορίσματα (αφού είναι στο ίδιο scope)            
}                                       //




