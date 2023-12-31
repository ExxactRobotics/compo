# !/bin/env python
import os.path

from model_dump import yaml

from Config import Configuration_manager
from model_exec import get_exec_function

from model_get import get_empty_main
from tools.Log import ERR, INFO, DEBUG

from model_parsing_context import *

from model_expand_type import type_expand
from model_expand_error import error_expand
from model_expand_event import event_expand, bus_expand
from model_expand_struct import struct_expand
from model_expand_interface import interface_expand
from model_expand_connector import connector_expand
from model_expand_component import component_expand
from model_expand_port import port_expand
from model_expand_link import link_expand
from model_expand_deployment import deployment_expand
from model_get import get_import


def nop_expand(main, data, log=False):
    ERR("Parsing is not implemented for",
        data)

    return None


def import_expand(context, main, data, log=False):

    if isinstance(data, dict) or isinstance(data, list):
        ERR("Import !y(", data, ") is not a string")

    if isinstance(data, str):
        file = data
        list_path = Configuration_manager.get_conf().get("import_path")
        valid = None

        for l in list_path:
            path_file = l + os.path.sep + file
            if os.path.isfile(path_file):
                valid = path_file
                break

        if valid is None:
            ERR("file: !y(", file, ") doesn't exit :\n",
                "".join(["> !y("+m+")\n" for m in context_list_file(context)]))
        valid = os.path.realpath(valid)
        if context_already_import(context, valid):
            return {"NAME": file,
                    "PATH": valid,
                    "MAIN": context_get_main(context, valid)}
        else:
            INFO(valid, "\n", "".join(
                ["> !y("+m+")\n" for m in context_list_file(context)]))

        if len(context_list_file(context)) > 100:
            ERR("Import stack upper than 100, maybe a infinite loop?\n",
                "".join(["> !y("+m+")\n" for m in context_list_file(context)]))

        main_import = get_empty_main()
        main_import["UP"] = main
        main_import = file_expand(context, main_import, valid, log)

        return {"NAME": file,
                "PATH": valid,
                "MAIN": main_import}


def get_expand_function():

    EXPAND_FONCTION = {
        "IMPORT": import_expand,
        "TYPE": type_expand,
        "ERROR": error_expand,
        "EVENT": event_expand,
        "BUS": bus_expand,
        "LINK": link_expand,
        "STRUCT": struct_expand,
        "INTERFACE": interface_expand,
        "PORT": port_expand,
        "CONNECTOR": connector_expand,
        "COMPONENT": component_expand,
        "DEPLOYMENT": deployment_expand}

    return EXPAND_FONCTION


def use_type_in_struct(type, struct):
    for d in struct["DATA"]:
        if use_type_in_TYPE(type, d):
            return True
    return False


def use_type_in_TYPE(type, TYPE):
    if TYPE == type:
        return True

    # on a une struct
    if "DATA" in TYPE:
        return use_type_in_struct(TYPE)


def get_struct_with_type(type, structs):

    use_by_structs = []
    for struct in structs:
        if use_type_in_struct(type, struct):
            use_by_structs.append(struct)

    return use_by_structs


def use_type_in_interface(type, interface):

    if "DATA" in interface:
        for d in interface["DATA"]:
            if use_type_in_TYPE(type, d["TYPE"]):
                return True

    if "FUNCTION" in interface:
        for d in interface["FUNCTION"]:
            if use_type_in_TYPE(type, interface["RETURN"]):
                return True
            for param in d["SIGNATURE"]:
                if use_type_in_TYPE(type, param["TYPE"]):
                    return True


def get_interfaces_with_type(type, interfaces):

    use_by_interface = []

    for interface in interfaces:
        if use_type_in_interface(type, interface):
            use_by_interface.append(interface)

    return use_by_interface


