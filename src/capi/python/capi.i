%{
#include "capi/algorithm.h"
#include "capi/model.h"
%}
%include "carrays.i"
%include "cstring.i"
%cstring_bounded_output(char *path, 1024);
%array_functions(void *, voidPtrArray);
// %typemap(in) char * {
// $1 = PyString_AsString($input);
// };
%include "capi/algorithm.h"
%include "capi/model.h"