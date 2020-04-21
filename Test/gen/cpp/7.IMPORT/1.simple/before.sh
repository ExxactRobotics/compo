export PATH=${PATH}:~/compo
export COMPOME_PATH=$(realpath "../../..")
export COMPOME_MODEL_PATH=$(echo $(pwd)/M_*.yaml | sed "s/.yaml /_d\/:/g;s/.yaml/_d/g")

echo $COMPOME_MODEL_PATH

function generate {
    cp ${1} ${1:0:-5}_d
    cp T_${1:2:-5}.list ${1:0:-5}_d/target.list
    cp .compoMe.py ${1:0:-5}_d/.compoMe.py
    cd ${1:0:-5}_d
    compome generate -f $1
    cd ..
}


function compile {
    cp CMakeLists_lib.txt ${1:0:-5}_d/CMakeLists.txt
    cd ${1:0:-5}_d
    cmake .
    make
    cd ..
}


for yamlfile in ./M_*.yaml ;
do
    mkdir ${yamlfile:0:-5}_d -p
done

generate M_empty.yaml
generate M_types.yaml
generate M_structs.yaml
generate M_interfaces.yaml
generate M_components.yaml
generate M_links.yaml
generate M_deploiments.yaml

compile M_empty.yaml
compile M_types.yaml
compile M_structs.yaml
compile M_interfaces.yaml
compile M_components.yaml
compile M_links.yaml
compile M_deploiments.yaml

