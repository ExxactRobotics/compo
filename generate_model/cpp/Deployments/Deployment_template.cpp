#include "Deployments/{{D_NAME.replace('::','/')}}/{{NAME}}.hpp"

{% include "helper/namespace_open.hpp" with context %}
// CONSTRUCTOR ////////////////////////////////////////////////////////////////
{{NAME}}::{{NAME}}():{%if PARENT %}{{PARENT.D_NAME}}(){% else %}Deployment(){% endif %} {

}

{{NAME}}::~{{NAME}}() {

}

// DEPLOYMENT BASIC FUNCTION //////////////////////////////////////////////////
void {{NAME}}::init() {
  {% if PARENT%}
  {{PARENT.D_NAME}}::init();
  {% else %}
  Deployment::init();
  {% endif %}

  {%for inst in COMPONENT_INSTANCE %}
  this->components_add(&{{inst.NAME}});
  {%endfor%}
}

void {{NAME}}::configuration() {
  {% if PARENT%}
  {{PARENT.D_NAME}}::configuration();
  {% else %}
  Deployment::configuration();
  {% endif %}

  {%for inst in COMPONENT_INSTANCE %}
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
    this->get_{{c.LINK.NAME}}().set_{{key}}({{val}});
    {% endfor %}
    {% endif %}

    {% if "FROM" in c %}
    this->get_{{c.LINK.NAME}}().set_out({% if "AT" in c%}{{c.AT}},{%endif%}
 this->get_{{c.FROM.INSTANCE.NAME}}().fake_{{c.FROM.INTERFACE.NAME}}());
    {% elif "TO" in c%}
    this->get_{{c.LINK.NAME}}().set_in({% if "AT" in c%}{{c.AT}},{%endif%}
 &this->get_{{c.TO.INSTANCE.NAME}}().get_{{c.TO.INTERFACE.NAME}}()
     );
    {% endif %}

    this->get_{{c.LINK.NAME}}().connect();
    this->link_add(&this->get_{{c.LINK.NAME}}());
    {% else %}
    this->get_{{c.FROM.INSTANCE.NAME}}().{{c.FROM.KIND}}_{{c.FROM.INTERFACE.NAME}}(&this->get_{{c.TO.INSTANCE.NAME}}().get_{{c.TO.INTERFACE.NAME}}());
    {% endif %}
  }
  {% endfor %}

  {%if PARENT -%}
  {{PARENT.D_NAME}}::link();
  {%else-%}
  Deployment::link();
  {%endif-%}

  {%for inst in COMPONENT_INSTANCE %}
  this->{{inst.NAME}}.connection();
  {%endfor%}
}

void {{NAME}}::start() {
  {%if PARENT -%}
  {{PARENT.D_NAME}}::start();
  {%else-%}
  Deployment::start();
  {%endif-%}

  {%for inst in COMPONENT_INSTANCE %}
  this->{{inst.NAME}}.start();
  {%endfor%}
}

void {{NAME}}::stop() {
  {%if PARENT -%}
  {{PARENT.D_NAME}}::stop();
  {%else-%}
  Deployment::stop();
  {%endif-%}

  {%for inst in COMPONENT_INSTANCE %}
  this->{{inst.NAME}}.stop();
  {%endfor%}
}

void {{NAME}}::quit() {
  {%if PARENT -%}
  {{PARENT.D_NAME}}::quit();
  {%else-%}
  Deployment::quit();
  {%endif-%}
}

// GET ////////////////////////////////////////////////////////////////////////
// COMPONENT
{%for inst in COMPONENT_INSTANCE %}
{{inst.COMPONENT.D_NAME}}::{{inst.COMPONENT.NAME}}&
  {{NAME}}::get_{{inst.NAME}}() {
    return this->{{inst.NAME}};
}
{%endfor%}

// CONNECTOR
{%for inst in CONNECTOR_INSTANCE %}
{{inst.CONNECTOR.D_NAME}}&
  {{NAME}}::get_{{inst.NAME}}() {
    return this->{{inst.NAME}};
}
{%endfor%}

// LINK
{%for link in LINK_INSTANCE %}
  {{link.TYPE.D_NAME}}&
   {{NAME}}::get_{{link.NAME}}() {
    return this->{{link.NAME}};
}
{%endfor%}


void {{NAME}}::save(std::ostream& os) const {
  os << "{";
  os << "addr:" << (void*)this;
  os << ",type:" << "{{NAME}}";

  {% if PARENT -%}
  os << ",parent:";
  {{PARENT.D_NAME}}::save(os);
  {%- endif-%}

  {% if DATA -%}
  os << ",data: {";
  {% for d in DATA %}
  os << "{{d.NAME}}:" << this->{{d.NAME}};
  {% endfor %}
  os << "}";
  {% endif %}
  // os << ",components_instances: [";
  // for (auto& i_sc : this->components) {
  //   os << i_sc;
  //   if(i_sc != this->components.back()){ os << ","; }
  // }
  // os << "]";

  // // os << ",connector_instance: [";
  // // for (auto& i_sc : this->connector_instance) {
  // //   os << i_sc;
  // //   if(i_sc != this->connector_instance.back()){ os << ","; }
  // // }
  // // os << "]";

  // os << ",links_instances: [";
  // for (auto& i_sc : this->links) {
  //   os << i_sc;
  //   if(i_sc != this->links.back()){ os << ","; }
  // }
  os << "]";
  os << "}";
}

void {{NAME}}::load(std::istream& is) {
  // TODO
}

{% include "helper/namespace_close.hpp" with context%}
