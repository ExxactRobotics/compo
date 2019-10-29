#pragma once

{% set i = MAIN.INTERFACES[INTERFACE] %}

#include "Interfaces/{{i.NAME}}/{{i.NAME}}.hpp"


class {{NAME}} {


  class {{NAME}}_{{i.NAME}} :  public {{i.NAME}} {
  public:
    {{NAME}}* lo;
    {{NAME}}_{{i.NAME}}({{NAME}}* p_lo = NULL):{{i.NAME}}(),lo(p_lo){
    }

    {%for f in i.FUNCTION %}
    virtual
    {{f.RETURN.NAME}} {{f.NAME}}(
      {%- for p in f.SIGNATURE -%}
      {{p.TYPE.NAME}} {{p.NAME}}{% if not loop.last %},{%endif%}
      {%- endfor -%}
      ){

      std::stringstream ss;

      struct timespec l_b;
      clock_gettime(CLOCK_MONOTONIC, &l_b);
      ss << l_b.tv_sec <<"," << l_b.tv_nsec << ":";

      ss << "{{f.NAME}}("
        {%-for p in f.SIGNATURE-%}
      << {{p.NAME}}{% if not loop.last %} << ","{%endif%}
      {%- endfor -%} << "):";

      {%if f.RETURN.NAME != "void" %}
      {{f.RETURN.NAME}} l_return = this->get__c().{{f.NAME}}({%- for p in f.SIGNATURE-%}{{p.NAME}}{% if not loop.last %},{%endif%}{%-endfor%});

      struct timespec l_a;
      clock_gettime(CLOCK_MONOTONIC, &l_a);
      ss << l_a.tv_sec <<"," << l_a.tv_nsec << ":";

      ss << l_return;
      {%else%}
      this->get__c().{{f.NAME}}({%- for p in f.SIGNATURE-%}{{p.NAME}}{% if not loop.last %},{%endif%}{%-endfor%});

      struct timespec l_a;
      clock_gettime(CLOCK_MONOTONIC, &l_a);
      ss << l_a.tv_sec <<"," << l_a.tv_nsec << ":void";
      {%endif%}

      ss << ":"<< (int64_t)(l_a.tv_sec - l_b.tv_sec) * (int64_t)1000000000UL
        + (int64_t)(l_a.tv_nsec - l_b.tv_nsec);

      this->get__os() << ss.str() << std::endl;

      {%if f.RETURN.NAME != "void" %}
      return l_return;
      {%else%}
      return;
      {%endif%}
    }
    {%endfor%}

    {%for d in i.DATA %}
    virtual
    {{d.TYPE.NAME}} get_{{d.NAME}}() const {
      std::stringstream ss;

      struct timespec l_b;
      clock_gettime(CLOCK_MONOTONIC, &l_b);
      ss << l_b.tv_sec <<"," << l_b.tv_nsec << ":";

      ss << "get_{{d.NAME}}():";
      {{d.TYPE.NAME}} l_return = this->get__c().get_{{d.NAME}}();

      struct timespec l_a;
      clock_gettime(CLOCK_MONOTONIC, &l_a);
      ss << l_a.tv_sec <<"," << l_a.tv_nsec << ":";

      ss << l_return;

      ss << ":"<< (int64_t)(l_a.tv_sec - l_b.tv_sec) * (int64_t)1000000000UL
        + (int64_t)(l_a.tv_nsec - l_b.tv_nsec);


      this->get__os() << ss.str() << std::endl;

      return l_return;
    }

    virtual
    void set_{{d.NAME}}({{d.TYPE.NAME}} {{d.NAME}}) {
      std::stringstream ss;

      struct timespec l_b;
      clock_gettime(CLOCK_MONOTONIC, &l_b);
      ss << l_b.tv_sec <<"," << l_b.tv_nsec << ":";

      ss << "set_{{d.NAME}}("<< {{d.NAME}} << "):";

      this->get__c().set_{{d.NAME}}({{d.NAME}});

      struct timespec l_a;
      clock_gettime(CLOCK_MONOTONIC, &l_a);
      ss << l_a.tv_sec <<"," << l_a.tv_nsec << ":";

      ss <<"void";

      ss << ":"<< (int64_t)(l_a.tv_sec - l_b.tv_sec) * (int64_t)1000000000UL
        + (int64_t)(l_a.tv_nsec - l_b.tv_nsec);

      this->get__os() << ss.str() << std::endl;
      return;
    }
    {%endfor%}

    {{i.NAME}}& get__c() const{
      return *this->lo->r;
    }

std::ostream& get__os() const{
      return *this->lo->os;
              }

  };

 public:

  {{NAME}}(std::ostream& p_os = std::cout):os(&p_os)
            {%for p in PROVIDE %},{{p.NAME}}(this){%endfor%} {
  }

  std::ostream* os;

  //  {{i.NAME}}* r;
  //  {{NAME}}_{{i.NAME}} p;
  // INTERFACE ////////////////////////////////////////////////////////////////
  // REQUIRES
  {% for pro in PROVIDE %}
  {{ pro.INTERFACE.NAME }}& get_{{ pro.NAME }}(){
    return this->{{ pro.NAME }};
  }
  {% endfor %}

  // PROVIDES
  {% for req in REQUIRE %}
  void set_{{ req.NAME }}({{ req.INTERFACE.NAME }}* p_r){
    this->{{ req.NAME }} = p_r;
  }
  {% endfor %}

 private:
  // INTERFACE ////////////////////////////////////////////////////////////////
  // REQUIRE
  {% for req in REQUIRE -%}
  {{ req.INTERFACE.NAME }}* {{ req.NAME }};
  {% endfor %}

  // PROVIDE
  {% for pro in PROVIDE -%}
  {{NAME}}_{{pro.INTERFACE.NAME }} {{pro.NAME}};
  {% endfor %}
};