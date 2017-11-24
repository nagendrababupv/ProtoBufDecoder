if [[ $# < 1 ]]
then
	echo "Please provide the class Name what to decode"
	echo "CreateDecoder.sh <className>"
	echo "Example:: CreateDecoder.sh DNDResponse"
	exit
fi

CPP_OUT=./inc
SOURCE=./src
echo 
echo "Generating source code ..."
protoc  --cpp_out $CPP_OUT *.proto

if [ $? != '0' ]
then
        echo "Failed to generate code please check the error message printed."
        exit 1
fi

echo 
echo " -->Successfully geneerated Protocol buffer source code!"
echo " -->Please check directory: $CPP_OUT for source code files."
echo " NOTE: If you are adding or changing an existing proto file"
echo " please make sure that its compiling successfully, this script"
echo " will suppress any error messages from protoc."
echo 
echo "Generating library..."
cd $CPP_OUT
make
if [ $? -ne 0 ]
then
        echo " -->Failed to generate lib"
        exit 1;
fi
echo "Successfully generated lib!"

cd ../
class=$1;
MaxLengthOfPacket=20000
#################Creating Define file ###########################
echo "#define className $class" > $CPP_OUT/Defines.h
echo "#define MaxLenPkt $MaxLengthOfPacket" >> $CPP_OUT/Defines.h
#################################################################
cd $SOURCE
#################Creating Header file ###########################
HEADER=Headers.h
echo "#ifndef __HEADERS__" > $HEADER
echo "#define __HEADERS__" >> $HEADER
for file in ../$CPP_OUT/*.h
do
   echo "#include <$file>" >> $HEADER
done
echo "#endif" >> $HEADER
#################################################################
make
