# What is CompoMe ?
 CompoMe is a Framework Component. This goal is to provide a way to organize the code and generate the connection code.
 
In order to do it, we create a component/interface generator and many other functionality.

This approach have to focus on
- Reuse Code
- Direct vision of a component
- Clear code organization
- Tool to code
- Code generation

## How to use it

- Create a interface
- Create a component
- Say which interfaces a component implement
- Say which interface a component use
- Generate Code
- Write the implementation code
- Instantiate them
- Connect the Component to each other

## How to install it

CompoMe is split in Three part
- The parser of the CompoMe File and Checker
- The generation template witch can be the CPP,PYTHON,UML or graph (or a new one than you can write for you)
- The lib part witch is the implementation of many useful link. (you can redevelop them if you want).

 


# How to install CompoMe?

clone the repository.
```bash
git clone https://gitlab.marger.it:10443/ruhtra/compo 
```

Install the dependencies.
For All:
* git
* python3
* python3-pip

CPP:
* cmake
* make
* g++
* clang++
* swig 
* clang-format

GRAPH:
* graphviz

UML:
* plantuml

Install the Python dependencies (python3).
```bash
pip install -r tools/env.txt
```

Define the environment variable.
```bash
export COMPOME_PATH=/where/i/clone/compo
export COMPOME_MODEL_PATH=${COMPOME_PATH}/CompoMe:.
```

Define the language that you want to use.
### For c++
```bash
export COMPOME_MODEL=CPP
```

### For Graph
```bash
export COMPOME_MODEL=GRAPH
export COMPOME_GRAPH_PATH=${COMPOME_PATH}/CompoMe:.
```

### Compile/Generate Lib
#### Cpp



#### Graph

# Example
## C++ basic example

Example : file.yaml
```bash
- IMPORT: CompoMe.yaml

- INTERFACE:
    NAME: Gate
    FUNCTION:
      - void lock ()
      - void unlock ()

- COMPONENT:
    NAME: Room
    PROVIDE:
    - Gate Front_door
    - Gate Back_door
```

Generate code
```bash
$ compome generate -f file.yaml
```

Write your specific code in the implementations
## More C++ example
You can find some C++ example:
* Examples/HelloWord: a basic example of a udp server that answer to the helloWord question
* Examples/Interface: an introduction CompoMe Interface and a test of COmpoMe::term
* Examples/Car: an introduction to CompoMe Component.

* Examples/Dbus_Server: Dbus server example
* Examples/Dbus_Client: Dbus client example

