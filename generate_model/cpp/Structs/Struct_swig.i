/* {{NAME}}.i */
%include <std_string.i>
%rename(stream_me_in) operator >>;

%rename(stream_out) operator <<(std::ostream &,{{NAME}} const &);
%rename(stream_pointer_out) operator <<(std::ostream &,{{NAME}} const *);

%rename(__str__) to_string;

%module {{NAME}}
%{
#include "Structs/{{F_NAME}}.hpp"
%}

{% if PARENT %}
%include "Structs/{{PARENT.F_NAME}}.i"
{% else %}
%include "Structs/Struct.i"
{% endif %}

%include "Structs/{{F_NAME}}.hpp"