def use_type_in_component(type, component):

    if "DATA" in component:
        for d in component["DATA"]:
            if use_type_in_TYPE(type, d):
                return True
    if "PROVIDE" in component:
        for d in component["PROVIDE"]:
            if use_type_in_interface(type, d):
                return True

    if "REQUIRE" in component:
        for d in component["REQUIRE"]:
            if use_type_in_interface(type, d):
                return True

    return False


def get_component_with_type(type, components):

    # STRUCT CHECK
    use_by_component = []

    for component in components:
        if use_type_in_component(type, component):
            use_by_component.append(component)

    return use_by_component


def use_type_in_deployment(type, deployment):

    if "COMPONENT_INSTANCE" in deployment:
        for d in deployment["COMPONENT_INSTANCE"]:
            if use_type_in_component(type, deployment):
                return True

    return False


def get_deployment_with_type(type, deployments):
    use_by_deployment = []

    for deployment in deployments:
        if use_type_in_deployment(type, deployment):
            use_by_deployment.append(deployment)

    return use_by_deployment


def file_expand(context, main, file_path, log=False):

    conf = Configuration_manager.get_conf()

    # apply a read only value as real values
    if not conf.exist("import_path"):
        conf.set("import_path", conf.get("import_path"))

    conf.get("import_path").append(os.path.dirname(file_path))

    fp = os.path.realpath(file_path)
    if context is None:
        first_in = True
        context = context_create(fp)
        main = context_get_main(context, fp)
    else:
        first_in = False
        main = context_add_file(context, fp)

    main["NAME"] = os.path.basename(fp)
    main["F_NAME"] = fp
    main["D_NAME"] = main["F_NAME"]
    main["NAMESPACE"] = os.path.dirname(fp)

    if not os.path.isfile(fp):
        ERR(">!y(", fp, ")",
            " doesn't exist")

    with open(fp) as file:
        data = yaml.load(file, Loader=yaml.SafeLoader)

    EXPAND_FONCTION = get_expand_function()
    EXEC_FUNCTION = get_exec_function()

    if data is None:
        return main

    for a in data:
        function_selector = list(a)[0]
        if function_selector not in EXEC_FUNCTION and function_selector not in EXPAND_FONCTION:
            ERR("The !y(", function_selector, ") is not a valid key choose one of !b(", ','.join(
                [*EXEC_FUNCTION, *EXPAND_FONCTION]), ")")

        information = a[function_selector]
        if function_selector in EXPAND_FONCTION:
            full_name = False
            if not isinstance(information, str):
                full_name = ((information["NAMESPACE"] + "::")
                             if "NAMESPACE" in information else "") + information["NAME"]
                l_tmp = full_name.split("::")
                if len(l_tmp) != 1:
                    namespace = "::".join(l_tmp[0:-1])
                else:
                    namespace = ""
                name = l_tmp[-1]

                information["NAME"] = name
                information["NAMESPACE"] = namespace
                information["D_NAME"] = full_name
                information["F_NAME"] = full_name.replace('::', '/')

            DEBUG("EXPAND_FONCTION: ", function_selector)
            if function_selector == "IMPORT":
                key = information
            else:
                key = full_name if full_name else information["NAME"]

            context_add_element(context, function_selector, information, main)
            continue

        if function_selector in EXEC_FUNCTION:
            context_add_exec(context, function_selector, information, main)
            # EXEC_FUNCTION[function_selector](main, information)
            continue

    while len(context["element_to_expand"]["IMPORTS"]) != 0:
        i = context["element_to_expand"]["IMPORTS"].pop(0)
        id = i[0]
        im = i[1]
        d = EXPAND_FONCTION["IMPORT"](context,
                                      im,
                                      id,
                                      log=True)
        if d is None:
            continue

        im["IMPORTS"][d["PATH"]] = d

    if first_in:
        for kind_exp in context["expand_order"][1:]:
            while len(context["element_to_expand"][kind_exp]) != 0:
                i = context["element_to_expand"][kind_exp].pop(0)
                id = i[0]
                im = i[1]
                im[kind_exp][id["D_NAME"]] = id
                d = EXPAND_FONCTION[kind_exp[:-1] if kind_exp != "BUS" else "BUS"](context,
                                                                                   im,
                                                                                   id,
                                                                                   log=True)
                if d is not id:
                    print("wrong for ", id["D_NAME"])
                    exit()

        for k, v, m in context["exec_code"]:
            EXEC_FUNCTION[k](m, v)

    context_pop_file(context)
    conf.get("import_path").pop()

    return main


