import collections
from termcolor import colored

from model_test import is_struct


def get_type_or_struct(main, key):
    if key in main["TYPES"] and key in main["STRUCTS"]:
        print("WARNING: TYPES and struct DEFINITION for ", key)

    if key in main["TYPES"]:
        return main["TYPES"][key]

    if key in main["STRUCTS"]:
        return main["STRUCTS"][key]

    print(colored("ERROR", "red"),
          "aucun STRUCT ou TYPE  avec le nom >",
          colored(key, "red"),
          "<")


def get_interface(main, key):
    if key in main["INTERFACES"]:
        return main["INTERFACES"][key]

    print(colored("ERROR", 'red'),
          "aucun INTERFACES avec le nom >",
          colored("key", 'green'),
          "<")


def get_component(main, key):

    if key in main["COMPONENTS"]:
        return main["COMPONENTS"][key]

    print(colored("ERROR", "red"),
          " aucun COMPONENT avec le nom >",
          colored(key, "green"),
          "<")

    return None


def get_link(main, key):
    key = key.replace("-(", "")
    key = key.replace(")->", "")

    if key in main["LINKS"]:
        return main["LINKS"][key]

    print(colored("ERROR", "red"),
          "aucun LINK avec le nom >",
          colored(key, "red"),
          "<")


def get_linker_instance(main, compo, key):

    if "LINKER" in compo:
        for linker in compo["LINKER"]:
            print(linker)
            if linker["NAME"] == key:
                return linker

    print(colored("ERROR", "red"),
          "aucune instance de LINKER avec le nom >",
          colored(key, "red"),
          "< dans le deploiment",
          colored(compo["NAME"], "red"))



def get_linker(main, key):

    if key in main["LINKERS"]:
        return main["LINKERS"][key]

    print(colored("ERROR", "red"),
          "aucun LINKER avec le nom >",
          colored(key, "red"),
          "<")


def get_stuct(main, key):
    if key in main["STRUCTS"]:
        return main["STRUCTS"][key]

    print(colored("ERROR", "red"),
          "aucune STRUCT avec le nom >",
          colored(key, "red"),
          "<")


def get_deployment(main, key):
    if key in main["DEPLOYMENTS"]:
        return main["DEPLOYMENTS"][key]

    print(colored("ERROR", "red"),
          "aucune DEPLOYMENT avec le nom >",
          colored(key, "red"),
          "<")


def get_instances(element_list, element_name ):
    element = element_list[element_name]
    f = element["INSTANCE"]

    if "PARENT" not in element or element["PARENT"] is None:
        return f

    parent_f = get_instances(element_list, element["PARENT"]["NAME"])

    return [*f, *parent_f]



def get_functions(element_list, element_name):

    element = element_list[element_name]
    f = element["FUNCTION"]

    if "PARENT" not in element or element["PARENT"] is None:
        return f

    parent_f = get_functions(element_list, element["PARENT"]["NAME"])

    return [*f, *parent_f]


def get_datas(element_list, element_name):

    element = element_list[element_name]
    d = element["DATA"]

    if "PARENT" not in element or element["PARENT"] is None:
        return d

    parent_d = get_datas(element_list, element["PARENT"]["NAME"])

    return [*d, *parent_d]


def get_struct_use_by(main, function, data):
    unique_list = dict()

    for f in function:
        if is_struct(f["RETURN"]["NAME"], main["STRUCTS"]):
            unique_list[f["RETURN"]["NAME"]] = f["RETURN"]

        for p in f["SIGNATURE"]:
            if not main["STRUCTS"] and is_struct(p["TYPE"]["NAME"], main["STRUCTS"]):
                unique_list[p["TYPE"]["NAME"]] = p["TYPE"]

    for a in data:
        if is_struct(a["TYPE"]["NAME"], main["STRUCTS"]):
            unique_list[a["TYPE"]["NAME"]] = a["TYPE"]

    return unique_list






def get_list_provide_of_composant(main, composant_name):
    pass


def get_list_require_of_composant(main, composant_name):
    pass


def get_empty_main():
    main = collections.OrderedDict()
    main["TYPES"] = collections.OrderedDict()
    main["STRUCTS"] = collections.OrderedDict()
    main["INTERFACES"] = collections.OrderedDict()
    main["LINKS"] = collections.OrderedDict()
    main["LINKERS"] = collections.OrderedDict()
    main["COMPONENTS"] = collections.OrderedDict()
    main["DEPLOYMENTS"] = collections.OrderedDict()
    main["IMPORTS"] = collections.OrderedDict()

    return main
