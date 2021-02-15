
#include "Interfaces/{{NAMESPACE.replace('::','/')}}/{{NAME}}/{{NAME}}.hpp"

{% include "helper/namespace_open.hpp" with context %}

{{NAME}}::{{NAME}}():a_caller_stream(nullptr){%if OPTIONS and OPTIONS.CALLER_DBUS %},a_caller_dbus(nullptr){% endif %} {}

{{NAME}}::~{{NAME}}() noexcept {
  if (a_caller_stream != nullptr) {
    delete a_caller_stream;
  }
  {%if OPTIONS and OPTIONS.CALLER_DBUS %}
  if (a_caller_dbus != nullptr) {
      delete a_caller_dbus;
  }
  {%endif%}
}

CompoMe::Caller_stream* {{NAME}}::get_caller_stream() {
  if (a_caller_stream == nullptr) {
    a_caller_stream = new MyCallerStream(*this);
  }
  return a_caller_stream;
}

{%if OPTIONS and OPTIONS.CALLER_DBUS %}
CompoMe::Caller_dbus* {{NAME}}::get_caller_dbus() {
  if (a_caller_dbus == nullptr) {
    a_caller_dbus = new MyCallerDbus(*this);
  }
  return a_caller_dbus;
}
{% endif %}
{% include "helper/namespace_close.hpp" with context %}