def str_expand(context, main, code, log=False):

    conf = Configuration_manager.get_conf()

    # apply a read only value as real values
    if not conf.exist("import_path"):
        conf.set("import_path", conf.get("import_path"))

    #    conf.get("import_path").append("-- Shell Code --")

    fp = "/dev/stdin"  # os.path.realpath(file_path)
    if context is None:
        first_in = True
        context = context_create(fp)
        main = context_get_main(context, fp)
    else:
        first_in = False
        main = context_add_file(context, fp)

    main["NAME"] = os.path.basename(fp)
    main["F_NAME"] = fp
    main["D_NAME"] = main["F_NAME"]
    main["NAMESPACE"] = os.path.dirname(fp)

    code = code.replace("\t", "    ")
    try:
        data = yaml.load(code, Loader=yaml.SafeLoader)
    except Exception as e:
        ERR(">!y(", code, ")",
            " is not valid", e)

    EXPAND_FONCTION = get_expand_function()
    EXEC_FUNCTION = get_exec_function()

    if data is None:
        return main

    for a in data:
        function_selector = list(a)[0]
        if function_selector not in EXEC_FUNCTION and function_selector not in EXPAND_FONCTION:
            raise ValueError("The !y(" + function_selector + ") is not a valid key choose one of !g(" +
                             "),!g(".join([*EXEC_FUNCTION.keys(), *EXPAND_FONCTION.keys()])+")")

        information = a[function_selector]

        if function_selector in EXPAND_FONCTION:
            full_name = False
            if not isinstance(information, str):
                full_name = ((information["NAMESPACE"] + "::")
                             if "NAMESPACE" in information else "") + information["NAME"]
                l_tmp = full_name.split("::")
                if len(l_tmp) != 1:
                    namespace = "::".join(l_tmp[0:-1])
                else:
                    namespace = ""
                name = l_tmp[-1]

                information["NAME"] = name
                information["NAMESPACE"] = namespace
                information["D_NAME"] = full_name
                information["F_NAME"] = full_name.replace('::', '/')

            DEBUG("EXPAND_FONCTION: ", function_selector)
            if function_selector == "IMPORT":
                key = information
            else:
                key = full_name if full_name else information["NAME"]

            context_add_element(context, function_selector, information, main)
            continue

        if function_selector in EXEC_FUNCTION:
            context_add_exec(context, function_selector, information, main)
            continue

    while len(context["element_to_expand"]["IMPORTS"]) != 0:
        i = context["element_to_expand"]["IMPORTS"].pop(0)
        id = i[0]
        im = i[1]
        d = EXPAND_FONCTION["IMPORT"](context,
                                      im,
                                      id,
                                      log=True)
        if d is None:
            continue

        im["IMPORTS"][d["PATH"]] = d

    if first_in:
        for kind_exp in context["expand_order"][1:]:
            while len(context["element_to_expand"][kind_exp]) != 0:
                i = context["element_to_expand"][kind_exp].pop(0)
                id = i[0]
                im = i[1]
                im[kind_exp][id["D_NAME"]] = id
                d = EXPAND_FONCTION[kind_exp[:-1] if kind_exp != "BUS" else "BUS"](context,
                                                                                   im,
                                                                                   id,
                                                                                   log=True)
                if d is not id:
                    print("wrong for ", id["D_NAME"])
                    exit()

        for k, v, t in context["exec_code"]:
            EXEC_FUNCTION[k](t, v)

    context_pop_file(context)
    conf.get("import_path").pop()

    return main
