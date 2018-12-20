
#include "Deployments/{{NAME}}/{{NAME}}.hpp"


{{NAME}}::{{NAME}}() {
  
}

{{NAME}}::~{{NAME}}() {
  
}

void {{NAME}}::init() {
  Deployment::init();

  {%for inst in INSTANCE %}
  this->components_add(&{{inst.NAME}});
  {%endfor%}
}

void {{NAME}}::configuration() {
  Deployment::configuration();

  {%for inst in INSTANCE %}
  {%if "WITH" in inst%}
  {%for key,val in inst.WITH.items() %}
  this->{{inst.NAME}}.set_{{key}}({{val}});
  {% endfor %}
  {% endif %}
  this->{{inst.NAME}}.configuration();
  {%endfor%}
}

void {{NAME}}::link() {


  {% for c in CONNECTION %}
  {
    {% if "LINK" in c %}
    {% if "WITH" in c.LINK %}
    {%for key,val in c.LINK.WITH.items() %}
    {{c.LINK.NAME}}.set_{{key}}({{val}});
    {% endfor %}
    {% endif %}
    {% if "FROM" in c and "TO" in c %}
    {{c.LINK.NAME}}.set_from_to((Interface**)&{{c.FROM.INSTANCE.NAME}}.{{c.FROM.INTERFACE.NAME}}, &{{c.TO.INSTANCE.NAME}}.{{c.TO.INTERFACE.NAME}});
    {% elif "TO" in c%}
    {{c.LINK.NAME}}.set_to(&{{c.TO.INSTANCE.NAME}}.{{c.TO.INTERFACE.NAME}});
    {% elif "FROM" in c%}
    {{c.LINK.NAME}}.set_from((Interface**) &{{c.FROM.INSTANCE.NAME}}.{{c.FROM.INTERFACE.NAME}});
    {% else %}
    // link error
    {%endif%}
    {{c.LINK.NAME}}.connect();
    this->link_add(&{{c.LINK.NAME}});
    
    {% endif %}

  }
  {% endfor %}

  Deployment::link();

  {%for inst in INSTANCE %}
  this->{{inst.NAME}}.connection();
  {%endfor%}
}

void {{NAME}}::start() {
  Deployment::start();

  {%for inst in INSTANCE %}
  this->{{inst.NAME}}.start();
  {%endfor%}
}

void {{NAME}}::stop() {
  Deployment::stop();

  {%for inst in INSTANCE %}
  this->{{inst.NAME}}.stop();
  {%endfor%}
}

void {{NAME}}::quit() {
  
}

