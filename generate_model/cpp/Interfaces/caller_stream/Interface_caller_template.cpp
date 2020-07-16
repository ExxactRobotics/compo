
#include "Interfaces/{{F_NAME}}/{{NAME}}_caller_stream.hpp"
#include "Errors/Error.hpp"

#include "Interfaces/Function_stream_recv.hpp"
#include "Interfaces/Return_stream_send.hpp"

{% include "helper/namespace_open.hpp" with context%}
constexpr unsigned int str2int(const char* str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

{{NAME}}_caller_stream::{{NAME}}_caller_stream({{NAME}}& pcomp)
:{%if PARENT%}{{PARENT.D_NAME}}_caller_stream(pcomp){%else%}Caller_stream(){%endif%}, comp(pcomp)
  {
    return ;
  }

bool {{NAME}}_caller_stream::call(CompoMe::Function_stream_recv& is, CompoMe::Return_stream_send& os)
{
  is.pull();
  os.start();

  std::string name_function;
  std::getline(is.get_si(), name_function, '(');
  bool b = this->call(name_function,is,os);

  is.end();
  os.send();
  return b;
}

bool {{NAME}}_caller_stream::call(std::string& name_function, CompoMe::Function_stream_recv& is, CompoMe::Return_stream_send& os)
{
  bool result = false;

  switch(str2int(name_function.c_str())){
    {% for func in FUNCTION%}
  case str2int("{{func.NAME}}"):
    result= this->{{func.NAME}}(is, os);
    break;
    {% endfor %}
    {% for d in DATA%}
  case str2int("get_{{d.NAME}}"):
    result = this->get_{{d.NAME}}(is, os);
    break;

  case str2int("set_{{d.NAME}}"):
    result = this->set_{{d.NAME}}(is, os);
    break;
    {% endfor %}

    {%if PARENT %}
  default:
    return {{PARENT.D_NAME}}_caller_stream::call(name_function, is, os);
    break;
    {%endif%}
  };

  return result;
}

{% for func in FUNCTION %}
bool {{NAME}}_caller_stream::{{ func.NAME }}(CompoMe::Function_stream_recv& is, CompoMe::Return_stream_send& os) {
  {% for arg in func.SIGNATURE %}
  {{arg.TYPE.D_NAME}} l_{{arg.NAME}};
  is >> l_{{arg.NAME}};
  {%- if not loop.last %}
  is.get();
  {% endif %}

  {% endfor %}

  char _l = is.get();
  if(_l != ')'){
    return false;
  }

  try {
  {% if func.RETURN.NAME == "void" %}
  this->comp.{{ func.NAME }}({% for arg in func.SIGNATURE -%}
    l_{{arg.NAME}}
      {%- if not loop.last %}, {% endif %}
    {%- endfor %});
  {%else%}
  os << this->comp.{{ func.NAME }}({% for arg in func.SIGNATURE -%}
    l_{{arg.NAME}}
      {%- if not loop.last %}, {% endif %}
    {%- endfor %});
  {% endif %}
  } catch (const CompoMe::Error &e) {
    os << "!" << &e;
  }

  return true;
}
{% endfor %}


{% for d in DATA %}
bool {{NAME}}_caller_stream::get_{{ d.NAME }}(CompoMe::Function_stream_recv& is, CompoMe::Return_stream_send& os)
{
  char _l = is.get();
  if(_l != ')'){
    return false;
  }

  try {
    os << this->comp.get_{{d.NAME}}();
  } catch (const CompoMe::Error &e) {
    os << "!" << &e;
  }

  return true;
}

bool {{NAME}}_caller_stream::set_{{ d.NAME }}(CompoMe::Function_stream_recv& is, CompoMe::Return_stream_send& os)
{
  {{d.TYPE.D_NAME}} set_val;
  is >> set_val;

  char l = is.get();
  if(l != ')'){
    return false;
  }

  try {
    this->comp.set_{{d.NAME}}(set_val);
  } catch (const CompoMe::Error &e) {
    os << "!" << &e;
  }

  return true;
}

{% endfor %}
{% include "helper/namespace_close.hpp" with context%}