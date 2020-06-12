# MYCI
_My_Composant_Implementation_

This project is a framework component.

Good for:
- Reuse Code
- Clear code organization
- Tool to code

Step:

- Create one or more interface.
- Create a component witch implements interfaces and other interfaces

Example : file.yaml

```bash
## Type Definition
- TYPE:
    NAME: int 
    DEFINITION: int
    NATIF: True

- TYPE:
    NAME: ui8
    DEFINITION: std::uint8_t
    INCLUDE: "<cstdint>"

- TYPE:
    NAME: void
    DEFINITION: void
    NATIF: True

- TYPE:
    NAME: string
    DEFINITION: std::string
    INCLUDE: <string>

## Interface to lock/open the door of a car
- INTERFACE:
    NAME: Car::Gate::Locker
    FUNCTION:
      - void open_window ()
      - void close_window ()
      - string state ()

## Interface to open/close the windows of a car
- INTERFACE:
    NAME: Car::Gate::Window
    DATA:
      - ui8 percent
    FUNCTION:
      - void lock ()
      - void unlock ()

## Interface to report the state of a car system
- INTERFACE:
    NAME: Car::Reporter
    FUNCTION:
      - void send_err (int err_code, string message)
      - void send_info (int info_code, string message)

## Component in place to manage a door and windows car
- COMPONENT:
    NAME: Car::Gates::controller
    PROVIDE:
    - Car::Gate::Window win
    - Car::Gate::Locker locker
    REQUIRE:
    - Car::Reporter reporting_station
```

- Generate code
```bash
$ compome generate -f file.yaml
$ # compile it // by default the code should compile
$ 
```

- Write your specific code in the implementations





#  How to run test ?

```bash
# Download the project
git clone https://www.gitlab.marger.it:10443/ruhtra/compo

# jump to test
cd compo/Test/gen

# run test for cpp
./run_test.sh cpp
./run_test.sh graph
./run_test.sh uml
./run_test.sh python
```

# Générateur
## Générateur list 
  * __C++__:  You need to support _c++11_ and the std.
  * __PYTHON__: started
  * __UML__: started
  * __GRAPH__: generate graphic view of component and deployment

### GLOBAL
| GÉNÉRATEUR | TYPE | STRUCTURE | INTERFACE | DÉPLOIEMENT | COMPOSANT | LINK | COMPILATION | RUN |
|------------|------|-----------|-----------|-------------|-----------|------|-------------|-----|
| C++        | OK   | OK        | OK        | OK          | OK        | OK   | OK          | OK  |


### TYPE
| GÉNÉRATEUR | TYPE | Function | Pointer | array | default | array TO_STR | pointer TO_STR | STR_TO_pointer | STR_TO_SP        |
|------------|------|----------|---------|-------|---------|--------------|----------------|----------------|------------------|
| C++        | OK   | OK       | OK      | OK    | OK      | OK           | OK             | OK             | OK               |


### STRUCTURE
| GÉNÉRATEUR   | STRUCT | get | set | constucteur | TO_STR | FROM_STR | default | PARENT | SHELL |
|--------------|--------|-----|-----|-------------|--------|----------|---------|--------|-------|
| C++        - | OK     | OK  | OK  | OK          | OK     | OK       | OK      | OK     | TD    |


### ERROR
| GÉNÉRATEUR | get | set | constucteur | TO_STR | FROM_STR | DEFAULT | PARENT |
|------------|-----|-----|-------------|--------|----------|---------|--------|
| C++        | OK  | OK  | OK          | OK     | OK       | TODO    | OK     |


### INTERFACE
| GÉNÉRATEUR | INTERFACE | COMPOSANT ACCÈS | FUNCTION | DATA | get | set | default | SHELL | FAKE | CALLER |
|------------|-----------|-----------------|----------|------|-----|-----|---------|-------|------|--------|
| C++        | OK        | OK              | OK       | OK   | OK  | OK  | OK      | OK    | OK   | OK     |


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


# Graphics
In order to help, visualisation of a deployment you can use graphical render.

## UML
You need to install PLANUML for rendering:
![Structs](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/Structs.png)
![Interfaces](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/Interfaces.png)
![Components](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/Components.png)
![Deployment](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/Deployments.png)

## GRAPH
You need to install GRAPHVIZ for rendering:
![1](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/D1.d.png)
![2](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/D2.d.png) 
![3](http://gitlab.marger.it:10443/ruhtra/compo/raw/master/doc/D3.d.png)


