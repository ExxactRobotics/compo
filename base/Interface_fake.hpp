#pragma once

#include "types.hpp"
#include "structs.hpp"

template <typename T>
class {{NAME}}_fake : public {{NAME}}
{
public:
  //! Default constructor
  {{NAME}}_fake(std::string& des, T& out):des(des),o(out)
            {

            }

  //! Destructor
  virtual ~{{NAME}}_fake() noexcept{}

  {%- for f in FUNCTION %}
  virtual
  {{ f["RETURN"]["NAME"] }} {{ f["NAME"] }}(
    {%- for a in f["SIGNATURE"] -%}
    {{a["TYPE"]["NAME"]}} {{a["NAME"] }}
    {%- if not loop.last%},{% endif %}
    {%- endfor-%}
    )
    {
      o << this->des << ".{{f["NAME"]}}("
                {% for a in f["SIGNATURE"] %}
        << {{a["NAME"] }}
           {%- if not loop.last%}
        << ","
           {% endif %}
      {%endfor%}
        << ")"
        << std::endl;
    }
  {%- endfor %}

  /////////////////////////////////////////////////////////////////////////////
  //                               GET and SET                               //
  /////////////////////////////////////////////////////////////////////////////
  {%- for v in DATA %}
  {{v["TYPE"]["NAME"]}} get_{{v["NAME"]}}() const {
    return {{v["NAME"]}};
  }

  void set_{{v["NAME"]}}(const {{v["TYPE"]["NAME"]}} {{v["NAME"]}}) {
    this->{{v["NAME"]}} = {{v["NAME"]}};
  }
  {%- endfor %}


protected:

private:
  std::string des;
  T& o;

  {%- for v in DATA %}
  {{v["TYPE"]["NAME"]}} {{v["NAME"]}};
  {%- endfor %}
};