## GRAPH generated example
![1](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/D1.d.png)
![2](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/D2.d.png 
![3](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/D3.d.png)

## UML generated example
![Structs](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/Structs.png)
![Interfaces](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/Interfaces.png)
![Components](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/Components.png)
![Deployment](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/Deployments.png)


# All Compome Element

## Type:
The type is a system to define Type:
- basic type of a language like void,int,long,char etc...
- external struct or class like std::string, std::vector etc... 
- pointer, std::shared_ptr and ref
- Template Type.

## Enum:
As c/c++ you can define enum.

## Struct:
Help the user to define struct.
You can define:

- Attribute (can be a other Struct/Type/Enum)
- Function (with One return value and many argument)
- Parent (only one Struct)

Compome is in charge of:
- Serialization to stream / to Dbus / ...
- UML generation
- get/set

## Interface
You can define:
- Attribute
- Function
- Parent

Compome is in charge of:
- Call to String
- String to Call
- get/set

Useful Note:
* CompoMe::call
* CompoMe::term

## Component
You can define:
- Attribute
- Function
- Provide
- Require
- Sub Component
- Sub Connector
- Connection
- Parent

## Connector
## Link
## Deployment


#  How to run test ?

```bash
# jump to test
cd Test/gen
./run_test.sh cpp
./run_test.sh graph
./run_test.sh uml
./run_test.sh python
```

# Générateur
## Générateur list 
  * __C++__:  You need to support _c++11_ and the std.
  * __PYTHON__: started
  * __UML__: Generate uml dep graph 
  * __GRAPH__: generate graphic view of component and deployment

### GLOBAL
| GÉNÉRATEUR | TYPE | STRUCTURE | INTERFACE | DÉPLOIEMENT | COMPOSANT | LINK | COMPILATION | RUN |
|------------|------|-----------|-----------|-------------|-----------|------|-------------|-----|
| C++        | OK   | OK        | OK        | OK          | OK        | OK   | OK          | OK  |

### TYPE
| GÉNÉRATEUR | Function | Pointer | array | default | array TO_STR | pointer TO_STR | STR_TO_pointer | STR_TO_SP |
|------------|----------|---------|-------|---------|--------------|----------------|----------------|-----------|
| C++        | OK       | OK      | OK    | OK      | OK           | OK             | OK             | OK        |

### Enum
| GÉNÉRATEUR | DEFAULT | SERIALIZATION |
|------------|---------|---------------|
| C++        | OK      | OK            |

### STRUCTURE
| GÉNÉRATEUR | get | set | constucteur | default | PARENT | SHELL |
|------------|-----|-----|-------------|---------|--------|-------|
| C++        | OK  | OK  | OK          | OK      | OK     | OK    |


### ERROR
| GÉNÉRATEUR | get | set | constucteur | TO_STR | FROM_STR | DEFAULT | PARENT |
|------------|-----|-----|-------------|--------|----------|---------|--------|
| C++        | OK  | OK  | OK          | OK     | OK       | TODO    | OK     |


### INTERFACE
| GÉNÉRATEUR | INTERFACE | COMPOSANT ACCÈS | FUNCTION | DATA | get | set | default | DISTRIBUTE | PARENT |
|------------|-----------|-----------------|----------|------|-----|-----|---------|------------|--------|
| C++        | OK        | OK              | OK       | OK   | OK  | OK  | OK      | -          | OK     |


### SERIALIZATION
| SERIALIZATION | TYPE | STRUCT | ERROR | CALLER | FAKE | POINTER | CONTEXT |
|---------------|------|--------|-------|--------|------|---------|---------|
| C++/STREAM    | OK   | OK     | OK    | OK     | OK   | OK      | PARTIAL |
| C++/DBUS      | OK   | OK     | -     | OK     | OK   | -       | -       |
| C++/JSON      | -    | -      | -     | -      | -    | -       | -       |


### COMPONENT
| GÉNÉRATEUR | INTERFACE | ACCES INTERFACE | FUNCTION | DATA | INIT | COPY | DESTRUCTION | get | set | default | PARENT | SAVE | RESTORE |
|------------|-----------|-----------------|----------|------|------|------|-------------|-----|-----|---------|--------|------|---------|
| C++        | OK        | OK              | OK       | OK   | OK   | OK   | OK          | OK  | OK  | OK      | OK     | -    | -       |

### SUBCOMPONENT
| GÉNÉRATEUR | SUBCOMPONENT | CONNECTION C2SC | CONNECTION SC2C | CONNECTION SC2SC | STEP |
|------------|--------------|-----------------|-----------------|------------------|------|
| C++        | OK           | OK              | OK              | OK               | OK   |


### DEPLOIMENT
| GÉNÉRATEUR | DEPLOIMENT | Instance | INSTALLATION LINK | default | CONNECTION |
|------------|------------|----------|-------------------|---------|------------|
| C++        | OK         | OK       | OK                | OK      | OK         |


### LINK
| GÉNÉRATEUR | LINK |
|------------|------|
| C++        | OK   |


### COMPILATION
| GÉNÉRATEUR        | COMPILATION | CMAKE FULL | CMAKE COMPOSANT | CMAKE RUN |
|-------------------|-------------|------------|-----------------|-----------|
| C++ CMAKE MAKE    | OK          | OK         | OK              | OK        |
| C++ CMAKE NINJA   | -           | -          | -               | -         |
| C++ CMAKE WINDOWS | -           | -          | -               | -         |
| ...               |             |            |                 |           |


### RUN
| GÉNÉRATEUR | RUN | MEMORY | DEBUG | UNIT TEST | SHELL |
|------------|-----|--------|-------|-----------|-------|
| C++        | OK  | OK     | OK    | -         | -     |
| ...        |     |        |       |           |       |

### LINK
| GÉNÉRATEUR | IN | OUT | MULTI_IN |
|------------|----|-----|----------|
| C++ FIFO   | OK | OK  | NO       |
| C++ UDP    | -  | -   | YES      |
| C++ TCP    | -  | -   | YES      |
| C++ SHMEM  | -  | -   | NO       |
| C++ DIRECT | OK | OK  | NO       |
