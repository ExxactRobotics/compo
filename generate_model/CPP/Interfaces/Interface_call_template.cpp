
#include "Interfaces/{{NAME}}/{{NAME}}_caller.hpp"


constexpr unsigned int str2int(const char* str, int h = 0)
{
  return !str[h] ? 5381 : (str2int(str, h+1) * 33) ^ str[h];
}

  {{NAME}}_caller::{{NAME}}_caller({{NAME}}& pcomp)
  : comp(pcomp)
  {

    return ;
  }


bool {{NAME}}_caller::call(std::istream& is, std::ostream& os)
{

  std::string name_function;

  std::getline(is, name_function, '(');

  switch(str2int(name_function.c_str())){
    {% for func in FUNCTION%}
  case str2int("{{func.NAME}}"):
    this->{{func.NAME}}(is, os);
    return true;
    break;
    {% endfor %}
    {% for d in DATA%}
  case str2int("get_{{d.NAME}}"):
    this->get_{{d.NAME}}(is, os);
    return true;
    break;
  case str2int("set_{{d.NAME}}"):
    this->set_{{d.NAME}}(is, os);
    return true;
    break;
    {% endfor %}
  };

  std::getline(is, name_function);

  return false;
}


  {% for func in FUNCTION %}
void {{NAME}}_caller::{{ func.NAME }}(std::istream& is, std::ostream& os)
{
  {% for arg in func.SIGNATURE %}
  {{arg.TYPE.NAME}} l_{{arg.NAME}};
  is >> l_{{arg.NAME}};
  {%- if not loop.last %}is.get();{% endif %}

  {% endfor %}

  std::string l;
  std::getline(is, l);

  os << this->comp.{{ func.NAME }}({% for arg in func.SIGNATURE -%}
    l_{{arg.NAME}}
      {%- if not loop.last %}, {% endif %}
      {%- endfor %}) << std::endl;

    return;
  }
  {% endfor %}


  {% for d in DATA %}
void {{NAME}}_caller::get_{{ d.NAME }}(std::istream& is, std::ostream& os)
{
  std::string l;
  std::getline(is, l);
  os << this->comp.get_{{d.NAME}}() << std::endl;

  return;
}

void {{NAME}}_caller::set_{{ d.NAME }}(std::istream& is, std::ostream& os)
{
  {{d.TYPE.NAME}} set_val;
  is >> set_val;
  this->comp.set_{{d.NAME}}(set_val);

  std::string l;
  std::getline(is, l);

  os << std::endl;
  return;
}
  {% endfor %}



