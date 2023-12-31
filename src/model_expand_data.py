import collections

from model_get import get_type_or_struct
from model_check import is_valid_name
from collections import OrderedDict

from tools.Uni import Uni
from tools.Log import ERR

from model_get import is_struct
import ast


def have_default(d):
    if isinstance(d, dict):
        return "DEFAULT" in d

    if isinstance(d, str):
        return "DEFAULT" in d or "WITH" in d


def parse_arg(data):
    position_first_realchar = 0
    for a in data:
        if a == " ":
            position_first_realchar += 1
        else:
            break
    data = data[position_first_realchar:]
    r = ast.literal_eval(data)
    return r


def default_expand(main, Type, data, log=False):

    if data is None or data == []:
        return ""

    if is_struct(Type["D_NAME"], main):
        return parse_arg(data)
    else:
        return data

    return "Erreur"


def declaration_expand(main, d, log=False):

    if isinstance(d, dict):
        r = collections.OrderedDict()
        r["NAME"] = d["NAME"]
        r["TYPE"] = get_type_or_struct(main, d["TYPE"])
        r["DEFAULT"] = default_expand(main, d["DEFAULT"])
        return r

    elif isinstance(d, str):
        words = d.split(" ")
        if len(words) == 1:
            ERR("The declaration !y(", d, ") have to be !b(TYPE) !g(NAME)")

        r = collections.OrderedDict()

        r["NAME"] = words[1]
        r["TYPE"] = get_type_or_struct(main, words[0])
        if have_default(d):
            r["DEFAULT"] = default_expand(main,
                                          r["TYPE"],
                                          d.split("WITH")[1],
                                          log)
        return r


def data_checks(p_all_data):
    if not isinstance(p_all_data, list):
        ERR("DATA !y(", p_all_data, ") is not a list or equivalent")

    for i_data in p_all_data:
        data_check(i_data)


def data_check(data):

    if "NAME" not in data:
        ERR("declaration sans NAME")

    is_valid_name(data["NAME"])

    if "TYPE" not in data:
        ERR("declaration sans TYPE")
    else:
        if not isinstance(data["TYPE"], dict):
            ERR("Type !y(", data["TYPE"], ") is not valid")


def data_expand(main, data, log=False):

    data_parser = []
    u = Uni()

    for d in data["DATA"]:
        p = declaration_expand(main, d, log)
        if not u.check(p["NAME"]):
            ERR("nom en double ",
                ">!y(", p["NAME"], ")<",
                " dans la struct ",
                ">!y(", data["NAME"], ")<")
        data_parser.append(p)

    return data_parser


def key_expand(main, data, log=False):

    data_parser = []
    u = Uni()

    for d in data["KEY"]:
        p = declaration_expand(main, d, log)
        if not u.check(p["NAME"]):
            ERR("nom en double ",
                ">!y(", p["NAME"], ")<",
                " dans la struct ",
                ">!y(", data["NAME"], ")<")
        data_parser.append(p)

    return data_parser
