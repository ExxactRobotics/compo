

#include "Components/CompoMe/Log/To_File_Log_I_log.hpp"
#include "Components/CompoMe/Log/To_File.hpp"

namespace CompoMe {

namespace Log {

constexpr unsigned int str2int(const char *str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

To_File_Log_I_log::To_File_Log_I_log(To_File *comp) : composant(comp) {
  return;
}

//! Destructor
To_File_Log_I_log::~To_File_Log_I_log() noexcept { return; }

To_File &To_File_Log_I_log::get_c() const { return *this->composant; }

void To_File_Log_I_log::error(CompoMe::String mess, CompoMe::Log::Log_Info i) {

  void();

  return;
}
void To_File_Log_I_log::warning(CompoMe::String mess,
                                CompoMe::Log::Log_Info i) {

  void();

  return;
}
void To_File_Log_I_log::debug(CompoMe::String mess, CompoMe::Log::Log_Info i) {

  void();

  return;
}
void To_File_Log_I_log::info(CompoMe::String mess, CompoMe::Log::Log_Info i) {

  void();

  return;
}
void To_File_Log_I_log::log(CompoMe::Log::Kind_e k, CompoMe::String mess,
                            CompoMe::Log::Log_Info i) {

  void();

  return;
}

// Log_I ///////////////////////////////////////////////////////////////////

std::ostream &To_File_Log_I_log::to_stream(
    std::ostream &os, CompoMe::Serialization_context_export &p_ctx) const {
  os << "{";
  os << "type:"
     << "CompoMe::Log::To_File_Log_I_log";

  os << "}";
  return os;
}

std::istream &
To_File_Log_I_log::from_stream(std::istream &is,
                               CompoMe::Serialization_context_import &p_ctx) {
  char l_c = is.get();
  if (l_c != '{') {
    std::cerr << "Wrong start: '" << l_c << "' != '{'";
    throw "Wrong start: '"
          "' != '{'";
  }

  do {
    std::string args;
    std::getline(is, args, ':');

    switch (str2int(args.c_str())) {
    case str2int("type"): {
      auto t = CompoMe::get_word(is, {',', '}'});
      if (t.first != "CompoMe::Log::To_File_Log_I_log") {
        throw "Wrong Type: ";
      }
      break;
    }

    default:
      std::cerr << "wrong attribute: \"" << args
                << "\" not in provide To_File_Log_I_log";
      throw "wrong attribute: \"" + args +
          "\" not in provide To_File_Log_I_log";
      break;
    }

    l_c = is.get();
  } while (l_c == ',');

  return is;
}

} // namespace Log

} // namespace CompoMe